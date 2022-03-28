#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <math.h>
#include "shape.h"
#include "visitor.h"

class Ellipse: public Shape{
public: 

    Ellipse(std::string id, double semiMajorAxes, double semiMinorAxes, std::string color = "white"):Shape(id,color) {
        _semiMajorAxes = semiMajorAxes;
        _semiMinorAxes = semiMinorAxes;
        if( _semiMajorAxes <=0 || _semiMinorAxes <= 0 || _semiMajorAxes < _semiMinorAxes) {
            throw(std::string("This is not an ellipse!"));
        }
    }
    
    double area() const {
        return M_PI * _semiMajorAxes * _semiMinorAxes;
    }
    
    double perimeter() const {
        return 2 * M_PI * _semiMinorAxes + 4 * (_semiMajorAxes - _semiMinorAxes);
    }
    
    std::string info() const {
        std::string res; 
        std::stringstream s1, s2;
        s1 << std::fixed << std::setprecision(3) << _semiMajorAxes;
        s2 << std::fixed << std::setprecision(3) << _semiMinorAxes;
        std::string semiMajorAxes = s1.str(); 
        std::string semiMinorAxes = s2.str(); 
        res = "Ellipse (" + semiMajorAxes + ", " + semiMinorAxes + ")";
        return res;
    }

    std::string type() const {
        std::string type;
        type = "Ellipse";
        return type;
    }

    double getDataOne() const {
        return _semiMajorAxes;
    }

    double getDataTwo() const {
        return _semiMinorAxes;
    }

    void accept(Visitor *visitor) {
        visitor->visit(this);
    }

private:
    double _semiMajorAxes , _semiMinorAxes;
};

#endif