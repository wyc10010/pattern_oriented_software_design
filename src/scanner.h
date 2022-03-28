#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <cctype>

using namespace std;

class Scanner {
public:
    Scanner(std::string input) {
        _input = input;
    }

    std::string nextToken() {
        std::string token="", left="", num ="", right="", comm="", space="", Left="", Right="";

        while(_input.length()!=0) {
            int i = 0;
            if(_input[i] == 67 || _input[i] == 69 || _input[i] == 82 || _input[i] == 84) {
                for(int i = 0; i < _input.length(); i++) {
                    if((_input[i]>=65 && _input[i]<=90) || (_input[i]>=97 && _input[i]<=122)) {
                        token += _input[i];
                    } else {
                        break;
                    }
                }
                break;
            }
            
            if((_input[i]>= 45 && _input[i]<=57) || (_input[i] == 46)) { //num
                for(int i = 0; i < _input.length(); i++) {
                    if((_input[i]>= 45 && _input[i]<=57) || (_input[i] == 46)) {
                        num += _input[i];
                    } else {
                        break;
                    }
                }
                break;
            }
            
            if(_input[i] == 40) {
                left = _input[i];
                break;
            }

            if(_input[i] == 123) {
                Left = _input[i];
                break;
            } 

            if(_input[i] == 41) {
                right = _input[i];
                break;
            }

            if(_input[i] == 125) {
                Right = _input[i];
                break;
            } 
            
            if(_input[i] == 44) {
                comm = _input[i];
                break;
            } 

            if(_input[i] == ' ') {
                _input.erase(0, 1);
                continue;
            } 
        }

        if(token.length()!=0) {
            _input.erase(0, token.length());
            return token;
        }

        if(num.length()!=0) {
            _input.erase(0, num.length());
            return num;
        }

        if(left.length()!=0) {
            _input.erase(0, left.length());
            return left;
        }

        if(Left.length()!=0) {
            _input.erase(0, Left.length());
            return Left;
        }

        if(right.length()!=0) {
            _input.erase(0, right.length());
            return right;
        }

        if(Right.length()!=0) {
            _input.erase(0, Right.length());
            return Right;
        }

        if(comm.length()!=0) {
            _input.erase(0, comm.length());
            return comm;
        }

        if(_input.length()==0) {
            throw std::string("next char doesn't exist.");
        }
        return "";
    }

private:
    std::string _input;

};

#endif
