//
// Created by Naser Ihab on 20/12/2021.
//

#ifndef UNTITLED4_MINCIRCLE_H
#define UNTITLED4_MINCIRCLE_H
#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"
using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
    Point center;
    float radius;
    Circle(Point c,float r):center(c),radius(r){}

    Circle() {}
};
// --------------------------------------

Circle findMinCircle(Point** points,size_t size);
Circle welzl_helper(vector<Point> P_copy, vector<Point> R, int n);
Circle  min_circle_trivial(vector<Point>& R);
float dist(const Point& a, const Point& b);

#endif //UNTITLED4_MINCIRCLE_H
