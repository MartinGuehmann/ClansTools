#include "BLAST2Distance.h"

#include "SparseDistanceMatrix.h"
#include "getopt_pp/getopt_pp.h"
#include <iostream>

void printUsage(){
/*	cerr << "Rapid neighbour-joining. An implementation of the canonical neighbour-joining method which utilize a fast search heuristic to reduce the running time. RapidNJ can be used to reconstruct large trees using a very small amount of memory by utilizing the HDD as storage." << endl << endl;
	cerr << "USAGE: rapidnj INPUT [OPTIONS]" << endl;
	cerr << "The INPUT can be a distance matrix in phylip (.phylip) format or a multiple alignment in stockholm (.sth) or phylip format (.phylip)." << endl;*/
	std::cerr << "OPTIONS:" << std::endl;
	std::cerr << "  -h, --help                Display this help message and exit." << std::endl;
/*	cerr << "  -v, --verbose             turn on verbose output." << endl;
	cerr << "  -i, --input-format ARG    Specifies the type of input. pd = distance" << endl;
	cerr << "                            matrix in phylip format, sth = multiple alignment in (single line) stockholm format." << endl;
	cerr << "                            fa = multiple alignment in (single line) FASTA format." << endl;
	cerr << "  -o, --output-format ARG   Specifies the type of output. t = phylogenetic tree in newick format" << endl;
	cerr << "                            (default), m = distance matrix." << endl;
	cerr << "  -a, --evolution-model ARG Specifies which sequence evolution method to use when computing" << endl;
	cerr << "                            distance estimates from multiple alignments. jc = juke cantor," << endl;
	cerr << "                            kim = Kimura's distance (default)." << endl;
	cerr << "  -m, --memory-size         The maximum amount of memory which rapidNJ is allowed to use (in MB)." << endl;
	cerr << "                            Default is 90% of all available memory." << endl;
	cerr << "  -k, --rapidnj-mem ARG     Force RapidNJ to use a memory efficient version of rapidNJ. The 'arg'" << endl;
	cerr << "                            specifies the percentage of a sorted distance matrix which should be" << endl;
	cerr << "                            stored in memory (arg=10 means 10%)." << endl;
	cerr << "  -d, --rapidnj-disk ARG    Force RapidNJ to use HDD caching where 'arg' is the directory used to" << endl;
	cerr << "                            store cached files." << endl;
//	cerr << "  -s, --simplenj            Use a naive implementation of the NJ method." << endl;
//	cerr << "  -f, --no-rapiddist        Disable rapid computation of distance estimates and use a naive" << endl;
//	cerr << "                            algorithm for this." << endl;
	cerr << "  -c, --cores ARG           Number of cores to use for computating distance matrices from multiple" << endl;
	cerr << "                            alignments. All available cores are used by default." << endl;
	cerr << "  -b  --bootstrap ARG       Compute bootstrap values using ARG samples. The output tree will be" << endl;
	cerr << "                            annotated with the bootstrap values." << endl;
	cerr << "  -t, --alignment-type ARG  Force the input alignment to be treated as: p = protein alignment, " << endl;
	cerr << "                            d = DNA alignment." << endl;
//	cerr << "  -g  --gpu                 Use CUDA enabled GPU to compute distance estimates." << endl;
	cerr << "  -n  --no-negative-length  Adjust for negative branch lengths." << endl;
	cerr << "  -x  --output-file ARG     Output the result to this file instead of stdout." << endl;*/
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

//	pts >> OptionPresent('v', "verbose", inFileName);
	opts >> Option('i',    "input-file",     inputFileName, "");
	opts >> Option('o',   "output-file",    outputFileName, "");
	opts >> Option('s', "sequence-file",  sequenceFileName, "");

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
	distanceMatrix.saveMatrix(outputFileName);

	return EXIT_SUCCESS;
}


