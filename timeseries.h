//
// Created by Naser Ihab on 20/12/2021.
//

#ifndef UNTITLED4_TIMESERIES_H
#define UNTITLED4_TIMESERIES_H
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <string>
using namespace std;
class TimeSeries{
public:
    vector<pair<string,vector<float>>> result;
    TimeSeries(const char* CSVfileName);
    int getraw(){
        return result[0].second.size();
    }
};
#endif //UNTITLED4_TIMESERIES_H
