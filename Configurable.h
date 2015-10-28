/*
 * Configurable.h
 *
 *  Created on: May 27, 2009
 *      Author: Carol Zhou
 *  Most recent update:  26 October 2015
 *
 *  This file contains configurable constants. Some of these should be changed from constants to variable,
 *  which may be later modified dynamically or specifically by underlying objects that use them.
 *
 *  This website has some quick facts:
 *  http://www.brown.edu/Courses/Bio_160/Projects2000/Polio/PoliovirusLifeCycle.htm
 */
// Copyright   : Copyright (C) 2015 Carol L. Ecale Zhou - All Rights Reserved.
// License     : See LICENSE.md for license information
//

#ifndef CONFIGURABLE_H_
#define CONFIGURABLE_H_

// Defaults - Realistic defaults in comments
// PARAMETER default value // command-line parameter / suggested value // explanation
#define ERROR_RATE                    0.1  // -e / 0.001  // should vary from 1/1000 to 1/100,000 nt per replication, as per literature
#define GENERATIONAL_GROWTH           1.0  // -g / 1.0    // population growth factor after a single replication cycle; 1.0 assumes every genome can replicate
#define HOMOLOGOUS_RECOMBINATION_RATE 0.3  // -r / 0.30   // zero to one; zero=never, one=always; 0.30 from literature 
#define BURST_SIZE                    1000 // -b / 1000   // population size when cell resources become exhausted or cell lysis (10k-100k)
#define MULTIPLICITY_OF_INFECTION     10   // -i / 10     // how many genotypes to randomly select for next inoculum / passage
                                                          // Can set much higher to simulate cell-to-cell spread in real infection
                                                          // Initial MOI will be determined by inoculating genotype m_iNumOfGenotypes
#define NUMBER_OF_PASSAGES            5    // -p / 5+     // Zero passages is a single inoculum, a single plate of cells
#define NUM_GENS_TO_CONSOLIDATE       5    // -c / 5      // Consolidation reduces memory needed to hold genotype data
						          // Adjust this to balance execution speed with memory usage
#define NUMBER_OF_POPULATIONS         1    // -P / 100000 // realistic would be up to 1 million cells (populations) on a plate
                                                          // Increasing this well beyond 1 will require parallel computing.
#define FITNESS_ACCELERATOR           2.0  // -a / 2.0    // Increases replication as fitness increases; fitness effect is linear when k=1.0, off when k=0.0
#define MAHONEY_THRESHOLD             80   // -t / 80     // Determines how many Mahoney mutations determine (essentially complete) reversion; suggest 80%
#define MAHONEY_SYNERGY               2.0  // -s / 2.0    // Controls degree of fitness increase afforded by accumulated Mahoney mutations
#define RETAIN_LETHALS                1    // -l / 1      // True means retain lethal mutant genotypes; False/0 if the should be routinely removed from population

// Additional Parameter Defaults - ***Not yet in service
// PARAMETER default value // command-line parameter / suggested value // explanation
#define GENERATION_DEPTH              10  // -d / 100    // number of replication cycles in a simulation (all passages)
#define FIXATION_RATE                 0.1 // -f / 0.1    // fully fixed is zero; 1 = no tendency for fixation of a mutation (applies to Mahoney nt)
#define MUTATIONAL_PREFERENCE         1.0 // -m / 1.0    // assume for now that there is no mutational preference
#define GENERATIONS_PER_CELL          1   // -G / 5      //
#define CELL_DENSITY                  1   //    / 100000 // number of cells on a culture plate; realistic would be 100k to 1million; for first model, use trivial case
#define TRANSITION_RATE               0.5 // -t /        // need to get this from literature
#define TRANSVERSION_RATE             0.5 // -T /        // need to get this from literature 
#define INFECTION_CYCLES              1   //    /        //  ?
#define FIXED_RESOURCES               100 //    / 100    // Represents 100% of what is available; don't need this if lysis terminates replication in cell
#define FIXED_SPACE                   100 //    / 100    // Represents 100% of what is available

// Other defaults
#define POSITION_SET_SIZE 55 // Sabin/Mahoney differ at 54 positions, 1 additional confers neurovirulence beyond those distinguishing Sabin/Mahoney
#define UNDEFINED_NT 'N'

// Standard genotypes (from literature) -- should leave these settings as they are!
#define SABIN1_COUNT         1
#define MAHONEY_COUNT        1
#define NEUROVIRULENT_COUNT  1

// Defaults for initial innocula
#define SABIN_COUNT          10  // This is the usual starting genotype; Initial MOI is determined here
#define FOOBAR1_COUNT        1   // Foobar genotypes can be user defined as something other than Sabin
#define FOOBAR2_COUNT        1   // Define Foobar genotypes in FixedState.h
#define FOOBAR3_COUNT        1   //

// For building genotypes
struct SPosition
{
	char m_cNucleotide;
	int  m_iPosition;               // locus: position number on the reference sequence (Mahoney/Sabin1 numbering)
	bool m_bMahoney;                // true if the nucleotide at this position is the nucleotide in Mahoney
	bool m_bNeurovirulent;          // true if the nucleotide at this position is associated with neurovirulence
	int  m_iDegreeOfNeurovirulence; // 0 = nonvirulent, 1 = confers mild neurovirulence, 2 = moderate, 3 = strong
};

// For building fitness measures
struct SFitness
{
	int    m_iPosition;  // position on genome
	double m_dAnt;       // fitness value for A nucleotide
	double m_dCnt;       // fitness value for C nucleotide
	double m_dGnt;       // fitness value for G nucleotide
	double m_dUnt;       // fitness value for U nucleotide
};

#endif /* CONFIGURABLE_H_ */
