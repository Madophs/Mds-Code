#include "FileCreation.h"
#include "CompileAndRun.h"
#include "Info.h"

int main(int argc, char *argv[]){
    cout<<fixed<<setfill(' ')<<setprecision(1)<<left;
    readFilenameSection();
    try{
        if(argc > 1){
            string parameter = argv[1];
            if(parameter == "-v" || parameter == "--version"){
                displayVersion();
            }else if(parameter == "-n" || parameter == "--new"){
                if(argc > 2){
                    string filename = "";
                    for(int i = 2; i<argc; i++){
                        if(i > 2) filename += " ";
                        filename += argv[i];
                    }
                    MdsFile file(filename);
                    file.create();
                    file.close();  
                }else{
                    cout<<"Error: filename not specified."<<endl;
                }
            }else if(parameter == "-h" || parameter == "--help"){
                displayHelp();
            }else if(parameter == "-s" || parameter == "--setup"){
                setupDefaultEnvironment();
            }else if(parameter == "-c++" || parameter == "--c++"){
                if(argc > 2){
                    createSourceCodeFile(argc, argv, "cpp","template_cpp.cpp");
                }else{
                    cout<<"Error: filename not specified."<<endl;
                }
            }else if(parameter == "-j" || parameter == "--java"){
                if(argc > 2){
                    createSourceCodeFile(argc, argv, "java","template_java.java");
                }else{
                    cout<<"Error: filename not specified."<<endl;
                }
            }else if(parameter == "-b" || parameter == "--build"){
                if(argc > 2){
                    buildSourceCode(argv[2]);
                }else{
                    cout<<"Error: filename not specified."<<endl;
                }
            }else if(parameter == "-c" || parameter == "--config"){
                createConfigfile();
            }else if(parameter == "-cc" || parameter == "--c++_tpl"){
                createDefaultCplusplusTemplate();
            }else if(parameter == "-cj" || parameter == "--java_tpl"){
                createDefaultJavaTemplate();
            }else if(parameter == "-io" || parameter == "--input_output"){
                createIOFiles();
            }else if(parameter == "-r" || parameter == "-rio" || parameter == "-ro" || parameter == "-ri" || parameter == "--run"){
                bool withInput = parameter == "-rio" || parameter == "-ri" ? true : false;
                bool withOutput = parameter == "-rio" || parameter == "-ro" ? true : false;
                executeBinaryFile(withInput, withOutput);
            }else if(parameter == "--run_with_io" || parameter == "--run_with_input" || parameter == "--run_with_output"){
                bool withInput = parameter == "--run_with_io" || parameter == "--run_with_input" ? true : false;
                bool withOutput = parameter == "--run_with_io" || parameter == "--run_with_output" ? true : false;
                executeBinaryFile(withInput, withOutput);
            }else if(parameter == "-e" || parameter == "--extension"){
                if(argc > 2){
                    string fileExtension = argv[2];
                    if(argc > 3){
                        string fourthParameter = argv[3];
                        if(fourthParameter[0] == '-' && fourthParameter == "-t"){
                            if(argc > 4){
                                string templateName = argv[4];
                                if(argc > 5){
                                    createSourceCodeFile(argc, argv, fileExtension,templateName,5);
                                }else{
                                    cout<<"Error: filename not specified"<<endl;
                                }
                            }else{
                                cout<<"Error: template name not specified."<<endl;
                            }
                        }else if(fourthParameter[0] == '-' && fourthParameter != "-t"){
                            cout<<"Option "<<fourthParameter<<" not recognized"<<endl;
                        }else{
                            createSourceCodeFile(argc,argv, fileExtension,"",3);
                        }
                    }else{
                        cout<<"Error: missing parameters."<<endl;
                    }
                }else{
                    cout<<"Error: file extension not specified."<<endl;   
                }
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