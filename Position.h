/*
 * Position.h
 *
 *  Created on: May 1, 2009
 *  Last update: 25 March 2015
 *      Author: Carol L. Ecale Zhou
 *
 * The position object organizes all of the data for a given position of interest in the genome.
 * For now (1may2009) the fixFactor and mutability are constant values, but in future versions
 * of the model these values may be allowed to change. Default is fixFactor=1, and mutability =1,
 * whereby neither of these values will change the probability of a nucleotide substitution.
 * The degreeOfNeurovirulence corresponds to "none" = 0, "low" = 1, "moderate" = 2, "strong" = 3.
 */

#ifndef POSITION_H_
#define POSITION_H_

#include "RandomC.h"
#include "Configurable.h"

class CPosition {

public:
	CPosition(char cNucleotide, 
			  int iPosition,
			  bool bSabin1 = true, 
			  bool bMahoney = false,
			  bool bNeurovirulent = false, 
			  bool bLethal = false,
			  int iDegreeOfNeurovirulence = 0,
                          double dFitness = 0.5,
			  double dFixFactor = 1.0, 
			  double dMutability = 1.0);
	CPosition(CPosition* pPosition);
	virtual ~CPosition();

 	void PrintPosition();
	bool DetermineSimilarity(SPosition* sPosition); 
		// Compares a position object to a struct position (e.g., Sabin1, Mahoney)
	bool DetermineNeurovirulence(SPosition* sPosition);
	void Mutate();

	// data members
	char   m_cNucleotide;
	int    m_iPosition;               // locus: position number on the reference sequence (Mahoney/Sabin1 numbering)
	bool   m_bSabin1;                 // true if the nucleotide at this position is the nucleotide in Sabin1
	bool   m_bMahoney;                // true if the nucleotide at this position is the nucleotide in Mahoney
	bool   m_bNeurovirulent;          // true if the nucleotide at this position is associated with neurovirulence
	bool   m_bLethal;                 // true if the nucleotide at this position confers a lethal mutation
	int    m_iDegreeOfNeurovirulence; // 0 = nonvirulent, 1 = confers mild neurovirulence, 2 = moderate, 3 = strong
	double m_dFitness;                // determined by SFitness values (see FixedState.h)
	double m_dFixFactor;              // tendency for the Mahoney nucleotide at this position to become fixed in the population (0-1)
	double m_dMutability;             // tendency for this position to preferentially mutate (1-10); default = 1, no reason currently to set this at any other value
};

bool ComparePosition(CPosition* pPosition1, CPosition* pPosition2);

#endif /* POSITION_H_ */
