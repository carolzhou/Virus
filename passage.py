########################################################################
#
# Module:  passage.py
# 
# This class manages the data for a given passage in a simulation
# 
# Programmer:  C Zhou
#
# Date:  21 December 2015
#
# License:  See LICENSE.md for license information
#
########################################################################

import sys
import re
import copy
import math

statisticsSet = {
    "min"       : 0.0,
    "max"       : 0.0,
    "mean"      : 0.0,
    "median"    : 0.0,
    "stddev"    : 0.0,
    "upper"     : 0.0,  # mean + stddev
    "lower"     : 0.0,  # mean - stddev
}

# The statKeyList list enables printing in correct order in PrintStatistics2fileTabbed(). Note: this corresponds to
# the statHeaderString in simulation.py

statKeyList = ["populationGenotypes","distinctGenotypes","populationDiversity","populationMin","populationMax","populationMean","populationMedian","health","defectives","averageFitness","viability","generations","neurovirulentGenotypes","neurovirulenceScore","averageNeurovirulenceIndex","MahoneyGenotypes","MahoneyMutations","MahoneyReversion"]

p_viable = re.compile('[Vv]iable')
p_extinct = re.compile('[Ee][Xx][Tt][Ii][Nn][Cc][Tt]')

class Passage(object):
 
    def __init__(self,passageNumber):
        self.passageNumber = passageNumber 

        self.passageReportValues = {
            "populationGenotypes"        : [],  # list of values arising from individual simulations
            "distinctGenotypes"          : [],
            "populationDiversity"        : [],
            "populationRange"            : [],  # gets split on '-' to create min and max
            "populationMin"              : [],
            "populationMax"              : [],
            "populationMean"             : [],
            "populationMedian"           : [],
            "health"                     : [],
            "defectives"                 : [],
            "averageFitness"             : [],
            "viability"                  : [],
            "generations"                : [],
            "neurovirulentGenotypes"     : [],
            "neurovirulenceScore"        : [],
            "averageNeurovirulenceIndex" : [],
            "MahoneyGenotypes"           : [],
            "MahoneyMutations"           : [],
            "MahoneyReversion"           : [],
        }

        self.passageStatistics = {
            "populationGenotypes"        : {},  # holds a statisticsSet object
            "distinctGenotypes"          : {},
            "populationDiversity"        : {},
            "populationMin"              : {},
            "populationMax"              : {},
            "populationMean"             : {},
            "populationMedian"           : {},
            "health"                     : {},
            "defectives"                 : {},
            "averageFitness"             : {},
            "viability"                  : {},
            "generations"                : {},
            "neurovirulentGenotypes"     : {},
            "neurovirulenceScore"        : {},
            "averageNeurovirulenceIndex" : {},
            "MahoneyGenotypes"           : {},
            "MahoneyMutations"           : {},
            "MahoneyReversion"           : {},
        }

        for key in self.passageStatistics:
            newStatisticsSet = copy.deepcopy(statisticsSet)
            self.passageStatistics[key] = newStatisticsSet

    def PrintAll(self):
        print "************************************"
        print "Passage Number:", self.passageNumber
        self.PrintReportValues()
        self.PrintStatistics()

    def PrintReportValues(self):
        print "REPORT VALUES:"
        for key in self.passageReportValues:
            print key, ":", self.passageReportValues[key]

    def PrintStatistics(self):
        print "STATISTICS:"
        for key in self.passageStatistics:
            print key, ":", self.passageStatistics[key] 
       
    def PrintStatistics2file(self,FILE_HANDLE):
        FILE_HANDLE.write("%s%s%s\n" % ("STATISTICS for passage ", self.passageNumber, ":"))
        for key in self.passageStatistics:
            FILE_HANDLE.write("%s%s\n" % (key,": ",self.passageStatistics[key]))

    def PrintStatistic2fileTabbed(self,FILE_HANDLE,statistic): 
        FILE_HANDLE.write("%s\t" % (self.passageNumber))
        if statistic in statisticsSet.keys():
            for key in statKeyList:
                FILE_HANDLE.write("%s\t" % (self.passageStatistics[key][statistic]))
            FILE_HANDLE.write("\n")
        else:
            print "ERROR: Unknown statistic,", statistic

    def PrintAll_verbose(self):
        print "************************************"
        print "Passage Number:", self.passageNumber
        print "REPORT VALUES:"
        print "Number of genotypes in population:", self.passageReportValues["populationGenotypes"]
        print "Number of distinct genotypes:", self.passageReportValues["distinctGenotypes"]
        print "Population diversity measures:", self.passageReportValues["populationDiversity"]
        print "Ranges of genotype counts per distinct genotype:", self.populationReportValues["populationRange"]
        print "Minimun number of genotype counts per distinct genotype:", self.populationReportValues["populationMin"]
        print "Maximun number of genotype counts per distinct genotype:", self.populationReportValues["populationMax"]
        print "Mean number of genotypes per distinct genotype:", self.populationReportValues["populationMean"]
        print "Median number of genotypes per distinct genotype:", self.populationReportValues["populationMedian"]
        print "Population health measure:", self.populationReportValues["health"]
        print "Number of defective interfering particles in population:", self.populationReportValues["defectives"]
        print "Average fitness value in the population:", self.populationReportValues["averageFitness"]
        print "Populations that remain viable:", self.populationReportValues["viability"], "%"
        print "Number of generations to achieve burst:", self.populationReportValues["generations"]
        print "Number of neurovirulent genotypes:", self.populationReportValues["neurovirulentGenotypes"]
        print "Neurovirulence score:", self.populationReportValues["neurovirulenceScore"]
        print "Average neurovirulence score among neurovirulent genotypes:", self.populationReportValues["averageNeurovirulenceIndex"]
        print "Number of Mahoney genotypes:", self.populationReportValues["MahoneyGenotypes"]
        print "Total number a Mahoney muations across the population:", self.populationReportValues["MahoneyMutations"]
        print "Degree of Mahoney reversion across the population:", self.populationReportValues["MahoneyReversion"]
        print "\nSTATISTICS: min, max, mean, median, standard deviation, upper, lower"
        PrintStatistics()

    def CalculateStatistics(self):

        for key in self.passageReportValues:
            #print "key is", key
            sum       = 0.0
            min       = sys.maxint 
            max       = 0.0
            mean      = 0.0
            median    = 0.0
            stddev    = 0.0  # standard deviation
            upper     = 0.0  # mean + stddev
            lower     = 0.0  # mean - stddev
            N         = 0    # number of values
            middle    = 0    # index of middle value (sorted)
            viable    = 0
            extinct   = 0

            if (key == "viability"):
                for value in self.passageReportValues[key]:
                    match = re.search(p_viable,value)
                    if match:
                        viable += 1
                    match = re.search(p_extinct,value)
                    if match:
                        extinct += 1 
                total = viable + extinct
                N = len(self.passageReportValues[key])
                if total < N:
                    print "WARNING: incomplete data detected for viability in passage::CalculateStatistics()"
                if total > 0:
                    mean = (float(viable) / float(total)) * 100.0 

            elif (key == "populationRange"):
                pass # Note: population range was already split to PopMin, PopMax)

            else:  # All others are numeric 
                N = len(self.passageReportValues[key])

                for number in self.passageReportValues[key]: # Calculate sum (total), minimum, and maximum
                    sum += float(number)
                    if min > float(number):
                        min = float(number)
                    if max < float(number):
                        max = float(number)

                if (sum > 0.0 and N > 0):  # Calculate mean, standard deviation, and median
                    # Mean (average)
                    mean = sum / float(N)

                    # Standard deviation
                    # First, calculate squares of differences
                    sumOfDiffsSquared = 0
                    for number in self.passageReportValues[key]:
                        differenceSquared = pow((mean - float(number)), 2.0)
                        sumOfDiffsSquared += differenceSquared
                    stddev = math.sqrt((1.0/float(N)) * sumOfDiffsSquared) 

                    # Median
                    # First, numerically order the numbers in the list
                    numberList = self.passageReportValues[key] 
                    numberList = [float(x) for x in numberList]
                    numberList.sort()
                    # Second, find the index of the "middle" value
                    middle = N / 2 
                    # Third, take middle value as median if len(list) is odd, else split middle 2
                    if (N % 2 == 0):
                        median = (float(numberList[middle]) + float(numberList[middle-1]))/2.0
                    else:
                        median = float(numberList[middle])

                    # Calculate upper and lower, as the mean plus or minus the standard deviation
                    upper = mean + stddev 
                    lower = mean - stddev

            # Record statistics
            if (key != "populationRange"):
                self.passageStatistics[key]["min"]    = min 
                self.passageStatistics[key]["max"]    = max 
                self.passageStatistics[key]["mean"]   = mean 
                self.passageStatistics[key]["median"] = median 
                self.passageStatistics[key]["stddev"] = stddev 
                self.passageStatistics[key]["upper"]  = upper
                self.passageStatistics[key]["lower"]  = lower
