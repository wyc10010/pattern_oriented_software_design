#ifndef AREA_VISITOR_H
#define AREA_VISITOR_H

#include "../src/visitor.h"
#include "../src/ellipse.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"

class AreaVisitor : public Visitor {
public:
    void visit(Ellipse* ellipse) {
        _area = ellipse->getDataOne() * ellipse->getDataTwo() * M_PI;
    }

    void visit(Triangle* triangle) {
        double _x = triangle->getDataOne();
        double _y = triangle->getDataTwo();
        double _z = triangle->getDataThree();
        double s = (_x + _y + _z) / 2;
        _area = sqrt(s * (s - _x) * (s - _y) * (s - _z));
    }

    void visit(Rectangle* rectangle) {
        _area = rectangle->getDataOne() * rectangle->getDataTwo();
    }

    void visit(CompoundShape* compoundShape) {
        _shapes = compoundShape->getData();
        std::list<Shape *>::const_iterator ptr;
        for(ptr = _shapes.begin(); ptr != _shapes.end(); ptr++) {
            AreaVisitor *v = new AreaVisitor();
            (*ptr)->accept(v);
            _area += v->area();
        }
    }

    double area() const {
        return _area;
    }

private:
    double _area;
    std::list<Shape *> _shapes;
};


#endif