/* 
 * Population.cpp
 *
 *  Created on: May 7, 2009
 *  Last update: 16 April 2015
 *      Author: Carol L. Ecale Zhou
 *
 */

#include <iostream>
#include <set>
#include <time.h>
#include "Population.h"

// Conditional compilation
//#define PRINT_POPULATION
#define PRINT_POPULATION_IN_DETAIL
//#define PRINT_GENOTYPE_STATS
//#define PRINT_GENOTYPES
//#define PRINT_DETAIL
#define BRIEF_REPORT

using namespace std;

extern double        iGENERATIONAL_GROWTH;
extern unsigned long iBURST_SIZE;
extern double        dERROR_RATE;
extern double        dHOMOLOGOUS_RECOMBINATION_RATE;
extern unsigned long iNUM_GENS_TO_CONSOLIDATE;
extern bool          bREMOVE_LETHALS;

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
	m_iGenotypeMaxCount = 0;
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
			m_vGenotypeSet[i]->PrintGenotype();
#ifdef PRINT_GENOTYPE_STATS
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
				iNeurovirulentIndex += m_vGenotypeSet[i]->m_iNeurovirulentIndex;
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
	m_bMahoney = bMahoney;
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
}

int CPopulation::ReportPopulationStatistics()
{
	UpdatePopulationStatistics(); // *** Testing:  Should not be necessary
	double dAveNeurovirulentIndex = 0.0;
	if(m_iNumOfNeurovirulentGenotypes)
	{
		dAveNeurovirulentIndex = (double)m_iNeurovirulentIndex / (double)m_iNumOfNeurovirulentGenotypes;
	}
	int iDistinctCount = m_vGenotypeSet.size();

	cout << "Population Statistics: " << endl;

#ifdef BRIEF_REPORT
	cout << "Pstats: " << m_iNumOfGenotypes << ' ' << iDistinctCount << ' ' << endl;
	cout << "Ngia: " << m_iNumOfNeurovirulentGenotypes << ' ' << m_iNeurovirulentIndex << ' ' << dAveNeurovirulentIndex << ' ' << endl;
	cout << "Mgpr: " << m_iNumOfMahoneyGenotypes << ' ' << m_iNumOfMahoneyPositions << ' ' << m_dMahoneyReversionIndex << ' ' << endl;
	cout << "DFV: " << m_iNumOfDefectiveGenotypes << ' ' << m_dAverageFitness << ' ' << (m_bExtinct ? "EXTINCT" : "Viable") << ' ';  
	cout << endl;
	return(0);
#endif
	cout << "Absolute number of genotypes in this population: " << m_iNumOfGenotypes << endl;
	cout << "Number of distinct genotypes: " << iDistinctCount << endl;
	cout << "Max genotype count " << m_iGenotypeMaxCount << endl;;
	cout << "Number of neurovirulent genotypes: " << m_iNumOfNeurovirulentGenotypes << endl;
	cout << "Neurovirulence index: " << m_iNeurovirulentIndex << endl;
	cout << "Average neurovirulence: " << dAveNeurovirulentIndex << endl;
	cout << "Number of Mahoney genotypes: " << m_iNumOfMahoneyGenotypes << endl;
	cout << "Number of Mahoney mutations in population: " << m_iNumOfMahoneyPositions << endl;
	cout << "Mahoney reversion index: " << m_dMahoneyReversionIndex << endl;
	cout << "Number of defective genotypes: " << m_iNumOfDefectiveGenotypes << endl;
	cout << "Average genotype fitness over population: " << m_dAverageFitness << endl;
	cout << "This population is " << (m_bExtinct ? "EXTINCT" : "Viable") << endl;
	cout << endl;
	return(0);
}

