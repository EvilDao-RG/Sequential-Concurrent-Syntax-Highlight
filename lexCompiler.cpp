#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
using namespace std;

extern int yylex();
extern int yylineno;
extern char* yytext;

int main(){
    ifstream arguments;
    string inputFile, outputFile, outputNumber;

    try{
        arguments.open("arguments.txt", ios::out);
        if(arguments.fail()){
            throw "Path error. The address or filename is incorrect\n";
        }
    } catch(char const* message){
        std::cerr<<message<<std::endl;
        exit(0);
    }

    getline(arguments, inputFile, ' ');
    getline(arguments, outputNumber);

    outputFile = "outputFiles/output" + outputNumber + ".txt";
    inputFile += ".txt";

    extern FILE *yyin, *yyout;
    yyin = fopen(inputFile.c_str(), "r");
    yyout = fopen(outputFile.c_str(),"w");

    yylex();
    return 0;
}