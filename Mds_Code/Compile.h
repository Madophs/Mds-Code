#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

string getExtension(string filename){
    int pos = filename.find_last_of('.');
    if(pos+1 == filename.length()) return "";
    return filename.substr(pos+1,string::npos);
}

bool sourceCodeFileExists(string filename){
    fstream file;
    file.open(filename);
    return !file.fail();
}

string constructCommand(string filename){
    string command = "", fileExtension = getExtension(filename);
    if(fileExtension.empty()) return "-1";
    ifstream configFile;
    string homeDirectory = getenv("HOME");
    string pathToConfigFile = homeDirectory + "/MdsCode/mdscode.conf";
    string pathToMdsBinary = homeDirectory + "/MdsCode/mds";
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
                            bool foundFilenameLocation = false, foundBinaryNameLocation = false;
                            for(int i = 0; commandTokenizer>>token; i++){
                                if(i) command += " ";
                                if(token == "{{binary}}"){
                                    command += pathToMdsBinary;
                                    foundBinaryNameLocation = true;
                                }else if(token == "{{filename}}"){
                                    command += filename;
                                    foundFilenameLocation = true;
                                }else{
                                    command += token;
                                }
                            }
                            if(!foundFilenameLocation) return "-5";
                            if(!foundBinaryNameLocation) return "-7";
                            return command;
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
    return "-6";
}

void buildSourceCode(string filename){
    if(!sourceCodeFileExists(filename)){
        cout<<"Error: file "<<filename<<" not found"<<endl;
        exit(1);
    }
    string command = constructCommand(filename);
    if(command == "-1"){
        cout<<"Error: file extension not valid."<<endl;
        exit(1);
    }else if(command == "-2"){
        cout<<"Error: config file not found"<<endl;
        exit(1);
    }else if(command == "-3"){
        cout<<"Errors in compilation section"<<endl;
        exit(1);
    }else if(command == "-4"){
        cout<<"Command sintax not found in config file"<<endl;
        exit(1);
    }else if(command == "-5"){
        cout<<"Error: you must specify {{ filename }} in the command"<<endl;
        exit(1);
    }else if(command == "-6"){
        cout<<"Error: compilation section not found"<<endl;
        exit(1);
    }else if(command == "-7"){
        cout<<"Error: binary file output location not specified"<<endl;
        exit(1);
    }
    system(command.c_str());
}