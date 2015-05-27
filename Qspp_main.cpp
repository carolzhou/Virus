//============================================================================
// Name        : Qspp_main.cpp
// Author      : Carol L. Ecale Zhou
// Original    : May 2009
// Current     : 25 March 2015
// Version     : 1.1
// Copyright   : see below
//
// Description : 
//    Qspp is an agent-based stochastic simulation model. Being a simplified
//    version of an original model plan, it contains only 3 agents:  genotypes,
//    populations, and the quasispecies cloud. This model could be expanded to a
//    full-scale, agent-based in-cell/cell-to-cell model. I am calling this a 
//    "transition model", as it models the Sabin to Mahoney genetic transition.
//    Sabin is an attenuated strain of poliovirus that was the basis for the
//    original polio vaccine. It is non-virulent, although it has potential to
//    mutate into a virulent state, specifically by means of reversion at any of
//    54 nucleotide positions distributed along the genome. Some of the nucleotide
//    differences between Sabin and Mahoney (the wide type) confer neurovirulence,
//    and thus are of particular interest.
//       This code simulates a cell-to-cell model of Poliovirus replication.
//    The model tracks genotypes (virus genomes) as they are replicated in cells, and
//    as the cells burst and release particles into the medium of a culture dish. An
//    inoculum is then taken from the pool of virions and used to inoculate cells on
//    a new dish.  This process repeates. The simulation is greatly simplified, as the
//    code models only the 54 positions that differ between the Sabin and Mahoney
//    strains, and the only cellular components are the genotypes. Various parameters
//    are controlled by the programmer (e.g., burst size, inoculum size, number of
//    generations). Genetic variability is achieved by random nucleotide mutation and
//    copy-choice replication. Indels are not modeled.  
//       Version 1 of this model is designed to simulate the transition from Sabin
//    to Mahoney. Thus, the Sabin genotype comprises the initial inoculum.
//    Nucleotide positions that match neurovirulence (from the literature)
//    are enumerated in FixedPosition.h. This current version, 1.1, 
//    is unconstrained, meaning that there are no data that determine when a random
//    mutation is lethal vs. neutral vs. beneficial. Therefore, the quasispecies cloud
//    continues to diversify as replication and passaging proceeds.
//       The overall purpose of this model is to simulate the Sabin-to-Mahoney
//    transition and to study the genetic mechanisms that drive this transition.
//    This model can be used as a teaching tool for better understanding the
//    potential impact of changes in the frequencies of these known genetic
//    mechanisms.
//
//============================================================================

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
#include <stdlib.h>
#include <string.h>
#include <typeinfo>
#include "FixedState.h"
#include "Configurable.h"  
#include "Cloud.h"

#define QSPP_TESTING

using namespace std; // 

// General
#define TRUE 1
#define FALSE 0

// Global
bool          bREMOVE_LETHALS = FALSE;

// Initialize according to defaults listed in Configurable.h 
// And modifiable by user at command line
double        dERROR_RATE                    = ERROR_RATE;
double        iGENERATIONAL_GROWTH           = GENERATIONAL_GROWTH;
double        dHOMOLOGOUS_RECOMBINATION_RATE = HOMOLOGOUS_RECOMBINATION_RATE;
unsigned long iBURST_SIZE                    = BURST_SIZE;
unsigned long iMULTIPLICITY_OF_INFECTION     = MULTIPLICITY_OF_INFECTION;
unsigned long iNUMBER_OF_PASSAGES            = NUMBER_OF_PASSAGES;
unsigned long iNUM_GENS_TO_CONSOLIDATE       = NUM_GENS_TO_CONSOLIDATE;
unsigned long iNUMBER_OF_POPULATIONS         = NUMBER_OF_POPULATIONS;

// Not yet in service
unsigned long iGENERATION_DEPTH              = GENERATION_DEPTH;
double        dFIXATION_RATE                 = FIXATION_RATE;
double        dMUTATIONAL_PREFERENCE         = MUTATIONAL_PREFERENCE;
unsigned long iGENERATIONS_PER_CELL          = GENERATIONS_PER_CELL;
unsigned long iCELL_DENSITY                  = CELL_DENSITY;
double        dTRANSITION_RATE               = TRANSITION_RATE;
double        dTRANSVERSION_RATE             = TRANSVERSION_RATE;
unsigned long iINFECTION_CYCLES              = INFECTION_CYCLES;
unsigned long iFIXED_RESOURCES               = FIXED_RESOURCES;
unsigned long iFIXED_SPACE                   = FIXED_SPACE;

