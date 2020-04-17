#include "Config.h"

void createFileInMdsDirectory(string filename, string extention){
    MdsFile file(filename,extention);
    file.createAtMdsCodeDirectory();
    file.close();
}

void createMdsCodeDirectory(){
    system(("mkdir -p "+Globals::BIN_DIR_PATH).c_str());
    system(("mkdir -p "+Globals::SOURCE_DIR_PATH).c_str());
    system(("mkdir -p "+Globals::EXPORTS_DIR_PATH).c_str());
    system(("mkdir -p "+Globals::TEMPLATE_DIR_PATH).c_str());
}

void createIOFiles(){
    createMdsCodeDirectory();
    createFileInMdsDirectory("input","txt");
    createFileInMdsDirectory("output","txt");
    createFileInMdsDirectory("solution","txt");
}

void removeMdsCodeDirectory(){
    createMdsCodeDirectory();
    system(("rm -r "+Globals::MDS_DIR_PATH).c_str());
}

void createDefaultCplusplusTemplate(){
    createMdsCodeDirectory();
    MdsFile cplusplusTemplate("template_cpp","cpp");
    cplusplusTemplate.create(Globals::TEMPLATE_DIR_PATH);
    string imports = "#include <bits/stdc++.h>";
    string namespaceStd = "using namespace std;";
    string unsyncWithStdio = "\tios_base::sync_with_stdio(false);";
    string fastInput = "\tcin.tie(nullptr);";
    string fastOutput = "\tcout.tie(nullptr);";
    cplusplusTemplate.addText(imports);
    cplusplusTemplate.addNewLine();
    cplusplusTemplate.addText(namespaceStd);
    cplusplusTemplate.addNewLine();
    cplusplusTemplate.addText("int main(){");
    cplusplusTemplate.addText(unsyncWithStdio);
    cplusplusTemplate.addText(fastInput);
    cplusplusTemplate.addText(fastOutput);
    cplusplusTemplate.addText("\t");
    cplusplusTemplate.addText("\treturn 0;");
    cplusplusTemplate.addText("}");
    cplusplusTemplate.close();
}

void createDefaultJavaTemplate(){
    createMdsCodeDirectory();
    MdsFile javaTemplate("template_java","java");
    javaTemplate.create(Globals::TEMPLATE_DIR_PATH);
    string imports = "import java.io.*;";
    string hereGoesClassName = "{{classname}}";
    string className = "class " + hereGoesClassName + " {";
    string instanceName = "Madophs";
    string instanceDeclaration = hereGoesClassName + " " + instanceName + " = new " + hereGoesClassName + "();";
    string callMethod = instanceName + ".justGetStarted();";
    javaTemplate.addText(imports);
    javaTemplate.addNewLine();
    javaTemplate.addText(className);
    javaTemplate.addNewLine();
    javaTemplate.addText("\tpublic static void main (String args[]) {");
    javaTemplate.addText("\t\t"+instanceDeclaration);
    javaTemplate.addText("\t\t"+callMethod);
    javaTemplate.addText("\t}");
    javaTemplate.addNewLine();
    javaTemplate.addText("\tvoid justGetStarted(){");
    javaTemplate.addText("\t\tBufferedReader mds = new BufferedReader(new InputStreamReader(System.in));");
    javaTemplate.addText("\t\t");
    javaTemplate.addText("\t\ttry{");
    javaTemplate.addText("\t\t\t");
    javaTemplate.addText("\t\t}catch(Exception e){\n");
    javaTemplate.addText("\t\t\tSystem.out.println(\"Error: \"+e.getMessage());\n");
    javaTemplate.addText("\t\t};\n");
    javaTemplate.addText("\t}");
    javaTemplate.addText("}");
    javaTemplate.close();
}

void createConfigfile(){
    createMdsCodeDirectory();
    MdsFile configFile("mdscode","conf");
    configFile.createAtMdsCodeDirectory();
    configFile.addText("###################### MdsCode configuration file ######################");
    configFile.addNewLine();
    configFile.addText("[filename]");
    configFile.addText("# Flags for naming files");
    configFile.addText("RemoveNumbers = false");
    configFile.addText("RemoveNonAlphabeticalCharacters = true # (./',\\-!, etc...) not include spaces or [ñ,á,é,í,ó,ú]");
    configFile.addText("CapitalizeEveryWord = false # hello world -> Hello World");
    configFile.addText("ProblemNumberToEndOfFilename = true");
    configFile.addText("SeparateFilenameWithUnderscores = true #true hello world = hello_word and false = helloworld");
    configFile.addText("ChangeLettersToEnglishAlphabet = true # Español -> Espanol, í -> i in other words [ñ,á,é,í,ó,ú] => [n,a,e,i,o,u]");
    configFile.addNewLine();
    configFile.addText("[compilation]");
    configFile.addText("# Sintax to compile a source code file output by default is \"mds\" save in this directory");
    configFile.addText("# {{output}} = /home/USER/MdsCode/bin/mds");
    configFile.addText("# {{bin}} = /home/USER/MdsCode/bin/");
    configFile.addText("# {{source}} =  /home/USER/MdsCode/source/");
    configFile.addText("# {{mds}} =  /home/USER/MdsCode/");
    configFile.addText("cpp = g++ -std=gnu++14 {{filename}} -o {{output}}");
    configFile.addText("c = gcc {{filename}} -o {{output}}");
    configFile.addText("java = javac {{source}}/Main.java -d {{bin}}");
    configFile.addNewLine();
    configFile.addText("[execution]");
    configFile.addText("# {{output}} = /home/USER/MdsCode/bin/mds");
    configFile.addText("# {{bin}} = /home/USER/MdsCode/bin/");
    configFile.addText("# {{source}} =  /home/USER/MdsCode/source/");
    configFile.addText("# {{mds}} =  /home/USER/MdsCode/");
    configFile.addText("cpp = {{bin}}");
    configFile.addText("c = {{bin}}");
    configFile.addText("java = {{bin}}");
    configFile.close();
}

void setupDefaultEnvironment(){
    removeMdsCodeDirectory();
    createIOFiles();
    createDefaultCplusplusTemplate();
    createDefaultJavaTemplate();
    createConfigfile();
}