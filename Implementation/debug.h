/*
 * debug.h
 *
 *  Created on: 25.11.2016
 *      Author: willy
 */

#ifndef DEBUG_H
#define DEBUG_H
#include <iostream>
#include "ParameterHandler.h"
#include <memory>
	/*! \brief This macro is used for Debuging-purposes.
	 *
	 * A lvl can be passed alongside a string. The message is only printed
	 * if the lvl is lower or equal to a globaly set verbosity-lvl specified int param->verbosityDebug.
	 * Only Classes that have a ParameterHandler-object called param can used this macro.
	 */
extern ParameterHandler *param;
//#define DEBUG(lvl, msg) if(lvl <= verbosityDebug) {std::cerr<<__FILE__ <<';'<<__LINE__<<':'<<msg; std::cerr<<std::endl;}
#define DEBUG(lvl, msg) if(lvl <= param->verbosityDebug) {std::cerr<<__FILE__ <<':'<<__LINE__<<';'<<msg; std::cerr<<std::endl;}


//void DEBUG(int lvl,char* msg) {
//	if(lvl <= verbosityDebug) {std::cerr<<__FILE__ <<';'<<__LINE__<<':'<<msg; std::cerr<<std::endl;}
//
//}

#endif // DEBUG

