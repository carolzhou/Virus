/* 
 * Population.cpp
 *
 *  Created on: May 7, 2009
 *  Last update: 16 April 2015
 *      Author: Carol L. Ecale Zhou
 *
 */

/*
Copyright (c) 2015, Lawrence Livermore National Security, LLC. Produced at the Lawrence Livermore National Laboratory. Written by Carol L. Ecale Zhou, zhou4@llnl.gov; carol.zhou@comcast.net. CODE-OCEC-15-045 All rights reserved. This file is part of Qspp. Please also read this link – Our Notice and GNU General Public License. 
This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License (as published by the Free Software Foundation) version 2, dated June 1991. 
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the IMPLIED WARRANTY OF MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the terms and conditions of the GNU General Public License for more details. 
You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 
OUR NOTICE AND TERMS AND CONDITIONS OF THE GNU GENERAL PUBLIC LICENSE 
Our Preamble Notice 
A. This notice is required to be provided under our contract with the U.S. Department of Energy (DOE). This work was produced at the Lawrence Livermore National Laboratory under Contract No. DE-AC52-07NA27344 with the DOE. 
B. Neither the United States Government nor Lawrence Livermore National Security, LLC nor any of their employees, makes any warranty, express or implied, or assumes any liability or responsibility for the accuracy, completeness, or usefulness of any information, apparatus, product, or process disclosed, or represents that its use would not infringe privately-owned rights. 
C. Also, reference herein to any specific commercial products, process, or services by trade name, trademark, manufacturer or otherwise does not necessarily constitute or imply its endorsement, recommendation, or favoring by the United States Government or Lawrence Livermore National Security, LLC. The views and opinions of authors expressed herein do not necessarily state or reflect those of the United States Government or Lawrence Livermore National Security, LLC, and shall not be used for advertising or product endorsement purposes. 
The precise terms and conditions for copying, distribution and modification follows. 
GNU Terms and Conditions for Copying, Distribution, and Modification 
_ 0. This License applies to any program or other work which contains a notice placed by the copyright holder saying it may be distributed under the terms of this General Public License. The “Program,” below, refers to any such program or work, and a “work based on the Program” means either the Program or any derivative work under copyright law: that is to say, a work containing the Program or a portion of it, either verbatim or with modifications and/or translated into another language. (Hereinafter, translation is included without limitation in the term “modification”.) Each licensee is addressed as “you.” 
_ Activities other than copying, distribution and modification are not covered by this License; they are outside its scope. The act of running the Program is not restricted, and the output from the Program is covered only if its contents constitute a work based on the Program (independent of having been made by running the Program). Whether that is true depends on what the Program does. 
_ 1. You may copy and distribute verbatim copies of the Program’s source code as you receive it, in any medium, provided that you conspicuously and appropriately publish on each copy an appropriate copyright notice and disclaimer of warranty; keep intact all the notices that refer to this License and to the absence of any warranty; and give any other recipients of the Program a copy of this License along with the Program. 
_ You may charge a fee for the physical act of transferring a copy, and you may at your option offer warranty protection in exchange for a fee. 
2 You may modify your copy or copies of the Program or any portion of it, thus forming a work based on the Program, and copy and distribute such modifications or work under the terms of Section 1 above, provided that you also meet all of these conditions: 
a) You must cause the modified files to carry prominent notices stating that you changed the files and the date of any change. 
b) You must cause any work that you distribute or publish, that in whole or in part contains or is derived from the Program or any part thereof, to be licensed as a whole at no charge to all third parties under the terms of this License. 
c) If the modified program normally reads commands interactively when run, you must cause it, when started running for such interactive use in the most ordinary way, to print or display an announcement including an appropriate copyright notice and a notice that there is no warranty (or else, saying that you provide a warranty) and that users may redistribute the program under these conditions, and telling the user how to view a copy of this License. (Exception: if the Program itself is interactive but does not normally print such an announcement, your work based on the Program is not required to print an announcement.) 
These requirements apply to the modified work as a whole. If identifiable sections of that work are not derived from the Program, and can be reasonably considered independent and separate works in themselves, then this License, and its terms, do not apply to those sections when you distribute them as separate work. But when you distribute the same section as part of a whole which is a work based on the Program, the distribution of the whole must be on the terms of this License, whose permissions for other licensees extend to the entire whole, and thus to each and every part regardless of who wrote it. 
Thus, it is not the intent of this section to claim rights or contest your rights to work written entirely by you; rather, the intent is to exercise the right to control the distribution of derivative or collective works based on the Program. 
In addition, mere aggregation of another work not based on the Program with the Program (or with a work based on the Program) on a volume of a storage or distribution medium does not bring the other work under the scope of this License. 
3. You may copy and distribute the Program (or a work based on it, under Section 2) in object code or executable form under the terms of Sections 1 and 2 above provided that you also do one of the following: 
a) Accompany it with the complete corresponding machine-readable source code, which must be distributed under the terms of Sections 1 and 2 above on a medium customarily used for software interchange; or, 
b) Accompany it with a written offer, valid for at least three years, to give any third party, for a charge no more than your cost of physically performing source distribution, a complete machine-readable copy of the corresponding source code, to be distributed under the terms of Sections 1 and 2 above on a medium customarily used for software interchange; or, 
c) Accompany it with the information you received as to the offer to distribute corresponding source code. (This alternative is allowed only for noncommercial distribution and only if you received the program in object code or executable form with such an offer, in accord with Subsection b above.) 
The source code for a work means the preferred form the work for making modifications to it. For an executable work, complete source code means all the source code for all modules it contains, plus any associated interface definition files, plus the scripts used to control compilation and installation of the executable. However, as a special exception, the source code distributed need not include anything that is normally distributed (in either source or binary form) with the major components (compiler, kernel, and so on) of the operating system on which the executable runs, unless that component itself accompanies the executable. 
If distribution of executable or object code is made by offering access to copy from a designated place, then offering equivalent access to copy the source code from the same place counts as distribution of the source code, even though third parties are not compelled to copy the source along with the object code. 
4. You may not copy, modify, sublicense, or distribute the Program except as expressly provided under this License. Any attempt otherwise to copy, modify, sublicense or distribute the 
Program is void, and will automatically terminate your rights under this License. However, parties who have received copies, or rights, from you under this License will not have their licenses terminated so long as such parties remain in full compliance. 
2 You are not required to accept this License, since you have not signed it. However, nothing else grants you permission to modify or distribute the Program or its derivative works. These actions are prohibited by law if you do not accept this License. Therefore, by modifying or distributing the Program (or any work based on the Program), you indicate your acceptance of this License to do so, and all its terms and conditions for copying, distributing or modifying the Program or works based on it. 
3 Each time you redistribute the Program (or any work based on the Program), the recipient automatically receives a license from the original licensor to copy, distribute or modify the Program subject to these terms and conditions. You may not impose any further restrictions on the recipients’ exercise of the rights granted herein. You are not responsible for enforcing compliance by third parties to this License. 
4 If, as a consequence of a court judgment or allegation of patent infringement or for any other reason (not limited to patent issues), conditions are imposed on you (whether by court order, agreement or otherwise) that contradict the conditions of this License, they do not excuse you from the conditions of this License. If you cannot distribute so as to satisfy simultaneously your obligations under this License and any other pertinent obligations, then as a consequence you may not distribute the Program at all. For example, if a patent license would not permit royalty-free redistribution of the Program by all those who receive copies directly or indirectly through you, then the only way you could satisfy both it and this License would be to refrain entirely from distribution of the Program. 
If any portion of this section is held invalid or unenforceable under any particular circumstance, the balance of the section is intended to apply and the section as a whole is intended to apply in other circumstances. 
It is not the purpose to this section to induce you to infringe any patents or other property right claims or to contest validity of any such claims; this section has the sole purpose of protecting the integrity of the free software distribution system, which is implemented by public license practices. Many people have made generous contributions to the wide range of software distributed through that system in reliance on consistent application of that system; it is up to the author/donor to decide if he or she is willing to distribute software through any other system and a licensee cannot impose that choice. 
This section is intended to make thoroughly clear what is believed to be a consequence of the rest of this License. 
1 If the distribution and/or use of the Program is restricted in certain countries either by patents or by copyrighted interfaces, the original copyright holder who places the Program under this License may add an explicit geographical distribution limitation excluding those countries, so that distribution is permitted only in or among countries not thus excluded. In such case, this License incorporates the limitation as if written in the body of this License. 
9. The Free Software Foundation may publish revised and/or new versions of the General Public License from time to time. Such new versions will be similar in spirit to the present version, but may differ in detail to address new problems or concerns. 
Each version is given a distinguishing version number. If the Program specifies a version number of this License which applies to it and “any later version,” you have the option of following the terms and conditions either of that version of any later version published by the Free Software Foundation. If the Program does not specify a version number of this License, you may choose any version ever published by the Free Software Foundation. 
2 If you wish to incorporate parts of the Program into other free programs whose distribution conditions are different, write to the author to ask for permission. For software which is copyrighted by the Free Software Foundation, write to the Free Software Foundation; we sometimes make exceptions for this. Our decision to grant permission will be guided by the two goals of preserving the free status of all derivatives of our free software and or promoting the sharing and reuse of software generally. 
NO WARRANTY 
11. BECAUSE THE PROGRAM IS LICENSED FREE OF CHARGE, THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF 
THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION. 
2 IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY AND/OR REDISTRIBUTE THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY GENERAL, SPECIAL INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. 
END OF TERMS AND CONDITIONS
*/

