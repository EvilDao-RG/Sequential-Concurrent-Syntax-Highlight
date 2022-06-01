/*
Autor: Gael Rodrígue Gómez
Matricula: A01639279

Este programa realiza resaltamiento sintáctico, en el que el usuario
carga un archivo .txt con las expresiones regulares según la notación
establecida en el documento de diseño, ademas se carga el texto a resaltar 
en el archivo text.txt. Finalmente, se arroja un documento html con los 
tokens resaltados según las expresiones establecidas

Requerimientos
    gcc version 6.3.0 en adelante
    flex versión 2.5.4

Instrucciones de compilación y ejecución:
    g++ main.cpp -o main
    ./main.exe

28 / Marzo / 2022
*/


#include "tokenHighlighter.h"
#include <ctime>
#include <thread>


vector<string> readDirectory(){
    system("python iterate.py");

    ifstream dirFile;
    vector<string> dirList;
    string file;

    try{
        dirFile.open("dir.txt", ios::in);
        if(dirFile.fail()){
            throw "Path error. The address or filename is incorrect\n";
        }
    } catch(char const* message){
        std::cerr<<message<<std::endl;
        exit(0);
    }

    while(!dirFile.eof()){
        getline(dirFile, file);
        dirList.push_back(file);
    }

    return dirList;
}


void sequentialHighlight(vector<string> dir, expressionProcessor lex, tokenHighlighter highlighter){
    unsigned t0, t1;
    t0 = clock();
    for(int i = 0; i < dir.size()-1; i++){
        lex.executeLex(dir[i],to_string(i));
        highlighter.highlight(dir[i],to_string(i));
    }
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Tiempo de ejecucion: " << time << endl;
}


void thread_function(string dir, string i, expressionProcessor lex, tokenHighlighter highlighter){
    cout<<"Start\n";
    lex.executeLex(dir, i);
    cout<<"lex\n";
    highlighter.highlight(dir, i);
    cout<<"done\n";
}


void parallelHighlight(vector<string> dir, expressionProcessor lex, tokenHighlighter highlighter){
    unsigned t0, t1;
    t0 = clock();
    // vector<thread> th;

    // for (int i = 0; i < dir.size()-1; i++){
    //     th.push_back(thread(thread_function, dir[i], i, lex, highlighter));
    // }
    
    // for (auto &t : th){
    //     t.join();
    // }


    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Tiempo de ejecucion: " << time << endl;
}



int main(){
    expressionProcessor lex;
    // Creación del archivo de lex a partir de las expresiones
    lex.createLex("expressions.txt");
    lex.compileLex();
    // Leer directorio
    vector<string> directory = readDirectory();
    for(int i = 0; i< directory.size()-1; i++){
        cout<<"1 "<<directory[i]<<endl;
    }
    // Resaltador
    tokenHighlighter highlighter(lex);
    //Secuencial
    sequentialHighlight(directory, lex, highlighter);

    //parallelHighlight(directory, lex, highlighter);


    
    // Resaltamiento de los tokens identificados
    // highlighter.highlight();




}
