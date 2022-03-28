#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <regex>

#include "sort.h"
#include "shape.h"
#include "terminal.h"

int main(int argc, char **argv) {
  if(argc < 5){
    std::cout << "bin/geo ${input_file} ${output_file} ${compare_target} ${order}" << std::endl;
    return -1;
  }

  std::string inputFile = argv[1];
  std::string outputFile = argv[2];
  std::string compare = argv[3];
  std::string order = argv[4];

  Terminal terminal(stringFromFile(inputFile));
  std::vector<Shape *> shapes = terminal.handleInput();
  std::vector<Shape *> sortedShapes = handleSort(shapes, compare, order);
  handleOutput(outputFile, sortedShapes, compare);

  return 0;

};
 
