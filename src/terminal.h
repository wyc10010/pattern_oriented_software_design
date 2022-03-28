#ifndef TERMINAL_H
#define TERMINAL_H

#include <iostream>
#include <fstream>
#include <string> 
#include <algorithm>
#include <sstream>
#include <regex>
#include <vector>
#include <numeric>
#include <iomanip>

#include "./shape.h"
#include "./sort.h"
#include "./triangle.h"
#include "./rectangle.h"
#include "./ellipse.h"

void handleOutput(std::string outputFile, std::vector<Shape *> shapes, std::string compare){
  std::ofstream ofs(outputFile);
  for(Shape *shape: shapes)
    if(compare == "area") {
        ofs << std::fixed << std::setprecision(3) << shape->area() << "\n";
    } else if(compare == "perimeter") {
        ofs << std::fixed << std::setprecision(3) << shape->perimeter() << "\n";
    }
}

std::string stringFromFile(std::string fileName) {
  std::ifstream ifs(fileName);
  std::string result = "";
  std::string line;
  std::getline(ifs, line);
  while(!ifs.eof() && !line.empty()) {
    result += line;
    std::getline(ifs, line);
  }
  return result;
}

void splitStr(std::string s, std::vector<std::string>& buf) {
    int current = 0;
    int next;
    while (1) {
      next = s.find_first_of(")", current);
    if (next != current) {
      std::string tmp = s.substr(current, next - current);
    if (tmp.size() != 0)
      buf.push_back(tmp);
  }
  if (next == std::string::npos) break;
    current = next + 1;
  }
}

void splitStrVec(std::string s, std::vector<std::string>& buf) {
    int current = 0;
    int next;
    while (1) {
      next = s.find_first_of(" ([,])", current);
    if (next != current) {
      std::string tmp = s.substr(current, next - current);
    if (tmp.size() != 0)
      buf.push_back(tmp);
  }
  if (next == std::string::npos) break;
    current = next + 1;
  }
}

std::vector<Shape *> handleSort(std::vector<Shape *> shapes, std::string compare, std::string order){
  if(compare == "area" && order == "inc"){
    quickSort(shapes.begin(), shapes.end(), areaAscendingCompare);
  }else if(compare == "area" && order == "dec"){
    quickSort(shapes.begin(), shapes.end(), areaDescendingCompare);
  }else if(compare == "perimeter" && order == "inc"){
    quickSort(shapes.begin(), shapes.end(), perimeterAscendingCompare);
  }else if(compare == "perimeter" && order == "dec"){
    quickSort(shapes.begin(), shapes.end(), perimeterDescendingCompare);
  }
  return shapes;
}

