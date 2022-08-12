//
// Created by Naser Ihab on 20/12/2021.
//

#ifndef UNTITLED4_ANOMALYDETECTOR_H
#define UNTITLED4_ANOMALYDETECTOR_H
#include "timeseries.h"

using namespace std;
class AnomalyReport{
public:
    const string description;
    const long timeStep;
    // long getts(){
    //     return this->timeStep;
    // }
    AnomalyReport(string description, long timeStep) :
            description(description),timeStep(timeStep){}
};
class TimeSeriesAnomalyDetector {
public:
    virtual void learnNormal(const TimeSeries& ts)=0;
    virtual vector<AnomalyReport> detect(const TimeSeries& ts)=0;
    virtual ~TimeSeriesAnomalyDetector(){}
};
#endif //UNTITLED4_ANOMALYDETECTOR_H
