//
// Created by Naser Ihab on 20/12/2021.
//

#ifndef UNTITLED4_HYBRIDANOMALYDETECTOR_H
#define UNTITLED4_HYBRIDANOMALYDETECTOR_H
#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
    HybridAnomalyDetector();
    virtual ~HybridAnomalyDetector();

    vector<AnomalyReport> detect(const TimeSeries &ts);
};
#endif //UNTITLED4_HYBRIDANOMALYDETECTOR_H