class Terminal {
public:
    Terminal(std::string input) {
        _inputfile = input;

        std::string segment;
        std::vector<std::string> seglist;
        std::vector<std::string> exception;
        std::vector<std::string> afterReg;
        
    	splitStr(_inputfile, seglist);
        
        std::string ss = "[\\s][\\(][\\s]*([\\d]|[\\s]*[\\d][\\.][\\d])[\\,]([\\s]*[\\d]|[\\s]*[\\d][\\.][\\d])";
        std::string sss = "[\\s][\\(][\\s]*(.*)([\\d]|[\\s]*[\\d][\\.][\\d])[\\,]([\\s]*[\\d]|[\\s]*[\\d][\\.][\\d])(.*)";

        std::regex rectangleReg ("[\\s]*Rectangle" + ss);
        std::regex ellipseReg ("[\\s]*Ellipse" + ss);
        std::regex triangleReg ("[\\s]*Triangle" + sss + "[\\,][\\s]*(.*)[\\s]*([\\d]|[\\s]*[\\d][\\.][\\d])(.*)[\\,][\\s]*(.*)[\\s]*([\\d]|[\\s]*[\\d][\\.][\\d])(.*)");

        for(int i=0;i < seglist.size();i++) {
          if (std::regex_match (seglist[i], ellipseReg)) {
              afterReg.push_back(seglist[i]);
          } else if (std::regex_match (seglist[i], rectangleReg)) {
              afterReg.push_back(seglist[i]);
          } else if (std::regex_match (seglist[i], triangleReg)) {
              afterReg.push_back(seglist[i]);
          } 
        }
        if(afterReg.size()==0) {
          throw(std::string("invalid input"));
        }
        for(int i=0;i < seglist.size();i++) {
            if(afterReg.size() == 1 && (seglist[i]== "area" || seglist[i]== "perimeter" || seglist[i]== "inc")) {
            throw(std::string("invalid input"));
            }
        }

        splitStrVec(_inputfile, exception);
        double a, b, c, d;
        double x1, x2, y1, y2, z1, z2;
        double _x, _y, _z;
        int error;
        std::regex num ("[\\d]*");
        std::vector<TwoDimensionalCoordinate*> trivectors;

        if(afterReg.size()==1) {
            for(int i=0;i < exception.size();i++){
                if (exception[i] == "Ellipse") {
                    a = std::stod(exception[i+1]);
                    b = std::stod(exception[i+2]);
                    if( a <=0 || b <= 0 || a < b) {
                    throw(std::string("invalid input"));
                    }        
                } else if(exception[i] == "Rectangle") {
                    c = std::stod(exception[i+1]);
                    d = std::stod(exception[i+2]);
                    if( c <=0 || d <= 0) {
                    throw(std::string("invalid input"));
                    }
                } else if(exception[i] == "Triangle") {
                    x1 = std::stod(exception[i+1]);
                    x2 = std::stod(exception[i+2]);
                    y1 = std::stod(exception[i+3]);
                    y2 = std::stod(exception[i+4]);
                    z1 = std::stod(exception[i+5]);
                    z2 = std::stod(exception[i+6]);

                    trivectors.push_back(new TwoDimensionalCoordinate(x1, x2));
                    trivectors.push_back(new TwoDimensionalCoordinate(y1, y2));
                    trivectors.push_back(new TwoDimensionalCoordinate(z1, z2));

                    _x = sqrt(pow((trivectors[0]->getX() - trivectors[1]->getX()),2) + pow((trivectors[0]->getY() - trivectors[1]->getY()),2));
                    _y = sqrt(pow((trivectors[0]->getX() - trivectors[2]->getX()),2) + pow((trivectors[0]->getY() - trivectors[2]->getY()),2));
                    _z = sqrt(pow((trivectors[1]->getX() - trivectors[2]->getX()),2) + pow((trivectors[1]->getY() - trivectors[2]->getY()),2));
                    if(std::regex_match (exception[i+7], num)) {
                      throw(std::string("invalid input"));
                    }
                    if(trivectors.size()!=3) {
                        throw(std::string("invalid input"));
                    } else if (_x + _y < _z && _y +_z < _x && _x + _z < _y) {
                        throw(std::string("invalid input"));
                    } else if (x1==0 && x2 ==0 && y1 ==0&& y2 ==0 && z1==0 && z2 ==0) {
                        throw(std::string("invalid input"));
                    }
                }
            }
        }
    }

