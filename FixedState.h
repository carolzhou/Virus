/*
 * FixedState.h
 *
 *  Created on: May 27, 2009
 *      Author: Carol Zhou
 *
 *  This file contains fixed genome states.
 */

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
