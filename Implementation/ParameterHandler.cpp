/*
 * ParameterHandler.cpp
 *
 *  Created on: 25.11.2016
 *      Author: willy
 */


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "vname.h"
#include "debug.h"
#include "Warning.h"

#include "ParameterHandler.h"
#include "Operators.h"
#include <iterator>
#include <string.h>

using namespace std;

int getoptCount = 0;


#ifndef PARAM
#define PARAM(x) {          \
		string name = #x;	\
    add_parameter(name, x); \
}
#endif

#ifndef INITPARAM
#define INITPARAM(x,use) {          \
		string name = #x;	\
    add_parameter(name, x); \
    usage[name] = use;		\
}
#endif

string ParameterHandler::lineLength(string s, const unsigned int l, const unsigned int maxS){
    std::string tmp;
    std::stringstream ssin(s);
    std::vector<std::string> wrds;
    while (ssin >> tmp)
    {
        wrds.push_back(tmp);
    }


    unsigned int whitespaceSize = 1;

    unsigned int ind = 0;

    string par = wrds[0];
    string ret = par;

	for(unsigned int j = 0; j < maxS-par.size(); j++){
		ret += " ";
	}

    unsigned int curr_length = maxS;

	for(unsigned int i = 1; i < wrds.size(); i++){
		// adding the next words leads to stepping over the border
		// +2 because of "\n"
		if(curr_length + wrds[i].size() + whitespaceSize> l){
			ret += "\n";
			for(unsigned int j = 0; j < maxS; j++){
				ret += " ";
			}
			curr_length = maxS;
		}
		ret += " " + wrds[i];
		curr_length += wrds[i].size() + whitespaceSize;
	}


//	unsigned int times = floor(s.size()/l);
//
//	for(unsigned int i = 1; i <= times; i++){
//		s.insert(l*i,"\n\t\t");
//	}
//
//	return s;

	return ret;
}

void ParameterHandler::print_usage() {
	/*! \brief Prints the usage of the program.
	 *
	 * The map<string,string> usage holds the name and its description for each parameter.
	 */

    cout << "Usage:\n";
    cout << "Online-algorithm to download RNA-seqdata.\n";
    for(unsigned int i = 0; i < 80; i++){
        cout << "-";
    }
    cout << "\n";


    map<string,string>::iterator i;
    unsigned int maxParLength = 0;
    for(i = usage.begin(); i != usage.end(); i++) {
    	if(i->first.size() > maxParLength) maxParLength = i->first.size();
    }

    // for "--" and ":"
    maxParLength += 3;

    for(i = usage.begin(); i != usage.end(); i++) {
    	string out = "--" + i->first + ": " + i->second;
    	cout << lineLength(out,80,maxParLength);
    	cout << "\n" << endl;
    }
}

