#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

class MdsFile {
    public:
        MdsFile(string,string);
        string getFilename() const;
        void create();
        void createAtHomeDirectory();
        void createFileWithContent(string);
        void setExtension(string);
    private:
        string filename;
        string homeDirectory;
        string fileExtension;
};

MdsFile::MdsFile(string filename, string fileExtension = ""){
    this->filename = filename;
    this->homeDirectory = getenv("HOME");
    this->fileExtension = fileExtension;
}

void MdsFile::create(){
    string fullFilename = filename;
    if(!fileExtension.empty()) fullFilename+="."+fileExtension;
    fstream fileExists;
    fileExists.open(fullFilename);
    if(fileExists.fail()){
        ofstream file(fullFilename, ios::out);
        file.close();
    }else{
        string decision;
        cout<<"File already exists, overwrite? (y,n)"<<endl;
        cin>>decision;
        transform(decision.begin(), decision.end(), decision.begin(),::tolower);
        if(decision == "y" || decision == "yes"){
            ofstream file(fullFilename, ios::out);
            file.close();
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
                ofstream file(fullFilename, ios::out);
                string line;
                while(getline(fileContent,line)){
                    file<<line<<"\n";
                }
                file.close();
            }else{
                string decision;
                cout<<"File already exists, overwrite? (y,n)"<<endl;
                cin>>decision;
                transform(decision.begin(), decision.end(), decision.begin(),::tolower);
                if(decision == "y" || decision == "yes"){
                    ofstream file(fullFilename, ios::out);
                    string line;
                    while(getline(fileContent,line)){
                        file<<line<<"\n";
                    }
                    file.close();
                }
            }
            
        }else{
            throw "Error: file does not exists.";
        }
    }catch(const char * error){
        cout<<error<<endl;
    }
}

void MdsFile::createAtHomeDirectory(){
    ofstream file(homeDirectory+"/"+filename, ios::out);
    file.close();
}

void MdsFile::setExtension(string fileExtension){
    this->fileExtension = fileExtension;
}