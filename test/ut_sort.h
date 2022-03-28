#include "../src/shape.h"
#include "../src/rectangle.h"
#include "../src/ellipse.h"
#include "../src/two_dimensional_coordinate.h"
#include "../src/triangle.h"
#include "../src/sort.h"
#include <iostream>
#include <array>

class ShapeSort : public ::testing::Test {
protected:
    void SetUp() override {
        e43 = new Ellipse("e1", 4, 3);
        r68 = new Rectangle("r1", 6, 8);
        r99 = new Rectangle("r2", 9, 9);
        std::vector<TwoDimensionalCoordinate*> triangleVector;
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(3, 0));
        triangleVector.push_back(new TwoDimensionalCoordinate(0, 4));
        t345 = new Triangle("t1", triangleVector);
    }
    void TearDown() override {
        delete e43;
        delete r68;
        delete t345;
        delete r99;
    }
    Shape *r68;
    Shape *e43;
    Shape *t345;
    Shape *r99;
};

TEST_F(ShapeSort, SubtypePolymorphism){
  Shape * shapes[3] = {r68, e43, t345};
  ASSERT_NEAR(48.000, shapes[0]->area(), 0.001);
  ASSERT_NEAR(37.699, shapes[1]->area(), 0.001);
  ASSERT_NEAR(6.000, shapes[2]->area(), 0.001);
}
//object
TEST_F(ShapeSort, ObjectOfAsArea){
  std::array<Shape *, 3> shapes = {r68, e43, t345};
  quickSort(shapes.begin(), shapes.end(), AscendingCompare("area"));
  ASSERT_NEAR(6.000, shapes[0]->area(), 0.001);
  ASSERT_NEAR(37.699, shapes[1]->area(), 0.001);
  ASSERT_NEAR(48.000, shapes[2]->area(), 0.001);
}

TEST_F(ShapeSort, ObjectOfDsArea){
  std::array<Shape *, 3> shapes = {r68, e43, t345};
  quickSort(shapes.begin(), shapes.end(), DescendingCompare("area"));
  ASSERT_NEAR(48.000, shapes[0]->area(), 0.001);
  ASSERT_NEAR(37.699, shapes[1]->area(), 0.001);
  ASSERT_NEAR(6.000, shapes[2]->area(), 0.001);
}

TEST_F(ShapeSort, ObjectOfAsPeri){
  std::array<Shape *, 3> shapes = {r68, e43, t345};
  quickSort(shapes.begin(), shapes.end(), AscendingCompare("perimeter"));
  ASSERT_NEAR(12.000, shapes[0]->perimeter(), 0.001);
  ASSERT_NEAR(22.849, shapes[1]->perimeter(), 0.01);
  ASSERT_NEAR(28.000, shapes[2]->perimeter(), 0.001);
}

TEST_F(ShapeSort, ObjectOfDePeri){
  std::array<Shape *, 3> shapes = {r68, e43, t345};
  quickSort(shapes.begin(), shapes.end(), DescendingCompare("perimeter"));
  ASSERT_NEAR(28.000, shapes[0]->perimeter(), 0.001);
  ASSERT_NEAR(22.849, shapes[1]->perimeter(), 0.01);
  ASSERT_NEAR(12.000, shapes[2]->perimeter(), 0.001);
}
//function
TEST_F(ShapeSort, FuncAscendingByArea) {
  std::array<Shape *, 3> shapes = {r68, e43, t345};
  quickSort(shapes.begin(), shapes.end(), areaAscendingCompare);
  ASSERT_NEAR(6.000, shapes[0]->area(), 0.001);
  ASSERT_NEAR(37.699, shapes[1]->area(), 0.001);
  ASSERT_NEAR(48.000, shapes[2]->area(), 0.001);
}

TEST_F(ShapeSort, FuncDescendingByArea) {
  std::array<Shape *, 3> shapes = {r68, e43, t345};
  quickSort(shapes.begin(), shapes.end(), areaDescendingCompare);
  ASSERT_NEAR(48.000, shapes[0]->area(), 0.001);
  ASSERT_NEAR(37.699, shapes[1]->area(), 0.001);
  ASSERT_NEAR(6.000, shapes[2]->area(), 0.001);
}