ParameterHandler::ParameterHandler() {
	/*! \brief All parameters are initialized with default-values. To change these values call
	 * readArguments().
	 */

	param = this;
	//"/home/willy/Bachelorarbeit/STAR-2.5.1b/source/"
    pathToSTAR 			= "default";
    	INITPARAM(pathToSTAR,"specifies the path to the executable of STAR, the alignment-program.");

//	"/home/willy/workspace/UnitTests/ParameterHandler/script/"
	pathToRuns 			= "default";
    	INITPARAM(pathToRuns, "specifies the path to Runlist.txt.");

//	readFilesIn 		= "default";
//    	INITPARAM(readFilesIn, "specifies the path to the folder in which the ");

//    	"/home/willy/Bachelorarbeit/Manager/genome/"
	genomeDir 			= "default";
    	INITPARAM(genomeDir,"specifies the path to the genome.");

    outFileNamePrefix 	= "default";
    	INITPARAM(outFileNamePrefix, "specifies the path in which all output of VARUS should be stored.");

    runThreadN = 4;
    	INITPARAM(runThreadN, "Number of threads to run STAR with. Read STAR-manual for more information.");

    blockSize = 5000;		// <---- 5000 default
    	INITPARAM(blockSize, "the number of bases one block will have. "
    			"This is done in order to be able"
    			" to compare the coverage of larger chromosomes with smaller ones, since "
    			"larger chromosomes will naturally have more reads mapped to them than smaller ones.");

    batchSize = 100;
    	INITPARAM(batchSize, "the number of reads to be downloaded at once.");

	pseudoCount = 1;
    	INITPARAM(pseudoCount, "adds a pseudocount to all possible observations. Only relevant for "
    			"estimators 1, 2.");

//    coverage = 10;
//    	PARAM(coverage);
//    zValue = 20;
//    	PARAM(zValue);
    lambda = 10.0;
    	INITPARAM(lambda, "parameter for estimator 2.");

//    logScore = 1;	// 1 == logScore, 0 == minScore
//    	PARAM(logScore);
    createDice = 0;		// 1 => creating dice, 0 => other options
    	INITPARAM(createDice, "if set to 1 dice will be created from real runs."
    			"Only needed for testing/simulation-purposes.");

	simulation = 1;		// 1 => running simulation, 0 => real downloadprogramm
    	INITPARAM(simulation, "if set to 1, the program will simulate downloads.");

	estimator = 1;	// 1 == simple, 2 == advanced, 3 == DM, else naive
    	INITPARAM(estimator, "1 == simple, 2 == advanced, 3 == dirichlet mixture, 4 == cluster estimator, else downloads will "
    			"be done choosing the runs randomly. Note that if you choose to download randomly, you "
    			"should specify maxBatches in order to let the program end at some point.");

//	dieList = 1;	// 1== uses "Dielist.txt", 0 == uses "Runlist.txt
//    	INITPARAM(dieList, "1== uses \"Dielist.txt\", 0 == uses \"Runlist.txt\"");

    lessInfo = 0; 	// 1 == Toy prints less info
    	INITPARAM(lessInfo, "if set to 1, Toy prints less info. Only Relevant for simulation.");

    pathToDice 	= "/home/willy/Bachelorarbeit/Manager/test138/";
    	INITPARAM(pathToDice, "specifies the path to the dice. Dice are saved in csv-format.");

    cost = 100000000000;
    	INITPARAM(cost, "sets the cost for downloading one read.");

    components = 1;
    	INITPARAM(components, "sets the number of components of the dirichlet mixture or the cluster estimator. "
    			"Only relevant for estimators 3 and 4.");

    numOfBlocks = 1;
    	INITPARAM(numOfBlocks, "sets the number of blocks into which the genome should be divided."
    			"Reading it automatically DOES NOT WORK YET! You must specify the correct number of blocks.");

    trainingsIterations = 1;
    	INITPARAM(trainingsIterations, "the number of iterations the dirichlet mixture or cluster estimator will be "
    			"trained in each step. Only relevant for estimators 3 and 4.");

    loadAllOnce = 0;
    	INITPARAM(loadAllOnce, "if set to 1, a single batch from each run will be downloaded once, before"
    			" the estimation process starts. Useful for the expensive estimators 3 and 4."
    			);

	verbosityDebug = 0;
		INITPARAM(verbosityDebug, "sets the debug-verbosity-level. There are 4 verbosity-levels. Higher values mean more output.");
//		verbosity_out_level = verbosityDebug;

	newtonIterations = 10;
		INITPARAM(newtonIterations, "number of times the newtons method is done to find the maximum-likelihood"
				" for the alpha-sum. Only relevant for estimator 3.");

	newtonPrecision = 0.001;
		INITPARAM(newtonPrecision, "threshold at which the newtons-method will aboard, and return the value."
				" Only relevant for estimator 3.");

	readParametersFromFile = 0;
		INITPARAM(readParametersFromFile, "if set to 1, the program will look for a file specified with "
				"pathToParameters and interpret its content as command-line arguments. "
				"These parameters will then be used to run the program. Note: additional parameters"
				" passed with the command line will overwrite the parameters read from the parameters-file.");
			readAllready = false;

	pathToParameters = "";
		INITPARAM(pathToParameters, "specifies the path and name to the parameters-file that should be read in and written to.");

	exportParametersToFile = 0;
		INITPARAM(exportParametersToFile, "if set to 1 the parameters used for this execution of the program"
				" will be exported into a parametersfile");

	exportObservationsToFile = 0;
		INITPARAM(exportObservationsToFile, "if set to 1 the program will output the observations in all"
				" runs in all steps into CSV-files. NOTE: Using this option can lead to performance-issues.");

	deleteLater = 0;
		INITPARAM(deleteLater, "if set to 1, the fasta-files and alignment-files will be deleted after"
				" they are used to identify the next run to be downloaded from. If you want to use the "
				"reads for your genome-annotation you should not use this option.");

	maxBatches = 0;
		INITPARAM(maxBatches, "if  maxBatches > 0, the program will exit as soon as it loaded maxBatches batches.");

	randomSeed = -1;
		INITPARAM(randomSeed, "if randomSeed > 0, the program will have deterministic results. Else the "
				"seed will be set according to the current time");

	profitCondition = 1;
		INITPARAM(profitCondition, "if profitConditon == 1, the program will exit if the"
				" expected profit falls below 0. Note that the expected profit can lead to the program downloading"
				" for a very long time, since some of the estimators tend to be very optimistic "
				"if the parameters are not set adequately.");

	ignoreReadNum = 0;
		INITPARAM(ignoreReadNum, "Only important for simulation: if ignoreReadNum == 1, it will be ignored in case of a simulation "
				"if a run has no reads left. Otherwise the run is not an option to download from after the maximum number of reads"
				" is downloaded from this run.")

	simpleDM = 0;
		INITPARAM(simpleDM, "refers to estimator 3. With this estimation procedure the calculation times are a bit better "
				"than with the normal dirichlet mixture. However the estimation is not that accurate.");

//	kMeansIterations = 10;
//		INITPARAM(kMeansIterations, "only relevant for estimator 4: Number of iterations for "
//				"the k-means-cluster-algorithm.");

	exportNewtons = 0;
		INITPARAM(exportNewtons, "exports the steps of the newtons method. Deprecated since it is very expensive."
				" Only relevant for estimator 3.");


//	param.reset(this);
}
ParameterHandler::~ParameterHandler() {
	cerr << "parameterHandler deleted" << endl;
}

