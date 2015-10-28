//============================================================================
// Name        : Qspp_main.cpp
// Author      : Carol L. Ecale Zhou
// Original    : May 2009
// Current     : 26 October 2015
// Version     : 1.2
// Copyright   : Copyright (C) 2015 Carol L. Ecale Zhou - All Rights Reserved.
// License     : See LICENSE.md for license information
//
// Description : 
//    Qspp is an agent-based stochastic simulation model. Being a simplified
//    version of an original model plan, it contains only 3 agents:  genotypes,
//    populations, and the quasispecies cloud. This model could be expanded to a
//    full-scale, parallel in-cell/cell-to-cell model. I am calling this a
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
//    are enumerated in FixedPosition.h. This current version, 1.2, implements
//    fitness, which is defined according to the neurovirulent Mahoney genotype.
//       The overall purpose of this model is to simulate the Sabin-to-Mahoney
//    transition and to study the genetic mechanisms that drive this transition.
//    This model can be used as a teaching tool for better understanding the
//    potential impact of changes in the frequencies of these known genetic
//    mechanisms.
//
//============================================================================

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
double        dGENERATIONAL_GROWTH           = GENERATIONAL_GROWTH;
double        dHOMOLOGOUS_RECOMBINATION_RATE = HOMOLOGOUS_RECOMBINATION_RATE;
unsigned long iBURST_SIZE                    = BURST_SIZE;
unsigned long iMULTIPLICITY_OF_INFECTION     = MULTIPLICITY_OF_INFECTION;
unsigned long iNUMBER_OF_PASSAGES            = NUMBER_OF_PASSAGES;
unsigned long iNUM_GENS_TO_CONSOLIDATE       = NUM_GENS_TO_CONSOLIDATE;
unsigned long iNUMBER_OF_POPULATIONS         = NUMBER_OF_POPULATIONS;
double        dFITNESS_ACCELERATOR           = FITNESS_ACCELERATOR;
int           iMAHONEY_THRESHOLD             = MAHONEY_THRESHOLD;
bool          bRETAIN_LETHALS                = true;
double        dMAHONEY_SYNERGY               = MAHONEY_SYNERGY;

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

// Other constants
unsigned long iNUMBER_SABIN1_POSITIONS       = 54;   // see FixedState.h
unsigned long iNUMBER_MAHONEY_POSITIONS      = 54;   // see FixedState.h

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
	pSabin->m_iGenotypeCount = iSABIN_COUNT;
	for(int i = 0; i < iNUMBER_OF_POPULATIONS; i++)
	{
		// Construct initial inoculum, comprising a pre-determined set of genotypes
		pInoculum = new CPopulation();

		// Add starting genotype to inoculum
		CGenotype * pNextStart = new CGenotype(pSabin,1);
		pInoculum->AddGenotype(pNextStart);  	
	
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
		//pCurCloud->PrintCloud();

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
			dGENERATIONAL_GROWTH = atof(argv[i+1]);
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
		else if(!strcmp(argv[i],"-a"))
			dFITNESS_ACCELERATOR = ((double)atof(argv[i+1]));
        else if(!strcmp(argv[i],"-t"))
            iMAHONEY_THRESHOLD = ((int)atoi(argv[i+1]));
        else if(!strcmp(argv[i],"-l"))
            bRETAIN_LETHALS = ((bool)atoi(argv[i+1]));
        else if(!strcmp(argv[i],"-s"))
            dMAHONEY_SYNERGY = ((double)atof(argv[i+1]));
	}
	cout << "Error rate = " << dERROR_RATE << endl;
	cout << "Generational growth rate = " << dGENERATIONAL_GROWTH << endl;
	cout << "Homologous recombination rate = " << dHOMOLOGOUS_RECOMBINATION_RATE << endl;
	cout << "Burst size = " << iBURST_SIZE << endl;
	cout << "Multiplicity of infection = " << iMULTIPLICITY_OF_INFECTION << endl;
	cout << "Number of passages = " << iNUMBER_OF_PASSAGES << endl;
	cout << "Number of generations to consolidate = " << iNUM_GENS_TO_CONSOLIDATE << endl;
	cout << "Number of populations = " << iNUMBER_OF_POPULATIONS << endl;
    cout << "Fitness accelerator = " << dFITNESS_ACCELERATOR << endl;
    cout << "Mahoney threshold (%) = " << iMAHONEY_THRESHOLD << endl;
    cout << "Retain lethals is " << (bRETAIN_LETHALS ? "true" : "false") << endl;

	cout << endl << "Creating initial genotypes..." << endl;
	
	// All of the following genotypes and fitness grids are configurable within FixedState.h
	// These must be created in order to drive a simulation
	
	// Sabin1, Mahoney, and Neurovirulent are based on literature
	pSabin1        = new CGenotype(Sabin1Positions, NUM_SABIN1_POSITIONS);
	pMahoney       = new CGenotype(MahoneyPositions, NUM_MAHONEY_POSITIONS);
	pNeurovirulent = new CGenotype(NeurovirulentPositions, NUM_NEUROVIRULENT_POSITIONS);
	
	// These are starting genotypes for running a simulation
	pSabin         = new CGenotype(Sabin1Positions, NUM_SABIN1_POSITIONS);
    
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
	cout << endl << "These are the relative fitness values: " << endl;
	pFitness->PrintFitness();

	cout << endl << "Running simulation..." << endl;
	Simulate();

	// Clean up
	delete pSabin1;
	delete pMahoney;
	delete pNeurovirulent;
	delete pSabin;  
	delete pFitness;
	
	return 0;
}
