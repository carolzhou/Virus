/* 
 * Population.cpp
 *
 *  Created on: May 7, 2009
 *  Last update: 28 October 2015
 *      Author: Carol L. Ecale Zhou
 *
 */

// Copyright   : Copyright (C) 2015 Carol L. Ecale Zhou - All Rights Reserved.
// License     : See LICENSE.md for license information
//

#include <iostream>
#include <set>
#include <time.h>
#include <math.h>
#include "Population.h"

// Conditional compilation: controlling what and how much to print
//#define PRINT_POPULATION
#define PRINT_POPULATION_IN_DETAIL
//#define PRINT_GENOTYPE
//#define REPORT_GENOTYPE_STATS
//#define PRINT_DETAIL
//#define BRIEF_REPORT
//#define LONG_REPORT
#define ONE_LINER // All stats reported on single line of text

using namespace std;

extern double        dGENERATIONAL_GROWTH;
extern unsigned long iBURST_SIZE;
extern double        dERROR_RATE;
extern double        dHOMOLOGOUS_RECOMBINATION_RATE;
extern unsigned long iNUM_GENS_TO_CONSOLIDATE;
extern bool          bRETAIN_LETHALS;
extern double        dFITNESS_ACCELERATOR;
extern int           iPURGE_PERCENT;

static unsigned long static_iReportNo = 0;

static TRandomMersenne oRandomNumGenerator(10);
static unsigned long   iRandomNumGen = 0;
static int GetRandomNum(int start, int end);

static int GetRandomNum(int start, int end)
{
	oRandomNumGenerator.RandomInit(clock () + time (NULL) + iRandomNumGen++);
	return oRandomNumGenerator.IRandom(start, end);
}

CPopulation::CPopulation()
{
	m_bBurstSizeReached = false;
	m_bGenerationDepthReached = false;
	m_iGenerationNum = 0;
	m_iNumOfNeurovirulentGenotypes = 0;
	m_iNumOfMahoneyGenotypes = 0;
	m_iNeurovirulentIndex = 0;
	m_iNumOfGenotypes = 0; 
	m_iNumOfDefectiveGenotypes = 0;
	m_dAverageFitness = 0.0;
	m_bMahoney = false;
	m_bNeurovirulent = false;
	m_bExtinct = false; // CHECK: true initially, actually, for an emptly population ;-)
	m_dPopulationHealth = 100.0; // Assume all viable genotypes to start
	m_dVariance          = 0.0; // Population diversity statistic
	m_iPopulationMinimum = 0; // Population diversity statistic
	m_iPopulationMaximum = 0;
	m_dPopulationMean    = 0.0;
	m_dPopulationMedian  = 0.0;
}

CPopulation::~CPopulation()
{
	for(unsigned int i = 0; i < m_vGenotypeSet.size(); i++)
	{
		if(m_vGenotypeSet[i])
		{
			delete m_vGenotypeSet[i];
			m_vGenotypeSet[i] = NULL;
		}
	}
	m_vGenotypeSet.clear();
}

void CPopulation::AddGenotype(CGenotype* pGenotype)
{
	m_vGenotypeSet.push_back(pGenotype);
	m_iNumOfGenotypes += pGenotype->m_iGenotypeCount;
}

//#define PRINT_POPULATION_IN_DETAIL
void CPopulation::PrintPopulation()
{
	UpdatePopulationStatistics();
	for(unsigned int i = 0; i < m_vGenotypeSet.size(); i++)
	{
		if(m_vGenotypeSet[i] == NULL)
		{
			cout << "WARNING:  m_vGenotypeSet[i] is NULL at i = " << i << endl;
		}
		else
		{
#ifdef PRINT_GENOTYPE
			m_vGenotypeSet[i]->PrintGenotype();
#endif
#ifdef REPORT_GENOTYPE_STATS
			m_vGenotypeSet[i]->ReportGenotypeStatistics();  
#endif
		}
	}
#ifdef PRINT_POPULATION_IN_DETAIL
	ReportPopulationStatistics();
#endif
}

bool CPopulation::IsNeurovirulent() // Reports whether neurovirulence has been reached by any genotype
{
	bool bNeurovirulent = false;  // Becomes true if any genotype is neurovirulent
	int iNeurovirulentCount = 0;
	int iNeurovirulentIndex = 0;

	for(unsigned int i = 0; i < m_vGenotypeSet.size(); i++)
	{
		if(m_vGenotypeSet[i] == NULL)
		{
			cout << "WARNING: m_vGenotypeSet[i] is NULL where i is " << i << endl;
		}
		else
		{
			if(m_vGenotypeSet[i]->IsNeurovirulent())
			{
				iNeurovirulentCount += m_vGenotypeSet[i]->m_iGenotypeCount;
				iNeurovirulentIndex += (m_vGenotypeSet[i]->m_iGenotypeCount * m_vGenotypeSet[i]->m_iNeurovirulentIndex);
				bNeurovirulent = true;
			}
		}
	}
	m_bNeurovirulent = bNeurovirulent;
	m_iNumOfNeurovirulentGenotypes = iNeurovirulentCount;
	m_iNeurovirulentIndex = iNeurovirulentIndex;

	return bNeurovirulent;
}