void CPopulation::Consolidate(void) // Remove redundancy in genotype list; collapse equivalents
// Method Consolidate removes all redundant genotype objects, thereby consolidating the list
// Each genotype object is moved to a holding list.  Then,
// it is compared to all remaining genotypes to determine if redundancy can be collapsed,
// which is accomplished by summing the counts between the two genotype objects.
// Also, genotypes with a lethal (fitness = 0.0) mutation are removed. 
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
		else // Retain genotype as long as it does not have a lethal mutation
		{
			if(vNewGenotypeSet[i]->IsLethal() && bREMOVE_LETHALS)  
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
	unsigned long iTotal = 0;
	for(unsigned int i = 0; i < m_vGenotypeSet.size(); i++)
	{
		if(m_vGenotypeSet[i] == NULL)
		{
			cout << "WARNING:  m_vGenotypeSet[i] is NULL at i = " << i << endl;
		}
		else
		{
			iTotal += m_vGenotypeSet[i]->m_iGenotypeCount;
		}
	}
	m_iNumOfGenotypes = iTotal;

	// Update absolute genotype count, including defective/lethal
	if(m_iGenotypeMaxCount < m_iNumOfGenotypes) 
		m_iGenotypeMaxCount = m_iNumOfGenotypes;

	return iTotal;
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
	int iNumOfMutations = (int)((double)iNumOfPositions * dERROR_RATE); // ***check rounding; calc is naive: ok if iNumOfMutations is large (as in a sim)
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
		//pGenotype->UpdateGenotypeStatistics();
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
			if(!ReplicateOnce())
				break;
			if((m_iGenerationNum % iNUM_GENS_TO_CONSOLIDATE) == 0)
			{
				cout << "Consolidating at iNUM_GENS_TO_CONSOLIDATE" << endl;
				bREMOVE_LETHALS = FALSE; // Be sure not to remove lethals just yet
				Consolidate();
			}
		}
		cout << "Performing final consolidation..." << endl;
		bREMOVE_LETHALS = TRUE;  // Remove lethals after all replication is done
		Consolidate();
		bREMOVE_LETHALS = FALSE;  // reset as default
	}
	else
	{
		cout << "WARNING: There are no genotypes to replicate" << endl;
	}
}

bool CPopulation::ReplicateOnce()
{
	if(m_iNumOfGenotypes >= iBURST_SIZE)
	{
		cout << "Burst size reached. m_iNumOfGenotypes is " << m_iNumOfGenotypes << endl;
		return false;
	}
	
	++m_iGenerationNum;  // Increment generation number, even if no replication

	double dLimitingFactor = (double)(iBURST_SIZE - m_iNumOfGenotypes) / (iBURST_SIZE);
	int iNumOfNewGenotypes = (int)((double)m_iNumOfGenotypes * iGENERATIONAL_GROWTH * dLimitingFactor); 

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
		vNewGenotypeSet.push_back(pNewGenotype); // Add this new genotype to holding array
	}

	// For replicates, it's simpler
	for(int i = 0; i < iNumOfReplicates; i++)
	{
		int iGenotype = GetRandomNum(0, m_iNumOfGenotypes-1);
		CGenotype* pNewGenotype = new CGenotype(SelectGenotype(iGenotype),false); // create a new genotype
		vNewGenotypeSet.push_back(pNewGenotype); // Add to new genotype list
	}
	for(int j = 0; j < vNewGenotypeSet.size(); j++)
		vNewGenotypeSet[j]->PrintGenotype();

	// Apply random mutation to the new genotypes  
	MutateGenotypes(vNewGenotypeSet); 

	// Update attributes of new genotypes and move them to m_vGenotypeSet
	CGenotype* pGenotype;
	for(unsigned int i = 0; i < vNewGenotypeSet.size(); i++)
	{
		pGenotype = vNewGenotypeSet[i];
		pGenotype->m_bNewRecombinant = false;
		pGenotype->m_bMutatedReplicate = false;
		m_vGenotypeSet.push_back(pGenotype); // A new object is added
	}
	vNewGenotypeSet.clear();  // Clean up

	// Total genotype count is increased by no. of newly replicated ones.	
	m_iNumOfGenotypes += iNumOfNewGenotypes; 
	return true;
}

