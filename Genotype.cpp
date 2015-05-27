/*
 * Genotype.cpp
 *
 *  Created on: Apr 16, 2009
 *  Last update:  25 March 2015
 *      Author: Carol Zhou
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
#include <typeinfo>
#include "Genotype.h"

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
	m_bLethal = pGenotype->m_bLethal; // Note: lethal genotype is removed at consolidation; until then, genotype exists
	m_iPositionCount = pGenotype->m_iPositionCount;
	m_iSelectionCount = 0;
	m_dFitness = pGenotype->m_dFitness;
	
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

//#define PRINT_GENOTYPE_IN_DETAIL
void CGenotype::PrintGenotype()
{
	for(unsigned int i = 0; i < m_vPositionSet.size(); i++)
	{
		m_vPositionSet[i]->PrintPosition();
	}
	cout << "  " << m_iGenotypeCount << endl;

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
	IsSabin1();
	IsMahoney();
	IsNeurovirulent();
	CalculateFitness();
	IsLethal();
}

void CGenotype::ReportGenotypeStatistics()
{
	PrintGenotype();	
	cout << "Genotype Statistics: " << endl;
	cout << "Number of genotypes with this sequence: " << m_iGenotypeCount << endl;
	cout << "Positions with Mahoney identity: " << m_iMahoneyCount << endl;
	cout << "Positions with Sabin1 identity: " << m_iSabin1Count << endl;
	cout << "Neurovirulence status: " << (m_bNeurovirulent ? "NEUROVIRULENT" : "benign") << endl;
	cout << "Positions that confer neurovirulence: " << m_iNeurovirulentCount << endl;
	cout << "Relative degree of neurovirulence: " << m_iNeurovirulentIndex << endl;
	cout << "Genotype fitness: " << m_dFitness << endl;
	cout << "Viability: " << (m_bLethal ? "LETHAL" : "viable") << endl;
	cout << endl;
}

double CGenotype::CalculateFitness()
// Returns genotype fitness measure. Note: genotype will have a positive fitness
// value even if it has a lethal mutation (see IsLethal()). 
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
	m_dFitness = dGenotypeFitness;  // Update at genotype level
	return dGenotypeFitness;
}

bool CGenotype::IsLethal() //CHECK: re-write inspecting fitness at each position (code from UpdateGenotypeStatistics())
{
	bool bLethal = false;  // True if any position has a lethal mutation  
	char cNucleotide;
	double dPositionFitness = 0.0;
	std::vector<SFitness*>::iterator it;
	CPosition* nextPosition = NULL;

	// Zero fitness at any position spells death for the genotype
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
	if(iSabin1Count >= 54) // CHECK: should not hard code here
		bSabin = true;

	m_bSabin1 = true; // Update at genotype level
	m_iSabin1Count = iSabin1Count;
	return bSabin;
}

bool CGenotype::IsMahoney() 
{
	int iMahoneyCount = 0;  // Number of positions that have reverted to Mahoney
	bool bMahoney = false;  // Assume false to start
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
	if(iMahoneyCount >= 54) // CHECK: should not hard code here
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