bool CPopulation::IsMahoney() 
// Reports whether any genotype resembles Mahoney in sequence.
// Calculates the number of Mahoney mutations that exist in the population
// and calculates the percent reversion to Mahoney genotype
{
	bool bMahoney = false;	
	int iMahoneyCount = 0;               // Total number of genotypes with Mahoney identity
	int iMahoneyPositionCount = 0;       // Total number of positions with Mahoney identity
	int iPositionCount = 0;              // Total number of positions in all genotypes
	double dMahoneyReversionIndex = 0.0; // Fraction of total positions that have Mahoney identity

	for(unsigned int i = 0; i < m_vGenotypeSet.size(); i++)
	{
		if(m_vGenotypeSet[i] == NULL)
		{
			cout << "WARNING: m_vGenotypeSet[i] is NULL where i is " << i << endl;
		}
		else
		{
			if(m_vGenotypeSet[i]->IsMahoney())
			{
				iMahoneyCount += m_vGenotypeSet[i]->m_iGenotypeCount;
				bMahoney = true;
			}
			iMahoneyPositionCount += m_vGenotypeSet[i]->m_iMahoneyCount;
			iPositionCount += m_vGenotypeSet[i]->m_iPositionCount;
		}
	}
	if (iPositionCount)
	{
		dMahoneyReversionIndex = (double)iMahoneyPositionCount / (double)iPositionCount;
	}
	m_bMahoney               = bMahoney;
	m_iNumOfMahoneyGenotypes = iMahoneyCount;
	m_iNumOfMahoneyPositions = iMahoneyPositionCount;
	m_dMahoneyReversionIndex = dMahoneyReversionIndex;

	return bMahoney;
}

bool CPopulation::IsExtinct() 
{
	bool bExtinct = true; // assume true: if any one genotype is viable, then the pop is too
	unsigned int iGenotypeCount = CountGenotypes(); // Number of genotypes in this population
	unsigned int iDefectiveCount = 0; // Number of lethal genotypes in population

	for(unsigned int i = 0; i < m_vGenotypeSet.size(); i++)
	{
		if(m_vGenotypeSet[i] == NULL)
		{	
			cout << "WARNING: m_vGenotypeSet[i] is NULL where i is " << i << endl;
		}
		else
		{
			if(!m_vGenotypeSet[i]->IsLethal())
				bExtinct = false;
			else
				iDefectiveCount += m_vGenotypeSet[i]->m_iGenotypeCount;
		}
	}
	m_iNumOfGenotypes = iGenotypeCount;
	m_iNumOfDefectiveGenotypes = iDefectiveCount;
	m_bExtinct = bExtinct;
	if(bExtinct)
		cout << "A Population has gone extinct!" << endl;

	return bExtinct;
}

double CPopulation::CalculateVariance()
// This is a crude measure of population diversity
// Assuming that the distribution of genotype frequencies (m_iGenotypeCount) is "normal",
// Calculate the variance and use that as a measure of population diversity
// Note:  A better measure of population diversity might be derived from information in
// the following publication:  Gregori et al 2014, "Inference with viral quasispecies
// diversity indices: clonal and NGS approaches", Bioinformatics Vol. 30 no. 8, pp 1104-11.
{
	double dVariance = 0.0;
	int iGenotypeCount = CountGenotypes();                 // Total number of genotypes
	int iDistinctGenotypeCount = m_vGenotypeSet.size();    // Number of distinct genotype sequences

	double dMean = (double)iGenotypeCount / (double)iDistinctGenotypeCount;
	double dSumOfSquares = 0.0;  // Sum of squares of distances of each genotype count from mean 

	for(unsigned int i = 0; i < m_vGenotypeSet.size(); i++)
	{
		dSumOfSquares += pow((dMean - (double)m_vGenotypeSet[i]->m_iGenotypeCount),2);
	}

	dVariance = dSumOfSquares / (double)m_vGenotypeSet.size();
	m_dVariance = dVariance;	

	return dVariance;
}

