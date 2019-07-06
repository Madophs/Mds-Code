#include "CompileAndRun.h"


void setFilenameAndExtension(string fullFilename, string &filename, string &extension){
    int pos = fullFilename.find_first_of('.');
    if(pos == fullFilename.length() || pos+1 == fullFilename.length()){
        filename = fullFilename;
        extension = "";
    }else{
        filename = fullFilename.substr(0,pos);
        extension = fullFilename.substr(pos+1, string::npos);
    }
}

string getCurrentPath(){
    FILE *fpipe = popen("pwd","r");
    char line[300];
    string output = "", token,path;
    while(fgets(line,200,fpipe)) output += line;
    stringstream ss(line);
    for(int i = 0; ss>>token; i++){
        path += token;
    }
    if(path.empty()) return "";
    return path;
}

bool directoryExists(string pathToDirectory){
    string command = "[ -d \""+pathToDirectory+"\" ] && echo \"Exists.\"";
    FILE *fpipe = popen(command.c_str(),"r");
    char line[50];
    string output = "", token,path;
    while(fgets(line,200,fpipe)) output += line;
    stringstream ss(line);
    for(int i = 0; ss>>token; i++){
        path += token;
    }
    if(path.empty()) return false;
    return true;
}

void exportSourceFile(int argc, char *argv[]){
    string exportPath = homeDirectory+"/MdsCode/exports/";
    if(argc > 2){
        if(argc == 3){
            string command = "cp "+((string)argv[2])+" "+homeDirectory+"/MdsCode/exports/"+((string)argv[2]);
            system(command.c_str());
        }else{
            string filename, extension;
            setFilenameAndExtension(argv[2], filename, extension);
            string originalFilename = filename;
            for(int i = 3; i < argc; i+=2){
                string parameter = argv[i];
                if(parameter != "-p" && parameter != "-name"){
                    printInColor("Error: ","red","option \""+parameter+"\" not known.\n");
                    exit(1);
                }
                if(parameter == "-p"){
                    if(i+1 >= argc){
                        printInColor("Error: ","red","path not specified.\n");
                        exit(1);
                    }
                    exportPath = argv[i+1];
                }
                if(parameter == "-name"){
                    if(i+1 >= argc){
                        printInColor("Error: ","red","filename not specified.\n");
                        exit(1);
                    }
                    filename = argv[i+1];
                }
            }
            if(exportPath.back() != '/') exportPath.push_back('/');
            if(!directoryExists(exportPath)){
                printInColor("Error: ","red","directory "+exportPath+" does not exists.\n");
                exit(1);
            }
            string currentFilePath = getCurrentPath()+"/"+argv[2];
            if(currentFilePath == exportPath+filename+"."+extension){
                printInColor("Error: ","red","you can not export to the same directory with the same filename.\n");
                exit(1);
            }
            if(extension != "java"){
                string command = "cp "+((string)argv[2])+" "+exportPath+filename+"."+extension;
                system(command.c_str());
            }else{
                MdsFile fileExport(filename,extension);
                fileExport.createFileWithContent(getCurrentPath()+"/"+((string)argv[2]),originalFilename);
                fileExport.close();
                string command = "cp "+((string)argv[2])+" "+exportPath+filename+"."+extension;
                system(command.c_str());       
            }
        }
    }else{
        printInColor("Error: ","red","filename not specified.\n");
    }
}