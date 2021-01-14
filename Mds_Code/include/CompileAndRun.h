#ifndef FILECREATION_H
#define FILECREATION_H

#include "FileFactory.h"

using namespace std;

string homeDirectory = getenv("HOME");

vector<int> kmpPreprocess(string line){
    vector<int> pattern(line.length()+1, 0);
    pattern[0] = -1;
    int j = -1, i = 0;
    while(i<line.length()){
        while(j > -1 && line[j] != line[i]) j = pattern[j];
        ++j, ++i;
        pattern[i] = j;
    }
    return pattern;
}

void kmpReplace(string &line, string search, string replaceString, vector<int> pattern, bool specialCase = false){
    int i = 0, j = 0;
    vector<pair<int,int>> indexes;
    while(i < line.length()){
        while(j>=0 && line[i] != search[j]) j = pattern[j];
        ++j,++i;
        if(j == search.length()){
            if(specialCase){
                if((i-j == 0 && !isalpha(line[i])) || (i-j > 0 && (!isalpha(line[i-j-1]) && !isalpha(line[i])))){
                    line.replace(i-j,j,replaceString);
                    i = 0, j = 0;
                }else{
                    j = pattern[j];
                }
            }else{
                line.replace(i-j,j,replaceString);
                i = 0, j = 0;
            }
        }
    }
}


string getExtension(string filename){
    int pos = filename.find_last_of('.');
    if(pos+1 == filename.length()) return "";
    return filename.substr(pos+1,string::npos);
}

bool fileExists(string filename){
    fstream file;
    file.open(filename);
    return !file.fail();
}

string constructCommand(string filename){
    string command = "", fileExtension = getExtension(filename);
    if(fileExtension.empty()) return "-1";
    ifstream configFile;
    string pathToConfigFile = homeDirectory + "/MdsCode/mdscode.conf";
    string pathToBinDirectory = homeDirectory + "/MdsCode/bin/";
    string pathToMdsBinary = pathToBinDirectory + "mds";
    configFile.open(pathToConfigFile);
    if(!configFile.fail()){
        string line, token;
        bool commandFound = false;
        while(getline(configFile, line)){
            stringstream lineTokenizer(line);
            while(lineTokenizer>>token){
                if(token == "[compilation]"){
                    while(getline(configFile, line)){
                        string extensionCommand;
                        char equals;
                        stringstream commandTokenizer(line);
                        while(commandTokenizer>>extensionCommand){
                            if(extensionCommand[0] == '#') break;
                            if(extensionCommand != fileExtension) break;
                            commandFound = true;
                            if(commandTokenizer.eof()) return "";
                            commandTokenizer>>equals;
                            if(equals != '=') return "-3";
                            if(commandTokenizer.eof()) return "-3";
                            while(*token.begin() == ' ') token.erase(token.begin());
                            if(token.empty()) return "-4";
                            getline(commandTokenizer,token);
                            kmpReplace(token,"{{output}}",pathToMdsBinary,kmpPreprocess("{{output}}"));
                            kmpReplace(token,"{{bin}}",pathToBinDirectory,kmpPreprocess("{{bin}}"));
                            kmpReplace(token,"{{filename}}",filename,kmpPreprocess("{{filename}}"));
                            kmpReplace(token,"{{source}}",homeDirectory+"/MdsCode/source/",kmpPreprocess("{{filename}}"));
                            kmpReplace(token,"{{mds}}",homeDirectory+"/MdsCode/bin/",kmpPreprocess("{{filename}}"));
                            return command = token;
                        }
                    }
                    return "-4";
                }else{
                    break;
                }
            }
        }
    }else{
        return "-2";
    }
    return "-5";
}

void buildSourceCode(string filename){
    if(!fileExists(filename)){
        printInColor("Error: ","red","file"+filename+" not found.\n");
        exit(1);
    }
    string command = constructCommand(filename);
    if(command == "-1"){
        printInColor("Error: ","red","file extension not valid.\n");
        exit(1);
    }else if(command == "-2"){
        printInColor("Error: ","red","config file not found.\n");
        exit(1);
    }else if(command == "-3"){
        printInColor("Errors in compilation section.\n","red");
        exit(1);
    }else if(command == "-4"){
        printInColor("Error: ","red","command sintax not found in config file.\n");
        exit(1);
    }else if(command == "-5"){
        printInColor("Error: ","red","compilation section not found in config file.\n");
        exit(1);
    }
    string fileExtension = getExtension(filename);
    string line, filenameWithoutExtension = filename.substr(0,filename.length()-fileExtension.length()-1);
    if(fileExtension == "java" && filenameWithoutExtension != "Main"){
        ifstream input(filename);
        ofstream output(homeDirectory+"/MdsCode/source/Main.java",ios::out);
        vector<int> pattern = kmpPreprocess(filenameWithoutExtension);
        while(getline(input,line)){
            kmpReplace(line,filenameWithoutExtension,"Main",pattern,true);
            output<<line<<endl;
        }
        input.close();
        output.close();
    }
    while(command[0] == ' ') command.erase(command.begin());
    system(command.c_str());
}

void executeBinaryFile(bool input = false, bool output = false, bool javaFile = false){
    string mdscodeDirectory = homeDirectory + "/MdsCode";
    string pathToInput = mdscodeDirectory + "/input.txt";
    string pathToOutput = mdscodeDirectory + "/output.txt";
    string inputCommand = input ? " < " + pathToInput: "";
    string outputCommand = output ? " > " + pathToOutput: "";
    if(!fileExists(mdscodeDirectory+"/bin/mds") && !javaFile){
        printInColor("Error: ","red","binary file \"mds\" not found.\n");
        exit(1);
    }
    if(input && !fileExists(pathToInput)){
        printInColor("Error: ","red","input file doesn't exists.\n");
        exit(1);
    }
    if(output && !fileExists(pathToOutput)){
        printInColor("Error: ","red","output file doesn't exists.\n");
        exit(1);
    }
    string command;
    if(javaFile){
        command = "cd "+mdscodeDirectory+"/bin/ && java Main "+ inputCommand + outputCommand;
    }else{
        command = mdscodeDirectory+"/bin/mds"+ inputCommand + outputCommand;
    }
    system(command.c_str());
}

#endif