double CPopulation::CalculatePopulationFitness()
{
	double dTotalFitness = 0.0;
	double dAverageFitness = 0.0;

	// Sum all the fitness values over the genotypes
	for(unsigned int i = 0; i < m_vGenotypeSet.size(); i++)
		if(m_vGenotypeSet[i] == NULL)
		{
			cout << "WARNING: m_vGenotypeSet[i] is NULL at i = " << i << endl;
		}
		else
		{
			dTotalFitness += (m_vGenotypeSet[i]->m_dFitness * m_vGenotypeSet[i]->m_iGenotypeCount);
		}

	// Calculate average fitness among genotypes in this population
	CountGenotypes();  // Update
	if(m_iNumOfGenotypes > 0) // CHECK: integer vs. double and precision rules
		dAverageFitness = dTotalFitness/m_iNumOfGenotypes;

	m_dAverageFitness = dAverageFitness;
	return dAverageFitness;
}

double CPopulation::CalculateAverageFitness(vector<CGenotype*> &vGenotypeSet)
{
    double dAveFitness = 0.0;
    double dFitnessSum = 0.0;
    
    if (vGenotypeSet.size() > 0)
    {
        for(unsigned int i = 0; i < vGenotypeSet.size(); i++)
        {
            vGenotypeSet[i]->CalculateFitness();
            dFitnessSum += vGenotypeSet[i]->m_dFitness;
        }
        dAveFitness = dFitnessSum / vGenotypeSet.size();
    }
    
    return dAveFitness;
}

int CPopulation::CalculateNumOfProgeny(double dGenotypeFitness, vector<CGenotype*> &vGenotypeSet)
// dGenotypeFitness parameter is the m_dFitness_synergy of a given genotype.
// For a given fitness value (for a certain genotype), calculate how many progeny it will generate
// Calculation of a genotype's contribution to the next generation depends on the genotype's
// fitness, the number of progeny to be produced by the current replicating set, the magnitude of the
// fitness accelerator (-a input parameter). The formula is based on a geometric progression
// whereby the number of progeny increases geometrically based on the genotype fitness. The formula
// is:  Pi = (int) [ P * f^k / SUMi=1..n(fi^k)]
// Translated into English: the current genotype's number of progeny is the rounded integer value of
// the total number of progeny times the ratio of the current genotype's fitness factor divided by
// the sum of the fitness factors for the replicating genotypes.  The fitness factor is calculated
// by raising the genotype's fitness value to the power iFITNESS_ACCELERATOR. To increase the differentials
// among the genotypes in the input replicating set, the minimum fitness value is used as an offset.
{
    int iProgenyCount = 1;
    int iTotalProgeny = vGenotypeSet.size(); // For now, is always = number of replicating genotypes
    double dFitnessFactorSum = 0.0;
    double dMinFitness = 0.0;  // The minimum fitness among incoming genotypes
    
    // Exploit "spread" among the genotype fitness values
    // Use the minimum fitness value as an offset
    
    // First, caculate the minimum fitness among the incoming genotypes (for calculating differentials)
    for(unsigned int i = 0; i < vGenotypeSet.size(); i++)
        if(dMinFitness > vGenotypeSet[i]->m_dFitness_synergy)  // Use Mahoney synergy fitness here
            dMinFitness = vGenotypeSet[i]->m_dFitness_synergy;
    
    // Next, calculate and sum the fitness factors over the genotype set
    for(unsigned int i = 0; i < vGenotypeSet.size(); i++)
    {
        dFitnessFactorSum += pow(vGenotypeSet[i]->m_dFitness_synergy - dMinFitness, dFITNESS_ACCELERATOR);
    }
    
    // Next, calculate number of progeny for given genotype
    // dGenotypeFitness - dMinFitness provides differential
    if (dFitnessFactorSum > 0.0)
    {
        iProgenyCount = (int)((iTotalProgeny) * (pow(dGenotypeFitness - dMinFitness,dFITNESS_ACCELERATOR) / dFitnessFactorSum) + 0.5);
    }
    return iProgenyCount;
}

void CPopulation::UpdatePopulationStatistics()
{
	// First, update statistics for each genotype in this population
	if(m_vGenotypeSet.empty())
	{
		cout << "WARNING:  m_vGenotypeSet is empty" << endl;
	}
	else
	{
		for(unsigned int i = 0; i < m_vGenotypeSet.size(); i++)
		{
			if(m_vGenotypeSet[i] == NULL)
			{	
				cout << "m_vGenotypeSet[i] is NULL" << endl;
			}
			else
			{
				m_vGenotypeSet[i]->UpdateGenotypeStatistics();
			}
		}
	}
	// Then, update the individual population statistics	
	IsMahoney();
	IsNeurovirulent();
	IsExtinct();
	CalculatePopulationFitness();
	CalculatePopulationHealth();
}