void ParameterHandler::readArguments(int argc, char *argv[]) {
	/*! \brief Reads the command line arguments.
	 */

    const char* const short_opts = "h";
    const option long_opts[] = {
    		{"batchSize", 1, nullptr, 'b'},
			{"blockSize", 1, nullptr, 'B'},
			{"components", 1, nullptr, 'c'},
			{"cost", 1, nullptr, 'C'},
			{"createDice", 1, nullptr, 'D'},
//			{"dieList", 1, nullptr, 'L'},
			{"estimator", 1, nullptr, 'e'},
			{"genomeDir", 1, nullptr, 'g'},
			{"lambda", 1, nullptr, 'l'},
			{"lessInfo", 1, nullptr, 'I'},
			{"loadAllOnce", 1, nullptr, 'A'},
			{"numOfBlocks", 1, nullptr, 'O'},
			{"outFileNamePrefix", 1, nullptr, 'F'},
			{"pathToDice", 1, nullptr, 'T'},
			{"pathToRuns", 1, nullptr, 'R'},
			{"pathToSTAR", 1, nullptr, 'S'},
//			{"readFilesIn", 1, nullptr, 'f'},
            {"pseudoCount", 1, nullptr, 'p'},
			{"runThreadN", 1, nullptr, 'N'},
			{"simulation", 1, nullptr, 's'},
			{"trainingsIterations", 1, nullptr, 't'},
			{"verbosityDebug", 1, nullptr, 'v'},
			{"newtonIterations", 1, nullptr, 'i'},
			{"newtonPrecision", 1, nullptr, 'P'},
			{"readParametersFromFile", 1, nullptr, 'q'},
			{"pathToParameters", 1, nullptr, 'Q'},
			{"exportParametersToFile", 1, nullptr, 'Z'},
			{"exportObservationsToFile", 1, nullptr, 'z'},
			{"deleteLater", 1, nullptr, 'd'},
			{"maxBatches", 1, nullptr, 'm'},
			{"randomSeed", 1, nullptr, 'a'},
			{"profitCondition", 1, nullptr, 'E'},
			{"ignoreReadNum", 1, nullptr, 'G'},
			{"simpleDM", 1, nullptr, 'H'},
//			{"kMeansIterations", 1, nullptr, 'J'},
			{"exportNewtons", 1, nullptr, 'j'},
            {"help", 0, nullptr, 'h'},
            {nullptr, 0, nullptr, 0}
    };

	optind = 0;

    while (true)
    {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

        if (-1 == opt)
            break;

        switch (opt)
        {
        case 'b':
            batchSize = std::stoi(optarg);
            	PARAM(batchSize);
            break;

        case 'B':
        	blockSize = std::stoi(optarg);
        		PARAM(blockSize);
            break;

        case 'c':
        	components = std::stoi(optarg);
        		PARAM(components);
            break;

        case 'C':
        	cost = std::stof(optarg);
        		PARAM(cost);
            break;

        case 'D':
            createDice = std::stoi(optarg);
            	PARAM(createDice);
            break;

//        case 'L':
//            dieList = std::stoi(optarg);
//            	PARAM(dieList);
//            break;

        case 'e':
            estimator = std::stoi(optarg);
            	PARAM(estimator);
            break;

        case 'g':
            genomeDir = std::string(optarg);
            	PARAM(genomeDir);
            break;

        case 'l':
            lambda = std::stof(optarg);
            	PARAM(lambda);
            break;

        case 'I':
            lessInfo = std::stoi(optarg);
            	PARAM(lessInfo);
            break;

        case 'A':
            loadAllOnce = std::stoi(optarg);
            	PARAM(loadAllOnce);
            break;

        case 'O':
            numOfBlocks = std::stoi(optarg);
            	PARAM(numOfBlocks);
            break;

        case 'F':
            outFileNamePrefix = std::string(optarg);
            	PARAM(outFileNamePrefix);
            break;

        case 'T':
            pathToDice = std::string(optarg);
            	PARAM(pathToDice);
            break;

        case 'R':
            pathToRuns = std::string(optarg);
            	PARAM(pathToRuns);
            break;

        case 'S':
        	pathToSTAR = std::string(optarg);
            	PARAM(pathToSTAR);
            break;

//        case 'f':
//            readFilesIn = std::string(optarg);
//            	PARAM(readFilesIn);
//            break;

        case 'p':
            pseudoCount = std::stof(optarg);
            	PARAM(pseudoCount);
            break;

        case 'N':
            runThreadN = std::stoi(optarg);
            	PARAM(runThreadN);
            break;

        case 's':
            simulation = std::stoi(optarg);
            	PARAM(simulation);
            break;

        case 't':
            trainingsIterations = std::stoi(optarg);
            	PARAM(trainingsIterations);
            break;

        case 'v':
            verbosityDebug = std::stoi(optarg);
            	PARAM(verbosityDebug);
//            	verbosity_out_level = verbosityDebug;
            break;

        case 'i':
            newtonIterations = std::stoi(optarg);
            	PARAM(newtonIterations);
            break;

        case 'P':
        	newtonPrecision = std::stof(optarg);
            	PARAM(newtonPrecision);
            break;

        case 'q':
            readParametersFromFile = std::stoi(optarg);
            	PARAM(readParametersFromFile);
            break;

        case 'Q':
            pathToParameters = std::string(optarg);
            	PARAM(pathToParameters);
            break;

        case 'Z':
            exportParametersToFile = std::stoi(optarg);
            	PARAM(exportParametersToFile);
            break;

        case 'z':
            exportObservationsToFile = std::stoi(optarg);
            	PARAM(exportObservationsToFile);
            break;

        case 'd':
            deleteLater = std::stoi(optarg);
            	PARAM(deleteLater);
            break;

        case 'm':
            maxBatches = std::stoi(optarg);
            	PARAM(maxBatches);
            break;

        case 'a':
            randomSeed = std::stoi(optarg);
            	PARAM(randomSeed);
            break;

        case 'E':
            profitCondition = std::stoi(optarg);
            	PARAM(profitCondition);
            break;

        case 'G':
            ignoreReadNum = std::stoi(optarg);
            	PARAM(ignoreReadNum);
            break;

        case 'H':
            simpleDM = std::stoi(optarg);
            	PARAM(simpleDM);
            break;

//        case 'J':
//            kMeansIterations = std::stoi(optarg);
//            	PARAM(kMeansIterations);
//            break;

        case 'j':
        	exportNewtons = std::stoi(optarg);
            	PARAM(exportNewtons);
            break;


        case 'h': // -h or --help
			print_usage();
			exit(-1);
        	break;
        case '?': // Unrecognized option
        	print_usage();
        	exit(-1);
        	break;
        default:
            print_usage();
            break;
        }
    }


    /**
     *  if the user selects the simulation, no real runs will be used
     */

//    if(simulation == 0) {
//    	dieList = 0;
//    }

    /**
     *  If the user selected a path readParameters from file, we have to call
     *  read_parameters_from_file(), which in turn will call readArguments.
     *  So we need to set a flag in order to not get stuck in a loop.
     */

    if(readParametersFromFile != 0)
    {
		if(readAllready == false)
		{
			argc_saved = argc;
			argv_saved = new char*[argc_saved];

			for(unsigned int i = 0; i < argc; i++) {
				argv_saved[i] = argv[i];
			}


			readAllready = true;
			read_parameters_from_file(pathToParameters);
		}
    }

}

