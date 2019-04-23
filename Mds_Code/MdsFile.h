#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

class MdsFile {
    public:
        MdsFile(string,string);
        string getFilename() const;
        void create();
        void createAtMdsCodeDirectory();
        void createFileWithContent(string);
        void setExtension(string);
        void addText(string);
        void addNewLine();
        void close();
        string getCurrentPath();
    private:
        string filename;
        string homeDirectory;
        string fileExtension;
        string mdscodeDirectory;
        string pathToFile;
        ofstream file;
};

MdsFile::MdsFile(string filename, string fileExtension = ""){
    this->filename = filename;
    this->homeDirectory = getenv("HOME");
    this->fileExtension = fileExtension;
    this->mdscodeDirectory = homeDirectory+"/MdsCode";
}

string MdsFile::getFilename() const{
    return this->filename;
}

void MdsFile::create(){
    string fullFilename = filename;
    if(!fileExtension.empty()) fullFilename+="."+fileExtension;
    fstream fileExists;
    fileExists.open(fullFilename);
    if(fileExists.fail()){
        file.open(fullFilename, ios::out);
    }else{
        string decision;
        cout<<"File already exists, overwrite? (y,n)"<<endl;
        cin>>decision;
        transform(decision.begin(), decision.end(), decision.begin(),::tolower);
        if(decision == "y" || decision == "yes"){
            file.open(fullFilename, ios::out);
        }
    }
}

void MdsFile::createFileWithContent(string pathToFile){
    string fullFilename = filename;
    if(!fileExtension.empty()) fullFilename+="."+fileExtension;
    try{
        ifstream fileContent;
        fileContent.open(pathToFile);
        if(!fileContent.fail()){
            fstream fileExists;
            fileExists.open(fullFilename);
            if(fileExists.fail()){
                file.open(fullFilename, ios::out);
                string line;
                while(getline(fileContent,line)){
                    file<<line<<"\n";
                }
            }else{
                string decision;
                cout<<"File already exists, overwrite? (y,n)"<<endl;
                cin>>decision;
                transform(decision.begin(), decision.end(), decision.begin(),::tolower);
                if(decision == "y" || decision == "yes"){
                    file.open(fullFilename, ios::out);
                    string line;
                    while(getline(fileContent,line)){
                        file<<line<<"\n";
                    }
                }
            }
        }else{
            throw "Error: file does not exists.";
        }
    }catch(const char * error){
        cout<<error<<endl;
    }
}


void MdsFile::createAtMdsCodeDirectory(){
    string fullFilename = filename;
    if(!fileExtension.empty()) fullFilename += "." + fileExtension;
    string fullFilenameWithPath = mdscodeDirectory+"/"+fullFilename;
    file.open(fullFilenameWithPath);
}

void MdsFile::setExtension(string fileExtension){
    this->fileExtension = fileExtension;
}

void MdsFile::addText(string line){
    file<<line<<"\n";
}

void MdsFile::addNewLine(){
    file<<"\n";
}

void MdsFile::close(){
    file.close();
}