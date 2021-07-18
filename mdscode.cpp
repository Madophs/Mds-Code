//#include "Config.h"
#include "MdsParser.h"

int main(int argc, char *argv[]){
    mds::Parser::parseArgs(argc, argv);
    // IO operations
    /*
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    cout << fixed << setfill(' ') << setprecision(1) << left;
    if(argc > 1){
        string parameter = argv[1];
        if(parameter == "-s" || parameter == "--setup"){
            setupDefaultEnvironment();
            return 0;
        }
        //readFilenameSection();
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
                printInColor("Error: ","red","filename not specified.\n");
                exit(1);
            }
        }else if(parameter == "-h" || parameter == "--help"){
            displayHelp();
        }else if(parameter == "-c++" || parameter == "--c++"){
            if(argc > 2){
                createSourceCodeFile(argv[2], "cpp","template_cpp.cpp");
            }else{
                printInColor("Error: ","red","filename not specified.\n");
                exit(1);
            }
        }else if(parameter == "-j" || parameter == "--java"){
            if(argc > 2){
                createSourceCodeFile(argv[2], "java","template_java.java");
            }else{
                printInColor("Error: ","red","filename not specified.\n");
                exit(1);
            }
        }else if(parameter == "-b" || parameter == "--build"){
            if(argc > 2){
                buildSourceCode(argv[2]);
            }else{
                printInColor("Error: ","red","filename not specified.\n");
                exit(1);
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
            bool javaFile = false;
            if(argc > 2){
                string javaFlag = argv[2];
                if(javaFlag == "-j") javaFile = true;
            }
            executeBinaryFile(withInput, withOutput, javaFile);
        }else if(parameter == "--run_with_io" || parameter == "--run_with_input" || parameter == "--run_with_output"){
            bool withInput = parameter == "--run_with_io" || parameter == "--run_with_input" ? true : false;
            bool withOutput = parameter == "--run_with_io" || parameter == "--run_with_output" ? true : false;
            bool javaFile = false;
            if(argc > 2){
                string javaFlag = argv[2];
                if(javaFlag == "-j") javaFile = true;
            }
            executeBinaryFile(withInput, withOutput, javaFile);
        }else if(parameter == "-e" || parameter == "--extension"){
            if(argc > 2){
                string fileExtension = argv[2];
                if(argc > 3){
                    string fourthParameter = argv[3];
                    if(fourthParameter[0] == '-' && fourthParameter == "-t"){
                        if(argc > 4){
                            string templateName = argv[4];
                            if(argc > 5){
                                createSourceCodeFile(argv[5], fileExtension,templateName);
                            }else{
                                printInColor("Error: ","red","filename not specified.\n");
                                exit(1);
                            }
                        }else{
                            printInColor("Error: ","red","template name not specified.\n");
                            exit(1);
                        }
                    }else if(fourthParameter[0] == '-' && fourthParameter != "-t"){
                        printInColor("Error: ","red","Option "+fourthParameter+" not recognized.");
                        exit(1);
                    }else{
                        createSourceCodeFile(argv[3],fileExtension,"",3);
                    }
                }else{
                    printInColor("Error: ","red","missing parameters.\n");
                    exit(1);
                }
            }else{
                printInColor("Error: ","red","file extension not specified..\n");
                exit(1);   
            }
        }else if(parameter == "-x" || parameter == "--export"){
            exportSourceFile(argc, argv);
        }else{
            printInColor("Error: ","red","invalid parameter.\n");
            exit(1);
        }
    }else{
        displayLogo();
        cout << "Developed by Jehú Jair Ruiz Villegas A.K.A Madophs" << endl;
    }*/
    return 0;
}
