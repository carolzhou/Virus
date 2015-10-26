/*
 * Fitness.cpp
 *
 * Created on: Mar 16, 2015
 * 	Author: Carol Zhou
 *
 */
// Copyright   : Copyright (C) 2015 Carol L. Ecale Zhou - All Rights Reserved.
// License     : See LICENSE.md for license information
//

#include <iostream>
#include "Fitness.h"

using namespace std;

CFitness::CFitness()
{
}

CFitness::CFitness(SFitness fitnesses[], int iNumPositions)
{
	SFitness * psFitness = NULL;
	for(unsigned int i = 0; i < iNumPositions; i++)
	{
		psFitness = new SFitness;
		psFitness->m_iPosition = fitnesses[i].m_iPosition;	
		psFitness->m_dAnt = fitnesses[i].m_dAnt;	
		psFitness->m_dCnt = fitnesses[i].m_dCnt;	
		psFitness->m_dGnt = fitnesses[i].m_dGnt;	
		psFitness->m_dUnt = fitnesses[i].m_dUnt;	
		m_vPositionSet.push_back(psFitness);
		m_mPositionMap[fitnesses[i].m_iPosition] = psFitness;
	}
	CalculateMaxFitness();
	CalculateMinFitness();
}

// Probably won't use copy constructor initially, but could be useful if 
// one wants to modify fitness dynamically and have >1 fitness in simulation.
CFitness::CFitness(CFitness* pFitness)
{
	SFitness * psFitness = NULL;
	for(unsigned int i = 0; i< pFitness->m_vPositionSet.size(); i++)
	{
		psFitness = new SFitness;
		psFitness->m_iPosition = pFitness->m_vPositionSet[i]->m_iPosition;
		psFitness->m_dAnt = pFitness->m_vPositionSet[i]->m_dAnt;
		psFitness->m_dCnt = pFitness->m_vPositionSet[i]->m_dCnt;
		psFitness->m_dGnt = pFitness->m_vPositionSet[i]->m_dGnt;
		psFitness->m_dUnt = pFitness->m_vPositionSet[i]->m_dUnt;
		m_vPositionSet.push_back(psFitness);
		m_mPositionMap[psFitness->m_iPosition] = psFitness;
	}
	this->m_dMaxFitness = pFitness->m_dMaxFitness;
	this->m_dMinFitness = pFitness->m_dMinFitness;
}

CFitness::~CFitness()
{
	for(unsigned int i = 0; i < m_vPositionSet.size(); i++)
	{
		if(m_vPositionSet[i])
		{
			delete m_vPositionSet[i];
			m_vPositionSet[i] = NULL;
		}
	}
}

double CFitness::GetMaxValue(SFitness* pSFitness)
{
	double dMaxValue = pSFitness->m_dAnt;
	if(dMaxValue < pSFitness->m_dCnt)
		dMaxValue = pSFitness->m_dCnt;
	if(dMaxValue < pSFitness->m_dGnt)
		dMaxValue = pSFitness->m_dGnt;
	if(dMaxValue < pSFitness->m_dUnt)
		dMaxValue = pSFitness->m_dUnt;
	return dMaxValue;
}

void CFitness::CalculateMaxFitness()
{
	double dMaxFitness = 0.0;
	for(unsigned int i = 0; i < m_vPositionSet.size(); i++)
	{
		dMaxFitness += GetMaxValue(m_vPositionSet[i]);
	}
	m_dMaxFitness = dMaxFitness;
}

double CFitness::GetMinValue(SFitness* pSFitness)
{
	double dMinValue = pSFitness->m_dAnt;
	if(dMinValue > pSFitness->m_dCnt)
		dMinValue = pSFitness->m_dCnt;
	if(dMinValue > pSFitness->m_dGnt)
		dMinValue = pSFitness->m_dGnt;
	if(dMinValue > pSFitness->m_dUnt)
		dMinValue = pSFitness->m_dUnt;
	return dMinValue;
}

void CFitness::CalculateMinFitness()
{
	double dMinFitness = 0.0;
	for(unsigned int i = 0; i < m_vPositionSet.size(); i++)
	{
		dMinFitness += GetMinValue(m_vPositionSet[i]);
	}
	m_dMinFitness = dMinFitness;
}

void CFitness::PrintFitness()
{
	for(unsigned int i = 0; i < m_vPositionSet.size(); i++)
	{
		cout << "Position " << m_vPositionSet[i]->m_iPosition;
		cout << " - fitness: ";
		cout << " A:" << m_vPositionSet[i]->m_dAnt;
		cout << " C:" << m_vPositionSet[i]->m_dCnt;
		cout << " G:" << m_vPositionSet[i]->m_dGnt;
		cout << " U:" << m_vPositionSet[i]->m_dUnt << endl;
	}
	cout << "The minimum fitness is " << m_dMinFitness << endl;
	cout << "The maximum fitness is " << m_dMaxFitness << endl;
}

