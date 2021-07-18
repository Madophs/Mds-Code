#include "Config.h"

namespace mds {
void createFileInMdsDirectory(std::string filename, std::string fileExtension){
    mds::MdsFile file(filename,fileExtension);
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
    mds::MdsFile cplusplusTemplate("template_cpp","cpp");
    cplusplusTemplate.create(Globals::TEMPLATE_DIR_PATH);
    std::string imports = "#include <bits/stdc++.h>";
    std::string namespaceStd = "using namespace std;";
    std::string unsyncWithStdio = "\tios_base::sync_with_stdio(false);";
    std::string fastInput = "\tcin.tie(nullptr);";
    std::string fastOutput = "\tcout.tie(nullptr);";
    cplusplusTemplate.addLine(imports);
    cplusplusTemplate.addCR();
    cplusplusTemplate.addLine(namespaceStd);
    cplusplusTemplate.addCR();
    cplusplusTemplate.addLine("int main(){");
    cplusplusTemplate.addLine(unsyncWithStdio);
    cplusplusTemplate.addLine(fastInput);
    cplusplusTemplate.addLine(fastOutput);
    cplusplusTemplate.addLine("\t");
    cplusplusTemplate.addLine("\treturn 0;");
    cplusplusTemplate.addLine("}");
    cplusplusTemplate.close();
}

void createDefaultJavaTemplate(){
    createMdsCodeDirectory();
    MdsFile javaTemplate("template_java","java");
    javaTemplate.create(Globals::TEMPLATE_DIR_PATH);
    std::string imports = "import java.io.*;";
    std::string hereGoesClassName = "{{classname}}";
    std::string className = "class " + hereGoesClassName + " {";
    std::string instanceName = "Madophs";
    std::string instanceDeclaration = hereGoesClassName + " " + instanceName + " = new " + hereGoesClassName + "();";
    std::string callMethod = instanceName + ".justGetStarted();";
    javaTemplate.addLine(imports);
    javaTemplate.addCR();
    javaTemplate.addLine(className);
    javaTemplate.addCR();
    javaTemplate.addLine("\tpublic static void main (String args[]) {");
    javaTemplate.addLine("\t\t"+instanceDeclaration);
    javaTemplate.addLine("\t\t"+callMethod);
    javaTemplate.addLine("\t}");
    javaTemplate.addCR();
    javaTemplate.addLine("\tvoid justGetStarted(){");
    javaTemplate.addLine("\t\tBufferedReader mds = new BufferedReader(new InputStreamReader(System.in));");
    javaTemplate.addLine("\t\t");
    javaTemplate.addLine("\t\ttry{");
    javaTemplate.addLine("\t\t\t");
    javaTemplate.addLine("\t\t}catch(Exception e){\n");
    javaTemplate.addLine("\t\t\tSystem.out.println(\"Error: \"+e.getMessage());\n");
    javaTemplate.addLine("\t\t};\n");
    javaTemplate.addLine("\t}");
    javaTemplate.addLine("}");
    javaTemplate.close();
}

void createConfigfile(){
    createMdsCodeDirectory();
    MdsFile configFile("mdscode","conf");
    configFile.createAtMdsCodeDirectory();
    configFile.addLine("###################### MdsCode configuration file ######################");
    configFile.addCR();
    configFile.addLine("[filename]");
    configFile.addLine("# Flags for naming files");
    configFile.addLine("RemoveNumbers = false");
    configFile.addLine("RemoveNonAlphabeticalCharacters = true # (./',\\-!, etc...) not include spaces or [ñ,á,é,í,ó,ú]");
    configFile.addLine("CapitalizeEveryWord = false # hello world -> Hello World");
    configFile.addLine("ProblemNumberToEndOfFilename = true");
    configFile.addLine("SeparateFilenameWithUnderscores = true #true hello world = hello_word and false = helloworld");
    configFile.addLine("ChangeLettersToEnglishAlphabet = true # Español -> Espanol, í -> i in other words [ñ,á,é,í,ó,ú] => [n,a,e,i,o,u]");
    configFile.addCR();
    configFile.addLine("[compilation]");
    configFile.addLine("# Sintax to compile a source code file output by default is \"mds\" save in this directory");
    configFile.addLine("# {{output}} = /home/USER/MdsCode/bin/mds");
    configFile.addLine("# {{bin}} = /home/USER/MdsCode/bin/");
    configFile.addLine("# {{source}} =  /home/USER/MdsCode/source/");
    configFile.addLine("# {{mds}} =  /home/USER/MdsCode/");
    configFile.addLine("cpp = g++ -std=gnu++14 {{filename}} -o {{output}}");
    configFile.addLine("c = gcc {{filename}} -o {{output}}");
    configFile.addLine("java = javac {{source}}/Main.java -d {{bin}}");
    configFile.addCR();
    configFile.addLine("[execution]");
    configFile.addLine("# {{output}} = /home/USER/MdsCode/bin/mds");
    configFile.addLine("# {{bin}} = /home/USER/MdsCode/bin/");
    configFile.addLine("# {{source}} =  /home/USER/MdsCode/source/");
    configFile.addLine("# {{mds}} =  /home/USER/MdsCode/");
    configFile.addLine("cpp = {{bin}}");
    configFile.addLine("c = {{bin}}");
    configFile.addLine("java = {{bin}}");
    configFile.close();
}

void setupDefaultEnvironment(){
    removeMdsCodeDirectory();
    createIOFiles();
    createDefaultCplusplusTemplate();
    createDefaultJavaTemplate();
    createConfigfile();
}
} // namespace mds
