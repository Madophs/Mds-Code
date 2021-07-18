#include "Utils.h"

namespace mds {
using namespace std;

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

void exportSourceFile(int argc, char *argv[]){
    if(argc > 2){
        if(argc == 3){
            string command = "cp "+((string)argv[2])+" "+ Globals::EXPORTS_DIR_PATH;
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

            if(!dirExists(exportPath)){
                printInColor("Error: ","red","directory "+exportPath+" does not exists.\n");
                exit(1);
            }
            string currentFilePath = Globals::CWD+"/"+argv[2];
            if(currentFilePath == exportPath+filename+"."+extension){
                printInColor("Error: ","red","you can not export to the same directory with the same filename.\n");
                exit(1);
            }
            if(extension != "java"){
                string command = "cp "+((string)argv[2])+" "+exportPath+filename+"."+extension;
                system(command.c_str());
            }else{
                MdsFile fileExport(filename,extension);
                fileExport.createFileWithContent(Globals::CWD+"/"+((string)argv[2]),originalFilename);
                fileExport.close();
                string command = "rm -f "+exportPath+filename+"."+extension+" ";
                system(command.c_str());
                command = "mv "+filename+"."+extension+" "+exportPath;
                system(command.c_str());
            }
        }
    }else{
        printInColor("Error: ","red","filename not specified.\n");
    }
}
} // namespace mds
