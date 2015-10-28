/*
 * Genotype.cpp
 *
 *  Created on: Apr 16, 2009
 *  Last update:  25 March 2015
 *      Author: Carol Zhou
 */

// Copyright   : Copyright (C) 2015 Carol L. Ecale Zhou - All Rights Reserved.
// License     : See LICENSE.md for license information
//

#include <iostream>
#include <typeinfo>
#include "Genotype.h"

// Conditional compilation
//#define PRINT_GENOTYPE
#define PRINT_GENOTYPE_SEQUENCE
//#define PRINT_GENOTYPE_IN_DETAIL

extern int iMAHONEY_THRESHOLD;
extern int iNUMBER_SABIN1_POSITIONS;
extern int iNUMBER_MAHONEY_POSITIONS;

using namespace std;

CGenotype::CGenotype(int iGenotypeCount)
{
	//m_vPositionSet.clear();  // CHECK
	//m_mPositionMap.clear();
	m_iGenotypeCount = iGenotypeCount;
	m_iMahoneyCount = 0;
	m_iSabin1Count = 0;
	m_iNeurovirulentCount = 0;
	m_iNeurovirulentIndex = 0;
	m_bNeurovirulent = false;
	m_bSabin1 = false;
	m_bMahoney = false;
	m_bLethal = false;
	m_bNewRecombinant = false;
	m_bMutatedReplicate = false;
	m_iPositionCount = 0;
	m_iSelectionCount = 0;
	m_dFitness = 0.0;
    m_dFitness_synergy = 0.0;
}

CGenotype::CGenotype(SPosition positions[], int iNumPositions, int iGenotypeCount)
// Note: cannot pre-set neurovirulence and mahoney values for genotype attributes
// by calling UpdateGenotypeStatistics (because pSabin1, pMahoney don't exist yet) 
// CHECK: the Position constructor is a bit messy -- fix this.
{
	CPosition * pPosition = NULL;
	bool bNeurovirulent = false;
	int iNeurovirulentIndex = 0;
	for(unsigned int i = 0; i < iNumPositions; i++)
	{
		if(positions[i].m_bNeurovirulent)
			bNeurovirulent = true;
		iNeurovirulentIndex += positions[i].m_iDegreeOfNeurovirulence;
		pPosition = new CPosition(positions[i].m_cNucleotide,
			  positions[i].m_iPosition,
			  false, //bSabin1 - not provided in SPosition 
			  positions[i].m_bMahoney,
			  positions[i].m_bNeurovirulent,
			  false, //bLethal - not provided in SPosition
			  positions[i].m_iDegreeOfNeurovirulence);

		m_vPositionSet.push_back(pPosition);
		m_mPositionMap[positions[i].m_iPosition] = pPosition;
	}

	m_iGenotypeCount = iGenotypeCount;
	m_iMahoneyCount = 0; 
	m_iSabin1Count = 0;
	m_iNeurovirulentCount = 0;
	m_iNeurovirulentIndex = iNeurovirulentIndex;
	m_bNeurovirulent = bNeurovirulent;
	m_bSabin1 = false;
	m_bMahoney = false;
	m_bLethal = false;
	m_bNewRecombinant = false;
	m_bMutatedReplicate = false;
	m_iPositionCount = iNumPositions;
	m_iSelectionCount = 0;
	m_dFitness = 0.0;
    m_dFitness_synergy = 0.0;
}

