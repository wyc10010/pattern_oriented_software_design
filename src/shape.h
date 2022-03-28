#include <iostream>
#include <string>

#ifndef SHAPE_H
#define SHAPE_H

class Iterator;
class Visitor;

class Shape {
public:
    Shape(std::string id); 
    Shape(std::string id, std::string color);
    virtual ~Shape(){};
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string info() const = 0;
    std::string id() const;
    std::string color() const;
    virtual void addShape(Shape *shape);
    virtual void deleteShapeById(std::string id); 
    virtual Shape* getShapeById(std::string id) const;
    virtual std::string type() const = 0;
    virtual Iterator* createIterator() const;
    virtual void accept(Visitor* visitor) = 0;
    void setColor(std::string color);

private:
    std::string _id;
    std::string _color;
};

#endif