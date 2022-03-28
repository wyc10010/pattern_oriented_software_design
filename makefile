.PHONY: dirs clean rut crut

all: dirs shape ut_main

TEST = test/ut_rectangle.h test/ut_ellipse.h test/ut_triangle.h \
	   test/ut_sort.h test/ut_terminal.h test/ut_compound_shape.h \
	   test/ut_iterator.h test/ut_utility.h test/ut_visitor.h \
	   test/ut_scanner.h test/ut_shape_builder.h test/ut_shape_parser.h  \
	   test/ut_filter.h
SRC = src/shape.h src/rectangle.h src/ellipse.h src/triangle.h src/two_dimensional_coordinate.h \
	  src/sort.h src/terminal.h src/compound_shape.h src/iterator.h src/shape_iterator.h src/null_iterator.h \
	  src/utility.h src/visitor.h src/area_visitor.h src/info_visitor.h \
	  src/scanner.h src/shape_builder.h src/shape_parser.h \
	  src/shape_setter.h src/shape_filter.h src/filter.h
OBJ = obj/shape.o

shape: src/shape.cpp src/shape.h
	g++ -std=c++11 -Wfatal-errors -c src/shape.cpp -o obj/shape.o

ut_main: test/ut_main.cpp ${TEST} ${SRC}
	g++ -std=c++11 -Wfatal-errors test/ut_main.cpp -o bin/ut_main obj/shape.o -lgtest -lpthread

bin/geo: src/main.cpp $(SRC)
	g++ -std=c++11 -Wfatal-errors src/main.cpp -o bin/geo

dirs:
	mkdir -p bin
	mkdir -p obj

clean: 
	rm -rf bin/*

rut:
	./bin/ut_main

crut: ut_main rut