CGenotype::CGenotype(CGenotype *pGenotype, bool bExactCopy)
{
	CPosition * pPosition = NULL;
	for(unsigned int i = 0; i < pGenotype->m_vPositionSet.size(); i++)
	{
		pPosition = new CPosition(pGenotype->m_vPositionSet[i]);
		m_vPositionSet.push_back(pPosition);
		m_mPositionMap[pPosition->m_iPosition] = pPosition;
	}

	m_iMahoneyCount = pGenotype->m_iMahoneyCount;  // Count of the number of Position objects that have reached Mahoney state
	m_iSabin1Count = pGenotype->m_iSabin1Count;
	m_iNeurovirulentCount = pGenotype->m_iNeurovirulentCount;
	m_iNeurovirulentIndex = pGenotype->m_iNeurovirulentIndex;
	m_bNeurovirulent = pGenotype->m_bNeurovirulent; // True if any of the Position objects confers neurovirulence
	m_bSabin1 = pGenotype->m_bSabin1;
	m_bMahoney = pGenotype->m_bMahoney;
	m_bLethal = pGenotype->m_bLethal; // Note: lethal genotype may be removed at consolidation; until then, genotype exists
	m_iPositionCount = pGenotype->m_iPositionCount;
	m_iSelectionCount = 0;
	m_dFitness = pGenotype->m_dFitness;
    m_dFitness_synergy = pGenotype->m_dFitness_synergy;
	
	if(bExactCopy)
	{
		m_iGenotypeCount = pGenotype->m_iGenotypeCount;
		m_bNewRecombinant = pGenotype->m_bNewRecombinant;
		m_bMutatedReplicate = pGenotype->m_bMutatedReplicate;
	}
	else
	{
		m_iGenotypeCount = 1;
		m_bNewRecombinant = false;
		m_bMutatedReplicate = false;
	}
}

CGenotype::~CGenotype()
{
	for(unsigned int i = 0; i < m_vPositionSet.size(); i++)
	{
		if(m_vPositionSet[i])
		{
			delete m_vPositionSet[i];
			m_vPositionSet[i] = NULL; //*** CHECK: is this good enough (ie, m_vPositionSet.erase()?)
		}
	}
	m_vPositionSet.clear();
}

void CGenotype::UpdatePositionCount()
{
    m_iPositionCount = m_vPositionSet.size();
}

void CGenotype::PrintGenotype()
{
#ifdef PRINT_GENOTYPE_SEQUENCE
	for(unsigned int i = 0; i < m_vPositionSet.size(); i++)
	{
		m_vPositionSet[i]->PrintPosition();
	}
	cout << "  " << m_iGenotypeCount << endl;
#endif
#ifdef PRINT_GENOTYPE_IN_DETAIL
	cout << "Genotype attributes:  " << endl;
	cout << "m_iGenotypeCount      " << m_iGenotypeCount << endl;
	cout << "m_iMahoneyCount       " << m_iMahoneyCount << endl;
	cout << "m_iSabin1Count        " << m_iSabin1Count << endl;
	cout << "m_iNeurovirulentCount " << m_iNeurovirulentCount << endl;
	cout << "m_iNeurovirulentIndex " << m_iNeurovirulentIndex << endl;
	cout << "m_bNeurovirulent      " << m_bNeurovirulent << endl;
	cout << "m_bSabin1             " << m_bSabin1 << endl;
	cout << "m_bMahoney            " << m_bMahoney << endl;
	cout << "m_bLethal             " << m_bLethal << endl;
	cout << "m_bNewRecombinant     " << m_bNewRecombinant << endl;
	cout << "m_bMutatedReplicate   " << m_bMutatedReplicate << endl;
	cout << "m_iPositionCount      " << m_iPositionCount << endl;
	cout << "m_iSelectionCount     " << m_iSelectionCount << endl;
	cout << "m_dFitness            " << m_dFitness << endl;
    cout << "m_dFitness_synergy    " << m_dFitness_synergy << endl;
#endif
}

bool CompareGenotype(CGenotype* pGenotype1, CGenotype* pGenotype2)
{
	if(!pGenotype1 || !pGenotype2)
		return false;
	
	if(pGenotype1->m_vPositionSet.size() != pGenotype2->m_vPositionSet.size())
		return false;
	
	if(pGenotype1->m_vPositionSet.size() == 0)
		return false;
	
	for(unsigned int i = 0; i < pGenotype1->m_vPositionSet.size(); i++)
	{
		if(!ComparePosition(pGenotype1->m_vPositionSet[i], pGenotype2->m_vPositionSet[i]))
			return false;	
	}
	
	return true;
}

void CGenotype::UpdateGenotypeStatistics()
{
    UpdatePositionCount();
	IsSabin1();
	IsMahoney();
	IsNeurovirulent();
	CalculateFitness();
	IsLethal();
}

