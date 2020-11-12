#include "ClansMaker.h"

#include <fstream>
#include <iostream>
#include <cmath>
#include <limits>

ClansMaker::ClansMaker(std::string & sequenceFileName, std::string & clansOutFileName, std::string & blastFileName)
:
    m_allSequences(sequenceFileName),
    m_clansOutFileName(clansOutFileName),
    m_blastFileName(blastFileName)
{
	m_allSequences.print();
}

void ClansMaker::saveFile() const
{
	std::cerr << "Writing to: " << m_clansOutFileName << std::endl;

	std::ofstream fout(m_clansOutFileName);
	fout << "sequences=" << m_allSequences.size() << std::endl;

	fout << "<param>" << std::endl;

	fout << "maxmove=0.1" << std::endl;
	fout << "pval=1" << std::endl;
	fout << "usescval=false" << std::endl;
	fout << "autosaveinterval=0" << std::endl;
	fout << "complexatt=true" << std::endl;
	fout << "cooling=1.0" << std::endl;
	fout << "currcool=1.0" << std::endl;
	fout << "attfactor=10.0" << std::endl;
	fout << "attvalpow=1" << std::endl;
	fout << "repfactor=10.0" << std::endl;
	fout << "repvalpow=1" << std::endl;
	fout << "dampening=1.0" << std::endl;
	fout << "minattract=1.0" << std::endl;
	fout << "cluster2d=false" << std::endl;
	fout << "blastpath=''" << std::endl;
	fout << "formatdbpath=''" << std::endl;
	fout << "showinfo=false" << std::endl;
	fout << "zoom=1.0" << std::endl;
	fout << "dotsize=2" << std::endl;
	fout << "ovalsize=10" << std::endl;
	fout << "groupsize=4" << std::endl;
	fout << "usefoldchange=false" << std::endl;
	fout << "avgfoldchange=false" << std::endl;
	fout << "colorcutoffs=0.0;0.1;0.2;0.3;0.4;0.5;0.6;0.7;0.8;0.9;" << std::endl;

	fout << "colorarr=";
	fout << "(230;230;230):";
	fout << "(207;207;207):";
	fout << "(184;184;184):";
	fout << "(161;161;161):";
	fout << "(138;138;138):";
	fout << "(115;115;115):";
	fout << "(92;92;92):";
	fout << "(69;69;69):";
	fout << "(46;46;46):";
	fout << "(23;23;23):" << std::endl;

	fout << "</param>" << std::endl;

	fout << "<rotmtx>" << std::endl;
	fout << "1.0;0.0;0.0;" << std::endl;
	fout << "0.0;1.0;0.0;" << std::endl;
	fout << "0.0;0.0;1.0;" << std::endl;
	fout << "</rotmtx>" << std::endl;

	fout << "<seq>" << std::endl;
	m_allSequences.saveToFile(fout);
	fout << "</seq>" << std::endl;

	fout << "<hsp>" << std::endl;

	std::ifstream fin(m_blastFileName);
	if(!fin.good())
	{
		std::cerr << "The BLAST output file " << m_blastFileName << " does not exist. Existing." << std::endl;
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

		fout << seqID1 << " " << seqID2 << ":" << eValue << std::endl;
	}

	fout << "</hsp>" << std::endl;
	fout << std::endl;
}
