#ifndef INFO_VISITOR_H
#define INFO_VISITOR_H

#include "../src/visitor.h"
#include "../src/ellipse.h"
#include "../src/triangle.h"
#include "../src/rectangle.h"

#include <sstream>

class InfoVisitor : public Visitor {
public:
    void visit(Ellipse* ellipse) {
        std::stringstream s1;
        s1 << "Ellipse (" << std::fixed << std::setprecision(3) << ellipse->getDataOne() << ", " << std::fixed << std::setprecision(3) << ellipse->getDataTwo() << ")";
        _info = s1.str();
    }

    void visit(Triangle* triangle) {
        std::stringstream s1;
        s1 << "Triangle ([" << std::fixed << std::setprecision(3) << triangle->x1() << ", " << std::fixed << std::setprecision(3) << triangle->y1() << "], " << "[" << std::fixed << std::setprecision(3) << triangle->x2() << ", " << std::fixed << std::setprecision(3) << triangle->y2() << "], " << "[" << std::fixed << std::setprecision(3) << triangle->x3() << ", " << std::fixed << std::setprecision(3) << triangle->y3() << "])";
        _info = s1.str();
    }

    void visit(Rectangle* rectangle) {
        std::stringstream s1;
        s1 << "Rectangle (" << std::fixed << std::setprecision(3) << rectangle->getDataOne() << ", " << std::fixed << std::setprecision(3) << rectangle->getDataTwo() << ")";
        _info = s1.str();
    }

    void visit(CompoundShape* compoundShape) {
        std::string _detail; 
        std::string _res;
        _shapes = compoundShape->getData();
        std::list<Shape *>::const_iterator ptr;
        std::list<Shape *>::const_iterator ftr = _shapes.end();
        auto it1 = prev(ftr, 1); 

        for(ptr = _shapes.begin(); ptr != _shapes.end(); ptr++) {
            InfoVisitor *v = new InfoVisitor();
            (*ptr)->accept(v);
            _detail += v->info();
            if(ptr != it1) {
                _detail = _detail + ", ";
            }
        }
        _info = "Compound Shape {" + _detail + "}";
    }

    std::string info() const {
        return _info;
    }

private:
    std::list<Shape *> _shapes;
    std::string _info;
};

#endif