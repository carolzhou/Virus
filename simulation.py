############################################################################
#
# Module:  simulation.py
#
# This class manages simulation data for calculateStats_S2M.py. 
#
# Programmer:  C Zhou
# 
# Date:  21 December 2015
#
# License:  See LICENSE.md for license information
#
############################################################################

import os
import copy
import re
import passage

# Data Columns in replicate report files:
REPORT_NUMBER        = 0
POPULATION_GENOTYPES = 1
DISTINCT_GENOTYPES   = 2
DIVERSITY            = 3
POPULATION_MIN_MAX   = 4
POPULATION_MEAN      = 5
POPULATION_MEDIAN    = 6
HEALTH               = 7
DEFECTIVES           = 8
AVERAGE_FITNESS      = 9
VIABILITY            = 10
NUM_GENERATIONS      = 11
NEUROVIR_GENOTYPES   = 12
NEUROVIR_SCORE       = 13
AVE_NEUROVIR_INDEX   = 14
MAHONEY_GENOTYPES    = 15
MAHONEY_MUTATIONS    = 16
MAHONEY_REVERSION    = 17

# Note: the statHeaderString corresponds to the statKeyList in passage.py
statHeaderString = "#Passage\tPgentps\tDstinct\tDivrsty\tPopMin\tPopMax\tPopMean\tPopMedn\tHealth\tDefctvs\tAveFitn\tViablty\tGnratns\tNgentps\tNscore\tAvNindx\tMgentyps\tMutns\tRevrsn"

class SimulationData(object):

    def __init__(self,passageCount,fileList,dataPath,statPath,simulationName,parameterSetting):
        self.simulationName = simulationName      # eg, "recombination"
        self.parameterSetting = parameterSetting  # eg, "-r3"
        self.passageCount = passageCount          # eg., 200
        self.replicateCount = len(fileList)       # should be len(self.simulationFileList) = number of replicates
        self.simulationFileList = fileList        # files containing 'Report' data from simulations
        self.dataPath = dataPath                  # path to simulation data files
        self.statPath = statPath                  # path to statistics output files
        self.simulationData = []                  # list of passage objects 
        self.CreatePassages()                     # create a set of Passage objects

    def CreatePassages(self):  # This method should only be called once, by __init__
        for i in xrange(0,self.passageCount+1):   # If 200 passages, then there are 201 reports)
           self.simulationData.append(passage.Passage(i)) # Dynamically create new Passage object

    def PrintAll(self):
        print "\nSIMULATION: ", self.simulationName 
        print "Number of passages in simulation:", self.passageCount
        print "Parameter setting:", self.parameterSetting
        print "Number of replicates:", self.replicateCount
        print "Directory path for data:", self.dataPath
        print "Directory path for stats:", self.statPath
        print "Files containing report values:", self.simulationFileList
        print "Simulation data:"
        for passage in self.simulationData:
            passage.PrintAll()
            #passage.PrintAll_verbose()

    def PrintSimulationValues(self):
        for passage in self.simulationData:
            passage.PrintReportValues()

    def PrintStatistics(self):
        for passage in self.simulationData:
            passage.PrintStatistics()

    def PrintStatistics2file(self,FILE_HANDLE):
        for passage in self.simulationData:
            passage.PrintStatistics2file(FILE_HANDLE)

    def PrintAllStatistics2fileTabbed(self):
        self.PrintStatistic2fileTabbed('min')
        self.PrintStatistic2fileTabbed('max')
        self.PrintStatistic2fileTabbed('mean')
        self.PrintStatistic2fileTabbed('median')
        self.PrintStatistic2fileTabbed('stddev')
        self.PrintStatistic2fileTabbed('upper')
        self.PrintStatistic2fileTabbed('lower')

    # Print all values for a single statistic to file
    def PrintStatistic2fileTabbed(self,statistic):  # statistic is one of 'min','max','mean','median','stddev','upper','lower'
        newFile = self.simulationName + "_" +  self.parameterSetting + '_' + statistic + '.stat'
        statPathFile = os.path.join(self.statPath,newFile)
        FILE_HANDLE = open(statPathFile,"w")
        FILE_HANDLE.write("%s\n" % (statHeaderString))
        for passage in self.simulationData:
            passage.PrintStatistic2fileTabbed(FILE_HANDLE,statistic)
        FILE_HANDLE.close()

    def ProcessSimulationData(self):
        self.GetSimulationReportValues()
        self.CalculateStatistics()

    def GetSimulationReportValues(self):
        for file in self.simulationFileList:
            pathfile = os.path.join(self.dataPath,file)
            SIM_FILE = open (pathfile,"r")
            fLines = SIM_FILE.read().splitlines() 
            fLines.pop(0)  # remove header line  # "Report No." followed by column titles
            for line in fLines:
                fields = line.split('\t') 
                reportString = fields[REPORT_NUMBER]
                reportNumber = re.sub('Report ','',reportString) 
                passageNumber = int(reportNumber) - 1
                self.simulationData[passageNumber].passageReportValues["populationGenotypes"].append(fields[POPULATION_GENOTYPES])
                self.simulationData[passageNumber].passageReportValues["distinctGenotypes"].append(fields[DISTINCT_GENOTYPES])
                self.simulationData[passageNumber].passageReportValues["populationDiversity"].append(fields[DIVERSITY])
                self.simulationData[passageNumber].passageReportValues["populationRange"].append(fields[POPULATION_MIN_MAX])
                self.simulationData[passageNumber].passageReportValues["populationMean"].append(fields[POPULATION_MEAN])
                self.simulationData[passageNumber].passageReportValues["populationMedian"].append(fields[POPULATION_MEDIAN])
                self.simulationData[passageNumber].passageReportValues["health"].append(fields[HEALTH])
                self.simulationData[passageNumber].passageReportValues["defectives"].append(fields[DEFECTIVES])
                self.simulationData[passageNumber].passageReportValues["averageFitness"].append(fields[AVERAGE_FITNESS])
                self.simulationData[passageNumber].passageReportValues["viability"].append(fields[VIABILITY])
                self.simulationData[passageNumber].passageReportValues["generations"].append(fields[NUM_GENERATIONS])
                self.simulationData[passageNumber].passageReportValues["neurovirulentGenotypes"].append(fields[NEUROVIR_GENOTYPES])
                self.simulationData[passageNumber].passageReportValues["neurovirulenceScore"].append(fields[NEUROVIR_SCORE])
                self.simulationData[passageNumber].passageReportValues["averageNeurovirulenceIndex"].append(fields[AVE_NEUROVIR_INDEX])
                self.simulationData[passageNumber].passageReportValues["MahoneyGenotypes"].append(fields[MAHONEY_GENOTYPES])
                self.simulationData[passageNumber].passageReportValues["MahoneyMutations"].append(fields[MAHONEY_MUTATIONS])
                self.simulationData[passageNumber].passageReportValues["MahoneyReversion"].append(fields[MAHONEY_REVERSION])
                range = fields[POPULATION_MIN_MAX]
                (min,max) = range.split('-')
                self.simulationData[passageNumber].passageReportValues["populationMin"].append(min) 
                self.simulationData[passageNumber].passageReportValues["populationMax"].append(max) 
            SIM_FILE.close 

    def CalculateStatistics(self):
        for passage in self.simulationData:
            passage.CalculateStatistics()

