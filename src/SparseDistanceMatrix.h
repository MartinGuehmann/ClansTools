#include "MapKey.h"
#include "FastaSequenceCollection.h"

#include <unordered_map>
#include <string>

class SparseDistanceMatrix
{
public:
	SparseDistanceMatrix(std::string & inputFileName, std::string & sequenceFileName);
	void saveMatrix(std::string & outputFileName, bool makeHalfMatrix, bool useSortNames) const;
	void print() const;

private:
	std::unordered_map<const MapKey, double, std::hash<MapKey>, std::equal_to<MapKey> > m_distanceMatrix;
	FastaSequenceCollection m_allSequences;
	double m_minValueGreaterThanZero;
};
