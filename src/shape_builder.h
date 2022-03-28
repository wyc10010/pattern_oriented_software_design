#ifndef SHAPE_BUILDER
#define SHAPE_BUILDER

#include <stack>
#include <string>

class ShapeBuilder {
public:
    ShapeBuilder() {}
    
    void buildRectangle(double length, double width) {
        int random_variable = std::rand();
        std::string str_random_variable = std::to_string(random_variable);
        std::string strLength = std::to_string(length);
        std::string strWidth = std::to_string(width);
        Shape * r = new Rectangle(str_random_variable + "R" + strLength + strWidth, length, width);
        _pushdown.push(r);
    }
    
    void buildEllipse(double semiMajorAxes, double semiMinorAxes) {
        int random_variable = std::rand();
        std::string str_random_variable = std::to_string(random_variable);
        std::string strSemiMajorAxes = std::to_string(semiMajorAxes);
        std::string strSemiMinorAxes = std::to_string(semiMinorAxes);
        Shape * e = new Ellipse(str_random_variable + "E" + strSemiMajorAxes + strSemiMinorAxes, semiMajorAxes, semiMinorAxes);
        _pushdown.push(e);
    }
    
    void buildTriangle(double x1, double y1, double x2, double y2, double x3, double y3) {
        int random_variable = std::rand();
        std::string str_random_variable = std::to_string(random_variable);
        std::vector<TwoDimensionalCoordinate*> triangleVector;
        triangleVector.push_back(new TwoDimensionalCoordinate(x1, y1));
        triangleVector.push_back(new TwoDimensionalCoordinate(x2, y2));
        triangleVector.push_back(new TwoDimensionalCoordinate(x3, y3));
        
        std::string strX = std::to_string(x1);
        std::string strY = std::to_string(x2);
        std::string strZ = std::to_string(x3);
        
        Shape * t = new Triangle(str_random_variable + "T" + strX + strY + strZ, triangleVector);
        _pushdown.push(t);
    }
    
    void buildCompoundShapeBegin() {
        std::string _id = "comp";
        std::list<Shape*> shapes;
        Shape * cs = new CompoundShape(_id, shapes);
        _pushdown.push(cs);
    }

    void buildCompoundShapeEnd() {
        std::string _id = "comp";
        std::list<Shape *> _c;
        
        while(_pushdown.top()->id()!="comp") {
            _c.push_back(_pushdown.top());
            _pushdown.pop();
        }
            
        _pushdown.pop();
        std::list<Shape *> _shapes;
        int random_variable = std::rand();
        std::string str_random_variable = std::to_string(random_variable);
        Shape * cs = new CompoundShape( "C" + str_random_variable , _shapes);
        _pushdown.push(cs);
        for(auto it=_c.rbegin(); it!=_c.rend(); it++){
            _pushdown.top()->addShape(*it);
        }
    }

    std::deque<Shape*> getResult() {
        std::deque<Shape *> result;
        while(!_pushdown.empty()){
            result.push_back(_pushdown.top());
            _pushdown.pop();
        }
        return std::deque<Shape*>(result.rbegin(),result.rend());
    }

private:
    std::stack<Shape *> _pushdown;
};

#endif