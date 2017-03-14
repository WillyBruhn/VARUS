//============================================================================
// Name        : RNAMv2.cpp
// Author      : Willy Bruhn
// Version     :
// Copyright   : Your copyright notice
// Description : RNAMv2 24.11.16
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include "Run.h"
#include "TypeConventions.h"
#include "ChromosomeInitializer.h"
#include "Alligner.h"
#include "Downloader.h"
#include "ParameterHandler.h"
#include "debug.h"
#include "Operators.h"
#include <memory>
#include "Controller.h"

using namespace std;
ParameterHandler *param;

int main(int argc, char *argv[]) {

	param = new ParameterHandler();
		param->readArguments(argc,argv);
		param->export_parameters();

	Controller *c = new Controller(param);
		c->initialize();

		if(1 == param->createDice){
			c->createDiceFromRuns();
		} else {
			c->algorithm();
		}

	return EXIT_SUCCESS;
}
