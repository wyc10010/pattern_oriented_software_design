#include "../src/filter.h"
#include "../src/shape_filter.h"
#include "../src/shape_setter.h"

class FilterTest : public ::testing::Test {
protected:
    void SetUp() override {
        e43 = new Ellipse("e1", 4, 3);
        r22 = new Rectangle("r1", 2, 2);
        r99 = new Rectangle("r2", 9, 9);
        std::vector<TwoDimensionalCoordinate*> triangleVector;
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
        t345 = new Triangle("t1", triangleVector , "black");
    }
    void TearDown() override {
        delete e43;
        delete r22;
        delete t345;
        delete r99;
    }
    Shape *r22;
    Shape *e43;
    Shape *t345;
    Shape *r99;
};


TEST_F(FilterTest, AreaFilter){

std::list<Shape*> data;

data.push_back(e43);
data.push_back(r22);
data.push_back(t345);

Filter* areaFilter = new ShapeFilter([](Shape* shape) {return shape->area() <= 30;});
std::list<Shape*> results = areaFilter->push(data);

ASSERT_EQ(2, results.size());
ASSERT_EQ(4, results.front()->area());
results.pop_front();
ASSERT_EQ(6, results.front()->area());

}

TEST_F(FilterTest, MultiFilter){

std::list<Shape*> data;

data.push_back(e43);
data.push_back(r22);
data.push_back(t345);

Filter* areaFilter = new ShapeFilter([](Shape* shape) {return shape->area() <= 30;});
Filter* perimeterFilter = new ShapeFilter([](Shape* shape) {return shape->perimeter() >= 10;});
Filter* colorFilter = new ShapeFilter([](Shape* shape) {return shape->color() == "black";});

areaFilter->setNext(perimeterFilter)->setNext(colorFilter);
std::list<Shape*> results = areaFilter->push(data);


ASSERT_EQ(1, results.size());
ASSERT_EQ("Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])", results.front()->info());

}

TEST_F(FilterTest, MultiSetter){
std::list<Shape*> data;

data.push_back(e43);
data.push_back(r22);
data.push_back(t345);

Filter* areaFilter = new ShapeFilter([](Shape* shape) {return shape->area() >= 30;});
Filter* perimeterFilter = new ShapeFilter([](Shape* shape) {return shape->perimeter() <= 150;});
Filter* colorSetter = new ShapeSetter([](Shape* shape) {shape->setColor("black");});

areaFilter->setNext(perimeterFilter)->setNext(colorSetter);
std::list<Shape*> results = areaFilter->push(data);


ASSERT_EQ(1, results.size());
ASSERT_EQ("Ellipse (4.000, 3.000)", results.front()->info());

}