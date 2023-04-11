#include "ConvexHullChansAlgorithm.h"
#include "Utilities.h"
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;



Number angleFactor(SimplePoint2D sp)
{
    if (sp.x == Number("0") && sp.y == Number("0"))
        return Number("2");     // the origin is always first
    return sp.x.sign() * (sp.x.square() / (sp.x.square() + sp.y.square()));
}

// from Grahamscan(Richard)
bool angularCompareFunc(SimplePoint2D p1, SimplePoint2D p2)
{

    Number a1 = angleFactor(p1);
    Number a2 = angleFactor(p2);
    SimplePoint2D origin = SimplePoint2D(Number("0"), Number("0"));\

    if (a1 != a2)
        return a1 > a2;
    else
        return distSquared(origin, p1) > distSquared(origin, p2);
}

vector<SimplePoint2D> arrangeHull(vector<SimplePoint2D> points)
{
    vector<SimplePoint2D> hull;
    int min = 0;
    for(int i=0; i<points.size(); i++){

    }
}

vector<SimplePoint2D> internalGrahamScan(vector<SimplePoint2D> pointset, int start, int end)
{
    vector<SimplePoint2D> points(&pointset[start],&pointset[end]);

    if (points.size() <= 3)
        return points;

    SimplePoint2D p0 = points[0];
    for (SimplePoint2D p : points) {
        if ((p.y < p0.y) || (p.y == p0.y && p.x < p0.x))
            p0 = p;
    }

    // This is a lambda expression. It will be used by std::sort to order the points.
    // A lambda function is needed here because the ordering is dependent on p0.
    auto comp = [p0](SimplePoint2D p1, SimplePoint2D p2) {
        return angularCompareFunc(relativeCoord(p0, p1), relativeCoord(p0, p2));
    };

    // Sort points by polar angle with p0
    sort(points.begin(), points.end(), comp);

    vector<SimplePoint2D> stack;
    for (SimplePoint2D p : points) {
        while (stack.size() > 1 && isCounterClockwiseTurn(stack[stack.size()-2], stack.back(), p) <= 0) {
            stack.pop_back();
        }
        stack.push_back(p);
    }

    return stack;

}

pair<bool,vector<SimplePoint2D>> partialHull(vector<SimplePoint2D> points, int m){
    int k = ceil(points.size() / m);
    vector<vector<SimplePoint2D>> subHulls;
    int start;
    int end;
    for(int i=0; i<k; i++){
        start = i*m;
        end = i*m + m;
        if(end > points.size()){end = points.size();}
        subHulls[i] = internalGrahamScan(points,start,end);
    }

}

Region2D ConvexHullChansAlgorithm(Point2D pointset)
{
    bool done = false;
    vector<SimplePoint2D> points;
    vector<SimplePoint2D> hull;
    pair<bool, vector<SimplePoint2D>> partial;

    for(Point2D::Iterator itr = pointset.begin(); itr != pointset.end(); itr++)
    {
        points.push_back(*itr);
    }

    if(points.size() < 3){
        return Region2D();
    }
    else if(points.size() == 3){
        return Region2D(pointsToSegments(points));
    }
    else{
        int count = 1;
        int m;
        while(!done)
        {
            m = min((int)pow(2,pow(2,count)), (int)points.size());
            partial = partialHull(points,m);
            if(partial.first){
                done = true;
            }
            count++;
        }
    }
    hull = partial.second;
    return Region2D(pointsToSegments(hull));
}
