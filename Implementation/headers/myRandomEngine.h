/*
 * myRandomEngine.h
 *
 *  Created on: 06.12.2016
 *      Author: willy
 */

#ifndef MYRANDOMENGINE_H_
#define MYRANDOMENGINE_H_

#include <algorithm>    // std::random_shuffle
#include <cstdlib>
#include <ctime>        // std::time
#include <random>

#include "ParameterHandler.h"
#include "TypeConventions.h"

class myRandomEngine {
public:
//	unsigned int randomSeed;

//	std::random_device rd;
	std::mt19937 gen;

	ParameterHandler *param;

	myRandomEngine();
	myRandomEngine(ParameterHandler *p);
	virtual ~myRandomEngine();

	template<typename V>
	V select_randomly(std::vector<V> &vec){

		return vec[select_randomly(vec.size()-1)];
	}

	template<typename V>
	void shuffle(std::vector<V> &vec){
//		std::random_shuffle(vec.begin(), vec.end(), std::default_random_engine(0));
		std::shuffle(vec.begin(), vec.end(), gen);
	}

//	void shuffle(std::vector<int> &vec);

	unsigned int select_randomly(unsigned int max);
	unsigned int select_randomly_p(std::vector<double> &vec);
	void seed(unsigned int t);

//	U32 select_randomly(UDmap::iterator begin, UDmap::iterator end);
};

#endif /* MYRANDOMENGINE_H_ */