void CGenotype::ReportGenotypeStatistics()
{
#ifdef PRINT_GENOTYPE
	PrintGenotype();	
#endif
	cout << "Genotype Statistics: " << endl;
	cout << "Number of genotypes with this sequence: " << m_iGenotypeCount << endl;
	cout << "Positions with Mahoney identity: " << m_iMahoneyCount << endl;
	cout << "Positions with Sabin1 identity: " << m_iSabin1Count << endl;
	cout << "Neurovirulence status: " << (m_bNeurovirulent ? "NEUROVIRULENT" : "benign") << endl;
	cout << "Positions that confer neurovirulence: " << m_iNeurovirulentCount << endl;
	cout << "Relative degree of neurovirulence: " << m_iNeurovirulentIndex << endl;
	cout << "Genotype fitness: " << m_dFitness << endl;
    cout << "Genotype fitness synergy: " << m_dFitness_synergy << endl;
	cout << "Viability: " << (m_bLethal ? "LETHAL" : "viable") << endl;
	cout << endl;
}

double CGenotype::CalculateFitness()
// Returns genotype 'synergy' fitness measure. Note: genotype will have a positive fitness
// value even if it has a lethal mutation (see IsLethal()).
// Calculates absolute fitness (sum of all position fitness values) and also
// a 'synergy' fitness value based on presumed synergy among Mahoney positions
{
	char cNucleotide;
	double dFitness = 0.0; // Sum of fitness values over all positions
	double dPositionFitness = 0.0;
	double dGenotypeFitness = 0.0;
	std::vector<SFitness*>::iterator it;
	CPosition* nextPosition = NULL;

	// Update genotype fitness based on fitness object established in Qspp_main.cpp (pFitness) 
	for(it = pFitness->m_vPositionSet.begin(); it != pFitness->m_vPositionSet.end(); it++)
	{
		cNucleotide = m_mPositionMap[(*it)->m_iPosition]->m_cNucleotide;
		switch (cNucleotide) {
		case 'A':
			dPositionFitness = (*it)->m_dAnt;
			break;
		case 'C':
			dPositionFitness = (*it)->m_dCnt;
			break;
		case 'G':
			dPositionFitness = (*it)->m_dGnt;
			break;
		case 'U':
			dPositionFitness = (*it)->m_dUnt;
			break;
		}
		m_mPositionMap[(*it)->m_iPosition]->m_dFitness = dPositionFitness;  
		dGenotypeFitness += dPositionFitness;
	}
    
    m_dFitness = dGenotypeFitness; // Update at genotype level
    
    // Simulate synergy among Mahoney mutations // *** CHECK: make power configurable? test effect...
    double dMahoneyBoost = 0.0;
    IsMahoney();  // Update the number of positions that resemble Mahoney
    if(m_iPositionCount > 0)
    {
        dMahoneyBoost = 1.0 + (pow((double)m_iMahoneyCount,dMAHONEY_SYNERGY) / (double)m_iPositionCount) * dGenotypeFitness;
    }
    dGenotypeFitness *= dMahoneyBoost;
    
	m_dFitness_synergy = dGenotypeFitness;  // Update at genotype level
	return m_dFitness_synergy;
}

bool CGenotype::IsLethal() //CHECK: re-write inspecting fitness at each position (code from UpdateGenotypeStatistics())
{
	bool bLethal = false;  // True if any position has a lethal mutation  
	char cNucleotide;
	double dPositionFitness = 0.0;
	std::vector<SFitness*>::iterator it;
	CPosition* nextPosition = NULL;

	// Zero fitness at any position may spell death for the genotype
	// Update genotype fitness based on fitness object established in Qspp_main.cpp (pFitness) 
	for(it = pFitness->m_vPositionSet.begin(); it != pFitness->m_vPositionSet.end(); it++)
	{
		cNucleotide = m_mPositionMap[(*it)->m_iPosition]->m_cNucleotide;
		switch (cNucleotide) {
		case 'A':
			dPositionFitness = (*it)->m_dAnt;
			break;
		case 'C':
			dPositionFitness = (*it)->m_dCnt;
			break;
		case 'G':
			dPositionFitness = (*it)->m_dGnt;
			break;
		case 'U':
			dPositionFitness = (*it)->m_dUnt;
			break;
		}
		if(dPositionFitness == 0.0)  //*** CHECK: double arithmetic - does it equal to 0.0?
		{
			m_mPositionMap[(*it)->m_iPosition]->m_bLethal = true;  // Update at position level
			bLethal = true;
		}
	}
	m_bLethal = bLethal;  // Update at genotype level
	return bLethal;
}

