//
// Created by Naser Ihab on 20/12/2021.
//
#include <iostream>
#include <math.h>
#include "anomaly_detection_util.h"
/* naser rabah
 * 207811282
 * safwan butto
 * 206724015
 */


/*
 * name: average
 * input : float*, int
 * output : float
 * return the average of x
 */
float average(float* x, int size) {
    if ( size == 0 ) {
        throw std::invalid_argument( " size can not be zero" );
    } else {
        float sum = 0;
        for (int j = 0; j < size; ++j) {
            sum += x[j];
        }
        return (float)(sum /size);
    }
}

/*
 * name: var
 * input : float*, int
 * output : float
 * returns the variance of X and Y
 */
float var(float* x, int size) {
    if ( size == 0 ) {
        throw std::invalid_argument( " size can not be zero" );
    } else {
        float av = average(x, size);
        float sum = 0;
        for (int j = 0; j < size; ++j) {
            sum += pow((x[j] - av), 2);
        }
        return sum / size;
    }
}

/*
 * name: cov
 * input : float*, float*, int
 * output : float
 * returns the covariance of X and Y
 */
float cov(float* x, float* y, int size) {
    if ( size == 0 ) {
        throw std::invalid_argument( " size can not be zero" );
    } else {
        float avX = 0, avY = 0, sum = 0;
        avX = average(x, size);
        avY = average(y, size);
        for (int j = 0; j < size; ++j) {
            sum += (x[j] - avX) * (y[j] - avY);
        }
        return sum / size;
    }
}

/*
 * name: pearson
 * input : float*, float*, int
 * output : float
 * returns the Pearson correlation coefficient of X and Y
 */
float pearson(float* x, float* y, int size) {
    if ( size == 0 ) {
        throw std::invalid_argument( " size can not be zero" );
    } else {
        float Cov = 0;
        float rootX = 0, rootY = 0;
        Cov = cov(x, y, size);
        rootX = sqrt(var(x, size));
        rootY = sqrt(var(y, size));
        if ( (rootX * rootY) != 0) {
            return Cov / (rootX * rootY);
        } else {
            throw std::invalid_argument( "rootX * rootY is zero " );
        }
    }
}

/*
 * name: dev
 * input : Point, Line
 * output : float
 * returns the deviation between point p and the line
 */
float dev(Point p,Line l){
    float lineY = l.f(p.x);
    if (p.y >= lineY) {
        return p.y - lineY;
    } else {
        return lineY -p.y;
    }
}

/*
 * name: linear_reg
 * input : Point**, int
 * output : Line
 * performs a linear regression and return s the line equation
 */
Line linear_reg(Point** points, int size) {
    float X[size], Y[size];
    for (int i = 0; i < size; ++i) {
        X[i] = points[i]->x;
        Y[i] = points[i]->y;
    }
    float a = cov(X, Y, size) / var(X, size);
    float b = average(Y, size) - a * average(X, size);
    return Line(a, b);
}

/*
 * name: dev
 * input : Point, Point**, int
 * output : float
 * returns the deviation between point p and the line equation of the points
 */
float dev(Point p,Point** points, int size) {
    Line line = linear_reg(points , size);
    return dev(p, line);
}


