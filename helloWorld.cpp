#include <iostream>
#include "ConvexHullDivideandConquer.h"
#include "ConvexHullJarvisMarch.h"
#include "ConvexHullIncremental.h"
#define PT(X, Y) SimplePoint2D(Number(#X), Number(#Y))
using namespace std;

vector<SimplePoint2D> randomVectorSimplePoint2D(long count, int minX, int maxX, int minY, int maxY)
{
    generateSeed();
    std::vector<SimplePoint2D> points;
    for (long i = 0; i < count; i++)
        points.push_back(randomSimplePoint2D(minX, maxX, minY, maxY));
    return points;
}

int main()
{  
    vector<SimplePoint2D> test2 = randomVectorSimplePoint2D(1000,0,1500,0,1500);
    Point2D test = Point2D(test2,false);
    //Region2D r1 = ConvexHullDivideandConquer(test);
    //cout<<"======================="<<endl;
    Region2D r2 = ConvexHullJarvisMarch(test);
    //cout<<"======================="<<endl;
    //Region2D r3 = ConvexHullIncremental(test);
}