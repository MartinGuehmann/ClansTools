#pragma once

#include <string>
#include <fstream>

class FastaSequence
{
public:
	FastaSequence(): m_name(), m_sequence()
	{
	}

	FastaSequence(std::string & name, std::string & sequence)
	: m_name     (name),
	  m_sequence (sequence)
	{
	}

	bool isValid() const { return m_name.length() > 0; }
	void print() const;
	void addName     (std::string & name)     { m_name = name; m_sequence.clear(); }
	void addSequence (std::string & sequence) { m_sequence += sequence; }
	const std::string & getName() const { return m_name; };
	void saveToFile(std::ofstream & fout) const;

private:
	std::string m_name;
	std::string m_sequence;
};

