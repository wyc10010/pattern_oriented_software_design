#include "../src/terminal.h"
#include "../src/shape.h"
#include "../src/rectangle.h"
#include "../src/ellipse.h"
#include "../src/two_dimensional_coordinate.h"
#include "../src/triangle.h"
#include "../src/sort.h"
#include <iostream>
#include <array>


TEST(TerminalTest, ShowResultMixedAreaInc){
    Terminal terminal("Rectangle (   2,   2) Rectangle (1, 1) Ellipse$%^&(1, 1) area inc");
    ASSERT_EQ("1.000\n4.000", terminal.showResult());
}

TEST(TerminalTest, ShowResultMixedAreaDec){
    Terminal terminal("Rectangle (   2,   2) Rectangle (1, 1) Ellipse$%^&(1, 1) area dec");
    ASSERT_EQ("4.000\n1.000", terminal.showResult());
}

TEST(TerminalTest, ShowResultMixedPerimeterDec){
    Terminal terminal("Rectangle (2, 2) Rectangle (1, 1) Ellipse$%^&(1, 1) perimeter dec");
    ASSERT_EQ("8.000\n4.000", terminal.showResult());
}

TEST(TerminalTest, ShowResultMixedPerimeterInc){
    Terminal terminal("Rectangle (2, 2) Rectangle (1, 1) Ellipse$%^&(1, 1) perimeter inc");
    ASSERT_EQ("4.000\n8.000", terminal.showResult());
}

TEST(TerminalTest, ShowResultMixedAreaIncTri){
    Terminal terminal("Rectangle%^&(1, 1)  Triangle ([0,0], [3,0], [0,4]) area inc");
    ASSERT_EQ("6.000\n", terminal.showResult());
}

TEST(TerminalTest, ShowResultMixedPerimeterTri){
    Terminal terminal("Triangle ([  0,0],   [3,0], [0,4]) perimeter inc");
    ASSERT_EQ("12.000\n", terminal.showResult());
}

TEST(TerminalTest, AreaIncreasingWithOtherShape){
    Terminal terminal("Rectangle (2, 2) Ellipse (4, 3) Triangle ([0,0], [-3,0], [0,-4]) area inc");
    ASSERT_EQ("4.000\n6.000\n37.699", terminal.showResult());
}

TEST(TerminalTest, ShowResultOneEllipse){
    Terminal terminal("Ellipse (4, 3) area inc");
    ASSERT_EQ("37.699\n", terminal.showResult());
}

TEST(TerminalTest, ShowResultOneTri){
    Terminal terminal("Triangle ([0,0], [-3,0], [0,-4]) area inc");
    ASSERT_EQ("6.000\n", terminal.showResult());
}

TEST(TerminalTest, AreaIncreasingWithOneShapeExceptionIgnore){
    Terminal terminal("Rectangle (3.7, 4.2) Ellipse (4, 3) Triangle ([0,0], [-3,0], [0,-4]) Ellipse (0, 0) area inc");
    ASSERT_EQ("6.000\n15.540\n37.699", terminal.showResult());
}

TEST(TerminalTest, AreaDescreasingWithOneShapeExceptionIgnore){
    Terminal terminal("Rectangle (3.7, 4.2) Ellipse (4, 3) Ellipse (0, 0) area dec");
    ASSERT_EQ("37.699\n15.540", terminal.showResult());
}

TEST(TerminalTest, AreaDescreasingWithErrorArgumentOneShapeExceptionIgnore){
    Terminal terminal("Rectangle (3.7, 4.2) Ellipse (4, 3) Triangle ([0,0], [-3,0], [0,-4]) Ellipse (four, 3) area dec");
    ASSERT_EQ("37.699\n15.540\n6.000", terminal.showResult());
}

TEST(TerminalTest, InvalidInputNoShape) {
    try {
        Terminal("area inc");
        FAIL();
    } catch (std::string e) {
      ASSERT_EQ("invalid input", e);
    }
}

TEST(TerminalTest, OneInvaildShapeExceptionEllipse) {
    try {
        Terminal("Ellipse (-1, -1) area inc");
        FAIL();
    } catch (std::string e) {
      ASSERT_EQ("invalid input", e);
    }
}

TEST(TerminalTest, ShowResultExceptionEllipse){
    try {
        Terminal terminal("Ellipse (3, 4)");
        FAIL();
    } catch (std::string e) {
      ASSERT_EQ("invalid input", e);
    }
}

TEST(TerminalTest, OneInvaildShapeExceptionTriangle) {
    try {
        Terminal("Triangle ([0,0], [0,0], [0,0]) area inc");
        FAIL();
    } catch (std::string e) {
      ASSERT_EQ("invalid input", e);
    }
}

TEST(TerminalTest, MuitlInvaildShapeException) {
    try {
        Terminal("Ellipse (-1, -1) Triangle ([*&2,0],   [3,0], [0,4]) area inc");
        FAIL();
    } catch (std::string e) {
      ASSERT_EQ("invalid input", e);
    }
}

TEST(TerminalTest, MoreInvaildShapeExceptionTriangle){
    try {
        Terminal terminal("Triangle ([0,-3], [-3,0], [0,-4], [0,-4]) area inc");
        FAIL();
    } catch (std::string e) {
      ASSERT_EQ("invalid input", e);
    }
}

TEST(TerminalTest, LessInvaildShapeExceptionTriangle){
    try {
        Terminal terminal("Triangle ([0,-3], [-3,0]) area");
        FAIL();
    } catch (std::string e) {
      ASSERT_EQ("invalid input", e);
    }
}

