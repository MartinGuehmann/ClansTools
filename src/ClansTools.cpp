#include "ClansTools.h"

#include "SparseDistanceMatrix.h"
#include "NodePositions.h"
#include "getopt_pp/getopt_pp.h"
#include <iostream>

void printUsage()
{
	std::cerr << "BLAST2Dinstance creates a distance matrix for RapidNJ in a relaxed phylip format. This means it uses more then 10 characters for the sequence names." << std::endl << std::endl;
	std::cerr << "USAGE: BLAST2Dinstance [OPTIONS]" << std::endl;
	std::cerr << "OPTIONS:" << std::endl;
	std::cerr << "  -h, --help                Display this help message and exit. Ignores all other options." << std::endl;
	std::cerr << "  -s, --sequence-file ARG   The fasta file from that BLAST generated the high scoring pairs. Ignored" << std::endl;
	std::cerr << "                            if --clans-file is used." << std::endl;
	std::cerr << "  -i, --input-file ARG      The file with the e-values of the high scoring pairs from an all to all comparison" << std::endl;
	std::cerr << "                            BLAST search of the input sequences. This file is a tab separated table" << std::endl;
	std::cerr << "                            with three columns. The first columns contains the query sequence ID." << std::endl;
	std::cerr << "                            The second column columns contains the subject sequence ID. And the" << std::endl;
	std::cerr << "                            third columns contains the e-value. Ignored if --clans-file is used." << std::endl;
	std::cerr << "  -c, --clans-file ARG      The clans file that contains the positions from which the distanced are to be calulated." << std::endl;
	std::cerr << "                            It is also used to extract the sequence names. If used --sequence-file and --input-file are" << std::endl;
	std::cerr << "                            ignored." << std::endl;
	std::cerr << "  -o, --output-file ARG     The output file for the distance matrix generated from the e-values in" << std::endl;
	std::cerr << "                            in a relaxed phylip format, that means the names can be longer then 10 characters." << std::endl;
	std::cerr << "  -m, --make-half-matrix    Generate only the lower triangular matrix. This cannot be used with rapidNJ." << std::endl;
	std::cerr << "  -u, --use-short-names     Generate the distance matrix with short names, that means it truncates the name at" << std::endl;
	std::cerr << "                            the first space, otherwise it will replace spaces, colons and slashes by" << std::endl;
	std::cerr << "                            by underscore and deletes semicolons,commas, quotation marks, brackets, and parentheses." << std::endl;
	std::cerr << "  -q, --square-distances    Square the distances in the matrix." << std::endl;
	exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[])
{
	using namespace GetOpt;
	GetOpt_pp opts(argc, argv);

	if(argc == 1 || opts >> OptionPresent('h',"help"))
	{
		printUsage();
	}

	std::string    clansFileName;
	std::string    inputFileName;
	std::string   outputFileName;
	std::string sequenceFileName;
	bool          makeHalfMatrix  = false;
	bool          useShortNames   = false;
	bool          squareDistances = false;

	opts >> Option       ('c',       "clans-file",    clansFileName, "");
	opts >> Option       ('i',       "input-file",    inputFileName, "");
	opts >> Option       ('o',      "output-file",   outputFileName, "");
	opts >> Option       ('s',    "sequence-file", sequenceFileName, "");
	opts >> OptionPresent('m', "make-half-matrix", makeHalfMatrix);
	opts >> OptionPresent('u',  "use-short-names", useShortNames);
	opts >> OptionPresent('q', "square-distances", squareDistances);

	if(outputFileName.size() == 0)
	{
		std::cerr << "Missing output file. Exiting." << std::endl;
		return EXIT_FAILURE;
	}

	bool    hasClansFile = (   clansFileName.size() > 0);
	bool    hasInputFile = (   inputFileName.size() > 0);
	bool hasSequenceFile = (sequenceFileName.size() > 0);

	if(hasClansFile)
	{
		std::cerr << "Generating distances from clans file." << std::endl;
		if(hasInputFile)
		{
			std::cerr << "Blast input file is ignored." << std::endl;
		}

		if(hasSequenceFile)
		{
			std::cerr << "Sequence file is ignored." << std::endl;
		}

		NodePositions nodePositions(clansFileName);
		nodePositions.saveMatrix(outputFileName, makeHalfMatrix, useShortNames, squareDistances);
	}
	else
	{
		if(!hasInputFile)
		{
			std::cerr << "Missing blast input file. No clans file, either. Exiting." << std::endl;
			return EXIT_FAILURE;
		}

		if(!hasSequenceFile)
		{
			std::cerr << "Missing sequence file. Exiting. No clans file, either." << std::endl;
			return EXIT_FAILURE;
		}

		SparseDistanceMatrix distanceMatrix(inputFileName, sequenceFileName);
		distanceMatrix.saveMatrix(outputFileName, makeHalfMatrix, useShortNames, squareDistances);
	}

	return EXIT_SUCCESS;
}


