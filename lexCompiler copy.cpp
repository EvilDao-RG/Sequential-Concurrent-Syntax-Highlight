#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;

extern int yylex();
extern int yylineno;
extern char* yytext;

int main(int argc, char* argv[]){
    extern FILE *yyin, *yyout;
    yyin = fopen(argv[1], "r");
    cout<<"Content: ";
    char s;
    while((s=fgetc(yyin))!=EOF) {
       printf("%c",s);
    }
    string str(argv[2]);
    string output = "output"+str+".txt";
    cout << output << endl;
    yyout = fopen(output.c_str(), "w");

    yylex();
    return 0;
}