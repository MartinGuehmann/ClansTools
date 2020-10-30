#pragma once

#include "FastaSequenceCollection.h"

#include <string>

class NodePositions
{
public:
	NodePositions(std::string & clansFileName);
	void saveMatrix(std::string & outputFileName, bool makeHalfMatrix, bool useSortNames) const;
	void print() const;

private:
	float ** m_positions;
	FastaSequenceCollection m_allSequences;
	
	static const uint32_t s_dimensions = 3; // Could later be converted to a variable member
};