    std::vector<Shape *> handleInput() {
      std::vector<Shape *> shapes;
      std::vector<std::string> exception;
      std::vector<TwoDimensionalCoordinate*> vectors;
      splitStrVec(_inputfile, exception);
      double a, b, c, d;
      double x1, x2, y1, y2, z1, z2;
      double _x, _y, _z;
      int error = 0;
      std::regex num ("[\\d]*");
      std::regex invaild ("[A-Za-z]*");

      for(int i=0;i < exception.size();i++){
        if(exception[i] == "Ellipse") {
            if(std::regex_match (exception[i+1], num)) {
            a = std::stod(exception[i+1]);
            b = std::stod(exception[i+2]);
            }
          if(std::regex_match (exception[i+1], invaild)) {
              error = error +1;
          } else if( a <=0 || b <= 0 || a < b) {
            error = error +1;
          } else {
            shapes.push_back(new Ellipse(a,b));
          }
        } else if(exception[i] == "Rectangle") {
          c = std::stod(exception[i+1]);
          d = std::stod(exception[i+2]);
          if( c <=0 || d <= 0) {
            error = error +1;
          } else {
            shapes.push_back(new Rectangle(c,d));
          }
        } else if (exception[i] == "Triangle") {
          if(std::regex_match (exception[i+1], num)) {
          x1 = std::stod(exception[i+1]);
          x2 = std::stod(exception[i+2]);
          y1 = std::stod(exception[i+3]);
          y2 = std::stod(exception[i+4]);
          z1 = std::stod(exception[i+5]);
          z2 = std::stod(exception[i+6]);
          }
          vectors.push_back(new TwoDimensionalCoordinate(x1, x2));
          vectors.push_back(new TwoDimensionalCoordinate(y1, y2));
          vectors.push_back(new TwoDimensionalCoordinate(z1, z2));

            _x = sqrt(pow((vectors[0]->getX() - vectors[1]->getX()),2) + pow((vectors[0]->getY() - vectors[1]->getY()),2));
            _y = sqrt(pow((vectors[0]->getX() - vectors[2]->getX()),2) + pow((vectors[0]->getY() - vectors[2]->getY()),2));
            _z = sqrt(pow((vectors[1]->getX() - vectors[2]->getX()),2) + pow((vectors[1]->getY() - vectors[2]->getY()),2));
            
            if(vectors.size()!=3) {
                error = error+1;
            } else if (_x + _y < _z && _y +_z < _x && _x + _z < _y) {
                error = error+1;
            } else {
                shapes.push_back(new Triangle(vectors));
            }
        }
      }
      return shapes;
    }

    std::string showResult() {
        std::string str,result;
        std::vector<std::string> exg;
        splitStrVec(_inputfile, exg);
        _shapes = handleInput();
        if(_shapes.size()==0) {
            throw(std::string("invalid input"));
        }
        for(int i=0;i < exg.size();i++){
          if(exg[i] == "area" && exg[i+1] == "inc") {
            quickSort(_shapes.begin(), _shapes.end(), areaAscendingCompare);
          } else if(exg[i] == "area" && exg[i+1] == "dec"){
            quickSort(_shapes.begin(), _shapes.end(), areaDescendingCompare);
          } else if(exg[i] == "perimeter" && exg[i+1] == "inc"){
            quickSort(_shapes.begin(), _shapes.end(), perimeterAscendingCompare);
          } else if(exg[i] == "perimeter" && exg[i+1] == "dec"){
            quickSort(_shapes.begin(), _shapes.end(), perimeterDescendingCompare);
          }
        }

        for(int i=1;i < exg.size();i++){
          if(exg[i] == "area") {
            std::stringstream s0,s1,s2;
            s0 << std::fixed << std::setprecision(3) << _shapes[0]->area();
            std::string r0 = s0.str();
            for(int i=1; i < _shapes.size();i++) {
              s1 << "\n" <<std::fixed << std::setprecision(3) << _shapes[i]->area();
            }
            std::string r1 = s1.str();
            result = r0 + r1;
            if(_shapes.size()==1) {
              s2 << std::fixed << std::setprecision(3) << _shapes[0]->area();
              std::string r2 = s2.str() + "\n";
              result = r2;
            } 
          }
        }
        for(int i=1;i < exg.size();i++){
          if(exg[i] == "perimeter") {
            std::stringstream s0,s1,s2;
            s0 << std::fixed << std::setprecision(3) << _shapes[0]->perimeter();
            std::string r0 = s0.str();
            for(int i=1; i < _shapes.size();i++) {
              s1 << "\n" <<std::fixed << std::setprecision(3) << _shapes[i]->perimeter();
            }
            std::string r1 = s1.str();
            result = r0 + r1;
            if(_shapes.size()==1) {
              s2 << std::fixed << std::setprecision(3) << _shapes[0]->perimeter();
              std::string r2 = s2.str() + "\n";
              result = r2;
            }
          }
        }
        
        return result;
    }

private:
    std::string _inputfile;
    std::string _afterReg;
    std::vector<std::string> _regexlist;
    std::vector<Shape *> _shapes;

};

#endif
