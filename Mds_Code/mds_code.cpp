#include <iomanip>
#include "FileCreation.h"
#include "Compile.h"

const double version = 1.2;
const int partialCommandLength = 6, fullCommandLength = 12;

string getOperatingSystem(){
    FILE *fpipe = popen("lsb_release -d","r");
    char line[200];
    string output = "", token, operatingSystem = "";
    while(fgets(line,200,fpipe)) output += line;
    stringstream ss(line);
    ss>>token;
    for(int i = 0; ss>>token; i++){
        operatingSystem += i?" ":"";
        operatingSystem += token;
    }
    if(operatingSystem.empty()) return "";
    return "("+operatingSystem+")";
}

void displayVersion(){
    cout<<"Mds Code "<<version<<" "<<getOperatingSystem()<<endl;
    cout<<"This is an open source software."<<endl;
    cout<<"Developed by Jehú Jair Ruiz Villegas A.K.A Madophs."<<endl;
}
void displayHelp(){
    cout<<"Mds Code "<<version<<" developed by Jehú Jair Ruiz Villegas"<<endl;
    cout<<"Operating System: "<<getOperatingSystem()<<endl;
    cout<<"mds_code [parameter] filename"<<endl;
    cout<<setw(partialCommandLength)<<"-s"<<setw(fullCommandLength)<<"--setup"<<"Create everything necessary to make this command work. (It will setup everything as default, including your own configurations)."<<endl;
    cout<<setw(partialCommandLength)<<"-n"<<setw(fullCommandLength)<<"--new"<<"Create a new file with specified name (literally)."<<endl;
    cout<<setw(partialCommandLength)<<"-c"<<setw(fullCommandLength)<<"--c"<<"Create a C file with predifined code."<<endl;
    cout<<setw(partialCommandLength)<<"-c++"<<setw(fullCommandLength)<<"--c++"<<"Create a C++ file with predifined code."<<endl;
    cout<<setw(partialCommandLength)<<"-j"<<setw(fullCommandLength)<<"--java"<<"Create a Java file with predifined code."<<endl;
    cout<<setw(partialCommandLength)<<"-b"<<setw(fullCommandLength)<<"--build"<<"Compile the specified file. (Binary file is located in MdsCode directory)"<<endl;
    cout<<setw(partialCommandLength)<<"-v"<<setw(fullCommandLength)<<"--version"<<"Displays the current version."<<endl;
    cout<<setw(partialCommandLength)<<"-h"<<setw(fullCommandLength)<<"--help"<<"Show this help."<<endl;
    cout<<endl;
    cout<<"This is an open source software feel free to use it, modified it and add your own features"<<endl;
    cout<<"Please tell me your recommendations and how can I improve it."<<endl;
    cout<<"I code this command to handle the creation of files quickly when I'm participanting in programming contest."<<endl;
    cout<<"I hope this command is useful for you like it is for me :)"<<endl;
}
void createStandardFile(int &argc,char *argv[]){
    string filename = "";
    for(int i = 2; i<argc; i++){
        if(i > 2) filename += " ";
        filename += argv[i];
    }
    MdsFile file(filename);
    file.create();
    file.close();
}

int main(int argc, char *argv[]){
    cout<<fixed<<setfill(' ')<<setprecision(1)<<left;
    readFilenameSection();
    try{
        if(argc > 1){
            string parameter = argv[1];
            if(parameter == "-v" || parameter == "--version"){
                displayVersion();
            }else if(parameter == "-n" || parameter == "--new"){
                createStandardFile(argc, argv);   
            }else if(parameter == "-h" || parameter == "--help"){
                displayHelp();
            }else if(parameter == "-s" || parameter == "--setup"){
                setupDefaultEnvironment();
            }else if(parameter == "-c++" || parameter == "--c++"){
                createSourceCodeFile(argc, argv, "cpp");
            }else if(parameter == "-b" || parameter == "--build"){
                buildSourceCode(argv[2]);
            }else{
                throw "Error: invalid parameter.";
            }
        }else{
            throw "Error: missing parameters.\nSee -h for help.";
        }
    }catch(const char * error){
        cout<<error<<endl;
    }
    return 0;
}