/* 
 * Fitness.h
 *
 * Created on: Mar 16, 2015
 *      Author:  Carol Zhou
 *
 * Description:
 * The Fitness class organizes one or more defintions of fitness for a given genotype. The
 * accepted values for fitness are defined in FixedState.h.  Fitness in the simplest case 
 * is defined as resemblence to the neurovirulent or Mahoney types. A Fitness object comprises
 * a list of positions and fitness values for each nucleotide at that position.
 *
 * Programmer's notes:
 *
 */

#ifndef FITNESS_H
#define FITNESS_H

#include <map>
#include <vector>
#include "Configurable.h"

using namespace std;

class CFitness {

public:
	CFitness();
	CFitness(SFitness fitnesses[], int iNumPositions);
	CFitness(CFitness* pFitness);
	~CFitness();
	double GetMaxValue(SFitness* pSFitness);
	void CalculateMaxFitness();
	double GetMinValue(SFitness* pSFitness);
	void CalculateMinFitness();
	void PrintFitness();
	
	// data members
	vector<SFitness*>	m_vPositionSet;
	map<int, SFitness*>	m_mPositionMap;
	double m_dMinFitness;
	double m_dMaxFitness;
	
};

// Declare above main
extern CFitness* pFitness;

#endif  /* FITNESS_H */
