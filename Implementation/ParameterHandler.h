/*
 * ParameterHandler.h
 *
 *  Created on: 25.11.2016
 *      Author: willy
 */

#ifndef PARAMETERHANDLER_H_
#define PARAMETERHANDLER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include "TypeConventions.h"
#include <memory>


/*! \brief This class holds all the data, that is read in as command-line arguments.
 *
 * A raw pointer is passed to all other instances, that need to have access to the input data.
 * A std::unique_ptr is created in main.cpp that is responsible for this instance.
 */

class ParameterHandler
{


public:
////     paths, commandline
    std::string pathToSTAR;
    std::string pathToRuns;
//    std::string readFilesIn;
    std::string genomeDir;
    std::string outFileNamePrefix;
    uI runThreadN;
    uI blockSize;
	uI batchSize;
	double pseudoCount;
	double lambda;
	int logScore;
	double cost;
	int createDice;
	int simulation;
	int estimator;
//	int dieList;
	int lessInfo = 1;
	uI components;
	uI numOfBlocks;
	uI trainingsIterations;
	int loadAllOnce;
	int verbosity;
	int verbosityDebug;
	int randomSeed;
	int profitCondition;


	uI newtonIterations;
	double newtonPrecision;

	int exportObservationsToFile;

	int readParametersFromFile;
	std::string pathToParameters;

//		bool readAllready;
	int exportParametersToFile;

	std::string pathToDice;
	int deleteLater;

	unsigned int maxBatches;

	int ignoreReadNum;

	int simpleDM;

//	int kMeansIterations;

	int exportNewtons;


//	std::shared_ptr<Parameters> parameters;


	bool readAllready;

	// for reading parameters from file and afterwards add commandline arguments
	int argc_saved;

	char **argv_saved;



	std::map <std::string, std::string> parameters;
	std::map<std::string, std::string> usage;

	void read_parameters_from_file(std::string path);	// uses parameters stored in the file

	void export_parameters();	// exports the parameters into a file, so that they can later be used

    void readArguments(int argc, char *argv[]);	// reads the arguments from the commandline
    void readInputRuns();	// reads in the list of runs that should be downloaded from
    std::ostream & printParameters(std::ostream& os);	// prints the parameters

	void print_usage();
	std::string lineLength(const std::string s, const unsigned int l, const unsigned int maxS);


	template<typename K>
	void add_parameter(std::string name, K a);

	ParameterHandler();
	~ParameterHandler();

private:
	ParameterHandler *param;
};


#endif /* PARAMETERHANDLER_H_ */


