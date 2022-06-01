#ifndef TOKENHIGHLIGHTER
#define TOKENHIGHLIGHTER
#include "expressionProcessor.h"
#include <sstream>

using namespace std;

class tokenHighlighter {
    public:
        tokenHighlighter(expressionProcessor lex_);
        void highlight(string file, string n_output);
    private:
        expressionProcessor lex;
};


tokenHighlighter::tokenHighlighter(expressionProcessor lex_){
    lex = lex_;
}

//Crea el archivo html con el texto resaltado
void tokenHighlighter::highlight(string file, string n_output){
    ofstream highlightedOutput;
    ifstream output;
    string line, word, token;
    bool found;

    try{
        highlightedOutput.open("htmlFiles/"+file+".html", ios::out);
        if(highlightedOutput.fail()){
            throw "Path error. The address or filename is incorrect\n";
        }
    } catch(char const* message){
        std::cerr<<message<<std::endl;
        exit(0);
    }

    
    try{
        output.open("outputFiles/output"+n_output+".txt", ios::in);
        if(output.fail()){
            throw "Path error. The address or filename is incorrect\n";
        }
    } catch(char const* message){
        std::cerr<<message<<std::endl;
        exit(0);
    }    

    highlightedOutput << "<!DOCTYPE html>\n<html lang=\"en\">\n";
    highlightedOutput << "<head>\n<meta charset=\"UTF-8\">\n";
    highlightedOutput << "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
    highlightedOutput << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    highlightedOutput << "<title>Highlighted Output</title>\n</head>\n<body>\n";
    highlightedOutput << "<div style=\"font-size:1.1rem; margin-top:20%; margin:auto; background-color:rgb(43, 41, 41); color:white; width:max-content; padding:1rem; border-radius:0.25rem;\">";

    while(!output.eof()){
        highlightedOutput << "\n";
        getline(output, line);
        stringstream lineStream(line);
        
        while(getline(lineStream, word, ' ')){
            found = false;
            for(int i = 0; i < lex.getSize(); i++){
                if(word == "&&"+lex.getToken(i)+"&&"){
                    highlightedOutput << " <a style=\"color:" << lex.getColor(i) << ";\"> ";
                    getline(lineStream, word, ' ');
                    token += word;
                    getline(lineStream, word, ' ');
                    while(word != "&&end&&"){
                        token += " "+word+" ";
                        getline(lineStream, word, ' ');
                    }
                    highlightedOutput << token << " </a> ";
                    found = true;
                    token = "";
                }  
            }
            if(found == false){
            highlightedOutput << word << " ";
            }
        }
        highlightedOutput << "<br>";
    }
    highlightedOutput << "</div>\n</body>\n</html>";
}


#endif // TOKENHIGHLIGHTER_H