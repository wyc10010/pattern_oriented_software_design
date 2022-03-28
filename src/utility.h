#ifndef UTILITY_H
#define UTILITY_H

#include "iterator.h"
#include "compound_shape.h"
#include <deque>

Shape* getShapeById(Shape* shape, std::string id) {
    Iterator * it = shape->createIterator();
    try {
        it->first();
    } catch(std::string e) {
        throw (std::string("Only compound shape can get shape!"));
    }

    for(it->first(); !it->isDone(); it->next()) {
        Shape * s = it->currentItem();
        if(s->id() == id) {
            return s;
        }
        try {
            return getShapeById(s, id);
        } catch(std::string e) {}
    } 
    throw (std::string("Expected get shape but shape not found"));
}

template <class Filter>
std::deque<Shape*> filterShape(Shape* shape, Filter filter) {
    Iterator * it = shape->createIterator();

    try {
        it->first();
    } catch(std::string e) {
        throw (std::string("Only compound shape can filter shape!"));
    }
    
    std::deque<Shape*> res;
    std::deque<Shape*> restwo;
    for(it->first(); !it->isDone(); it->next()) {
        Shape * s = it->currentItem();
        if(filter(s)) {
            res.push_back(s);
        }
        try {
            restwo = filterShape(s, filter);
            while (!restwo.empty()) {
                res.push_back(restwo.front());
                restwo.pop_front();
            }
        } catch(std::string e) {}
    }
    return res;
}

class AreaFilter {
public:
    AreaFilter(double upperBound, double lowerBound) {
        _upperBound = upperBound;
        _lowerBound = lowerBound;
    }
    bool operator() (Shape* shape) const {
        return shape->area() <= _upperBound && shape->area() >= _lowerBound;
    }
private:
        double _upperBound;
        double _lowerBound;
};

class PerimeterFilter {
    public:
    PerimeterFilter(double upperBound, double lowerBound) {
        _upperBound = upperBound;
        _lowerBound = lowerBound;
    }
    bool operator() (Shape* shape) const {
        return shape->perimeter() <= _upperBound && shape->perimeter() >= _lowerBound;
    }
    private:
        double _upperBound;
        double _lowerBound;
};

class ColorFilter {
    public:
    ColorFilter(std::string color) {
        _color = color;
    }
    bool operator() (Shape* shape) const {
        return shape->color() == _color;
    }
    private:
        std::string _color;
};

class TypeFilter {
    public:
    TypeFilter(std::string type) {
        _type = type;
    }
    bool operator() (Shape* shape) const {
        return shape->type() == _type;
    }
    private:
        std::string _type;
};

#endif