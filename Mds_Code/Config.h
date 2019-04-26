#include "MdsFile.h"

void createMdsCodeDirectory(){
    string homeDirectory = getenv("HOME");
    string command = "mkdir -p "+homeDirectory+"/MdsCode";
    system(command.c_str());
}

void createIOFiles(){
    createMdsCodeDirectory();
    MdsFile inputFile("input","txt");
    inputFile.createAtMdsCodeDirectory();
    inputFile.close();
    MdsFile outputFile("output","txt");
    outputFile.createAtMdsCodeDirectory();
    outputFile.close();
}

void removeMdsCodeDirectory(){
    createMdsCodeDirectory();
    string homeDirectory = getenv("HOME");
    string mdsDirectory = homeDirectory+"/MdsCode";
    string command = "rm -r "+mdsDirectory;
    system(command.c_str());
}

void createDefaultCplusplusTemplate(){
    createMdsCodeDirectory();
    MdsFile cplusplusTemplate("template_cpp","cpp");
    cplusplusTemplate.createAtMdsCodeDirectory();
    string imports = "#include <bits/stdc++.h>";
    string namespaceStd = "using namespace std;";
    string unsyncWithStdio = "\tios_base::sync_with_stdio(false);";
    string fastInput = "\tcin.tie(NULL);";
    string fastOutput = "\tcout.tie(NULL);";
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
    javaTemplate.createAtMdsCodeDirectory();
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
    javaTemplate.addText("\t\t}catch(Exception e){};");
    javaTemplate.addText("\t}");
    javaTemplate.addText("}");
    javaTemplate.close();
}

void createConfigfile(){
    createMdsCodeDirectory();
    MdsFile configFile("mdscode","conf");
    configFile.createAtMdsCodeDirectory();
    configFile.addText("[filename]");
    configFile.addText("# Flags for naming files");
    configFile.addText("RemoveNumbers = false");
    configFile.addText("RemoveNonAlphabeticalCharacters = true # (./',\\-!, etc...) not include spaces");
    configFile.addText("CapitalizeEveryWord = false");
    configFile.addText("ProblemNumberToEndOfFilename = true");
    configFile.addText("SeparateFilenameWithUnderscores = true #true hello world = hello_word and false = helloworld");
    configFile.addNewLine();
    configFile.addText("[compilation]");
    configFile.addText("# Sintax to compile a source code file output by default is \"mds\" save in this directory");
    configFile.addText("cpp = g++ -std=gnu++14 {{filename}} -o {{binary}}");
    configFile.addText("c = gcc {{filename}} -o {{output}}");
    configFile.close();
}

void setupDefaultEnvironment(){
    removeMdsCodeDirectory();
    createIOFiles();
    createDefaultCplusplusTemplate();
    createDefaultJavaTemplate();
    createConfigfile();
}