#include <iostream>
#include <set>
#include <time.h>
#include "Population.h"

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

#define PRINT_POPULATION_IN_DETAIL
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
#ifdef PRINT_POPULATION_IN_DETAIL
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

bool CPopulation::IsMahoney() // Reports whether any genotype resembles Mahoney in sequence
{

	bool bMahoney = false;	
	int iMahoneyCount = 0;

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
		}
	}
	m_bMahoney = bMahoney;
	m_iNumOfMahoneyGenotypes = iMahoneyCount;

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

bool CPopulation::OddsAreInFavor(CGenotype* pGenotype)
{
	int iMAX_RANDOM = 8;  // Set to positive integer
	bool bOdds = 1;
	double dAverageFitness = CalculatePopulationFitness();
	double dFitness = pGenotype->CalculateFitness();

	// Calculate odds using simple formula: step-linear relationship based on pop average
	int iRandomNum = GetRandomNum(0, iMAX_RANDOM-1);
	double dFitnessFactor = 2.0 * dAverageFitness * ((double)iRandomNum / (double)iMAX_RANDOM);

	if(dFitnessFactor < dAverageFitness)
	{
		bOdds = 0; 
	}

	return bOdds;
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
	// Then, update the population statistics	
	IsMahoney();
	IsNeurovirulent();
	IsExtinct();
	CalculatePopulationFitness();
}