double CPopulation::CalculatePopulationHealth()
// First call CalculatePopulationFitness() to assure data are up to date. 
{
	double dPopulationHealth = 100.0;  // Assume perfect health to start

	if(IsExtinct())  // Updates total and defective genotype counts
	{	
		// Extinction spells worst possible health
		dPopulationHealth = 0.0; // Population is extinct
	}
	else
	{
		// Health is the percent of healthy genotypes in the population
		dPopulationHealth = (int)(100 * (((double)m_iNumOfGenotypes - (double)m_iNumOfDefectiveGenotypes) / (double)m_iNumOfGenotypes) + 0.005);
	}

	m_dPopulationHealth = dPopulationHealth;
	return(dPopulationHealth);
}

void CPopulation::PurgeDefectives() // *** CHECK: This method is incomplete
// *** Need to implement a search through genotypes and collect ones to purge (see SelectGenotype())
// Remove some or all of the defective genotypes. 
// What proportion to remove is determined by input parameter, expressed as a percent.
{
	int iPurgeCount = 0;
	unsigned int iNumberToPurge = 0;

	if((0 < iPURGE_PERCENT) && (iPURGE_PERCENT < 101)) // Check if in range; should be controlled parameter in main
	{
		iNumberToPurge = (int)(m_iNumOfDefectiveGenotypes * (iPURGE_PERCENT / 100));
		for(unsigned int i = 0; i < m_vGenotypeSet.size(); i++)
		{
			iPurgeCount += 1;
		}
	}
}

int CPopulation::ReportPopulationStatistics()
{
	double dAveNeurovirulentIndex = 0.0;
    	double dDiversity = 0.0; 
	unsigned int iDistinctCount = 0;

	UpdatePopulationStatistics(); // *** May not be necessary, and may slow execution, but better safe than sorry
	CalculatePopulationDistribution();
	
	// Calculate diversity  // *** CHECK devise better method
	// Calculates the ratio of distinct to total genotypes
	if(m_iNumOfNeurovirulentGenotypes)
	{
		dAveNeurovirulentIndex = (double)m_iNeurovirulentIndex / (double)m_iNumOfNeurovirulentGenotypes;
	}
	iDistinctCount = m_vGenotypeSet.size();
    	dDiversity = (int)(100 * (double)iDistinctCount / (double)m_iNumOfGenotypes + 0.5); 

	cout << "Population Statistics: " << endl;

#ifdef BRIEF_REPORT
	cout << "P-genomes,distinct,diversity,health: " << m_iNumOfGenotypes << ' ' << iDistinctCount << ' ' << dDiversity << ' ' << m_dPopulationHealth << '%' << endl;
	cout << "P-statistics: min,max,mean,median: " << m_iPopulationMinimum << ' ' << m_iPopulationMaximum << ' ' << m_dPopulationMean << ' ' << m_dPopulationMedian << endl;
	cout << "P-defective,fitness,viability: " << m_iNumOfDefectiveGenotypes << ' ' << m_dAverageFitness << ' ' << (m_bExtinct ? "EXTINCT" : "Viable") << ' ' << m_iGenerationNum << endl;  
	cout << "N-genomes,neurovirIndex,aveNeurovir: " << m_iNumOfNeurovirulentGenotypes << ' ' << m_iNeurovirulentIndex << ' ' << dAveNeurovirulentIndex << endl;
	cout << "M-genomes,positions,reversion: " << m_iNumOfMahoneyGenotypes << ' ' << m_iNumOfMahoneyPositions << ' ' << m_dMahoneyReversionIndex << endl;
	PrintPopulationDistribution();
	cout << endl;
#endif
#ifdef ONE_LINER
	++static_iReportNo;
	if(static_iReportNo == 1)
	{
		cout << "Report No." << "\tPgentps\tDstinct\tDivrsty\tPMinMax\tPopMean\tPopMedn\t";
		cout << "Health\tDefctvs\tAveFitn\tViablty\tGnratns\tNgentps\tNscore\tAvNindx\tMgentyps\tMutns\tRevrsn" << endl;
	}
	cout << "Report " << static_iReportNo << "\t" << m_iNumOfGenotypes << '\t' << iDistinctCount << '\t' << dDiversity << '\t';
	cout << m_iPopulationMinimum << '-' << m_iPopulationMaximum << '\t' << m_dPopulationMean << '\t' << m_dPopulationMedian << '\t';
	cout << m_dPopulationHealth << '\t' << m_iNumOfDefectiveGenotypes << '\t' << m_dAverageFitness << '\t';
	cout << (m_bExtinct ? "Extinct" : "Viable") << '\t' << m_iGenerationNum << '\t';
	cout << m_iNumOfNeurovirulentGenotypes << '\t' << m_iNeurovirulentIndex << '\t' << dAveNeurovirulentIndex << '\t';
	cout << m_iNumOfMahoneyGenotypes << '\t' << m_iNumOfMahoneyPositions << '\t' << m_dMahoneyReversionIndex << endl;
#endif
#ifdef LONG_REPORT
	cout << "Absolute number of genotypes in this population: " << m_iNumOfGenotypes << endl;
	cout << "Number of distinct genotypes: " << iDistinctCount << endl;
	cout << "Total number of genotypes " << m_iNumOfGenotypes << endl;;
	cout << "Number of neurovirulent genotypes: " << m_iNumOfNeurovirulentGenotypes << endl;
	cout << "Neurovirulence index: " << m_iNeurovirulentIndex << endl;
	cout << "Average neurovirulence: " << dAveNeurovirulentIndex << endl;
	cout << "Number of Mahoney genotypes: " << m_iNumOfMahoneyGenotypes << endl;
	cout << "Number of Mahoney mutations in population: " << m_iNumOfMahoneyPositions << endl;
    	cout << "Number of genotypes that have reached " << iMAHONEY_THRESHOLD << " Mahoney status: " << cout << dMahoneyReversionIndex << cout << endl;
	cout << "Mahoney reversion index: " << m_dMahoneyReversionIndex << endl;
	cout << "Number of defective genotypes: " << m_iNumOfDefectiveGenotypes << endl;
    	cout << "Estimate of population diversity simple: " << dDiversity << endl;
    	cout << "Estimate of population diversity variance: " << m_dVariance << endl;
	cout << "Population min and max: " << m_iPopulationMinimum << ", " << m_iPopulationMaximum << endl;
	cout << "Population mean and median: " << m_dPopulationMean << ", " << m_dPopulationMedian << endl;
	cout << "Average genotype fitness over population: " << m_dAverageFitness << endl;
	cout << "Relative health of population: " << m_dPopulationHealth << endl;
	cout << "Number of replication cycles required to reach current state: " << m_iGenerationNum << endl;
	cout << "This population is " << (m_bExtinct ? "EXTINCT" : "Viable") << endl;
	cout << endl;
#endif
	return(0);
}