std::ostream & ParameterHandler::printParameters(std::ostream& os) {
	/*! \brief The parameters are appended to the std::ostream os.
	 *
	 * The format is in such a way, that a call of read_parameters_from_file()
	 *  with an output-file created with this method can be read in again.
	 * For example: Let lambda=1.2
	 *
	 * outFile:
	 * .
	 * .
	 * .
	 * --lambda 1.2
	 * .
	 * .
	 * .
	 */

	map<string,string>::iterator it;
	for(it = parameters.begin(); it != parameters.end(); it++) {
		os << "--" << it->first << " " << it->second << "\n";
	}
	return os;
}

void ParameterHandler::export_parameters() {
	/*! \brief The parameters are exported into a file.
	 *
	 * The parameters can be read in from this file with read_parameters_from_file().
	 */

	if(exportParametersToFile != 0)
	{
		DEBUG(0,"Exporting parameters to " << pathToParameters);

		ofstream f;
//		f.open(pathToParameters);

		f.open(pathToParameters, ios::out);
		if(!f) { DEBUG(0,"Cant export to file " << pathToParameters);}


		ostringstream ss;

		printParameters(ss);
		f << ss.str();
//		cout << ss.str() << endl;

		f.close();
	}
}

template<typename K>
void ParameterHandler::add_parameter(string name, K a) {
	/*! \brief This function is called when a new parameter should be added.
	 *
	 * With this function and the map parameters it is possible to
	 * import and export the values of the parameters easily.
	 */

    stringstream ss;
    ss << a;
    string value = ss.str();

    parameters[name] = value;
}

