/*
 * ChromosomInitializer.cpp
 *
 *  Created on: 28.11.2016
 *      Author: willy
 */

#include "../headers/ChromosomeInitializer.h"
#include <string>
#include "../headers/debug.h"
#include <math.h>
#include <memory>
#include <algorithm>    // std::random_shuffle
#include <cstdlib>
#include <ctime>        // std::time

using namespace std;

ChromosomeInitializer::ChromosomeInitializer(ParameterHandler *p) {
	param = p;
	ran = new myRandomEngine(p);
}

ChromosomeInitializer::~ChromosomeInitializer() {
}

void ChromosomeInitializer::readInputRuns() {
	/*! \brief Reads in the accession-ids of the Runs to download from.
	 *
	 * reads from "Runlist.txt"
	 */

	stringstream st;

	st << param->pathToRuns << "/Runlist.txt";

	const char * c = st.str().c_str();

    std::string line;
    ifstream myfile (c);

    if (!myfile.is_open())
    {
		DEBUG(0,"Unable to open Runfile:" << st.str());
		exit(-1);
    }

    while (getline (myfile,line))
    {
        if(!line.empty() && line[0] != '@')
        {
             std::string tmp;
             std::stringstream ssin(line);
             std::vector<std::string> wrds;
             while (ssin >> tmp)
             {
                 wrds.push_back(tmp);
             }
             InputRuns.push_back(wrds[0]);
        }
    }
    myfile.close();

	if(InputRuns.size() < 1) {
		DEBUG(0,"Runlist.txt is empty: " << st.str());
		exit(1);
	}
}

void ChromosomeInitializer::getChromosomeLengths() {
	/*! \brief Reads in the length of the chromosomes in a file called "chrNameLength.txt".
	 *
	 */

	if (param->genomeDir != "") {
		string s = param->genomeDir + "chrNameLength.txt";

		const char * c = s.c_str();
		string line;
		ifstream myfile(c);

		if (!myfile.is_open()) {
			DEBUG(0,"Can't open chromosomefile " << s);
		}

		while (getline(myfile, line)) {
			if (line.size() > 1) {
				// example line: FBgn0000003	299
				string tmp;
				stringstream ssin(line);
				vector<string> wrds;
				while (ssin >> tmp) {
					wrds.push_back(tmp);
				}
				string chromosomeName = wrds[0];
				string chromosomeLength = wrds[1];

				// store the chromosomelengths in the map
				// "chromosom_lengths<chromosomeName, chromosomeLength>"
				chromosomLengths[chromosomeName.c_str()] = atoll(
						chromosomeLength.c_str());
			}
		}
		return;
	}
}

void ChromosomeInitializer::create_transcript_units(UUmap &totalObservations) {

	/*! \brief divides each chromosom in blocks of length blocksize
	 * names are given as x:1,...x:(x.size/blocksize) where x is a specific chromosom
	 *
	 */

	unsigned int number_of_blocks = 0;
	SUmap::iterator it;
	for (it = chromosomLengths.begin(); it != chromosomLengths.end(); ++it) {
		number_of_blocks = ceil((double) it->second / (double)param->blockSize);

		for(unsigned int i = 0; i < number_of_blocks; i++) {
			// fill up the unused digits with 0s, for sortability
			std::ostringstream oss;
			oss << i;
			string blockName = it->first + ":" + oss.str();

			if (i < number_of_blocks -1) {
				transcriptUnitsByNames[blockName] = param->blockSize;

			} else {
				transcriptUnitsByNames[blockName] = it->second
						- param->blockSize * (number_of_blocks - 1);
			}

			// needed later to print in exact order
			translate2str[order.size()] = blockName;
			translate2int[blockName] = order.size();
			totalObservations[order.size()] = 0;

			order.push_back(order.size());
		}
	}
	return;
}

void ChromosomeInitializer::initializeRuns(std::vector<Run*> &runs) {
	/*! \brief Reads in information about the runs such as numOfSpots, accessionId from
	 * the Runlist.txt.
	 *
	 */

	string s = param->pathToRuns + "/Runlist.txt";

	const char * c = s.c_str();
	string line;
	ifstream myfile(c);

	if (!myfile.is_open()) {
		DEBUG(0,"Can't open Runlist " << s);
	}

	while (getline(myfile, line)) {
		if (!line.empty()) {
			if (line.size() > 2 && line[0] != '@') {
				string tmp;
				stringstream ssin(line);
				vector<string> wrds;
				while (ssin >> tmp) {
					wrds.push_back(tmp);
				}
				string runName = wrds[0];
				string spots   = wrds[1];
				string paired  = wrds[3];

				// transcriptUnits.size() ca 30 000 for blockSize = 5000
				DEBUG(4, "blsize:" << transcriptUnitsByNames.size());
				Run *r = new Run(runName, transcriptUnits.size(),
						atoi(spots.c_str()), param->batchSize);

//				unique_ptr<Run> r(new Run(runName, transcriptUnitsByNames.size(),
//								atoi(spots.c_str()), param->batchSize));

				if (1 == atoi(paired.c_str())) {
					r->paired = true;
				} else {
					r->paired = false;
				}

				DEBUG(4, "r.transcriptBlocks:" << r->transcriptBlocks);

				initializeSigma(r);
//				runs.push_back(std::move(r));
				runs.push_back(r);
			}
		}
	}
	if (0 == runs.size()) {
		DEBUG(0, "WARNING:No Runs found!");
	}
	return;
}

void ChromosomeInitializer::initializeSigma(Run *r) {
	/*! \brief The sigma-vector contains the order in which the batches should be downloaded.
	 *  The order is randomized so that potential biases in the order of the reads
	 *  in the run are minimalized. The second argument is the seed used for the suffler.
	 *  If set to a positive value, the seed is set, else the seed is derived randomly
	 *  according to the current time.
	 */

	// if the vector is allready initialized we need to first delete it
	if(r->sigma.size() > 0) r->sigma.clear();

//	if(0 < t){
//		ran->seed(t);
//	}

	DEBUG(3,"Max number of batches for run " << r->accesionId << " " << r->maxNumOfBatches);
	// set all values
	for (int i=0; i<r->maxNumOfBatches; i++) r->sigma.push_back(i);

	ran->shuffle(r->sigma);
}