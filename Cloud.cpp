/*
 * Cloud.cpp
 *
 *  Created on: May 7, 2009
 *  Last update: 25 March 2015
 *      Author: Carol L. Ecale Zhou 
 */
// Copyright   : Copyright (C) 2015 Carol L. Ecale Zhou - All Rights Reserved.
// License     : See LICENSE.md for license information

#include <ctime>
#include <iostream>
#include "Cloud.h"

// Conditional compilation
//#define PRINT_CLOUD
#define BRIEF_REPORT

using namespace std;

extern bool bFILTER_DEFECTIVES;

static TRandomMersenne oRandomNumGenerator(10);
static unsigned long iRandomNumGen = 0;
static int GetRandomNum(int start, int end);

static int GetRandomNum(int start, int end)
{
	oRandomNumGenerator.RandomInit(clock () + time (NULL) + iRandomNumGen++);
	return oRandomNumGenerator.IRandom(start, end);
}

CCloud::CCloud()
{
	//m_vPopulationSet.clear();  //*** CHECK:  Is this necessary? good?
	m_pSuperPopulation        = NULL;
	m_bInfectionCyclesReached = false;
	m_bNeurovirulent          = false;
	m_bMahoney                = false;
	m_iCensus                 = 0;
	m_bExtinct                = false;
}

CCloud::~CCloud()
{
	for(unsigned int i = 0; i < m_vPopulationSet.size(); i++)
	{
		if(m_vPopulationSet[i])
		{
			delete m_vPopulationSet[i];
			m_vPopulationSet[i] = NULL;
		}
	}
	
	if(m_pSuperPopulation)
	{
		delete m_pSuperPopulation;
		m_pSuperPopulation = NULL;
	}
}

void CCloud::AddPopulation(CPopulation* pPopulation)
{
	m_vPopulationSet.push_back(pPopulation);
}

bool CCloud::Grow()
{
	bool bExtinct = true;  // Disprove if even 1 population remains viable 
	for(unsigned int i = 0; i < m_vPopulationSet.size(); i++)
	{
		if(m_vPopulationSet[i]->IsExtinct())
			cout << "Current Population is extinct: cannot Replicate()" << endl;
		else	
		{
			bExtinct = false;  // At least one population is viable
			m_vPopulationSet[i]->Replicate();
		}
	}
	m_bExtinct = bExtinct;
	return bExtinct;
}

void CCloud::Burst()
// Each population represents virus replication within a cell; all cells burst at once
// Combine all populations into a super-population, representing the medium containing progeny virus.
{
	m_pSuperPopulation = new CPopulation;
	for(unsigned int i = 0; i < m_vPopulationSet.size(); i++)
	{
		m_vPopulationSet[i]->UpdatePopulationStatistics();
		m_pSuperPopulation->m_vGenotypeSet.insert(m_pSuperPopulation->m_vGenotypeSet.end(), 
				m_vPopulationSet[i]->m_vGenotypeSet.begin(), 
				m_vPopulationSet[i]->m_vGenotypeSet.end());
		m_pSuperPopulation->m_iNumOfGenotypes += m_vPopulationSet[i]->m_iNumOfGenotypes;
		m_pSuperPopulation->m_iGenerationNum  += m_vPopulationSet[i]->m_iGenerationNum;
		
		// Clear the old population after being merged into the m_pSuperPopulation
		m_vPopulationSet[i]->m_bBurstSizeReached = false;
		m_vPopulationSet[i]->m_bGenerationDepthReached = false;
		m_vPopulationSet[i]->m_iGenerationNum = 0;
		m_vPopulationSet[i]->m_iNumOfNeurovirulentGenotypes = 0;
		m_vPopulationSet[i]->m_iNeurovirulentIndex = 0;
		m_vPopulationSet[i]->m_iNumOfGenotypes = 0;
		m_vPopulationSet[i]->m_vGenotypeSet.clear();
		delete m_vPopulationSet[i]; 
	}
	m_vPopulationSet.clear();
	
	m_pSuperPopulation->Consolidate();
	m_pSuperPopulation->UpdatePopulationStatistics(); 
	if(m_pSuperPopulation->IsExtinct())
		cout << "Current Superpopulation is EXTINCT" << endl;
}