void ParameterHandler::read_parameters_from_file(string path) {
	/*! \brief The parameters are read from a file.
	 *
	 * The parameters can be written to a file with exportParameters().
	 */

//	DEBUG(1,"reading from " << path);
	ifstream filestr;
	filestr.open (path);
	if (!filestr.is_open())
	{
		WARN("Unable to open parameters-file " << path);
		if(path.empty()) WARN("path is empty!");
	}


	std::vector<std::string> wrds;
	wrds.push_back("./RNAM");

	string line;
	while (getline (filestr,line))
	{
		if(!line.empty() && line.size() > 1)
		{
			if(line[0] == '-' && line[1] == '-') {
				std::string tmp;
				std::stringstream ssin(line);

				while (ssin >> tmp)
				{
					wrds.push_back(tmp);
				}
			} else {
				WARN("unable to read parameter \"" << line << "\" in parameter-file!");
			}
		}
	}
	filestr.close();

	int argc_test = wrds.size();
//	cerr << __FUNCTION__ << argc_test << endl;


	char **argv_test = new char*[argc_test];
	for(unsigned int i = 0; i < wrds.size(); i++) {
		char *p = new char[wrds[i].size() + 1];
		strncpy(p, wrds[i].c_str(), wrds[i].size());
		p[wrds[i].size()] = '\0';
		argv_test[i] = p;
	}

	/**
	 * readArguments() is called twice, because in the first call the parameters form
	 * the file are read, in the second call the parameters from the command-line are added.
	 */

	readArguments(argc_test,argv_test);

//	cerr << "argc_saved " << argc_saved << endl;
	readArguments(argc_saved,argv_saved);

//	cerr << "yo" << endl;
}