void CPopulation::CalculatePopulationDistribution()
{
	vector<int> identicals;
	double dMean = 0.0;
	double dMedian = 0.0;
	unsigned int iMin = iBURST_SIZE; // 
	unsigned int iMax = 0;

	// Gather the numbers of identical genotypes in population	
	for(unsigned int i = 0; i < m_vGenotypeSet.size(); i++)
	{
		identicals.push_back(m_vGenotypeSet[i]->m_iGenotypeCount);
	}

	// Sort in order from sparse to abundant genotypes
	sort(identicals.begin(),identicals.end());

	// Calculate mean number of identicals per genotype
	if(m_vGenotypeSet.size() > 0)
	{
		dMean = (double)m_iNumOfGenotypes / (double)m_vGenotypeSet.size();
	}
	
	// Calculate mid point of identicals list and get median value // *** CHECK this
	if(identicals.size() % 2 == 0)  // Even number of numbers; median is average of middle two
	{
		unsigned int left  = (identicals.size() / 2);
		unsigned int right = (identicals.size() / 2) + 1;
		dMedian = ((double)identicals[left] + (double)identicals[right]) / 2.0;
	}
	else // Odd number of values => take middle value
	{
		//unsigned int iMidPoint = (int)(((double)identicals.size() / 2.0) + 0.5);
		unsigned int iMidPoint = identicals.size() / 2;
		dMedian = identicals[iMidPoint];
	}

	// Print raw distribution
	cout << "Pop distribution: ";
	for(vector<int>::const_iterator it=identicals.begin(); it!=identicals.end(); ++it)
	{
		cout << *it << " ";
		if(iMin > *it)
		{
			iMin = *it;
		} 
		if(iMax < *it)
		{
			iMax = *it;
		}
	}
	cout << endl;
	
	// Calculate and print basic distribution statistics  
	m_iPopulationMinimum = iMin;
	m_iPopulationMaximum = iMax;
	m_dPopulationMean    = dMean;
	m_dPopulationMedian  = dMedian;

	//cout << "Distribution stats (genotype copy min, max, mean, and median):\t" << iMin << '\t' << iMax << '\t' << dMean << '\t' << dMedian << endl;
}