// There need only exist 1 of each standard genotype
unsigned long iSABIN1_COUNT        = SABIN1_COUNT;        // Standard
unsigned long iMAHONEY_COUNT       = MAHONEY_COUNT;       // Standard
unsigned long iNEUROVIRULENT_COUNT = NEUROVIRULENT_COUNT; // Standard

// These variables control composition of initial inoculum
unsigned long iSABIN_COUNT         = SABIN_COUNT;         // For inoculum
unsigned long iFOOBAR1_COUNT       = FOOBAR1_COUNT;       // For inoculum 
unsigned long iFOOBAR2_COUNT       = FOOBAR2_COUNT;       // For inoculum
unsigned long iFOOBAR3_COUNT       = FOOBAR3_COUNT;       // For inoculum

// The following genotypes are defined in FixedState.h and declared extern in Genotype.h
CGenotype* pSabin1;        // Standard
CGenotype* pMahoney;       // Standard
CGenotype* pNeurovirulent; // Standard
CGenotype* pSabin;         // for inoculum
CGenotype* pFoobar1;       // For inoculum
CGenotype* pFoobar2;       // For inoculum
CGenotype* pFoobar3;       // For inoculum

// The following fitness objects guide genotype selection for subsequent replication
CFitness* pFitness;        // Standard fitness based on Mahoney/Neurovirulence

void Simulate(void)
{
	CPopulation* pInoculum = NULL;
	CCloud* pPrevCloud = NULL;
	CCloud* pCurCloud = new CCloud;

	cout << "Starting Qspp simulation..." << endl;

	// construct the initial inoculum and cloud
	for(int i = 0; i < iNUMBER_OF_POPULATIONS; i++)
	{
		// Construct initial inoculum, comprising a pre-determined set of genotypes
		pInoculum = new CPopulation();

		pSabin->m_iGenotypeCount   = iSABIN_COUNT;
		pFoobar1->m_iGenotypeCount = iFOOBAR1_COUNT;
		pFoobar2->m_iGenotypeCount = iFOOBAR2_COUNT;
		pFoobar3->m_iGenotypeCount = iFOOBAR3_COUNT;
	
		pInoculum->AddGenotype(pSabin);  	
		//pInoculum->AddGenotype(pFoobar1);  	
		//pInoculum->AddGenotype(pFoobar2);  	
		//pInoculum->AddGenotype(pFoobar3);  	
	
		// Each population (cell model) receives this inoculum	
		pCurCloud->AddPopulation(pInoculum); // Add inoculum (population object) to cloud
	}	
	
	// Passage iNUMBER_OF_PASSAGES times (ie, that many cycles plus 1) 
	// Passage 0 is the initial plate 
	for(unsigned int i = 0; i <= iNUMBER_OF_PASSAGES; i++)
	{
		if(i != 0) // Skip first time through
		{
			// Re-inoculation:
			// If not the first cycle, pick new inoculum from previous cloud
			// and create new cloud from new inoculum
			pPrevCloud = pCurCloud;
			pCurCloud = new CCloud;
			
			for(unsigned int j = 0; j < iNUMBER_OF_POPULATIONS; j++)
			{
				pInoculum = pPrevCloud->PickInoculum(iMULTIPLICITY_OF_INFECTION);
				pCurCloud->AddPopulation(pInoculum);
			}
			delete pPrevCloud;
		}
		cout << endl << "********** Passage " << i << " Inoculum **********" << endl;
		pCurCloud->PrintCloud();

		cout << "Growing..." << endl;
		pCurCloud->Grow();
		cout << "Bursting..." << endl;
		pCurCloud->Burst();

		cout << endl << "Passage " << i << " Final cloud" << endl;
		pCurCloud->PrintCloud();
		cout << endl << "Conclusion of Passage " << i << " Data" << endl;
	}
	delete pCurCloud;
	
	cout << endl << "Simulation complete." << endl;
}

