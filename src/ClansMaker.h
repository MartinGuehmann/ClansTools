#pragma once

#include "MapKey.h"
#include "FastaSequenceCollection.h"

#include <unordered_map>
#include <string>

class ClansMaker
{
public:
	ClansMaker(std::string & sequenceFileName, std::string & clansOutFileName, std::string & blastFileName);
	void saveFile() const;

private:
	FastaSequenceCollection m_allSequences;
	std::string m_clansOutFileName;
	std::string m_blastFileName;
};
