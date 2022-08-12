//
// Created by Naser Ihab on 20/12/2021.
//

#include <math.h>
#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"
#include "minCircle.h"

bool is_inside(const Circle& c, const Point& p)
{
    return dist(c.center, p) <= c.radius;
}

bool is_valid_circle(const Circle& c,const vector<Point>&  P)
{
    // Iterating through all the points
    // to check  whether the points
    // lie inside the circle or not
    for (const Point& p : P)
        if (!is_inside(c, p))
            return false;
    return true;
}

Point get_circle_center(float bx, float by,
                        float cx, float cy)
{
    float B = bx * bx + by * by;
    float C = cx * cx + cy * cy;
    float D = bx * cy - by * cx;
    return { (cy * B - by * C) / (2 * D),(bx * C - cx * B) / (2 * D) };
}


float dist(const Point& a, const Point& b)
{
    return sqrt(((a.x - b.x)*(a.x - b.x)) + ((a.y - b.y)*(a.y - b.y)));
}
// Function to return a unique circle that
// intersects three points
Circle circle_from(const Point& A, const Point& B,
                   const Point& C)
{
    Point I = get_circle_center(B.x - A.x, B.y - A.y,C.x - A.x, C.y - A.y);

    I.x += A.x;
    I.y += A.y;
    return { I, dist(I, A) };
}

// Function to return the smallest circle
// that intersects 2 points
Circle circle_from(const Point& A, const Point& B)
{
    // Set the center to be the midpoint of A and B
    Point C = { (((A.x + B.x) / 2)), (((A.y + B.y) / 2)) };

    // Set the radius to be half the distance AB
    return { C, (dist(A, B) / 2) };
}
Circle  min_circle_trivial(vector<Point>& R) {
    if (R.empty()) {
        return { { 0, 0 }, 0 };
    }
    else if (R.size() == 1) {
        return {R[0], 0 };
    }
    else if (R.size() == 2) {
        return circle_from(R[0], R[1]);
    }

    // To check if MEC can be determined
    // by 2 points only
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {

            Circle c = circle_from(R[i], R[j]);
            if (is_valid_circle(c, R))
                return c;
        }
    }
    return circle_from(R[0], R[1], R[2]);
}
Circle welzl_helper(Point** P, vector<Point> R, int n){
    // Base case when all points processed or |R| = 3
    if (n == 0 || R.size() == 3) {
        return min_circle_trivial(R);
    }

    // Pick a random point randomly
    int idx = rand() % n;
    Point p = *P[idx];

    // Put the picked point at the end of P
    // since it's more efficient than
    // deleting from the middle of the vector
    swap(P[idx], P[n - 1]);

    // Get the MEC circle d from the
    // set of points P - {p}
    Circle d = welzl_helper(P, R, n - 1);

    // If d contains p, return d
    if (is_inside(d, p)) {
        return d;
    }

    // Otherwise, must be on the boundary of the MEC
    R.push_back(p);

    // Return the MEC for P - {p} and R U {p}
    return welzl_helper(P, R, n - 1);
}
Circle findMinCircle(Point** points,size_t size){

    return welzl_helper(points,{},size);
}