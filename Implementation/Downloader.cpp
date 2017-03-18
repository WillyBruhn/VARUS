/*
 * Downloader.cpp
 *
 *  Created on: 29.11.2016
 *      Author: willy
 */

#include "Downloader.h"
#include "debug.h"

Downloader::Downloader(ParameterHandler *p) {
	// TODO Auto-generated constructor stub
	param = p;
}

Downloader::~Downloader() {
	// TODO Auto-generated destructor stub
}

std::string Downloader::shellCommand(Run *r){
    std::string s;


    std::ostringstream n,x;
    n << r->N;
    x << r->X;

    if(r->paired == false)
    {
        s = "fastq-dump -N " + n.str() + " -X " + x.str() + " -O " + param->outFileNamePrefix + r->accesionId + "/"
         + "N" + n.str() + "X" + x.str() + "/ --fasta " + r->accesionId;
    }
    else
    {
        s = "fastq-dump -N " + n.str() + " -X " + x.str() + " -O " + param->outFileNamePrefix + r->accesionId + "/"
          + "N" + n.str() + "X" + x.str() + "/ --fasta " + r->accesionId + " --split-files";
    }
    return s;
}

void Downloader::nextBatchIndices(Run *r) {
	/*! \brief	Calculates the batch-indices N and X.
	 */

//	assert(sigmaIndex < sigma.size());
	r->N = r->sigma[r->sigmaIndex]*r->batchSize;
	r->X = r->N + r->batchSize - 1;

	if(r->X > r->numOfSpots) {
		r->X = r->numOfSpots;
	}

	r->sigmaIndex++;
}

bool Downloader::getBatch(Run *r, bool all)
{
	/*! \brief	The next batch will be downloaded according to the sigma-vector.
	 * 	The command for the download is invoked throught the shell and calls fastq-dump.
	 *
	 *	Sometimes batches are not loaded correctly. This is a problem with fastq-dump.
	 *	In this case the reads can not be alligned. This function returns "false", if the
	 *	download failed.
	 */

	if(all == false) nextBatchIndices(r);	// chooses the correct N and X
	else
	{
		r->N = 0;
		r->X = r->numOfSpots;
	}

    std::string s = shellCommand(r);

    DEBUG(1,"getBatch(" << r->accesionId << "): " << s);

    int status = system(s.c_str());

    if(0 != status)
    {
        DEBUG(0,"\nFailed to save batch :"  << r->accesionId << " -N  " << r->N << " -X " << r->X);
//        writeBadRunSection(outFileNamePrefix);

//        exit(0);
        return false;
    }

    r->timesDownloaded++;
    return true;
}
