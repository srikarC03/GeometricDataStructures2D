#include "Point2D.h"
#include <algorithm>
#include <iostream>
using namespace std;


struct Point2D::Impl
{
    Impl(){};

    Impl(vector<SimplePoint2D> _pointCollection): pointCollection(move(_pointCollection)){};

    vector<SimplePoint2D> pointCollection;
    
    bool ordered;
};
Point2D::Point2D() {}


Point2D::Point2D(vector<SimplePoint2D> _pointCollection):pimpl(new Impl())
{
    _pointCollection.erase(unique(_pointCollection.begin(), _pointCollection.end()), _pointCollection.end());
    sort(_pointCollection.begin(), _pointCollection.end());
    this->pimpl->pointCollection = _pointCollection;
    this->pimpl->ordered = true;
}

Point2D::Point2D(vector<SimplePoint2D> _pointCollection, bool _ordered):pimpl(new Impl())
{
   this->pimpl->ordered = _ordered;
   if(_ordered){
        _pointCollection.erase(unique(_pointCollection.begin(), _pointCollection.end()), _pointCollection.end());
        sort(_pointCollection.begin(), _pointCollection.end());
   }
   this->pimpl->pointCollection = _pointCollection;
}

Point2D::Point2D(Point2D const &sourcePoint2D): pimpl(new Impl(*sourcePoint2D.pimpl))
{
}

Point2D::Point2D(Point2D &&sourcePoint2D)
{
    this->pimpl = move(sourcePoint2D.pimpl);
    sourcePoint2D.pimpl = nullptr;
}

Point2D::~Point2D(){}

bool Point2D::isOrdered()
{
    return this->pimpl->ordered;
}

int Point2D::count()
{
    return this->pimpl->pointCollection.size();
}

Point2D::Iterator Point2D::begin()
{
    return Iterator(&(this->pimpl->pointCollection)[0]);
}

Point2D::Iterator Point2D::end()
{
    return Iterator(&(this->pimpl->pointCollection)[size(this->pimpl->pointCollection)]);
}
