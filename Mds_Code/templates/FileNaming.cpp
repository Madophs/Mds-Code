#include "FileNaming.h"

// Public members

FileNaming &FileNaming::get(){
    static FileNaming instance;
    return instance;
}

void FileNaming::removeNumbers(string &filename){
    get().interRemoveNumbers(filename);
}

void FileNaming::removeNonAlphabeticalCharacters(string &filename){
    get().interRemoveNonAlphabeticalCharacters(filename);
}

void FileNaming::capitalizeEveryWord(string &filename){
    get().interCapitalizeEveryWord(filename);
}

void FileNaming::problemNumberToEndOfFilename(string &filename){
    get().interProblemNumberToEndOfFilename(filename);  
}

void FileNaming::separateFilenameWithUnderscores(string &filename){
   get().interSeparateFilenameWithUnderscores(filename);
}

void FileNaming::applyAllFormats(string &filename){
    removeNonAlphabeticalCharacters(filename);
    removeNumbers(filename);
    capitalizeEveryWord(filename);
    problemNumberToEndOfFilename(filename);
    separateFilenameWithUnderscores(filename);
}

// Private members

FileNaming::FileNaming(){
    readFilenameSection();
}

void FileNaming::interRemoveNonAlphabeticalCharacters(string &filename){
    if(!RemoveNonAlphabeticalCharacters || filename.empty()) return;
    auto iter = remove_if(filename.begin(), filename.end(), [&](char &c){
        if(c == ' ') return false;
        return !isalpha(c) && !isdigit(c);
    });
    filename.erase(iter, filename.end());
}

void FileNaming::interRemoveNumbers(string &filename){
    if(!RemoveNumbers || filename.empty()) return;
    auto iter = remove_if(filename.begin(), filename.end(), [&](char &c){
        return isdigit(c);
    });
    filename.erase(iter, filename.end());
}

void FileNaming::interCapitalizeEveryWord(string &filename){
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

void FileNaming::interProblemNumberToEndOfFilename(string &filename){
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

void FileNaming::interSeparateFilenameWithUnderscores(string &filename){
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

bool FileNaming::isTrue(string flag){
    return flag == "true";
}

void FileNaming::readFilenameSection(){
    ifstream configFile;
    string line;
    configFile.open(Globals::CONFIG_FILE_PATH.c_str());
    if(!configFile.fail()){
        string token;
        bool finished = false, sectionFound = false, foundSection = false;
        while(getline(configFile,line)){
            stringstream ss(line);
            while(ss>>token){
                if(token != "[filename]" || token[0] == '#') break;
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
                            printInColor("Errors in [filename] section.\n","red");
                            exit(EXIT_FAILURE);
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
                        }else if(flagName == "ChangeLettersToEnglishAlphabet"){
                            ChangeLettersToEnglishAlphabet = isTrue(flagValue);
                        }else{
                            printInColor("Errors in [filename] section.\n","red");
                            exit(EXIT_FAILURE);
                        }
                    }
                    if(finished) break;
                }
                if(finished) break;  
            }
        }
        if(!sectionFound){
            printInColor("Error: ","red","section [filename] not found in config file.\n");
            exit(EXIT_FAILURE);
        }
    }else{
        printInColor("Error: ","red","mdscode.conf not found.\nmdscode --config may fix this. (If you are doing this, ignore this message).\n");
    }
}
