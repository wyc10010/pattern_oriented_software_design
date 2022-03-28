#ifndef COMPOUND_SHAPE_H
#define COMPOUND_SHAPE_H

#include <list>

#include "shape.h"
#include "shape_iterator.h"
#include "iterator.h"
#include "visitor.h"

class CompoundShape : public Shape {
public:

    CompoundShape(std::string id, std::list<Shape*> shapes, std::string color = "transparent"):_shapes(shapes),Shape(id,color) {
        _shapes = shapes;
        // if(_shapes.size()==0) {
        //     throw(std::string("This is not a compound shape!"));
        // }
    }
    
    Iterator * createIterator() const {
        return new ShapeIterator<std::list<Shape *>::const_iterator>(_shapes.begin(), _shapes.end());
    }

    double area() const {
        double _area = 0;
        std::list<Shape *>::const_iterator ptr;
        for(ptr = _shapes.begin(); ptr != _shapes.end(); ptr++) {
            _area += (*ptr)->area();
        }
        return _area;
    }

    double perimeter() const { 
        double _perimeter = 0;
        std::list<Shape *>::const_iterator ptr;
        for(ptr = _shapes.begin(); ptr != _shapes.end(); ptr++) {
            _perimeter += (*ptr)->perimeter();
        }
        return _perimeter;
    }

    std::string info() const {
        std::string _detail; 
        std::string _res;
        std::list<Shape *>::const_iterator ptr;
        std::list<Shape *>::const_iterator ftr = _shapes.end();
        auto it1 = prev(ftr, 1); 

        for(ptr = _shapes.begin(); ptr != _shapes.end(); ptr++) {
            _detail += (*ptr)->info();
            if(ptr != it1) {
                _detail = _detail + ", ";
            }
        }
        _res = "Compound Shape {" + _detail + "}";
        return _res;
    }
    
    void addShape(Shape* shape) {
        _shapes.push_back(shape);
    }
    
    void deleteShapeById(std::string id) {
        std::list<Shape *>::iterator ptr;
        for(ptr = _shapes.begin(); ptr != _shapes.end();ptr++) {
            if((*ptr)->id() == id) {
                _shapes.erase(ptr);
                return;
            }
            try {
                (*ptr)->deleteShapeById(id);
                return;
            } catch(std::string e) {}
        }
        throw (std::string("Expected delete shape but shape not found"));
    }
    
    Shape* getShapeById(std::string id) const {
        std::list<Shape *>::const_iterator ptr;
        for(ptr = _shapes.begin(); ptr != _shapes.end(); ptr++) {
            if((*ptr)->id() == id) {
                return (*ptr);
            }
            try {
                return (*ptr)->getShapeById(id);
            } catch(std::string e) {}
        } 
        throw (std::string("Expected get shape but shape not found"));
    }

    std::string type() const {
        std::string type;
        type = "Compound Shape";
        return type;
    }

    std::list<Shape *> getData() {
        return _shapes;
    }

    void accept(Visitor *visitor) {
        visitor->visit(this);
    }

private:
    std::list<Shape *> _shapes;
};



#endif