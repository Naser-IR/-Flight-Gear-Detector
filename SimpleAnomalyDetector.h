//
// Created by Naser Ihab on 20/12/2021.
//

#ifndef UNTITLED4_SIMPLEANOMALYDETECTOR_H
#define UNTITLED4_SIMPLEANOMALYDETECTOR_H
#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <map>
#include <algorithm>
#include <string>
#include "AnomalyDetector.h"
#include "anomaly_detection_util.h"
#include "minCircle.h"
using namespace std;

struct correlatedFeatures {

    string feature1,feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
    float maxdis;
    Circle mincircle;

};
class SimpleAnomalyDetector: public TimeSeriesAnomalyDetector {
    float threshold=0.9;
public:
    vector<correlatedFeatures> Cf;
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();
    virtual void learnNormal(const TimeSeries& ts) ;
    void setth(float th){
        this->threshold=th;
    }
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    vector<correlatedFeatures> getNormalModel(){
        return Cf;
    }
};
#endif //UNTITLED4_SIMPLEANOMALYDETECTOR_H
