#include "FastaSequenceCollection.h"

#include <fstream>
#include <iostream>

FastaSequenceCollection::FastaSequenceCollection(std::string & sequenceFileName)
{
	std::ifstream fin(sequenceFileName);
	if(!fin.good())
	{
		std::cerr << "The sequence file " << sequenceFileName << " does not exist. Existing." << std::endl;
		exit(EXIT_FAILURE);
	}

	FastaSequence seq;
	// Reuse those this object instead of recreating it each interaction
	std::string line;

	while(fin.good())
	{
		std::getline(fin, line);

		if(line[0] == '>')
		{
			if(seq.isValid())
			{
				m_sequences.push_back(seq);
			}

			line.erase(0, 1);
			seq.addName(line);

			if(line.find_first_of(" ") != std::string::npos)
			{
				line.erase(line.find_first_of(" "));
			}

			std::size_t newIndex = m_sequences.size();
			m_name2index[line] = newIndex;
		}
		else
		{
			seq.addSequence(line);
		}
	}

	// Add the last sequence, there is no new line starting with '>'
	if(seq.isValid())
	{
		m_sequences.push_back(seq);
	}

	fin.close();
}

std::string FastaSequenceCollection::getShortSeqName(int32_t seqID) const
{
	const std::string seqName = m_sequences.at(seqID).getName();

	if(seqName.find_first_of(" ") != std::string::npos)
	{
		return seqName.substr(0, seqName.find_first_of(" "));
	}
	else
	{
		return seqName;
	}
}

void FastaSequenceCollection::print() const
{
	std::cerr << m_sequences.size() << " sequences loaded" <<  std::endl;
}
