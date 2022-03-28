#ifndef SHAPE_SETTER_H
#define SHAPE_SETTER_H

#include "../src/shape.h"
#include "../src/filter.h"

class Filter;
typedef void (*Setter)(Shape *);

class ShapeSetter : public Filter {
public:

    ShapeSetter(Setter set) {
        _set = set;
    }

    Filter* setNext(Filter* filter) {
        _next = filter;
        return _next;
    }

    std::list<Shape*> push(std::list<Shape*> shapes) {
        // push down setted data and return result.
        if(shapes.size()!=0) {
            for(auto it = shapes.begin(); it != shapes.end(); ++it) {
                _set(*it);
            }   

        }
        if(_next) {
            return _next->push(shapes);
        }
        return shapes;
    }

private:
    Setter _set;
    Filter * _next = nullptr;
    std::list<Shape*> _result;
};

#endif
