//
// Created by Naser Ihab on 20/12/2021.
//


#include <string>
#include <vector>
#include <utility> // std::pair
#include <algorithm>
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include "HybridAnomalyDetector.h"
#include "minCircle.h"
#include "SimpleAnomalyDetector.h"
using namespace std;
vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
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
        for (int l = 0; l < temp1.size(); ++l) {
            if (dev(*parr[l], Cf[i].lin_reg) > Cf[i].threshold) {
                AnomalyReport report(Cf[i].feature1 + "-" + Cf[i].feature2, l + 1);
                reports.push_back(report);
            }
        }
    }
    return reports;
}
void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts) {
    vector<pair<string,vector<float>>>::const_iterator col1;
    vector<pair<string,vector<float>>>::const_iterator col2;
    vector<pair<string,vector<float>>>::const_iterator temp;
    correlatedFeatures curr;
    for(col1= ts.result.begin(); col1!=ts.result.end();col1++){
        curr.threshold = this->threshold; // if error try to put it in the next forrr
        float m=0;
        // might give runtime error
        for (col2 =col1+1;col2!=ts.result.end();col2++) {
            if (col1==col2)
                continue;
            float arr[col1->second.size()];
            float arr2[col2->second.size()];
            for (int i = 0; i < col1->second.size(); i++) {
                arr[i] = col1->second[i];
                arr2[i] = col2->second[i];
            }
            int i=col1->second.size();
            if ((pearson(arr,arr2,col1->second.size()) > m) && (pearson(arr,arr2,col1->second.size()) >= 0.5||
                                                                (pearson(arr,arr2,col1->second.size()) >= curr.threshold))) { //<=
                m=pearson(arr,arr2,col1->second.size());
                temp=col2;
            }
        }
        Point* parr[temp->second.size()];
        for (int i = 0; i < temp->second.size() ;++i ) { // fix was col1
            float x = col1->second[i];
            float y = temp->second[i];
            parr[i] = new Point(x,y);
        }
        if (m!=0) { //
            curr.corrlation = m;
            if (m >= curr.threshold) {
                Line reg = linear_reg(parr, temp->second.size());
                curr.lin_reg = reg;
                float j=0;
                for (int i = 0; i < temp->second.size(); ++i) {
                    if (dev(*parr[i],curr.lin_reg) > j)
                        j=dev(*parr[i],curr.lin_reg);
                }
                curr.maxdis=j;
                curr.threshold=j*1.1;
            } else {
                curr.mincircle = findMinCircle(parr,temp->second.size());
                curr.threshold=curr.mincircle.radius*1.1;
            }
            curr.feature1 = col1->first;
            curr.feature2 = temp->first;
            Cf.push_back(curr); //move
        }
    }

}
SimpleAnomalyDetector::SimpleAnomalyDetector(){
}
SimpleAnomalyDetector::~SimpleAnomalyDetector(){
}