TEST_F(ShapeSort, FuncAscendingByPerimeter) {
  std::array<Shape *, 3> shapes = {r68, e43, t345};
  quickSort(shapes.begin(), shapes.end(), perimeterAscendingCompare);
  ASSERT_NEAR(12.000, shapes[0]->perimeter(), 0.001);
  ASSERT_NEAR(22.849, shapes[1]->perimeter(), 0.01);
  ASSERT_NEAR(28.000, shapes[2]->perimeter(), 0.001);
}

TEST_F(ShapeSort, FuncDescendingByPerimeterPerimeter) {
  std::array<Shape *, 3> shapes = {r68, e43, t345};
  quickSort(shapes.begin(), shapes.end(), perimeterDescendingCompare);
  ASSERT_NEAR(28.000, shapes[0]->perimeter(), 0.001);
  ASSERT_NEAR(22.849, shapes[1]->perimeter(), 0.01);
  ASSERT_NEAR(12.000, shapes[2]->perimeter(), 0.001);
}

//lambda
TEST_F(ShapeSort, AscendingByAreaOnArray) {
  std::array<Shape *, 3> shapes = {r68, e43, t345};
  quickSort(shapes.begin(), shapes.end(), [](Shape * a, Shape * b) { return a->area() < b->area(); });
  ASSERT_NEAR(6.000, shapes[0]->area(), 0.01);
  ASSERT_NEAR(37.699, shapes[1]->area(), 0.01);
  ASSERT_NEAR(48.000, shapes[2]->area(), 0.01);
}

TEST_F(ShapeSort, DescendingByAreaOnArray) {
  std::array<Shape *, 3> shapes = {r68, e43, t345};
  quickSort(shapes.begin(), shapes.end(), [](Shape * a, Shape * b) { return a->area() > b->area(); });
  ASSERT_NEAR(48.000, shapes[0]->area(), 0.01);
  ASSERT_NEAR(37.699, shapes[1]->area(), 0.01);
  ASSERT_NEAR(6.000, shapes[2]->area(), 0.01);
}

TEST_F(ShapeSort, AscendingByPerimeterOnArray) {
  std::array<Shape *, 3> shapes = {r68, e43, t345};
  quickSort(shapes.begin(), shapes.end(), [](Shape * a, Shape * b) { return a->perimeter() < b->perimeter(); });
  ASSERT_NEAR(12.000, shapes[0]->perimeter(), 0.001);
  ASSERT_NEAR(22.849, shapes[1]->perimeter(), 0.01);
  ASSERT_NEAR(28.000, shapes[2]->perimeter(), 0.001);
}

TEST_F(ShapeSort, DescendingByPerimeterOnArray) {
  std::array<Shape *, 3> shapes = {r68, e43, t345};
  quickSort(shapes.begin(), shapes.end(), [](Shape * a, Shape * b) { return a->perimeter() > b->perimeter(); });
  ASSERT_NEAR(28.000, shapes[0]->perimeter(), 0.001);
  ASSERT_NEAR(22.849, shapes[1]->perimeter(), 0.01);
  ASSERT_NEAR(12.000, shapes[2]->perimeter(), 0.001);
}

TEST_F(ShapeSort, DescendingByPerimeterOnArrayTest) {
  std::array<Shape *, 4> shapes = {r68, e43, t345, r99};
  quickSort(shapes.begin(), shapes.end(), [](Shape * a, Shape * b) { return a->perimeter() > b->perimeter(); });
  EXPECT_EQ(36.000, shapes[0]->perimeter());
  EXPECT_EQ(28.000, shapes[1]->perimeter());
  ASSERT_NEAR(22.849, shapes[2]->perimeter(), 0.01);
  EXPECT_EQ(12.000, shapes[3]->perimeter());
}