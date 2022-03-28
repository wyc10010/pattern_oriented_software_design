#ifndef SHAPE_FILTER_H
#define SHAPE_FILTER_H

#include "../src/shape.h"
#include "../src/filter.h"
#include <list>

class Filter;
typedef bool (*Predicate)(Shape *);

class ShapeFilter : public Filter {
public:

    ShapeFilter(Predicate pred) {
        _pred = pred;
    }

    Filter* setNext(Filter* filter) { 
        _next = filter;
        return _next;
    }

    std::list<Shape*> push(std::list<Shape*> shapes) {
        if(shapes.size()!=0) {
            for(auto it = shapes.begin(); it != shapes.end(); ++it) {
                if(_pred(*it)) {
                    _result.push_back(*it);
                } 
            }   
        }
        if(_next) {
            return _next->push(_result);
        }
        return _result;
    }


private:
    Predicate _pred;
    Filter * _next = nullptr;
    std::list<Shape*> _result;
};

#endif
