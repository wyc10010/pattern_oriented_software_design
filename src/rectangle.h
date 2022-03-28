#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include "shape.h"
#include "visitor.h"

class Rectangle: public Shape {
public: 
    Rectangle(std::string id, double length, double width ,std::string color = "white"):Shape(id,color),_length(length),_width(width) {
        _length = length;
        _width = width;
        if(_length<=0 || _width <= 0) {
            throw(std::string("This is not a rectangle!"));
        }
    }

    double area() const {
        return _length * _width;
    }
    
    double perimeter() const {
        return (_length + _width) * 2;
    }
    
    std::string info() const {
        std::string res; 
        std::stringstream s1, s2;
        s1 << std::fixed << std::setprecision(3) << _length;
        s2 << std::fixed << std::setprecision(3) << _width;
        std::string length = s1.str(); 
        std::string width = s2.str(); 
        res = "Rectangle (" + length + ", " + width + ")";
        return res;
    }

    std::string type() const {
        std::string type;
        type = "Rectangle";
        return type;
    }

    double getDataOne() const {
        return _length;
    }

    double getDataTwo() const {
        return _width;
    }

    void accept(Visitor *visitor) {
        visitor->visit(this);
    }

private:
    double _width, _length;
};

#endif