#include "FastaSequenceCollection.h"

#include <fstream>
#include <iostream>
#include <algorithm>

FastaSequenceCollection::FastaSequenceCollection(std::string & sequenceFileName)
{
	std::ifstream fin(sequenceFileName);
	if(!fin.good())
	{
		std::cerr << "The sequence/clans file " << sequenceFileName << " does not exist. Existing." << std::endl;
		exit(EXIT_FAILURE);
	}

	FastaSequence seq;
	bool gotFirstSeq = false;
	// Reuse this object instead of recreating it each interaction
	std::string line;

	while(fin.good())
	{
		std::getline(fin, line);

		if(line[0] == '>')
		{
			if(!gotFirstSeq) gotFirstSeq = true; // Probably, it does not cost more then having it set each round

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
		else if(gotFirstSeq)
		{
			// If we are loading the sequences from a clans file
			// break when we encounter </seq>, checking the first character is enough
			if(line[0] == '<')
			{
				break;
			}
			else
			{
				seq.addSequence(line);
			}
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

std::string FastaSequenceCollection::getCleanSeqName(int32_t seqID) const
{
	std::string seqName = m_sequences.at(seqID).getName();
	std::replace(seqName.begin(), seqName.end(), ' ', '_');
	std::replace(seqName.begin(), seqName.end(), '/', '_');
	std::replace(seqName.begin(), seqName.end(), ':', '_');

	seqName.erase(std::remove(seqName.begin(), seqName.end(), '"'), seqName.end());
	seqName.erase(std::remove(seqName.begin(), seqName.end(), '\''), seqName.end());
	seqName.erase(std::remove(seqName.begin(), seqName.end(), ';'), seqName.end());
	seqName.erase(std::remove(seqName.begin(), seqName.end(), ','), seqName.end());
	seqName.erase(std::remove(seqName.begin(), seqName.end(), '['), seqName.end());
	seqName.erase(std::remove(seqName.begin(), seqName.end(), ']'), seqName.end());
	seqName.erase(std::remove(seqName.begin(), seqName.end(), '('), seqName.end());
	seqName.erase(std::remove(seqName.begin(), seqName.end(), ')'), seqName.end());

	return seqName;
}

void FastaSequenceCollection::print() const
{
	std::cerr << m_sequences.size() << " sequences loaded" <<  std::endl;
}
