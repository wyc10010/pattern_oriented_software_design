#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <algorithm>
#include "./shape.h"

template <class RandomAccessIterator, class Compare>
void quickSort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) { 
    int size = std::distance(first, last);
    if (size < 2) return;

    RandomAccessIterator idx = first-1;
    for(RandomAccessIterator i = first ; i != (last-1); i++) {
        if(comp(*i, *(last-1))){
            idx++;
            std::swap(*i, *idx);
        }
    }
    idx++;
    std::swap(*idx, *(last-1));

    quickSort(first, idx, comp);
    quickSort(idx+1, last, comp);
}

bool areaAscendingCompare(Shape *a, Shape *b) {
    return a->area() < b->area();
};

bool areaDescendingCompare(Shape *a, Shape *b) {
    return a->area() > b->area();
};

bool perimeterAscendingCompare(Shape *a, Shape *b) {
    return a->perimeter() < b->perimeter();
};

bool perimeterDescendingCompare(Shape *a, Shape *b) {
    return a->perimeter() > b->perimeter();
};

class AscendingCompare{
public:
    AscendingCompare(std::string feature): _feature(feature) {}

    bool operator()(Shape *a, Shape *b) const {
        if (_feature == "area") {
            return a->area() < b->area();
        } else if (_feature == "perimeter") {
            return a->perimeter() < b->perimeter();
        }
        return 0;
    }

private:
    std::string _feature;
};

class DescendingCompare{
public:
    DescendingCompare(std::string feature): _feature(feature) {}

    bool operator()(Shape *a, Shape *b) {
        if (_feature == "area") {
            return a->area() > b->area();
        } else if (_feature == "perimeter") {
            return a->perimeter() > b->perimeter();
        }
        return 0;
    }

private:
    std::string _feature;
};

#endif