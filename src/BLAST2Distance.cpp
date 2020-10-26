#include "BLAST2Distance.h"

#include "SparseDistanceMatrix.h"
#include "getopt_pp/getopt_pp.h"
#include <iostream>

void printUsage(){
	std::cerr << "BLAST2Dinstance creates a distance matrix for RapidNJ in a relaxed phylip format. This means it uses more then 10 characters for the sequence names." << std::endl << std::endl;
	std::cerr << "USAGE: BLAST2Dinstance [OPTIONS]" << std::endl;
	std::cerr << "OPTIONS:" << std::endl;
	std::cerr << "  -h, --help                Display this help message and exit." << std::endl;
	std::cerr << "  -s, --sequence-file ARG   The fasta file from that BLAST generated the high scoring pairs." << std::endl;
	std::cerr << "  -i, --input-file ARG      The file with the e-values of the high scoring pairs from an all to all comparison" << std::endl;
	std::cerr << "                            BLAST search of the input sequences. This file is a tab separated table" << std::endl;
	std::cerr << "                            with three columns. The first columns contains the query sequence ID." << std::endl;
	std::cerr << "                            The second column columns contains the subject sequence ID. And the" << std::endl;
	std::cerr << "                            third columns contains the e-value." << std::endl;
	std::cerr << "  -o, --output-file ARG     The output file for the distance matrix generated from the e-values in" << std::endl;
	std::cerr << "                            in a relaxed phylip format, that means the names can be longer then 10 characters." << std::endl;
	std::cerr << "  -m, --make-half-matrix    Generate only the lower triangular matrix. This cannot be used with rapidNJ." << std::endl;
	exit(EXIT_SUCCESS);
}

#include <cmath>
#include <limits>

int main(int argc, char* argv[])
{
	using namespace GetOpt;
	GetOpt_pp opts(argc, argv);

	if(argc == 1 || opts >> OptionPresent('h',"help"))
	{
		printUsage();
	}

	std::string    inputFileName;
	std::string   outputFileName;
	std::string sequenceFileName;
	bool          makeHalfMatrix = false;

	opts >> Option       ('i',       "input-file",    inputFileName, "");
	opts >> Option       ('o',      "output-file",   outputFileName, "");
	opts >> Option       ('s',    "sequence-file", sequenceFileName, "");
	opts >> OptionPresent('m', "make-half-matrix", makeHalfMatrix);

	if(inputFileName.size() == 0)
	{
		std::cerr << "Missing blast input file. Exiting." << std::endl;
		return EXIT_FAILURE;
	}

	if(outputFileName.size() == 0)
	{
		std::cerr << "Missing output file. Exiting." << std::endl;
		return EXIT_FAILURE;
	}

	if(sequenceFileName.size() == 0)
	{
		std::cerr << "Missing sequence file. Exiting." << std::endl;
		return EXIT_FAILURE;
	}

	SparseDistanceMatrix distanceMatrix(inputFileName, sequenceFileName);
	distanceMatrix.saveMatrix(outputFileName, makeHalfMatrix);

	return EXIT_SUCCESS;
}


