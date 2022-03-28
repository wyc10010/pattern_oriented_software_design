#ifndef SHAPE_PARSER_H
#define SHAPE_PARSER_H

#include "scanner.h"
#include "shape_builder.h"
#include <stack>

class ShapeParser {
public:
    ShapeParser(std::string input) {
        _input = input;
        _scan = new Scanner(_input); 
        _sb = new ShapeBuilder();
    }

    void parser() {

        double _length, _width;
        double _semiMajorAxes, _semiMinorAxes;
        double _x1, _y1, _x2, _y2, _x3, _y3;
        std::string _check;

        while(true) {
            try {
                _check = _scan->nextToken();
                if(_check == "Rectangle") {
                    if(_scan->nextToken() == "(") {
                        _length = std::stod(_scan->nextToken());
                        if(_scan->nextToken() == ",") {
                            _width = std::stod(_scan->nextToken());
                            if(_scan->nextToken() == ")") {
                                _sb->buildRectangle(_length, _width);
                            }
                        }   
                    }
                }
                
                if(_check == "Ellipse") {
                    if(_scan->nextToken() == "(") {
                        _semiMajorAxes = std::stod(_scan->nextToken());
                        if(_scan->nextToken() == ",") {
                            _semiMinorAxes = std::stod(_scan->nextToken());
                            if(_scan->nextToken() == ")") {
                                _sb->buildEllipse(_semiMajorAxes, _semiMinorAxes);
                            }
                        }   
                    }
                }

                if(_check == "Triangle") {
                    if(_scan->nextToken() == "(") {
                    _x1 = std::stod(_scan->nextToken());
                        if(_scan->nextToken() == ",") {
                        _y1 = std::stod(_scan->nextToken());
                            if(_scan->nextToken() == ",") {
                            _x2 = std::stod(_scan->nextToken());
                                if(_scan->nextToken() == ",") {
                                _y2 = std::stod(_scan->nextToken());
                                    if(_scan->nextToken() == ",") {
                                    _x3 = std::stod(_scan->nextToken());
                                        if(_scan->nextToken() == ",") {
                                        _y3 = std::stod(_scan->nextToken());
                                            if(_scan->nextToken() == ")") {
                                                _sb->buildTriangle(_x1, _y1, _x2, _y2, _x3, _y3);
                                            }
                                        }
                                    }
                                }
                            }
                        }   
                    }
                }

                if(_check == "CompoundShape") {
                    if(_scan->nextToken() == "{") {
                        _sb->buildCompoundShapeBegin();
                    }
                }
                if(_check == "}") {
                    _sb->buildCompoundShapeEnd();
                }

            } catch (std::string e) {
                break;
            }
        }

    }
    
    std::deque<Shape*> getResult() {
        return _sb->getResult();
    }
    private:
        std::string _input;
        Scanner *_scan; 
        ShapeBuilder *_sb;
};

#endif