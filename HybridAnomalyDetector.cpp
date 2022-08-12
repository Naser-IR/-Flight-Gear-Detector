//
// Created by Naser Ihab on 20/12/2021.
//
#include "HybridAnomalyDetector.h"

vector<AnomalyReport> HybridAnomalyDetector::detect(const TimeSeries& ts) {
    vector<AnomalyReport> reports;
    vector<float> temp1;
    vector<float> temp2;
    for (int i = 0; i < Cf.size(); ++i) {
        string f1 = Cf[i].feature1;
        string f2 = Cf[i].feature2;
        for (int j = 0; j < ts.result.size(); j++) {
            if (f1 == ts.result[j].first) {
                temp1 = ts.result[j].second;
            }
            if (f2 == ts.result[j].first) {
                temp2 = ts.result[j].second;
                break;

            }
        }
        Point *parr[temp1.size()];
        for (int k = 0; k < temp1.size(); k++) {
            parr[k] = new Point(temp1[k], temp2[k]);
        }
        if (Cf[i].corrlation >= 0.9) {
            for (int l = 0; l < temp1.size(); ++l) {
                if (dev(*parr[l], Cf[i].lin_reg) > Cf[i].threshold) {
                    AnomalyReport report(Cf[i].feature1 + "-" + Cf[i].feature2, l + 1);
                    reports.push_back(report);
                }
            }
        } else {
            for (int l = 0; l < temp1.size(); ++l) {
                if (dist(*parr[l], Cf[i].mincircle.center) > Cf[i].threshold) {
                    AnomalyReport report(Cf[i].feature1 + "-" + Cf[i].feature2, l + 1);
                    reports.push_back(report);
                }
            }
        }
    }
    return reports;
}
HybridAnomalyDetector::HybridAnomalyDetector() {}
HybridAnomalyDetector::~HybridAnomalyDetector() noexcept {}