int main(int argc, char* argv[])
{
	// Read input parameters (if any)
	cout << "Your input parameters are: " << endl;
	if(argc == 1)
		cout << "none provided, using defaults" << endl;
	for(unsigned int i = 1; i < argc; i++)
	{
		if(!strcmp(argv[i],"-e"))
			dERROR_RATE = atof(argv[i+1]);
		else if(!strcmp(argv[i],"-g"))
			iGENERATIONAL_GROWTH = atof(argv[i+1]);
		else if(!strcmp(argv[i],"-r"))
			dHOMOLOGOUS_RECOMBINATION_RATE = atof(argv[i+1]);
		else if(!strcmp(argv[i],"-b"))
			iBURST_SIZE = ((unsigned)atol(argv[i+1]));
		else if(!strcmp(argv[i],"-i"))
			iMULTIPLICITY_OF_INFECTION = ((unsigned)atol(argv[i+1]));
		else if(!strcmp(argv[i],"-p"))
			iNUMBER_OF_PASSAGES = ((unsigned)atol(argv[i+1]));
		else if(!strcmp(argv[i],"-c"))
			iNUM_GENS_TO_CONSOLIDATE = ((unsigned)atol(argv[i+1]));
		else if(!strcmp(argv[i],"-P"))
			iNUMBER_OF_POPULATIONS = ((unsigned)atol(argv[i+1]));
	}
	cout << "Error rate = " << dERROR_RATE << endl;
	cout << "Generational growth rate = " << iGENERATIONAL_GROWTH << endl;
	cout << "Homologous recombination rate = " << dHOMOLOGOUS_RECOMBINATION_RATE << endl;
	cout << "Burst size = " << iBURST_SIZE << endl;
	cout << "Multiplicity of infection = " << iMULTIPLICITY_OF_INFECTION << endl;
	cout << "Number of passages = " << iNUMBER_OF_PASSAGES << endl;
	cout << "Number of generations to consolidate = " << iNUM_GENS_TO_CONSOLIDATE << endl;
	cout << "Number of populations = " << iNUMBER_OF_POPULATIONS << endl;

	cout << endl << "Creating initial genotypes..." << endl;
	
	// All of the following genotypes and fitness grids are configurable within FixedState.h
	// These must be created in order to drive a simulation
	
	// Sabin1, Mahoney, and Neurovirulent are based on literature
	pSabin1        = new CGenotype(Sabin1Positions, NUM_SABIN1_POSITIONS);
	pMahoney       = new CGenotype(MahoneyPositions, NUM_MAHONEY_POSITIONS);
	pNeurovirulent = new CGenotype(NeurovirulentPositions, NUM_NEUROVIRULENT_POSITIONS);
	
	// These are starting genotypes for running a simulation
	pSabin         = new CGenotype(Sabin1Positions, NUM_SABIN1_POSITIONS);  
	pFoobar1       = new CGenotype(Foobar1Positions, NUM_FOOBAR1_POSITIONS);
	pFoobar2       = new CGenotype(Foobar2Positions, NUM_FOOBAR2_POSITIONS);
	pFoobar3       = new CGenotype(Foobar3Positions, NUM_FOOBAR3_POSITIONS);

	// Creating Fitness based on Mahoney and Neurovirulence
	//pFitness = new CFitness(Fitness1Positions, NUM_FITNESS1_POSITIONS);
	pFitness = new CFitness(Fitness3Positions, NUM_FITNESS3_POSITIONS);
	
	// Print starting data for this simulation
	cout << endl << "These are the standard genotypes: ";
	cout << endl << "Mahoney:       ";
	pMahoney->PrintGenotype();
	cout << endl << "Sabin1:        ";
	pSabin1->PrintGenotype();
	cout << endl << "Neurovirulent: ";
	pNeurovirulent->PrintGenotype();
	cout << endl << "These are the simulation genotypes: ";
	cout << endl << "Sabin_a:         ";
	pSabin->PrintGenotype();
	cout << endl << "Foobar1:       ";
	pFoobar1->PrintGenotype();
	cout << endl << "Foobar2:       ";
	pFoobar2->PrintGenotype();
	cout << endl << "Foobar3:       ";
	pFoobar3->PrintGenotype();
	cout << endl << "These are the relative fitness values: " << endl;
	pFitness->PrintFitness();

	cout << endl << "Running simulation..." << endl;
	Simulate();

	// Clean up
	delete pSabin1;
	delete pMahoney;
	delete pNeurovirulent;
	delete pSabin;
	delete pFoobar1;
	delete pFoobar2;
	delete pFoobar3;
	delete pFitness;
	
	return 0;
}
