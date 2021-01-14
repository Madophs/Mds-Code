#include "FileFactory.h"
#include "Utils.h"

// Public members

namespace mds {

FileFactory &FileFactory::get(){
    static FileFactory instance;
    return instance;
}

void FileFactory::removeNumbers(std::string &filename){
    get().interRemoveNumbers(filename);
}

void FileFactory::removeNonAlphabeticalCharacters(std::string &filename){
    get().interRemoveNonAlphabeticalCharacters(filename);
}

void FileFactory::capitalizeEveryWord(std::string &filename){
    get().interCapitalizeEveryWord(filename);
}

void FileFactory::problemNumberToEndOfFilename(std::string &filename){
    get().interProblemNumberToEndOfFilename(filename);
}

void FileFactory::separateFilenameWithUnderscores(std::string &filename){
   get().interSeparateFilenameWithUnderscores(filename);
}

void FileFactory::applyAllFormats(std::string &filename){
    removeNonAlphabeticalCharacters(filename);
    removeNumbers(filename);
    capitalizeEveryWord(filename);
    problemNumberToEndOfFilename(filename);
    separateFilenameWithUnderscores(filename);
}

void FileFactory::createSourceCodeFile(std::string filename,
        std::string fileExtension,
        std::string templateName /* = "" */,
        unsigned int index /* = 2 */){
    get().interCreateSourceCodeFile(filename, fileExtension, templateName, index);
}

// Private members

FileFactory::FileFactory(){
    readFilenameSection();
}

void FileFactory::interRemoveNonAlphabeticalCharacters(std::string &filename){
    if(!RemoveNonAlphabeticalCharacters || filename.empty()) return;
    auto iter = remove_if(filename.begin(), filename.end(), [&](char &c){
        if(c == ' ') return false;
        return !isalpha(c) && !isdigit(c);
    });
    filename.erase(iter, filename.end());
}

void FileFactory::interRemoveNumbers(std::string &filename){
    if(!RemoveNumbers || filename.empty()) return;
    auto iter = remove_if(filename.begin(), filename.end(), [&](char &c){
        return isdigit(c);
    });
    filename.erase(iter, filename.end());
}

void FileFactory::interCapitalizeEveryWord(std::string &filename){
    if(!CapitalizeEveryWord || filename.empty()) return;
    std::string tempFilename = "", word;
    std::stringstream ss(filename);
    for(int i = 0; ss>>word; i++){
        if(i) tempFilename += " ";
        word[0] = toupper(word[0]);
        tempFilename += word;
    }
    filename = tempFilename;
}

void FileFactory::interProblemNumberToEndOfFilename(std::string &filename){
    if(!ProblemNumberToEndOfFilename || filename.empty()) return;
    std::string tempFilename = "", word, number = "";
    std::stringstream ss(filename);
    for(int i = 0; ss>>word; i++){
        if(!i){
            if(!std::regex_match(word,std::regex("^[0-9]+$")))
                return;
            else
                number = word, word = "";
        }
        if(i){
            tempFilename += " ";
        }
        tempFilename += word;
    }
    filename = tempFilename + " " + number;
}

void FileFactory::interSeparateFilenameWithUnderscores(std::string &filename){
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

bool FileFactory::isTrue(std::string flag){
    return flag == "true";
}

void FileFactory::interCreateSourceCodeFile(std::string& filename,
        std::string& fileExtension,
        std::string& templateName,
        unsigned int& index) {
    applyAllFormats(filename);
    if(filename.empty()){
        printInColor("Error: ","red","filename is empty, please check the configuration file in /home/{USER}/MdsCode/mdscode.conf\n");
        return;
    }
    if(templateName.empty()){
        MdsFile file(filename, fileExtension);
        file.create();
        file.close();
    }else{
        std::string pathToTemplate = Globals::TEMPLATE_DIR_PATH+"/"+templateName;
        if(mds::fileExists(pathToTemplate)){
            MdsFile file(filename, fileExtension);
            file.createFileWithContent(pathToTemplate);
            file.close();
        }else{
            printInColor("Error: ","red","template "+templateName+" does not exists.\n");
        }
    }
}

void FileFactory::readFilenameSection(){
    std::ifstream configFile;
    std::string line;
    configFile.open(Globals::CONFIG_FILE_PATH.c_str());
    if(!configFile.fail()){
        std::string token;
        bool finished = false, sectionFound = false, foundSection = false;
        unsigned int lineNumber = 0;
        while(getline(configFile,line)){
            ++lineNumber;
            std::stringstream ss(line);
            while(ss>>token){
                if(token != "[filename]" || token[0] == '#') break;
                std::string flagName, flagValue;
                char equals; // To get the '=' character
                sectionFound = true; // We found the [filename] section
                while(getline(configFile,line)){
                    std::stringstream flagLine(line);
                    while(flagLine>>flagName){
                        if(flagName[0] == '#') break;
                        // An opening bracket means a new section, we finish with [filename]
                        if(flagName[0] == '['){
                            finished = true;
                            break;
                        }
                        flagLine>>equals; // We take out the equals symbol
                        flagLine>>flagValue; // let's tet the flag value
                        if(flagValue != "true" && flagValue != "false"){
                            printInColor("Errors in [filename] section, line #"+std::to_string(lineNumber)+".\n","red");
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
                            printInColor("Errors in [filename] section, line # "+std::to_string(lineNumber)+".\n","red");
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
} // namespace mds
