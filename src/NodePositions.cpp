#include "NodePositions.h"

#include <fstream>
#include <iostream>
#include <cmath>
#include <limits>

NodePositions::NodePositions(std::string & clansFileName)
:
    m_allSequences(clansFileName)
{
	std::ifstream fin(clansFileName);
	if(!fin.good())
	{
		std::cerr << "The clans file " << clansFileName << " does not exist. Existing." << std::endl;
		exit(EXIT_FAILURE);
	}

	size_t numSeqs = m_allSequences.size();

	m_positions = new float * [s_dimensions];

	for(uint32_t i = 0; i < s_dimensions; i++)
	{
		m_positions[i] = new float[numSeqs];
	}

	// Skip until we get to the positions
	std::string line;
	while(fin.good())
	{
		std::getline(fin, line);

		if(line.find("<pos>") != std::string::npos)
		{
			break;
		}
	}

	// Load the positions
	uint32_t nodeID;
	while(fin.good())
	{
		if(line.find("</pos>") != std::string::npos)
		{
			break;
		}

		fin >> nodeID;

		if(nodeID >= numSeqs)
		{
			std::cerr << "Num Seqs: " << numSeqs << " NodeID " << nodeID << std::endl;
			std::cerr << "The clans file contains a position with a higher node ID than the number of given sequences. Existing." << std::endl;
			exit(EXIT_FAILURE);
		}

		for(uint32_t i = 0; i < s_dimensions; i++)
		{
			fin >> m_positions[i][nodeID];
		}
	}

	m_allSequences.print();
	print();
}

void NodePositions::saveMatrix(std::string & outputFileName, bool makeHalfMatrix, bool useSortNames) const
{
	std::ofstream fout(outputFileName);
	fout << m_allSequences.size() << std::endl;

	size_t limit = m_allSequences.size();

	for(size_t i = 0; i < m_allSequences.size(); i++)
	{
		if(useSortNames)
			fout << m_allSequences.getShortSeqName(i);
		else
			fout << m_allSequences.getCleanSeqName(i);

		if(makeHalfMatrix) limit = i;

		for(size_t j = 0; j < limit; j++)
		{
			if(i == j)
			{
				fout << " " << 0;
			}
			else
			{
				float distance = 0.0;

				for(uint32_t k = 0; k < s_dimensions; k++)
				{
					distance += std::pow(m_positions[k][i] - m_positions[k][j], 2.0f);
				}

				fout << " " << std::sqrt(distance);
			}
		}

		fout << std::endl;
	}
}

void NodePositions::print() const
{
	std::cerr << m_allSequences.size() << " positions loaded" <<  std::endl;
}
