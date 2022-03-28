#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <iomanip>
#include <math.h>
#include "../src/shape.h"
#include "../src/two_dimensional_coordinate.h"
#include "visitor.h"

class Triangle: public Shape{
public: 
    Triangle(std::string id, std::vector<TwoDimensionalCoordinate*> vectors, std::string color = "white"):Shape(id,color),_vectors(vectors) {
        _vectors = vectors;
        if(vectors.size()!=3) {
            throw(std::string("This is not a triangle!"));
        }
        _x = sqrt(pow((vectors[0]->getX() - vectors[1]->getX()),2) + pow((vectors[0]->getY() - vectors[1]->getY()),2));
        _y = sqrt(pow((vectors[0]->getX() - vectors[2]->getX()),2) + pow((vectors[0]->getY() - vectors[2]->getY()),2));
        _z = sqrt(pow((vectors[1]->getX() - vectors[2]->getX()),2) + pow((vectors[1]->getY() - vectors[2]->getY()),2));
    
        if( _x + _y > _z && _y +_z > _x && _x + _z > _y) {
        } else {
            throw(std::string("This is not a triangle!"));
        }
    }

    double area() const {
        double s = (_x + _y + _z) / 2;
        return sqrt(s * (s - _x) * (s - _y) * (s - _z));
    }
    
    double perimeter() const {
        double p = _x + _y + _z;
        return p;
    }
    
    std::string info() const {
        std::string res; 
        std::stringstream s1, s2, s3, s4, s5, s6;
        s1 << std::fixed << std::setprecision(3) << _vectors[0]->getX();
        s2 << std::fixed << std::setprecision(3) << _vectors[0]->getY();
        s3 << std::fixed << std::setprecision(3) << _vectors[1]->getX();
        s4 << std::fixed << std::setprecision(3) << _vectors[1]->getY();
        s5 << std::fixed << std::setprecision(3) << _vectors[2]->getX();
        s6 << std::fixed << std::setprecision(3) << _vectors[2]->getY();
        std::string ss1 = s1.str(); 
        std::string ss2 = s2.str();
        std::string ss3 = s3.str(); 
        std::string ss4 = s4.str(); 
        std::string ss5 = s5.str(); 
        std::string ss6 = s6.str(); 
        res = "Triangle ([" + ss1 + ", " + ss2 + "], " + "[" + ss3 + ", " + ss4 + "], " + "[" + ss5 + ", " + ss6 + "])";
        return res;
    }

    std::string type() const {
        std::string type;
        type = "Triangle";
        return type;
    }

    double getDataOne() const {
        return _x;
    }

    double getDataTwo() const {
        return _y;
    }
    
    double getDataThree() const {
        return _z;
    }

    double x1() const {
        return _vectors[0]->getX();
    }

    double x2() const {
        return _vectors[1]->getX();
    }

    double x3() const {
        return _vectors[2]->getX();
    }

    double y1() const {
        return _vectors[0]->getY();
    }

    double y2() const {
        return _vectors[1]->getY();
    }

    double y3() const {
        return _vectors[2]->getY();
    }
    
    void accept(Visitor *visitor) {
        visitor->visit(this);
    }

private:
    std::vector<TwoDimensionalCoordinate*> _vectors;
    double _x, _y, _z;
};

#endif