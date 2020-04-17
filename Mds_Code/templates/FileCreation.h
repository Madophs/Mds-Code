#include "FileNaming.h"
#include "Message.h"
#include "MdsFile.h"

bool existsTemplate(string pathToTemplate){
    fstream templateFile;
    templateFile.open(pathToTemplate);
    return templateFile.fail() ? false : true;
}

void createSourceCodeFile(string filename, string fileExtension, string templateName = "", int index = 2){
    FileNaming::applyAllFormats(filename);
    if(filename.empty()){
        printInColor("Error: ","red","filename is empty, please check the configuration file in /home/{USER}/MdsCode/mdscode.conf\n");
        return;
    }
    if(templateName.empty()){
        MdsFile file(filename, fileExtension);
        file.create();
        file.close();
    }else{
        string pathToTemplate = Globals::TEMPLATE_DIR_PATH+"/"+templateName;
        if(existsTemplate(pathToTemplate)){
            MdsFile file(filename, fileExtension);
            file.createFileWithContent(pathToTemplate);
            file.close();
        }else{
            printInColor("Error: ","red","template "+templateName+" does not exists.\n");
        }
    }
}