void CPopulation::Consolidate(void) // Remove redundancy in genotype list; collapse equivalents
// Method Consolidate removes all redundant genotype objects, thereby consolidating the list
// Each genotype object is moved to a holding list.  Then,
// it is compared to all remaining genotypes to determine if redundancy can be collapsed,
// which is accomplished by summing the counts between the two genotype objects.
// Also, genotypes with a lethal (fitness = 0.0) mutation may be removed.
{ 
	if(m_vGenotypeSet.size() == 0)  // If population has no genotypes, then it's extinct
	{
		m_bExtinct = true;
		cout << "Population is extinct, as it has no genotypes" << endl;
		return;
	}

	vector<CGenotype*> vNewGenotypeSet;           // temporary holding array
	CGenotype* pNextGenotype = NULL;              // next genotype for comparison
	unsigned int iGcount = m_vGenotypeSet.size(); // number of genotypes to consolidate

	// Remove genotypes to holding array, one at a time, comparing each
	// to the other genotypes already in the holding array.
	// If equivalent, merge and delete the redundant genotype,
	// setting array pointer to null
	for(unsigned int i = 0; i < iGcount; i++)
	{
		// Transfer next genotype to temp holding array
		pNextGenotype = m_vGenotypeSet[i];

		if(pNextGenotype == NULL)
		{
			continue; 
		}
		else // Add this genotype to the holding array
		{
			vNewGenotypeSet.push_back(pNextGenotype);
			m_vGenotypeSet[i] = NULL;
		}

		// Compare pNextGenotype to each genotype in m_vGenotypeSet
		for(unsigned int j = 0; j < iGcount; j++)
		{
			if(CompareGenotype(pNextGenotype, m_vGenotypeSet[j]))
			{
				// merge and clean up redundant genotype object
				pNextGenotype->m_iGenotypeCount += m_vGenotypeSet[j]->m_iGenotypeCount;
				delete m_vGenotypeSet[j];
				m_vGenotypeSet[j] = NULL;
			}
		}
	}

    
	// vNewGenotypeSet now holds consolidated genotypes, and m_vGenotypeSet holds NULL pointers
	m_vGenotypeSet.clear();
	
	// Move _viable_ genotypes from the holding list back to the original list
	for(unsigned int i = 0; i < vNewGenotypeSet.size(); i++)
	{
		if(vNewGenotypeSet[i] == NULL)
		{
			cout << "WARNING: vNewGenotypeSet[i] is NULL for i = " << i << endl;
		}
		else // If genotype is lethal (is a defective interfering particle), retain depending on bool
		{
			if(vNewGenotypeSet[i]->IsLethal() && !bRETAIN_LETHALS)
			//if(vNewGenotypeSet[i]->IsLethal())  
			{
#ifdef PRINT_DETAIL
				cout << "A LETHAL genotype has been detected during consolidation " << endl;
#endif
				delete vNewGenotypeSet[i];
				vNewGenotypeSet[i] = NULL;
			}
			else
			{
				m_vGenotypeSet.push_back(vNewGenotypeSet[i]);
			}
		}
	}

	// Clean up temporary holding array
	for(unsigned int i = 0; i < vNewGenotypeSet.size(); i++)
	{
		vNewGenotypeSet[i] = NULL;
	}
	vNewGenotypeSet.clear();
	
	// If no genotype was viable, then population goes extinct
	if(m_vGenotypeSet.size() == 0)
		m_bExtinct = true;

	UpdatePopulationStatistics(); // Need to update m_iNumOfGenotypes
	cout << "Consolidation complete" << endl; 
}

unsigned long CPopulation::CountGenotypes()
{
	unsigned long iHealthyTally = 0;  // Sum of "healthy" genotypes
	unsigned long iDefectiveTally = 0; // Sum of defective (lethal) genotypes

	for(unsigned int i = 0; i < m_vGenotypeSet.size(); i++)
	{
		if(m_vGenotypeSet[i] == NULL)
		{
			cout << "WARNING:  m_vGenotypeSet[i] is NULL at i = " << i << endl;
		}
		else
		{
			if(m_vGenotypeSet[i]->IsLethal())
			{
				iDefectiveTally += m_vGenotypeSet[i]->m_iGenotypeCount;
			}
			else
			{
				iHealthyTally += m_vGenotypeSet[i]->m_iGenotypeCount;
			}
		}
	}
	m_iNumOfGenotypes = iHealthyTally + iDefectiveTally;
	m_iNumOfDefectiveGenotypes = iDefectiveTally;

	return m_iNumOfGenotypes; // Return grand total
}

CGenotype* CPopulation::SelectGenotype(int iRandomPosition)
// Called by ReplicateOnce()
{
	int iAbsoluteGenotypeCount = CountGenotypes();
	if(iRandomPosition > iAbsoluteGenotypeCount)
	{
		cout << "WARNING:  the random position is beyond the genotype count !!! iRandomPosition, GenotypeCount are " << iRandomPosition << ", " << iAbsoluteGenotypeCount << endl;
#ifdef PRINT_POPULATION
		PrintPopulation();
#endif
	}
	int iTotal = 0;

	for(unsigned int i = 0; i < m_vGenotypeSet.size(); i++)
	{
		if(m_vGenotypeSet[i] == NULL)
		{
			cout << "WARNING:  in SelectGenotype(), m_vGenotypeSet[i] is NULL" << endl;
		}
		else
		{
			m_vGenotypeSet[i]->UpdateGenotypeStatistics();
			iTotal += m_vGenotypeSet[i]->m_iGenotypeCount;
			if(iRandomPosition < iTotal)
			{
				if(m_vGenotypeSet[i] == NULL)
					cout << "WARNING: selected genotype is null" << endl;
				return m_vGenotypeSet[i];
			}
		}
	}
	cout << "WARNING:  genotype not selected !!!" << endl;
	return NULL;
}