CPopulation* CCloud::PickInoculum(int iInoculumSize) 
// Randomly select a sampling of virus particles (genotypes) from the superpopulation
{				
	unsigned int iAdjustedInoculumSize = iInoculumSize;
						
	if(!m_pSuperPopulation)
		return NULL;

	m_pSuperPopulation->CountGenotypes();  // CHECK	
	if(m_pSuperPopulation->m_iNumOfGenotypes == 0)
		return NULL;

	if(m_pSuperPopulation->IsExtinct())
	{
		cout << "Current Superpopulation is extinct: cannot PickInoculum()" << endl;
		return NULL;
	}

	// Check if there are enough genotypes to form an inoculum
	if(m_pSuperPopulation->m_iNumOfGenotypes < iInoculumSize)
	{
		cout << "Current Superpopulation census is too small: using all genotypes for inoculum" << endl;
		iAdjustedInoculumSize = m_pSuperPopulation->m_iNumOfGenotypes; // Take everything
	}
	
	vector<CGenotype*> SelectedGenotypeSet;

	// Eliminate redundant genotype objects in inoculum 
	for(int i = 0; i < iAdjustedInoculumSize; i++)
	{
		int iGenotype;
		CGenotype* pGenotype;
		
		// Assure that no genotype is selected beyond m_iGenotypeCount 
		// You can't pick more of a given genotype than exist of that genotype in the superpPopulation
		// If you happen to have already selected all of them, don't take yet another!
		do 
		{	
			iGenotype = GetRandomNum(0, m_pSuperPopulation->m_iNumOfGenotypes-1);
			pGenotype = m_pSuperPopulation->SelectGenotype(iGenotype);
		} while (pGenotype->m_iSelectionCount >= pGenotype->m_iGenotypeCount);

		// Check whether an identical genotype is already selected. If it is, add to its tally   
		bool bFoundIdenticalGenotype = false;
		for(unsigned int j = 0; j < SelectedGenotypeSet.size(); j++)
		{
			CGenotype * pSelectedGenotype = SelectedGenotypeSet[j];
			if(CompareGenotype(pGenotype, pSelectedGenotype))
			{
				pSelectedGenotype->m_iSelectionCount++; // upping its tally essentially adds it to set
				bFoundIdenticalGenotype = true;
				break;
			}
		}
	    	// Did not find an identical genotype (ie one like pGenotype not already selected), so add to the set
		if(!bFoundIdenticalGenotype)
		{
			pGenotype->m_iSelectionCount++;  // Should be adding 1 to 0 (ie, 1st of this genotype in selection set) 
			SelectedGenotypeSet.push_back(pGenotype);
		}
	}

	// Create the inoculum, comprising the selected genotypes from the superPop.	
	CPopulation * pNewInoculum = new CPopulation();

	// Create new genotype for each pointed to within selected genotype set	
	for (unsigned int k = 0; k < SelectedGenotypeSet.size(); k++)
	{
		CGenotype * pGenotype = SelectedGenotypeSet[k];
		if(pGenotype->IsLethal() && bFILTER_DEFECTIVES)
		{
			cout << "Removing a defective interfering particle from inoculum set" << endl;
		}
		else
		{
			CGenotype * pNewGenotype = new CGenotype(pGenotype);
			pNewGenotype->m_iGenotypeCount = pGenotype->m_iSelectionCount;
			pGenotype->m_iSelectionCount = 0; // reset for next time inoculum is created (next passage)
			pNewInoculum->AddGenotype(pNewGenotype);
		}
	}
		
	SelectedGenotypeSet.clear();
	return pNewInoculum;
}

