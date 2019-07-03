#include <sstream>
#include <regex>
#include "Config.h"

bool RemoveNonAlphabeticalCharacters = true;
bool ProblemNumberToEndOfFilename = true;
bool SeparateFilenameWithUnderscores = true;
bool CapitalizeEveryWord = false;
bool RemoveNumbers = false;

bool isTrue(string flag){
    return flag == "true";
}

bool readFilenameSection(){
    ifstream configFile;
    string homeDirectory = getenv("HOME");
    string pathToConfigfile = homeDirectory + "/MdsCode/mdscode.conf";
    string line;
    configFile.open(pathToConfigfile);
    if(!configFile.fail()){
        string token;
        bool finished = false, sectionFound = false, foundSection = false;
        while(getline(configFile,line)){
            stringstream ss(line);
            while(ss>>token){
                if(token != "[filename]") break;
                string flagName, flagValue;
                char equals;
                sectionFound = true;
                while(getline(configFile,line)){
                    stringstream flagLine(line);
                    while(flagLine>>flagName){
                        if(flagName[0] == '#') break;
                        if(flagName[0] == '['){
                            finished = true;
                            break;
                        }
                        flagLine>>equals;
                        flagLine>>flagValue;
                        if(flagValue != "true" && flagValue != "false"){
                            printInColor("Errors in [filename] section.","red");
                            exit(1);
                        }
                        if(flagName == "RemoveNonAlphabeticalCharacters"){
                            RemoveNonAlphabeticalCharacters = isTrue(flagValue);
                        }else if(flagName == "ProblemNumberToEndOfFilename"){
                            ProblemNumberToEndOfFilename = isTrue(flagValue);
                        }else if(flagName == "SeparateFilenameWithUnderscores"){
                            SeparateFilenameWithUnderscores = isTrue(flagValue);
                        }else if(flagName == "CapitalizeEveryWord"){
                            CapitalizeEveryWord = isTrue(flagValue);
                        }else if(flagName == "RemoveNumbers"){
                            RemoveNumbers = isTrue(flagValue);
                        }else{
                            printInColor("Errors in [filename] section.","red");
                            exit(1);
                        }
                    }
                    if(finished) break;
                }
                if(finished) break;  
            }
        }
        if(!sectionFound){
            printInColor("Error: ","red","section [filename] not found in config file.\n");
            exit(1);
        }
    }else{
        printInColor("Error: ","red","mdscode.conf not found.\nmdscode --config may fix this. (If you are doing this, ignore this message).\n");
    }
    return true;
}

string rawFilename(int argc, char * argv[], int index){
    string rawFilename = "";
    bool firstLoop = true;
    for(; index < argc; index++, firstLoop = false){
        if(!firstLoop) rawFilename += " ";
        rawFilename += argv[index];
    }
    return rawFilename;
}

void flagRemoveNonAlphabeticalCharacters(string &filename){
    if(!RemoveNonAlphabeticalCharacters || filename.empty()) return;
    auto iter = remove_if(filename.begin(), filename.end(), [&](char &c){
        if(c == ' ') return false;
        return !isalpha(c) && !isdigit(c);
    });
    filename.erase(iter, filename.end());
}
void flagRemoveNumbers(string &filename){
    if(!RemoveNumbers || filename.empty()) return;
    auto iter = remove_if(filename.begin(), filename.end(), [&](char &c){
        return isdigit(c);
    });
    filename.erase(iter, filename.end());
}
void flagCapitalizeEveryWord(string &filename){
    if(!CapitalizeEveryWord || filename.empty()) return;
    string tempFilename = "", word;
    stringstream ss(filename);
    for(int i = 0; ss>>word; i++){
        if(i) tempFilename += " ";
        word[0] = toupper(word[0]);
        tempFilename += word;
    }
    filename = tempFilename;
}

void flagProblemNumberToEndOfFilename(string &filename){
    if(!ProblemNumberToEndOfFilename || filename.empty()) return;
    string tempFilename = "", word, number = "";
    stringstream ss(filename);
    for(int i = 0; ss>>word; i++){
        if(!i){
            if(!regex_match(word,regex("^[0-9]+$")))
                return;
            else
                number = word, word = "";
        }
        if(i>1){
            tempFilename += " ";
        }
        tempFilename += word;
    }
    filename = tempFilename + " " + number;   
}

void flagSeparateFilenameWithUnderscores(string &filename){
    if(filename.empty()) return;
    if(SeparateFilenameWithUnderscores){
        transform(filename.begin(), filename.end(), filename.begin(),[&](char &c){
            return c == ' ' ? '_' : c;
        });
    }else{
        filename.erase(remove_if(filename.begin(), filename.end(),[&](char &c){
            return c == ' ';
        }), filename.end());
    }
}