bool CGenotype::IsSabin1()
{
	int iSabin1Count = 0;  // Number of positions that remain in Sabin1 state
	bool bSabin = false;   // Becomes true if all positions match Sabin1 genotype
	std::vector<CPosition*>::iterator it;
	CPosition* nextPosition = NULL;

	// Update positions, gather stats, based on comparison to Sabin1 strain
	for(it = pSabin1->m_vPositionSet.begin(); it != pSabin1->m_vPositionSet.end(); it++)
	{
		nextPosition = m_mPositionMap[(*it)->m_iPosition];
		if(ComparePosition(*it,nextPosition)) // Does it resemble Sabin1 in position, nucleotide?
		{
			nextPosition->m_bSabin1 = true;
			iSabin1Count++;
		}
		else
			nextPosition->m_bSabin1 = false;
	}
	if(iSabin1Count >= iNUMBER_SABIN1_POSITIONS) //
		bSabin = true;

	m_bSabin1 = true; // Update at genotype level
	m_iSabin1Count = iSabin1Count;
	return bSabin;
}

bool CGenotype::IsMahoney() 
{
	int iMahoneyCount = 0;  // Number of positions that have reverted to Mahoney
	bool bMahoney = false;  // Assume false to start
    int iMahoneyPercent = 0; // What percentage of positions are Mahoney
	std::vector<CPosition*>::iterator it;
	CPosition* nextPosition = NULL;

	// Update positions, gather stats, based on comparison to Mahoney strain
	for(it = pMahoney->m_vPositionSet.begin(); it != pMahoney->m_vPositionSet.end(); it++)
	{
		nextPosition = m_mPositionMap[(*it)->m_iPosition]; // Corresponding position in this genotype
		if(ComparePosition(*it,nextPosition)) // Does it resemble Mahoney in position, nucleotide?
		{
			nextPosition->m_bMahoney = true;  // Update at position level
			iMahoneyCount++;
		}
		else
			nextPosition->m_bMahoney = false;
	}
    iMahoneyPercent = (int)((100 * iMahoneyCount) / iNUMBER_MAHONEY_POSITIONS);
	if(iMahoneyCount >= iMAHONEY_THRESHOLD) //
		bMahoney = true;

	m_bMahoney = bMahoney;  // Update at genotype level
	m_iMahoneyCount = iMahoneyCount;
	return bMahoney;
}

bool CGenotype::IsNeurovirulent() //CHECK: re-write comparing neurovirulent to corresponding positions (code from UpdateGenotypeStatistics())
{
	int iNeurovirulentCount = 0;  // Number of positions that convey neurovirulence
	int iNeurovirulentIndex = 0;  // Degree of neurovirulence for this genotype
	bool bNeurovirulent = false;  // Becomes true if any position is neurovirulent
	std::vector<CPosition*>::iterator it;
	CPosition* nextPosition = NULL;

	// Update positions, gather stats, based on correspondence to neurovirulence
	for(it = pNeurovirulent->m_vPositionSet.begin(); it != pNeurovirulent->m_vPositionSet.end(); it++)
	{
		nextPosition = m_mPositionMap[(*it)->m_iPosition]; // Corresponding position in this genotype
		if(ComparePosition(*it,nextPosition)) // Does it resemble Neurovirulence at this position?
		{
			nextPosition->m_bNeurovirulent = true; // Update at position level
			nextPosition->m_iDegreeOfNeurovirulence = (*it)->m_iDegreeOfNeurovirulence;
			iNeurovirulentCount++;   
			iNeurovirulentIndex += (*it)->m_iDegreeOfNeurovirulence;
			bNeurovirulent = true;
		}
		else
			nextPosition->m_bNeurovirulent = false;
	}

	m_bNeurovirulent = bNeurovirulent;  // Update at genotype level
	m_iNeurovirulentCount = iNeurovirulentCount;
	m_iNeurovirulentIndex = iNeurovirulentIndex;
	return bNeurovirulent;
}

bool CGenotype::AllowMutation()
{
	return true;
}

char CGenotype::SelectMutation()
{
	return 'c';
}