void CCloud::PrintCloud()
{
	UpdateCloudStatistics();
	cout << "Printing Cloud...  " << endl;

	// If super population is not null, then it takes precedence over a population list
	if(m_pSuperPopulation)
	{
		cout << "SuperPopulation: " << endl;
		m_pSuperPopulation->PrintPopulation();
	}
	else if(m_vPopulationSet.size() > 0) // Print population list
	{
		cout << "Population Set: " << "size " << m_vPopulationSet.size() << endl;
		for(unsigned int i = 0; i < m_vPopulationSet.size(); i++)
			m_vPopulationSet[i]->PrintPopulation();
	}
	else
		cout << "WARNING: no population to print" << endl;

	ReportCloudStatistics();
}

void CCloud::UpdateCloudStatistics()
// *** CHECK types of iGenotypeCount and CGenotype::m_iGenotypeCount are not the same--does it matter?
//     unsigned long vs. int
// Update the following statistics:
// a) whether neurovirulence has been reached (m_bNeurovirulent)
// b) whether Mahoney reversion has been reached (m_bMahoney)
// c) how many genotypes have been produced (m_iCensus)
{
	bool bNeurovirulent = false;
	bool bMahoney = false;
	unsigned long iGenotypeCount = 0;

	// If the super population is not null, update its statistics.
	// The super population takes precedence over the population list wrt Cloud 
	// statistics because the genotypes have been combined and consolidated
	if(m_pSuperPopulation)
	{
		m_pSuperPopulation->UpdatePopulationStatistics();
		if(m_pSuperPopulation->IsNeurovirulent())
			bNeurovirulent = true;
		if(m_pSuperPopulation->IsMahoney())
			bMahoney = true;
		for(unsigned int i = 0; i < m_pSuperPopulation->m_vGenotypeSet.size(); i++)
			iGenotypeCount += m_pSuperPopulation->m_vGenotypeSet[i]->m_iGenotypeCount;
	}
	else if(m_vPopulationSet.size() > 0) // If there are existing individual populations, update their statistics
	{
		for(unsigned int i = 0; i < m_vPopulationSet.size(); i++)
		{
			m_vPopulationSet[i]->UpdatePopulationStatistics();
			if(m_vPopulationSet[i]->IsNeurovirulent())
				bNeurovirulent = true;
			if(m_vPopulationSet[i]->IsMahoney())
				bMahoney = true;
			for(unsigned int j = 0; j < m_vPopulationSet[i]->m_vGenotypeSet.size(); j++)
				iGenotypeCount += m_vPopulationSet[i]->m_vGenotypeSet[j]->m_iGenotypeCount;
		}
	}
	else
		cout << "WARNING: No population to update!" << endl;

	m_bNeurovirulent = bNeurovirulent;
	m_bMahoney = bMahoney;
	m_iCensus = iGenotypeCount;
}

int CCloud::ReportCloudStatistics()
{
	cout << "Cloud Statistics:" << endl;
#ifdef BRIEF_REPORT
	cout << "Cstats:" << (m_pSuperPopulation ? "yes" : "no") << ' ' << m_vPopulationSet.size() << ' ';
	cout << m_iCensus << " NV:" << (m_bNeurovirulent ? "yes" : "no") << " MA:" << (m_bMahoney ? "yes" : "no") << ' ';
	cout << endl;
	return (0);
#endif
	cout << "Exists as Super-population: " << (m_pSuperPopulation ? "yes" : "no") << endl;
	cout << "Number of individual Populations: " << m_vPopulationSet.size() << endl;
	cout << "Number of Genotypes in Cloud: " << m_iCensus << endl;
	cout << "Neurovirulence: " << (m_bNeurovirulent ? "yes" : "no") << endl;	
	cout << "Mahoney reversion: " << (m_bMahoney ? "yes" : "no") << endl;
	//cout << "Infection cycles reached: " << (m_bInfectionCyclesReached ? "yes" : "no") << endl;
}
