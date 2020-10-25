#include "FastaSequence.h"

#include <cstdint>
#include <unordered_map>
#include <string>
#include <vector>

class FastaSequenceCollection
{
public:
	FastaSequenceCollection(std::string & sequenceFileName);
	const int32_t getSeqID(const std::string & seqName) const { return m_name2index.at(seqName); };
	std::string getShortSeqName(int32_t seqID) const;
	void print() const;
	size_t size() const { return m_sequences.size(); };
private:
	std::vector<FastaSequence> m_sequences;
	std::unordered_map<std::string, uint32_t > m_name2index;
};

