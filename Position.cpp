/*
 * Position.cpp
 *
 *  Created on: May 1, 2009
 *  Last update: 25 March 2015
 *      Author: Carol L. Ecale Zhou 
 */

#include <iostream>
#include "Position.h"
#include "RandomC.h"

// Conditional compilation
//#define PRINT_POSITION_IN_DETAIL

using namespace std;

static TRandomMersenne oRandomNumGenerator(5);
static unsigned long iRandomNumGen = 0;

static char NucleotideArray[4] = {'A', 'C', 'G', 'U'};

// Constructor
CPosition::CPosition(char cNucleotide, 
		int iPosition,
		bool bSabin1, 
		bool bMahoney,
		bool bNeurovirulent, 
		bool bLethal,
		int iDegreeOfNeurovirulence,
                double dFitness,
		double dFixFactor, 
		double dMutability)
{
	m_cNucleotide = cNucleotide;
	m_iPosition = iPosition;
	m_bSabin1 = bSabin1;
	m_bMahoney = bMahoney;
	m_bNeurovirulent = bNeurovirulent;
	m_bLethal = bLethal;
	m_iDegreeOfNeurovirulence = iDegreeOfNeurovirulence;
	m_dFitness = dFitness;
	m_dFixFactor = dFixFactor;
	m_dMutability = dMutability;
}

CPosition::CPosition(CPosition* pPosition) // copy constructor
{
	m_cNucleotide = pPosition->m_cNucleotide;
	m_iPosition = pPosition->m_iPosition;
	m_bSabin1 = pPosition->m_bSabin1;
	m_bMahoney = pPosition->m_bMahoney;
	m_bNeurovirulent = pPosition->m_bNeurovirulent;
	m_bLethal = pPosition->m_bLethal;
	m_iDegreeOfNeurovirulence = pPosition->m_iDegreeOfNeurovirulence;
	m_dFitness = pPosition->m_dFitness;
	m_dFixFactor = pPosition->m_dFixFactor;
	m_dMutability = pPosition->m_dMutability;
}

CPosition::~CPosition() {
	// destructor
}

void CPosition::PrintPosition() {
#ifdef PRINT_POSITION_IN_DETAIL
	cout << m_cNucleotide <<  m_iPosition
	     << (m_bSabin1 ? " Sabin1" : " Non-Sabin1")
	     << (m_bMahoney ? " Mahoney" : " Non-Mahoney")
	     << (m_bNeurovirulent ? " Neurovirulent " : " Neutral ")
	     << (m_bLethal ? "Lethal " : "Viable ")
	     << m_iDegreeOfNeurovirulence << " " << m_dFitness
	     << m_dFixFactor << " " << m_dMutability << endl;
#else
	cout << m_cNucleotide;
#endif	
}

bool CPosition::DetermineSimilarity(SPosition* sPosition)
{
	// Compare nt at this position to Struct data at corresponding position
	if((m_iPosition == sPosition->m_iPosition) && (m_cNucleotide == sPosition->m_cNucleotide))
 	{
		return true;
	}
	return false;
}

bool CPosition::DetermineNeurovirulence(SPosition* sPosition) 
{
	// Compare nt at this position to Neurovirulent at corresponding position
	if((m_iPosition == sPosition->m_iPosition) && (m_cNucleotide == sPosition->m_cNucleotide))
 	{
		m_bNeurovirulent = sPosition->m_bNeurovirulent;
		m_iDegreeOfNeurovirulence = sPosition->m_iDegreeOfNeurovirulence;
		return true;
	}
	return false;	
}

void CPosition::Mutate()
{
	oRandomNumGenerator.RandomInit(clock () + time (NULL) + iRandomNumGen++);
	int iRandomNum = oRandomNumGenerator.IRandom(1, 3);

	switch(m_cNucleotide) {
	case 'A':
		m_cNucleotide = NucleotideArray[iRandomNum];
		break;
	case 'C':
		m_cNucleotide = NucleotideArray[(iRandomNum + 1)%4];
		break;
	case 'G':
		m_cNucleotide = NucleotideArray[(iRandomNum + 2)%4];
		break;
	case 'U':
		m_cNucleotide = NucleotideArray[(iRandomNum + 3)%4];
		break;
	}
}

bool ComparePosition(CPosition* pPosition1, CPosition* pPosition2)
{
	if(!pPosition1 || !pPosition2)
		return false;
	
	if(pPosition1->m_cNucleotide == pPosition2->m_cNucleotide && 
	   pPosition1->m_iPosition == pPosition2->m_iPosition)
		return true;
	else
		return false;
}