void CPopulation::MutateGenotypes(vector<CGenotype*> &vGenotypeSet)
{
	int iNumOfGenotypes = vGenotypeSet.size();
	if(iNumOfGenotypes == 0)
		return;

	int iGenotypeLength = vGenotypeSet[0]->m_vPositionSet.size();
	int iNumOfPositions = iNumOfGenotypes * iGenotypeLength;
	int iNumOfMutations = (int)(((double)iNumOfPositions * dERROR_RATE) + 0.5); // *** CHECK rounding
    set<int> MutatedPositionSet;

	for(int i = 0; i < iNumOfMutations; i++)
	{
		// Find a random position at which to mutate (ok if redundant)
		int iRandomPosition = GetRandomNum(0, iNumOfPositions-1);
		MutatedPositionSet.insert(iRandomPosition);
		int iGenotypeSetIndex;
		int iGenotypeOffset;

		// Determine where (which position), in which genotype, to mutate
		
		iGenotypeSetIndex = iRandomPosition/iGenotypeLength;
		iGenotypeOffset = iRandomPosition%iGenotypeLength;

		CGenotype* pGenotype = vGenotypeSet[iGenotypeSetIndex];
		CPosition* pPosition = pGenotype->m_vPositionSet[iGenotypeOffset];
		pPosition->Mutate();
		pGenotype->UpdateGenotypeStatistics();
	}
}

CGenotype* CPopulation::CombineGenotypes(CGenotype* pGenotype_a, CGenotype* pGenotype_b)
// Method CombineGentotypes performs copy-choice to produce a new genotype via a random cross-over point
{
	int iGenotypeLength = pGenotype_a->m_vPositionSet.size();
	int iCrossover = GetRandomNum(0, iGenotypeLength-1);
	CGenotype* pGenotype_c = new CGenotype();
	pGenotype_c->m_bNewRecombinant = true;

	for (int i = 0; i < iCrossover; i++)
	{
		CPosition * pNewPosition = new CPosition(pGenotype_a->m_vPositionSet[i]);
		pGenotype_c->m_vPositionSet.push_back(pNewPosition);
		pGenotype_c->m_mPositionMap[pNewPosition->m_iPosition] = pNewPosition;
	}

	for (int i = iCrossover; i < iGenotypeLength; i++)
	{
		CPosition * pNewPosition = new CPosition(pGenotype_b->m_vPositionSet[i]);
		pGenotype_c->m_vPositionSet.push_back(pNewPosition);
		pGenotype_c->m_mPositionMap[pNewPosition->m_iPosition] = pNewPosition;
	}
    
    pGenotype_c->UpdateGenotypeStatistics(); // Essential!
    
	return pGenotype_c;
}

void CPopulation::Replicate() 
// Continue to replicate genotypes within the population until end conditions are reached;
// specifically until burst size is reached. Extinction may occur upon the final
// consolidation due to removal of lethal genotypes, possibly leaving no viable genotypes.
// Assume that lethal genotypes may be replicated within a cell, but that upon burst any
// lethal genotype is not infective in the next round (passage).
{
	unsigned int iGenotypeCount = CountGenotypes(); // Update genotype count

	if(iGenotypeCount)
	{
		while (1) // 
		{
#ifdef PRINT_GENOTYPES
			cout << "Current Population's genotype set: " << endl;
			for(unsigned int z = 0; z < m_vGenotypeSet.size(); z++)
			{
				if(m_vGenotypeSet[z] == NULL)
					cout << "m_vGenotypeSet[z] is NULL at z = " << z << endl;
				else
					m_vGenotypeSet[z]->PrintGenotype();
			}
#endif
			PurgeDefectives(); // Remove some/all defective genotypes (with lethal mutation)
			if(!ReplicateOnce())
				break;
			if((m_iGenerationNum % iNUM_GENS_TO_CONSOLIDATE) == 0)
			{
				cout << "Consolidating at iNUM_GENS_TO_CONSOLIDATE" << endl;
				Consolidate();
			}
		}
		cout << "Performing final consolidation..." << endl;
		Consolidate();
	}
	else
	{
		cout << "WARNING: There are no genotypes to replicate" << endl;
	}
}

