#include <iomanip>
#include <iostream>

using namespace std;

const double version = 1.5;
const int partialCommandLength = 6, fullCommandLength = 18;

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
    cout<<endl;
    cout<<"Sintax: mds_code [parameter] filename"<<endl;
    cout<<endl;
    cout<<setw(partialCommandLength)<<"-s"<<setw(fullCommandLength)<<"--setup"<<"Create everything necessary to make this command work"<<endl;
    cout<<setw(partialCommandLength+fullCommandLength)<<" "<<"It will setup everything as default, including your own configurations."<<endl;
    cout<<setw(partialCommandLength)<<"-n"<<setw(fullCommandLength)<<"--new"<<"Create a new file with specified name (literally)."<<endl;
    cout<<setw(partialCommandLength)<<"-c++"<<setw(fullCommandLength)<<"--c++"<<"Create a C++ file with predefined code."<<endl;
    cout<<setw(partialCommandLength)<<"-j"<<setw(fullCommandLength)<<"--java"<<"Create a Java file with predefined code."<<endl;
    cout<<setw(partialCommandLength)<<"-e"<<setw(fullCommandLength)<<"--extension"<<"Create a file with specified extension."<<endl;
    cout<<setw(partialCommandLength+fullCommandLength)<<" "<<"Sintax mdscode -e cpp -t mytemplate.cpp hello world"<<endl;
    cout<<setw(partialCommandLength+fullCommandLength)<<" "<<"(optional -t stands for template, the specified template must be in MdsCode directory)"<<endl;
    cout<<setw(partialCommandLength)<<"-b"<<setw(fullCommandLength)<<"--build"<<"Compile the specified file. (Binary file is located in MdsCode directory)"<<endl;  
    cout<<setw(partialCommandLength)<<"-r"<<setw(fullCommandLength)<<"--run"<<"Execute the mds binary file in MdsCode directory"<<endl;  
    cout<<setw(partialCommandLength+fullCommandLength)<<" "<<"-ri -ro -rio are valid parameters, i = input and o = output making reference to the IO files in MdsDirectory."<<endl;
    cout<<setw(partialCommandLength+fullCommandLength)<<" "<<"Fullname commands: --run_with_input, --run_with_output, --run_with_io."<<endl;
    cout<<setw(partialCommandLength)<<"-io"<<setw(fullCommandLength)<<"--input_output"<<"Creates input and output files."<<endl;
    cout<<setw(partialCommandLength)<<"-c"<<setw(fullCommandLength)<<"--config"<<"Create mdscode configuation file."<<endl;
    cout<<setw(partialCommandLength)<<"-cc"<<setw(fullCommandLength)<<"--c++_tpl"<<"Creates default C++ template."<<endl;
    cout<<setw(partialCommandLength)<<"-cj"<<setw(fullCommandLength)<<"--java_tpl"<<"Creates default Java template."<<endl;
    cout<<setw(partialCommandLength)<<"-v"<<setw(fullCommandLength)<<"--version"<<"Displays the current version."<<endl;
    cout<<setw(partialCommandLength)<<"-h"<<setw(fullCommandLength)<<"--help"<<"Show this help."<<endl;
    cout<<endl;
    cout<<"This is an open source software feel free to use it, modified it and add your own features"<<endl;
    cout<<"Please tell me your recommendations and how can I improve it."<<endl;
    cout<<"I code this command to handle the creation of files quickly when I'm participanting in programming contest."<<endl;
    cout<<"I hope this command is useful for you like it is for me :)"<<endl;
}