void CPopulation::ReportPopulationStatistics()
{
	double dAveNeurovirulentIndex = 0.0;

	cout << "Population Statistics: " << endl;
	cout << "Absolute number of genotypes in this population: " << m_iNumOfGenotypes << endl;
	int iDistinctCount = m_vGenotypeSet.size();
	cout << "Number of distinct genotypes: " << iDistinctCount << endl;
	cout << "Max genotype count " << m_iGenotypeMaxCount << endl;;
	cout << "Number of neurovirulent genotypes: " << m_iNumOfNeurovirulentGenotypes << endl;
	if(m_iNumOfNeurovirulentGenotypes)
		dAveNeurovirulentIndex = (double)m_iNeurovirulentIndex / (double)m_iNumOfNeurovirulentGenotypes;
	cout << "Neurovirulence index: " << m_iNeurovirulentIndex << endl;
	cout << "Average neurovirulence: " << dAveNeurovirulentIndex << endl;
	cout << "Number of Mahoney genotypes: " << m_iNumOfMahoneyGenotypes << endl;
	cout << "Number of defective genotypes: " << m_iNumOfDefectiveGenotypes << endl;
	cout << "Average genotype fitness: " << m_dAverageFitness << endl;
	cout << "This population is " << (m_bExtinct ? "EXTINCT" : "Viable") << endl;
	cout << endl;
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
				cout << "A LETHAL genotype has been detected during consolidation " << endl;
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
		PrintPopulation();
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
	int iNumOfMutations = (int)((double)iNumOfPositions * dERROR_RATE); // ***check rounding; calc is naive: ok if iNumOfMutations is large (as in a simulation)
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
		//pGenotype->UpdateGenotypeStatistics(); //Note: update when essential; updating now costs time
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
			cout << "Current Population's genotype set: " << endl;
			for(unsigned int z = 0; z < m_vGenotypeSet.size(); z++)
			{
				if(m_vGenotypeSet[z] == NULL)
					cout << "m_vGenotypeSet[z] is NULL at z = " << z << endl;
				else
					m_vGenotypeSet[z]->PrintGenotype();
			}
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

	// LimitingFactor is a measure of remaining resources
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

	// *** To implement fitness, determine odds of successful replication based on fitness 
	// Then, replicate yes/no based on random event: higher fittness increases odds 
	// And keep track of how many new genotypes were actually replicated
	int iNewGenotypesReplicated = 0;

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
		if(OddsAreInFavor(pNewGenotype)) // Based on fitness
                {
			vNewGenotypeSet.push_back(pNewGenotype); // Add this new genotype to holding array
			iNewGenotypesReplicated++;
		}
	}

	// For replicates, it's simpler
	for(int i = 0; i < iNumOfReplicates; i++)
	{
		int iGenotype = GetRandomNum(0, m_iNumOfGenotypes-1);
		CGenotype* pNewGenotype = new CGenotype(SelectGenotype(iGenotype),false); // create a new genotype
                if(OddsAreInFavor(pNewGenotype)) // Based on fitness
		{
			vNewGenotypeSet.push_back(pNewGenotype); // Add to new genotype list (holding array)
			iNewGenotypesReplicated++;
		}
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
	//m_iNumOfGenotypes += iNumOfNewGenotypes; 
	m_iNumOfGenotypes += iNewGenotypesReplicated; 
	return true;
}