bool CPopulation::ReplicateOnce()
{
	UpdatePopulationStatistics();
    
	if(m_iNumOfGenotypes >= iBURST_SIZE)
	{
		cout << "Burst size reached. m_iNumOfGenotypes is " << m_iNumOfGenotypes << endl;
		return false;
	}
    
	++m_iGenerationNum;  // Increment generation number, even if no replication

	double dLimitingFactor = (double)(iBURST_SIZE - m_iNumOfGenotypes) / (iBURST_SIZE);
	int iNumOfNewGenotypes = (int)((double)m_iNumOfGenotypes * dGENERATIONAL_GROWTH * dLimitingFactor);
    
	// Reduce number of new genotypes so as not to exceed burst size;
	// ie, do not go beyond remaining resources
	if(iNumOfNewGenotypes + m_iNumOfGenotypes > iBURST_SIZE)
        iNumOfNewGenotypes = iBURST_SIZE - m_iNumOfGenotypes;
    
	// If nothing to replicate, get out of Dodge
	if(iNumOfNewGenotypes == 0)  // Nothing to replicate
	{
		cout << "WARNING: nothing to replicate in generation number " << m_iGenerationNum << endl;
		return false;
	}
    
	// Calculate how many new genotypes to produce (ie, how many replicates plus recombinants)	
	int iNumOfRecombinants = (int)((double)iNumOfNewGenotypes * dHOMOLOGOUS_RECOMBINATION_RATE);
	int iNumOfReplicates = iNumOfNewGenotypes - iNumOfRecombinants;

	vector<CGenotype*> vNewGenotypeSet; // Holds new genotypes, formed via replication or recombination

	// For recombinants, simulate copy choice mechanism of replication
	for(int i = 0; i < iNumOfRecombinants; i++) //
	{
		// Choose randomly which genotypes to combine
		int iGenotype_a = GetRandomNum(0, m_iNumOfGenotypes-1);
		int iGenotype_b = GetRandomNum(0, m_iNumOfGenotypes-1);

		// Assure they are physically different genomes
		while(iGenotype_a == iGenotype_b)
			iGenotype_b = GetRandomNum(0, m_iNumOfGenotypes-1);

		// Get the genotypes  
		CGenotype* pGenotype_a = SelectGenotype(iGenotype_a);
		CGenotype* pGenotype_b = SelectGenotype(iGenotype_b);
        
		// Combine the 2 genotypes using copy-choice mechanism
		CGenotype* pNewGenotype = CombineGenotypes(pGenotype_a, pGenotype_b); // Creates a new genotype
        
		pNewGenotype->m_bNewRecombinant = true;
		pNewGenotype->m_bMutatedReplicate = false;
		vNewGenotypeSet.push_back(pNewGenotype); // Add this new genotype to holding array
	}
    
	// For replicates, it's simpler
	for(int i = 0; i < iNumOfReplicates; i++)
	{
		int iGenotype = GetRandomNum(0, m_iNumOfGenotypes-1);
		CGenotype* pNewGenotype = new CGenotype(SelectGenotype(iGenotype),false); // create a new genotype
        
		pNewGenotype->m_bMutatedReplicate = true;
		pNewGenotype->m_bNewRecombinant = false;
        
		vNewGenotypeSet.push_back(pNewGenotype); // Add to new genotype list
	}
    
	// Apply random mutation to the new genotypes, then update fitness values (et al)
	MutateGenotypes(vNewGenotypeSet);
	for(int i = 0; i < vNewGenotypeSet.size(); i++)
	{
		vNewGenotypeSet[i]->UpdateGenotypeStatistics();
	}
   
	int iPotentialProgeny = 0;
	iPotentialProgeny = vNewGenotypeSet.size();
	int iNewGenotypeCount = 0;  // Count of how many new genotype are actually added to population
    
	// Update attributes of new genotypes and move them to m_vGenotypeSet
	CGenotype* pGenotype;
	for(unsigned int i = 0; i < vNewGenotypeSet.size(); i++)
	{
		pGenotype = vNewGenotypeSet[i];
		pGenotype->m_bNewRecombinant = false;
		pGenotype->m_bMutatedReplicate = false;
        
	        // Calculate how many of this genotype to produce based on fitness
	        // Note:  normally number of progeny = number of replicating genotypes, but code accommodates more progeny
	        // And...Not every genotype can become a parent--survival of the fittest!
	        int iProgenyCount = CalculateNumOfProgeny(pGenotype->m_dFitness_synergy, vNewGenotypeSet);
		if (iProgenyCount > 0)
		{
			pGenotype->m_iGenotypeCount = iProgenyCount;
			m_vGenotypeSet.push_back(pGenotype); // A bouncing baby genotype is born!
			iNewGenotypeCount += iProgenyCount;  // Update the "census"
		}
		else
		{
			delete pGenotype;
		}
	}
	vNewGenotypeSet.clear();  // Clean up
    
	// Total genotype count is increased by no. of newly replicated ones.	
	m_iNumOfGenotypes += iNewGenotypeCount;

	UpdatePopulationStatistics();
    
	return true;
}

