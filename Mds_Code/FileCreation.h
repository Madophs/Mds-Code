#include "FileNaming.h"

bool existsTemplate(string pathToTemplate){
    fstream templateFile;
    templateFile.open(pathToTemplate);
    return templateFile.fail()? false : true;
}

void createSourceCodeFile(int argc, char *argv[], string fileExtension, string templateName = "", int index = 2){
    if(readFilenameSection()){
        string fullFilename = rawFilename(argc, argv, index);
        flagRemoveNonAlphabeticalCharacters(fullFilename);
        flagRemoveNumbers(fullFilename);
        flagCapitalizeEveryWord(fullFilename);
        flagProblemNumberToEndOfFilename(fullFilename);
        flagSeparateFilenameWithUnderscores(fullFilename);
        if(fullFilename.empty()){
            cout<<"Filename is empty, please check the configuration file in /home/{USER}/MdsCode/mdscode.conf"<<endl;
            return;
        }
        string homeDirectory = getenv("HOME");
        if(templateName.empty()){
            MdsFile file(fullFilename, fileExtension);
            file.create();
            file.close();
        }else{
            string pathToTemplate = homeDirectory+"/MdsCode/"+templateName;
            if(existsTemplate(pathToTemplate)){
                MdsFile file(fullFilename, fileExtension);
                file.createFileWithContent(pathToTemplate);
                file.close();   
            }else{
                cout<<"Template "<<templateName<<" does not exits"<<endl;
            }
        }
    }
}