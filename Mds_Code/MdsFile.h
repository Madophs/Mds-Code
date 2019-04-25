#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

class MdsFile {
    public:
        MdsFile(string,string);
        string getFilename() const;
        void create();
        void createAtMdsCodeDirectory();
        void createFileWithContent(string);
        vector<int> kmpPreprocess(string);
        string kmpReplace(string &,string &,string,vector<int> &);
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
    string searchString = "{{classname}}";
    vector<int> pattern = kmpPreprocess(searchString);
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
                    kmpReplace(line,searchString,filename,pattern);
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
                        kmpReplace(line,searchString,filename,pattern);
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

vector<int> MdsFile::kmpPreprocess(string line){
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

string MdsFile::kmpReplace(string &line, string &search, string replaceString, vector<int> &pattern){
    int i = 0, j = 0;
    vector<pair<int,int>> indexes;
    while(i < line.length()){
        while(j>=0 && line[i] != search[j]) j = pattern[j];
        ++j,++i;
        if(j == search.length()){
            line.replace(i-j,j,replaceString);
            i = 0, j = 0;
        }
    }
    return line;
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