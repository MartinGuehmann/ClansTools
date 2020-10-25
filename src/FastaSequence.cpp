#include "FastaSequence.h"

#include <iostream>

void FastaSequence::print() const
{
	std::cout << '>' << m_name     << std::endl;
	std::cout <<        m_sequence << std::endl;
}

