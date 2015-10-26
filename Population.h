/*
 * Population.h
 *
 *  Created on: May 7, 2009
 *  Last update: 26 October 2015
 *      Author: Carol L. Ecale Zhou
 *
 *  Description:  The Population class is the focus of cellular genome replication. It is managed by class Cloud.
 *  The Population class manages replication, mutation, and recombination of genotypes.  It inputs an
 *  inoculum (representing an initial set of genotypes infecting a cell), and outputs a set of genotypes that exist
 *  once replication has ceased.  Replication ceases when a set number of replication cycles have concluded, or when
 *  a maximum number of genotypes has been reached (representing cell burst). In the absence of a Cell class, the
 *  Population class is essentially the in-cell model of virus replication, but with only the genotype agent, and
 *  lacking all other agents (e.g., ribosomes, peptides).  In an actual simulation, a single  population object should
 *  run its course on a single processor.  The object that manages populations (Cloud) distributes population objects
 *  as parallel processes.
 *
 *  Programmer's notes:
 *  1) Mutation rate can be split into rates for transition error (Es) and transversion error (Ev) in a later version
 *  of the model.
 *  2) Need a Replication class to manage the replication cycle. a) Population should examine generationalGrowth (say 0.1)
 *  and current population size (census) to determine how many genotypes to replicate; then randomly select the
 *  replication "set", and pass this to the Replication object.  The Replication object then calculates how many
 *  point mutations are to occur and where within the set of mutating genotypes; it then passes mutation directives
 *  to the affected genotypes. b) The Population object also examines the homologous recombination rate and the current
 *  population size (census) to determine how many recombination events will occur; it then selects from among the
 *  genotypes in the replication "set" the appropriate number of randomly selected genotype pairs to be recombined,
 *  and sends this directive to the Replication object. Both directives (a and b) are sent together to the Replication
 *  object.
 *
 *  Replication cycle procedure:
 *  1) Determine census; use generationalGrowth to calculate how many genotypes to replicate; randomly select them
 *     and place them in the genotype replication pool. Recall that a genotype has a field designating the number
 *     of identical genotypes. Only one of these (usually) will be selected for replication.
 *  2) Determine fitness of a replicating genotype, and calculate the proportion of new genotypes that the current
 *     genotype will produce, based on its relative fitness.
 *  3) Use mutation rate to determine how many nts will mutate in the pool (that is, in nts we care about).
 *  4) Use recombination rate to determine how many replicating genotypes will recombine; randomly formulate pairs.
 *  5) For each pair, randomly determine a "crossover point" and assign pairs as "a" and "b".
 *  6) To compensate for each homologous recombination event, add a randomly selected genotype to the replication
 *     pool (since the recombination event (template jump) will essentially eliminate one genome's worth of
 *     progeny strand synthesis).
 *  7) Using the calculated number of nt mutations in this replication cycle, randomly distribute those mutations
 *     among the "available" template nucleotide positions: that is, all non-recombining genotypes plus the
 *     "a" genotypes up to the crossover point, and the "b" genotypes beyond the crossover point. (In an advanced
 *     version of the model, this would be the point at which the "mutation hotspot" factor would be invoked to
 *     bias mutations toward certain residues or regions of the genome. However, we must assume that replicational
 *     mutations are entirely random--the bias is really at the level of fitness/selection, although this could
 *     reasonably be modeled/simulated at the replication level so as to keep the model simple.)
 *  8) For each genotype in the pool, construct a Mutation object, which specifies the position(s) at which a
 *     mutation is to occur, and link the Mutation object to its genotype.
 *  9) Invoke the Replication object, passing to it the genotype replication pool and the recombination object.
 *  10) The Replication object returns a set of genotypes, comprising the templates and the progeny. Recall that
 *     replication of a genotype without a mutation or recombination occurring will simply duplicate the template,
 *     so the Replication object only needs to update the genotype's number field.
 */

// Copyright   : Copyright (C) 2015 Carol L. Ecale Zhou - All Rights Reserved.
// License     : See LICENSE.md for license information
//


#ifndef POPULATION_H_
#define POPULATION_H_

#define FALSE 0
#define TRUE  1

#include "Genotype.h"
#include "Fitness.h"
//#include "FixedState.h"

class CPopulation {

public:
	CPopulation();                 // Input: inoculum; later add: burstSize, generationDepth, mutationRate, recombinationRate,
	virtual ~CPopulation();

	void AddGenotype(CGenotype* pGenotype);
	
	void PrintPopulation();            // Enumerates the Population in detail (for development/debugging/logging)
	bool IsNeurovirulent();            // Returns true if any genotype in the population is neurovirulent 
	bool IsMahoney();                  // Returns true if any genotype in the population resembles Mahoney in sequence
	bool IsExtinct();                  // Returns true if all of the genotypes have lethal mutation; genotype count is zero
	unsigned long CountGenotypes();    // Returns the number of genotypes in the Population
	double CalculatePopulationFitness(); // Returns average of fitness values across genotypes
	void UpdatePopulationStatistics(); // Provide summary statistics regarding Sabin, Mahoney, Neurovirulence.	
	int ReportPopulationStatistics(); // Report summary of statistics gathered in UpdatePopulationStatistics().
	void Consolidate();
	bool ReplicateOnce();
	void Replicate();                  // Constructs a Pool object and invokes replication cycle

	void MutateGenotypes(vector<CGenotype*> &vGenotypeSet); // Performs genotype mutation
	CGenotype* CombineGenotypes(CGenotype* pGenotype_a, CGenotype* pGenotype_b); // Performs copy-choice replication
	CGenotype* SelectGenotype(int iRandomPosition);
    double CalculateAverageFitness(vector<CGenotype*> &vGenotypeSet); // Calculate the average fitness over a genotype set
    int CalculateNumOfProgeny(double dFitness, vector<CGenotype*> &vGenotypeSet);  // Calculate number of progeny for a genoytpe

	// data members
	vector<CGenotype*> m_vGenotypeSet;
	bool               m_bBurstSizeReached;        // true when the population has reached BURST_SIZE
	bool               m_bGenerationDepthReached;  // true when the number of replication cycles has reached generationDepth
	unsigned long      m_iGenerationNum;           // Tracks how many generations have been completed by ReplicateOnce()
	unsigned long      m_iNumOfGenotypes;          // Tally of all the genotypes in the population
	unsigned long      m_iNumOfNeurovirulentGenotypes; // Number of genotypes that have achieved (at least minimal) neurovirulence.
	unsigned long      m_iNeurovirulentIndex;      // Sum of neurovirulent indexes across all genotypes in population.
	unsigned long      m_iNumOfMahoneyGenotypes;   // Tally of the number of genotypes that have reached Mahoney state
	unsigned long      m_iNumOfMahoneyPositions;   // Tally of the total number of positions in all genotypes that have identity to Mahoney
	double             m_dMahoneyReversionIndex;   // Measure of the degree to which the population has reverted to Mahoney genotype
	unsigned long      m_iNumOfDefectiveGenotypes; // Sum of genotypes with a lethal mutation
	double             m_dAverageFitness;          // Average fitness value over member genotypes
	bool		       m_bMahoney;                 // True if any genotype resembled Mahoney in sequence
	bool               m_bNeurovirulent;           // True if any genotype is neurovirulent
	bool               m_bExtinct;                 // True if no viable genotypes remain
	unsigned long      m_iGenotypeMaxCount;        // Number of genotypes (total, including defective/lethal) reached
};


#endif /* POPULATION_H_ */
