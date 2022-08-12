//
// Created by Naser Ihab on 20/12/2021.
//
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <map>
#include <string>
#include "timeseries.h"
using namespace std;


TimeSeries::TimeSeries(const char* CSVfileName) {
    ifstream myfile(CSVfileName);
    string line, colname;
    float val;
    if (myfile.good()) {
        getline(myfile, line);
        stringstream ss(line);
        while (getline(ss, colname, ',')) {
            result.push_back({colname, vector<float>{}});

        }
    }
    while (getline(myfile, line)) {
        // Create a stringstream of the current line
        stringstream ss(line);

        // Keep track of the current column index
        int colIdx = 0;

        // Extract each integer
        while (ss >> val) {

            // Add the current integer to the 'colIdx' column's values vector
            result.at(colIdx).second.push_back(val);

            // If the next token is a comma, ignore it and move on
            if (ss.peek() == ',') ss.ignore();
            // Increment the column index
            colIdx++;
        }
    }
}


