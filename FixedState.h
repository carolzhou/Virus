/*
 * FixedState.h
 *
 *  Created on: May 27, 2009
 *      Author: Carol Zhou
 *
 *  This file contains fixed genome states.
 */

// Copyright   : Copyright (C) 2015 Carol L. Ecale Zhou - All Rights Reserved.
// License     : See LICENSE.md for license information
//
// Position and nucleotide values are taken from Georgescu et al. 1997, JVirology 71:7758.
// Sabin 1

#ifndef FIXEDSTATE_H_
#define FIXEDSTATE_H_

#include "Configurable.h"

/*enum EFitness 
{
	ePosition,
	eA,
	eC,
	eG,
	eU
};
*/
// Fitness-1 values (hypothetical for testing).
// Fitness values may be assigned based on experimental data.
// 0.0 indicates a lethal mutation; 1.0 is highly selected.
// Position 1 in data structure indicates position along genome.
// Positions 1-4 correspond to A,C,G,T at that position.
// For development and testing, assign highest fitness values
//   to neurovirulent positions/nucleotides, and moderate
//   fitness values to Mahoney sequence. A lethal mutation would
//   be indicated by 0.0--none set initially.
// Initially setting Mahoney to 0.8, neurovirulence to 1.0
//   default to 0.5, Sabin1 to 0.2 (assume poorly selected)
struct SFitness Fitness1Positions[] =
{
	{21,   0.5, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1 
	{189,  0.5, 1.0, 0.5, 0.2}, // C - neurovirulence, Mahoney; U - Sabin1
	{480,  1.0, 0.5, 0.9, 0.5}, // A - neurovirulence, Mahoney; G - Sabin1
	{525,  0.5, 1.0, 0.5, 0.5}, // C - neurovirulence if 480=G; N - Mahoney, Sabin1 (does not distinguish)
	{649,  0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{674,  0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{935,  0.5, 0.5, 1.0, 0.2}, // G - neurovirulence, Mahoney; U - Sabin1
	{1208, 0.8, 0.2, 0.5, 0.5}, // A - Mahoney; C - Sabin1
	{1228, 0.5, 0.2, 0.8, 0.5}, // G - Mahoney; C - Sabin1
	{1442, 0.8, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{1465, 0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{1490, 0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{1507, 0.2, 0.5, 0.8, 0.5}, // G - Mahoney; A - Sabin1
	{1747, 0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{1885, 0.8, 0.5, 0.5, 0.2}, // A - Mahoney; U - Sabin1
	{1942, 0.2, 0.8, 0.5, 0.5}, // C - Mahoney; A - Sabin1
	{1944, 0.2, 0.8, 0.5, 0.5}, // C - Mahoney; A - Sabin1
	{2353, 0.5, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1
	{2438, 0.2, 0.5, 0.5, 0.8}, // U - Mahoney; A - Sabin1
	{2545, 0.8, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{2585, 0.8, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{2741, 0.8, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{2749, 0.2, 0.5, 0.8, 0.5}, // G - Mahoney; A - Sabin1
	{2762, 0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{2775, 0.2, 0.8, 0.5, 0.5}, // C - Mahoney; A - Sabin1
	{2795, 0.2, 0.5, 1.0, 0.5}, // G - neurovirulence, Mahoney; A - Sabin1
	{2879, 0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{3163, 0.5, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1
	{3445, 0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{3460, 0.2, 0.5, 0.5, 0.8}, // U - Mahoney; A - Sabin1
	{3492, 0.2, 0.5, 0.8, 0.5}, // G - Mahoney; A - Sabin1
	{3766, 0.2, 0.8, 0.5, 0.5}, // C - Mahoney; A - Sabin1
	{3785, 0.2, 0.5, 0.5, 0.8}, // U - Mahoney; A - Sabin1
	{3896, 0.8, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{3898, 0.2, 0.8, 0.5, 0.5}, // C - Mahoney; A - Sabin1
	{3919, 0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{4003, 0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{4116, 0.5, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1
	{4444, 0.5, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1
	{4789, 0.8, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{5107, 0.5, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1
	{5137, 0.8, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{5420, 0.2, 0.8, 0.5, 0.5}, // C - Mahoney; A - Sabin1
	{5440, 0.8, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{6140, 0.2, 0.8, 1.0, 0.5}, // C - neurovirulence; A - Sabin1
	{6143, 0.2, 0.5, 0.8, 0.5}, // G - Mahoney; A - Sabin1
	{6203, 0.5, 0.2, 0.5, 1.0}, // U - neurovirulence, Mahoney; C - Sabin1
	{6373, 0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{6616, 0.2, 0.5, 0.8, 0.5}, // G - Mahoney; A - Sabin1
	{6679, 0.5, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1
	{6853, 0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{7071, 0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{7198, 0.2, 0.5, 0.5, 0.8}, // U - Mahoney; A - Sabin1
	{7243, 0.2, 0.5, 0.5, 0.8}, // U - Mahoney; A - Sabin1
	{7410, 0.5, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1
	{7441, 0.8, 0.5, 0.2, 0.5}  // A - Mahoney; G - Sabin1
};
#define NUM_FITNESS1_POSITIONS (sizeof(Fitness1Positions) / sizeof(struct SFitness))

// This fitness grid is for testing, currently incorporated lethal mutations
// Lethal mutations are indicated with fitness value of 0.0
struct SFitness Fitness2Positions[] =
{
	{21,   0.0, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1 
	{189,  0.0, 1.0, 0.5, 0.2}, // C - neurovirulence, Mahoney; U - Sabin1
	{480,  0.0, 0.5, 0.9, 0.5}, // A - neurovirulence, Mahoney; G - Sabin1
	{525,  0.0, 1.0, 0.5, 0.5}, // C - neurovirulence if 480=G; N - Mahoney, Sabin1 (does not distinguish)
	{649,  0.0, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{674,  0.0, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{935,  0.0, 0.5, 1.0, 0.2}, // G - neurovirulence, Mahoney; U - Sabin1
	{1208, 0.0, 0.2, 0.5, 0.5}, // A - Mahoney; C - Sabin1
	{1228, 0.0, 0.2, 0.8, 0.5}, // G - Mahoney; C - Sabin1
	{1442, 0.0, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{1465, 0.0, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{1490, 0.0, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{1507, 0.0, 0.5, 0.8, 0.5}, // G - Mahoney; A - Sabin1
	{1747, 0.0, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{1885, 0.0, 0.5, 0.5, 0.2}, // A - Mahoney; U - Sabin1
	{1942, 0.0, 0.8, 0.5, 0.5}, // C - Mahoney; A - Sabin1
	{1944, 0.0, 0.8, 0.5, 0.5}, // C - Mahoney; A - Sabin1
	{2353, 0.0, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1
	{2438, 0.0, 0.5, 0.5, 0.8}, // U - Mahoney; A - Sabin1
	{2545, 0.0, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{2585, 0.0, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{2741, 0.0, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{2749, 0.0, 0.5, 0.8, 0.5}, // G - Mahoney; A - Sabin1
	{2762, 0.0, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{2775, 0.0, 0.8, 0.5, 0.5}, // C - Mahoney; A - Sabin1
	{2795, 0.0, 0.5, 1.0, 0.5}, // G - neurovirulence, Mahoney; A - Sabin1
	{2879, 0.0, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{3163, 0.0, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1
	{3445, 0.0, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{3460, 0.0, 0.5, 0.5, 0.8}, // U - Mahoney; A - Sabin1
	{3492, 0.0, 0.5, 0.8, 0.5}, // G - Mahoney; A - Sabin1
	{3766, 0.0, 0.8, 0.5, 0.5}, // C - Mahoney; A - Sabin1
	{3785, 0.0, 0.5, 0.5, 0.8}, // U - Mahoney; A - Sabin1
	{3896, 0.0, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{3898, 0.0, 0.8, 0.5, 0.5}, // C - Mahoney; A - Sabin1
	{3919, 0.0, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{4003, 0.0, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{4116, 0.0, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1
	{4444, 0.0, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1
	{4789, 0.0, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{5107, 0.0, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1
	{5137, 0.0, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{5420, 0.0, 0.8, 0.5, 0.5}, // C - Mahoney; A - Sabin1
	{5440, 0.0, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{6140, 0.0, 0.8, 1.0, 0.5}, // C - neurovirulence; A - Sabin1
	{6143, 0.0, 0.5, 0.8, 0.5}, // G - Mahoney; A - Sabin1
	{6203, 0.0, 0.2, 0.5, 1.0}, // U - neurovirulence, Mahoney; C - Sabin1
	{6373, 0.0, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{6616, 0.0, 0.5, 0.8, 0.5}, // G - Mahoney; A - Sabin1
	{6679, 0.0, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1
	{6853, 0.0, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{7071, 0.0, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{7198, 0.0, 0.5, 0.5, 0.8}, // U - Mahoney; A - Sabin1
	{7243, 0.0, 0.5, 0.5, 0.8}, // U - Mahoney; A - Sabin1
	{7410, 0.0, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1
	{7441, 0.0, 0.0, 0.2, 0.0}  // A - Mahoney; G - Sabin1
};
#define NUM_FITNESS2_POSITIONS (sizeof(Fitness2Positions) / sizeof(struct SFitness))

struct SFitness Fitness3Positions[] =
{
	{21,   0.5, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1 
	{189,  0.5, 1.0, 0.5, 0.2}, // C - neurovirulence, Mahoney; U - Sabin1
	{480,  1.0, 0.5, 0.9, 0.5}, // A - neurovirulence, Mahoney; G - Sabin1
	{525,  0.5, 1.0, 0.5, 0.5}, // C - neurovirulence if 480=G; N - Mahoney, Sabin1 (does not distinguish)
	{649,  0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{674,  0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{935,  0.5, 0.5, 1.0, 0.2}, // G - neurovirulence, Mahoney; U - Sabin1
	{1208, 0.8, 0.2, 0.5, 0.5}, // A - Mahoney; C - Sabin1
	{1228, 0.5, 0.2, 0.8, 0.5}, // G - Mahoney; C - Sabin1
	{1442, 0.8, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{1465, 0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{1490, 0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{1507, 0.2, 0.5, 0.8, 0.5}, // G - Mahoney; A - Sabin1
	{1747, 0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{1885, 0.8, 0.5, 0.5, 0.2}, // A - Mahoney; U - Sabin1
	{1942, 0.2, 0.8, 0.5, 0.5}, // C - Mahoney; A - Sabin1
	{1944, 0.2, 0.8, 0.5, 0.5}, // C - Mahoney; A - Sabin1
	{2353, 0.5, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1
	{2438, 0.2, 0.5, 0.5, 0.8}, // U - Mahoney; A - Sabin1
	{2545, 0.8, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{2585, 0.8, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{2741, 0.8, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{2749, 0.2, 0.5, 0.8, 0.5}, // G - Mahoney; A - Sabin1
	{2762, 0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{2775, 0.2, 0.8, 0.5, 0.5}, // C - Mahoney; A - Sabin1
	{2795, 0.2, 0.5, 1.0, 0.5}, // G - neurovirulence, Mahoney; A - Sabin1
	{2879, 0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{3163, 0.5, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1
	{3445, 0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{3460, 0.2, 0.5, 0.5, 0.8}, // U - Mahoney; A - Sabin1
	{3492, 0.2, 0.5, 0.8, 0.5}, // G - Mahoney; A - Sabin1
	{3766, 0.2, 0.8, 0.5, 0.5}, // C - Mahoney; A - Sabin1
	{3785, 0.2, 0.5, 0.5, 0.8}, // U - Mahoney; A - Sabin1
	{3896, 0.8, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{3898, 0.2, 0.8, 0.5, 0.5}, // C - Mahoney; A - Sabin1
	{3919, 0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{4003, 0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{4116, 0.5, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1
	{4444, 0.5, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1
	{4789, 0.8, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{5107, 0.5, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1
	{5137, 0.8, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{5420, 0.2, 0.8, 0.5, 0.5}, // C - Mahoney; A - Sabin1
	{5440, 0.8, 0.5, 0.2, 0.5}, // A - Mahoney; G - Sabin1
	{6140, 0.2, 0.8, 1.0, 0.5}, // C - neurovirulence; A - Sabin1
	{6143, 0.2, 0.5, 0.8, 0.5}, // G - Mahoney; A - Sabin1
	{6203, 0.5, 0.2, 0.5, 1.0}, // U - neurovirulence, Mahoney; C - Sabin1
	{6373, 0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{6616, 0.2, 0.5, 0.8, 0.5}, // G - Mahoney; A - Sabin1
	{6679, 0.5, 0.2, 0.5, 0.8}, // U - Mahoney; C - Sabin1
	{6853, 0.5, 0.8, 0.5, 0.2}, // C - Mahoney; U - Sabin1
	{7071, 0.5, 0.8, 0.0, 0.2}, // C - Mahoney; U - Sabin1; G - LETHAL (testing)
	{7198, 0.2, 0.5, 0.0, 0.8}, // U - Mahoney; A - Sabin1; G - LETHAL (testing)
	{7243, 0.2, 0.5, 0.0, 0.8}, // U - Mahoney; A - Sabin1; G - LETHAL (testing)
	{7410, 0.5, 0.2, 0.0, 0.8}, // U - Mahoney; C - Sabin1; G - LETHAL (testing)
	{7441, 0.8, 0.5, 0.2, 0.5}  // A - Mahoney; G - Sabin1
};
#define NUM_FITNESS3_POSITIONS (sizeof(Fitness3Positions) / sizeof(struct SFitness))

struct SPosition Sabin1Positions[] =
{
	{'C', 21,   false, false, 0},
	{'U', 189,  false, false, 0},
	{'G', 480,  false, false, 0},
	{'A', 525,  false, false, 0},  // !!! virulent if position 525 is C and 480 is G; set Sabin1 to A
	{'U', 649,  false, false, 0},
	{'U', 674,  false, false, 0},
	{'U', 935,  false, false, 0},
	{'C', 1208, false, false, 0},
	{'C', 1228, false, false, 0},
	{'G', 1442, false, false, 0},
	{'U', 1465, false, false, 0},
	{'U', 1490, false, false, 0},
	{'A', 1507, false, false, 0},
	{'U', 1747, false, false, 0},
	{'U', 1885, false, false, 0},
	{'A', 1942, false, false, 0},
	{'A', 1944, false, false, 0},
	{'C', 2353, false, false, 0},
	{'A', 2438, false, false, 0},
	{'G', 2545, false, false, 0},
	{'G', 2585, false, false, 0},
	{'G', 2741, false, false, 0},
	{'A', 2749, false, false, 0},
	{'U', 2762, false, false, 0},
	{'A', 2775, false, false, 0},
	{'A', 2795, false, false, 0},
	{'U', 2879, false, false, 0},
	{'C', 3163, false, false, 0},
	{'U', 3445, false, false, 0},
	{'A', 3460, false, false, 0},
	{'A', 3492, false, false, 0},
	{'A', 3766, false, false, 0},
	{'A', 3785, false, false, 0},
	{'G', 3896, false, false, 0},
	{'A', 3898, false, false, 0},
	{'U', 3919, false, false, 0},
	{'U', 4003, false, false, 0},
	{'C', 4116, false, false, 0},
	{'C', 4444, false, false, 0},
	{'G', 4789, false, false, 0},
	{'C', 5107, false, false, 0},
	{'G', 5137, false, false, 0},
	{'A', 5420, false, false, 0},
	{'G', 5440, false, false, 0},
	{'A', 6140, false, false, 0}, // !!! can be neurovirulent, but does not distinguish Sabin1 from Mahoney
	{'A', 6143, false, false, 0},
	{'C', 6203, false, false, 0},
	{'U', 6373, false, false, 0},
	{'A', 6616, false, false, 0},
	{'C', 6679, false, false, 0},
	{'U', 6853, false, false, 0},
	{'U', 7071, false, false, 0},
	{'A', 7198, false, false, 0},
	{'A', 7243, false, false, 0},
	{'C', 7410, false, false, 0},
	{'G', 7441, false, false, 0}
};
#define NUM_SABIN1_POSITIONS (sizeof(Sabin1Positions) / sizeof(struct SPosition))

struct SPosition MahoneyPositions[] =
// pMahoney should be a constant; note: no need to include position 6140 here,
// as it does not distinguish Mahoney from Sabin, and we don't care about 
// checking if pMahoney is neurovirulent at that position! CPopulation::
// UpdatePopulationStatistics() uses NUM_MAHONEY_POSITIONS to determine
// whether an underlying genotype has reached full Mahoney state; includeing
// position 6140 in pMahoney complicates things. 
{
	{'U', 21,   true, false, 0},
	{'C', 189,  true, true, 1},
	{'A', 480,  true, true, 2},
	{'U', 525,  true, true, 2},  // !!! virulent if position 585 is C and 480 is G; set Mahoney to U
	{'C', 649,  true, false, 0},
	{'C', 674,  true, false, 0},
	{'G', 935,  true, true, 1},
	{'A', 1208, true, false, 0},
	{'G', 1228, true, false, 0},
	{'A', 1442, true, false, 0},
	{'C', 1465, true, false, 0},
	{'C', 1490, true, false, 0},
	{'G', 1507, true, false, 0},
	{'C', 1747, true, false, 0},
	{'A', 1885, true, false, 0},
	{'C', 1942, true, false, 0},
	{'C', 1944, true, false, 0},
	{'U', 2353, true, false, 0},
	{'U', 2438, true, false, 0},
	{'A', 2545, true, false, 0},
	{'A', 2585, true, false, 0},
	{'A', 2741, true, false, 0},
	{'G', 2749, true, false, 0},
	{'C', 2762, true, false, 0},
	{'C', 2775, true, false, 0},
	{'G', 2795, true, true, 1},
	{'C', 2879, true, false, 0},
	{'U', 3163, true, false, 0},
	{'C', 3445, true, false, 0},
	{'U', 3460, true, false, 0},
	{'G', 3492, true, false, 0},
	{'C', 3766, true, false, 0},
	{'U', 3785, true, false, 0},
	{'A', 3896, true, false, 0},
	{'C', 3898, true, false, 0},
	{'C', 3919, true, false, 0},
	{'C', 4003, true, false, 0},
	{'U', 4116, true, false, 0},
	{'U', 4444, true, false, 0},
	{'A', 4789, true, false, 0},
	{'U', 5107, true, false, 0},
	{'A', 5137, true, false, 0},
	{'C', 5420, true, false, 0},
	{'A', 5440, true, false, 0},
	{'C', 6140, true, false, 0}, // !!! can be neurovirulent, but does not distinguish Sabin1 from Mahoney
	{'G', 6143, true, false, 0},
	{'U', 6203, true, true, 1},
	{'C', 6373, true, false, 0},
	{'G', 6616, true, false, 0},
	{'U', 6679, true, false, 0},
	{'C', 6853, true, false, 0},
	{'C', 7071, true, false, 0},
	{'U', 7198, true, false, 0},
	{'U', 7243, true, false, 0},
	{'U', 7410, true, false, 0},
	{'A', 7441, true, false, 0},
};
#define NUM_MAHONEY_POSITIONS (sizeof(MahoneyPositions) / sizeof(struct SPosition))

// neurovirulence

/*  Description: This section organizes the currently known mutations that confer neurovirulence.
*  The following mutations have been associated with restoring neurovirulence in S-->M
*      189	U->C
*      480	G->A			5'NC - believed to restore base pairing in a stem of domain V
*      935	U->G	S->A (65)	VP4
*      2795	A->G	T->A (106)	VP1
*      6140	A->G	T->A (52)	3D (Sabin 1 IIs)
*      6203	C->U	H->Y (73)	3D (Sabin 1 IIs)
*  More info:
*      480	G->A	believed to restore base pairing in a stem of domain V
*      525	?	mutation at this position compensates for G at position 480 (check: is 525 mutant neurovir?)
*
*  Note: The following nt positions are associated with neurovirulence: 189, 480, 935, 2795, 6140, and 6203.
*  Of these, only 6140 is a position at which Sabin1 and Mahoney have identity but Mahoney does not
*  have the neurovirulence-associated nt seen in mutant Sabin1-IIs.
*/

struct SPosition NeurovirulentPositions[] =
{
	{'C', 189, true, true, 1},
	{'A', 480, true, true, 2},
	{'C', 525, true, true, 2},  // !!! virulent if position 480 is G
	{'G', 935, true, true, 1},
	{'G', 2795, true, true, 1},
	{'G', 6140, true, true, 1}, // !!! neurovirulent, but does not distinguish Sabin1 from Mahoney
	{'U', 6203, true, true, 1},
};
#define NUM_NEUROVIRULENT_POSITIONS (sizeof(NeurovirulentPositions) / sizeof(struct SPosition))

// Sampe input data for Inoculum
struct SPosition Foobar1Positions[] =
{
	{'Z', 21, false, false, 0},
	{'U', 189, false, false, 0},
	{'G', 480, false, false, 0},
	{'W', 525, false, false, 0},  // !!! virulent if position 585 is C and 480 is G
	{'U', 649, false, false, 0},
	{'U', 674, false, false, 0},
	{'U', 935, false, false, 0},
	{'C', 1208, false, false, 0},
	{'C', 1228, false, false, 0},
	{'G', 1442, false, false, 0},
	{'U', 1465, false, false, 0},
	{'U', 1490, false, false, 0},
	{'A', 1507, false, false, 0},
	{'U', 1747, false, false, 0},
	{'U', 1885, false, false, 0},
	{'A', 1942, false, false, 0},
	{'A', 1944, false, false, 0},
	{'C', 2353, false, false, 0},
	{'A', 2438, false, false, 0},
	{'G', 2545, false, false, 0},
	{'G', 2585, false, false, 0},
	{'G', 2741, false, false, 0},
	{'A', 2749, false, false, 0},
	{'U', 2762, false, false, 0},
	{'A', 2775, false, false, 0},
	{'A', 2795, false, false, 0},
	{'U', 2879, false, false, 0},
	{'C', 3163, false, false, 0},
	{'U', 3445, false, false, 0},
	{'A', 3460, false, false, 0},
	{'A', 3492, false, false, 0},
	{'A', 3766, false, false, 0},
	{'A', 3785, false, false, 0},
	{'G', 3896, false, false, 0},
	{'A', 3898, false, false, 0},
	{'U', 3919, false, false, 0},
	{'U', 4003, false, false, 0},
	{'C', 4116, false, false, 0},
	{'C', 4444, false, false, 0},
	{'G', 4789, false, false, 0},
	{'C', 5107, false, false, 0},
	{'G', 5137, false, false, 0},
	{'A', 5420, false, false, 0},
	{'G', 5440, false, false, 0},
	{'A', 6140, false, false, 0}, // !!! can be neurovirulent, but does not distinguish Sabin1 from Mahoney
	{'A', 6143, false, false, 0},
	{'C', 6203, false, false, 0},
	{'U', 6373, false, false, 0},
	{'A', 6616, false, false, 0},
	{'C', 6679, false, false, 0},
	{'U', 6853, false, false, 0},
	{'U', 7071, false, false, 0},
	{'A', 7198, false, false, 0},
	{'A', 7243, false, false, 0},
	{'C', 7410, false, false, 0},
	{'Z', 7441, false, false, 0}
};
#define NUM_FOOBAR1_POSITIONS (sizeof(Foobar1Positions) / sizeof(struct SPosition))

struct SPosition Foobar2Positions[] =
{
	{'Z', 21, false, false, 0},
	{'U', 189, false, false, 0},
	{'G', 480, false, false, 0},
	{'W', 525, false, false, 0},  // !!! virulent if position 585 is C and 480 is G
	{'U', 649, false, false, 0},
	{'U', 674, false, false, 0},
	{'U', 935, false, false, 0},
	{'C', 1208, false, false, 0},
	{'C', 1228, false, false, 0},
	{'G', 1442, false, false, 0},
	{'U', 1465, false, false, 0},
	{'U', 1490, false, false, 0},
	{'A', 1507, false, false, 0},
	{'U', 1747, false, false, 0},
	{'U', 1885, false, false, 0},
	{'A', 1942, false, false, 0},
	{'A', 1944, false, false, 0},
	{'C', 2353, false, false, 0},
	{'A', 2438, false, false, 0},
	{'G', 2545, false, false, 0},
	{'G', 2585, false, false, 0},
	{'G', 2741, false, false, 0},
	{'A', 2749, false, false, 0},
	{'U', 2762, false, false, 0},
	{'A', 2775, false, false, 0},
	{'A', 2795, false, false, 0},
	{'U', 2879, false, false, 0},
	{'C', 3163, false, false, 0},
	{'U', 3445, false, false, 0},
	{'G', 3460, false, false, 0},
	{'U', 3492, false, false, 0},
	{'C', 3766, false, false, 0},
	{'A', 3785, false, false, 0},
	{'G', 3896, false, false, 0},
	{'A', 3898, false, false, 0},
	{'U', 3919, false, false, 0},
	{'U', 4003, false, false, 0},
	{'C', 4116, false, false, 0},
	{'C', 4444, false, false, 0},
	{'G', 4789, false, false, 0},
	{'C', 5107, false, false, 0},
	{'G', 5137, false, false, 0},
	{'A', 5420, false, false, 0},
	{'G', 5440, false, false, 0},
	{'A', 6140, false, false, 0}, // !!! can be neurovirulent, but does not distinguish Sabin1 from Mahoney
	{'A', 6143, false, false, 0},
	{'C', 6203, false, false, 0},
	{'U', 6373, false, false, 0},
	{'A', 6616, false, false, 0},
	{'C', 6679, false, false, 0},
	{'U', 6853, false, false, 0},
	{'U', 7071, false, false, 0},
	{'A', 7198, false, false, 0},
	{'A', 7243, false, false, 0},
	{'C', 7410, false, false, 0},
	{'Z', 7441, false, false, 0}
};
#define NUM_FOOBAR2_POSITIONS (sizeof(Foobar2Positions) / sizeof(struct SPosition))

struct SPosition Foobar3Positions[] =
{
	{'Z', 21, false, false, 0},
	{'U', 189, false, false, 0},
	{'G', 480, false, false, 0},
	{'W', 525, false, false, 0},  // !!! virulent if position 585 is C and 480 is G
	{'U', 649, false, false, 0},
	{'U', 674, false, false, 0},
	{'U', 935, false, false, 0},
	{'C', 1208, false, false, 0},
	{'C', 1228, false, false, 0},
	{'G', 1442, false, false, 0},
	{'U', 1465, false, false, 0},
	{'U', 1490, false, false, 0},
	{'A', 1507, false, false, 0},
	{'U', 1747, false, false, 0},
	{'U', 1885, false, false, 0},
	{'A', 1942, false, false, 0},
	{'A', 1944, false, false, 0},
	{'C', 2353, false, false, 0},
	{'A', 2438, false, false, 0},
	{'G', 2545, false, false, 0},
	{'G', 2585, false, false, 0},
	{'G', 2741, false, false, 0},
	{'A', 2749, false, false, 0},
	{'U', 2762, false, false, 0},
	{'A', 2775, false, false, 0},
	{'A', 2795, false, false, 0},
	{'U', 2879, false, false, 0},
	{'C', 3163, false, false, 0},
	{'U', 3445, false, false, 0},
	{'A', 3460, false, false, 0},
	{'C', 3492, false, false, 0},
	{'U', 3766, false, false, 0},
	{'G', 3785, false, false, 0},
	{'G', 3896, false, false, 0},
	{'A', 3898, false, false, 0},
	{'U', 3919, false, false, 0},
	{'U', 4003, false, false, 0},
	{'C', 4116, false, false, 0},
	{'C', 4444, false, false, 0},
	{'G', 4789, false, false, 0},
	{'C', 5107, false, false, 0},
	{'G', 5137, false, false, 0},
	{'A', 5420, false, false, 0},
	{'G', 5440, false, false, 0},
	{'A', 6140, false, false, 0}, // !!! can be neurovirulent, but does not distinguish Sabin1 from Mahoney
	{'A', 6143, false, false, 0},
	{'C', 6203, false, false, 0},
	{'U', 6373, false, false, 0},
	{'A', 6616, false, false, 0},
	{'C', 6679, false, false, 0},
	{'U', 6853, false, false, 0},
	{'U', 7071, false, false, 0},
	{'A', 7198, false, false, 0},
	{'A', 7243, false, false, 0},
	{'C', 7410, false, false, 0},
	{'Z', 7441, false, false, 0}
};
#define NUM_FOOBAR3_POSITIONS (sizeof(Foobar3Positions) / sizeof(struct SPosition))

#endif  /* FIXEDSTATE_H_ */
