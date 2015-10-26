/*
 * Cloud.h
 *
 *  Created on: May 7, 2009
 *  Last update: 25 March 2015
 *      Author: Carol L. Ecale Zhou
 *
 */

#ifndef CLOUD_H_
#define CLOUD_H_

//#include "RandomC.h"
#include "Population.h"

class CCloud {

public:
	CCloud();                 // Input: inoculum; later add: burstSize, generationDepth, mutationRate, recombinationRate,
	virtual ~CCloud();

	// methods	
	void AddPopulation(CPopulation* pPopulation);
	void Grow();                  // Proceed with replication
	void Burst();                 // Deconstruct populations, consolidate to super-population
	CPopulation* PickInoculum(int iInoculumSize);  // Randomly select a small set of genotypes from super-pop
	void PrintCloud();            // Enumerates the Population in detail (for development/debugging/logging)
	void UpdateCloudStatistics(); // Computes Cloud statistics: neurovirulence, reversion to Mahoney
	int ReportCloudStatistics();  // Provides statistical information about Cloud 

	// data members
	CPopulation*         m_pSuperPopulation;         // Holds all Cloud genotypes after burst
	vector<CPopulation*> m_vPopulationSet;           // List of current replicating populations (each in a cell)
	bool                 m_bInfectionCyclesReached;  // true when num cell infection cycles has been reached (may be 1)
	bool                 m_bNeurovirulent;           // true if any genotype is neurovirulent
	bool                 m_bMahoney;                 // true if any genotype has reverted to Mahoney 
	unsigned long        m_iCensus;                  // number of genotypes in Cloud
};

#endif /* CLOUD_H_ */
