/*
 * Genotype.h
 *
 *  Created on: Apr 16, 2009
 *  Last update: 25 March 2015
 *      Author: Carol L. Ecale Zhou
 *
 * Description:
 * The Genotype class organizes a specific physical genome in the model. Although in reality a genotype
 * would comprise an entire genomic sequence, in the model we track only those positions that are of
 * interest. For example, for the Sabin-->Mahoney transition, we track only the positions that a) differentiate
 * Sabin type 1 from Mahoney and those positions that are known to confer neurovirulence (based on
 * data in the literature). Almost all of the neurovirulence mutations coincide with Sabin-->Mahoney
 * mutations; a notable exception is the position 525 mutation to C, which compensates for Sabin's 525 G.
 *    A genotype will manage the mutation process at the level of determining which nucleotide substitution
 * will be made.  The genotype is told which position to mutate, but genotype determines whether the mutation
 * is a transition/transversion, and furthermore, depending on other factors (i.e., fixation) whether the
 * mutation will actually occur.  Note that in nature, fixation is a result of relative fitness, and "fit"
 * genomes tend to produce more progeny genomes. However, the code (initial model) will not model this as
 * realistically as determining fitness and removing unfit genomes (thereby increasing liklihood that a
 * more fit genome will replicate in the next cycle).  Rather, the code will model tendency for fixation
 * of a mutation in the population as a factor that will determine whether the mutation on the given genome
 * will occur.  Thus, a genotype object will receive a directive to mutate at position i; the genotype will
 * check the fixation factor at that position; if the fixation factor is high, then a random number will
 * determine whether the mutation will proceed (the nt will change) or whether no mutation will occur after
 * all.  So, the fixation factor may modify the mutation directive after the fact.  I believe this is
 * close to "realistic" because one would expect that, for example, as a population narrows or migrates
 * toward a more fit state (e.g., toward Mahoney-like), there will be fewer persistent mutational changes
 * in the 54 nts, given an unmodified polymerase. (Note, however, that 3 of the S-->M mutations are aa
 * changes in the polymerase; what are the precise effects of these mutations?)
 *
 * Programmer's notes:
 * 1) Should the genotype produce a progeny copy of itself? Is this done using a copy constructor?
 * 2) If a mutation is halted (due to fixation), the genotype should return "failure" or some such to the
 * population object.
 * 3) If a mutation occurs, the genotype should make a copy of itself, then modify the nt at the specified
 * position, and return the new genotype object to the population (if using a copy constructor for itself???)
 *
 *
 */

#ifndef GENOTYPE_H_
#define GENOTYPE_H_

#include <map>
#include <vector>
#include "Position.h"
#include "Fitness.h"

using namespace std;

class CGenotype {

public:
	CGenotype(int iGenotypeCount = 1);
	CGenotype(SPosition positions[], int iNumPositions, int iGenotypeCount = 1);
	CGenotype(CGenotype* pGenotype, bool bExactCopy = false);

	~CGenotype();

	void   PrintGenotype();
	void   UpdateGenotypeStatistics();
	void   ReportGenotypeStatistics();
	double CalculateFitness(); // Returns genotype fitness or 0.0 if genotype has lethal mutation
	bool   IsNeurovirulent(); // Determines if a genotype has at least one neurviurlent position
	bool   IsMahoney();       // Determines if the genotype resembles Mahoney
	bool   IsSabin1();         // Determines if the genotype resembles Sabin1
	bool   IsLethal();  // Returns true if fitness is zero at any position (must UpdateStatistics first)
	bool   AllowMutation();  // Based on fixationFactor, determines whether current mutation directive should proceed
	char   SelectMutation();  // Selects a nucleotide substitution based on rates (e.g., transverionRate)

	// data members
	vector<CPosition*>    m_vPositionSet;
	map<int, CPosition*>  m_mPositionMap;
	int                   m_iGenotypeCount; // Count of the number of identical genotypes of this genotypeString
	int                   m_iMahoneyCount;  // Count of the number of Position objects that have reached Mahoney state
	int                   m_iSabin1Count;   // Count of the number of Position objects that remain in Sabin state
	int		      m_iNeurovirulentCount; // Count of the number of Position objects in neurovirulent state
	int		      m_iNeurovirulentIndex; // Degree of neurovirulence (sum positions' degree of neurovirulence values)
	bool                  m_bNeurovirulent; // True if any of the Position objects confers neurovirulence
	bool		      m_bSabin1;  // True if all nucleotides resemble Sabin1
	bool		      m_bMahoney; // True if all nucleotides resemble Mahoney
	bool		      m_bLethal;  // True if this genotype contains a lethal mutation at any position
	bool                  m_bNewRecombinant;
	bool                  m_bMutatedReplicate;
	int		      m_iPositionCount; // Number of positions defined for this genotype
	int                   m_iSelectionCount; // Tallies the number of genotypes that have been selected for an inoculum (in Cloud.cpp)
	double                m_dFitness; // Sum of fitness values over nucleotide positions
	//static int staticGenotypeCount; // how many instances of genotype have been created
};

bool CompareGenotype(CGenotype* pGenotype1, CGenotype* pGenotype2);

// Declared above main
extern CGenotype* pSabin1;
extern CGenotype* pMahoney;
extern CGenotype* pNeurovirulent;
extern CGenotype* pFoobar1;
extern CGenotype* pFoobar2;
extern CGenotype* pFoobar3;

#endif /* GENOTYPE_H_ */
