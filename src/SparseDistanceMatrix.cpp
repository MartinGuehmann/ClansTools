#include "SparseDistanceMatrix.h"

#include <fstream>
#include <iostream>
#include <cmath>
#include <limits>

SparseDistanceMatrix::SparseDistanceMatrix(std::string & inputFileName, std::string & sequenceFileName)
:
    m_allSequences(sequenceFileName),
    m_distanceMatrix()
{
	std::ifstream fin(inputFileName);
	if(!fin.good())
	{
		std::cerr << "The sequence file " << inputFileName << " does not exist. Existing." << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string  firstSequence;
	std::string secondSequence;
	double eValue;

	while(fin.good())
	{
		fin >>  firstSequence;
		fin >> secondSequence;
		fin >> eValue;

		int32_t seqID1 = m_allSequences.getSeqID( firstSequence);
		int32_t seqID2 = m_allSequences.getSeqID(secondSequence);

		if(seqID1 == seqID2)
			continue;

		const MapKey key(seqID1, seqID2);

		if(m_distanceMatrix.count(key) == 0)
		{
			m_distanceMatrix[key] += eValue;
			m_distanceMatrix[key] /= 2;
		}
		else
		{
			m_distanceMatrix[key] = eValue;
		}
	}

	m_minValueGreaterThanZero = std::numeric_limits<double>::max();
	for(auto element : m_distanceMatrix)
	{
		double value = element.second;
		if(value > 0.0 && value < m_minValueGreaterThanZero)
		{
			m_minValueGreaterThanZero = value;
		}
	}

	m_allSequences.print();
	print();
}

void SparseDistanceMatrix::saveMatrix(std::string & outputFileName, bool makeHalfMatrix, bool useSortNames) const
{
	std::ofstream fout(outputFileName);
	fout << m_allSequences.size() << std::endl;

	double offSetDistance = -std::log(m_minValueGreaterThanZero) + 10; // Still have some distance to zero

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
			const MapKey key(i, j);
			if(m_distanceMatrix.count(key) > 0)
			{
				double distance = m_distanceMatrix.at(key);

				if(distance != 0.0)
				{
					distance  = std::log(distance);
					distance += offSetDistance;
				}

				fout << " " << distance;
			}
			else if(i == j)
			{
				fout << " " << 0;
			}
			else
			{
				double distance  = offSetDistance;
				       distance *= 2;
				fout << " " << std::ceil(distance); // Save space, we are writing to a text file, so get rid of the decimal fractions
			}
		}

		fout << std::endl;
	}
}

void SparseDistanceMatrix::print() const
{
	std::cerr << m_distanceMatrix.size() << " HSPs loaded" <<  std::endl;
}
