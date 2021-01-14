#ifndef INFO_H
#define INFO_H

#include <iomanip>
#include <iostream>
#include <vector>

const double version = 2.0;
const int partialCommandLength = 6, fullCommandLength = 18;

std::string getOperatingSystem() {
    FILE *fpipe = popen("lsb_release -d","r");
    char line[200];
    std::string output = "", token, operatingSystem = "";
    while(fgets(line,200,fpipe)) output += line;
    std::stringstream ss(line);
    ss >> token;
    for (int i = 0; ss >> token; i++) {
        operatingSystem += i?" ":"";
        operatingSystem += token;
    }
    if(operatingSystem.empty()) return "";
    return operatingSystem;
}

std::string getCodename() {
    FILE *fpipe = popen("lsb_release -c","r");
    char line[200];
    std::string output = "", token, codename = "";
    while(fgets(line,200,fpipe)) output += line;
    std::stringstream ss(line);
    ss >> token;
    for(int i = 0; ss >> token; i++) {
        codename += i?" ":"";
        codename += token;
    }
    if(codename.empty()) return "";
    return codename;
}

void displayVersion() {
    std::cout << "Mds Code " << version << " " << getOperatingSystem() << std::endl;
    std::cout << "This is an open source software." << std::endl;
    std::cout << "Developed by Jehú Jair Ruiz Villegas A.K.A Madophs." << std::endl;
}

void displayHelp() {
    std::cout << "Mds Code " << version << " developed by Jehú Jair Ruiz Villegas" << '\n';
    std::cout << "Operating System: " << getOperatingSystem() << '\n';
    std::cout << "Codename: " << getCodename() << '\n';
    std::cout << '\n';
    std::cout << "Sintax: mds_code [parameter] filename" << '\n';
    std::cout << '\n';
    std::cout << std::setw(partialCommandLength) << "-s" << std::setw(fullCommandLength) << "--setup" << "Create everything necessary to make this command work" << '\n';
    std::cout << std::setw(partialCommandLength+fullCommandLength) << " " << "It will setup everything as default, including your own configurations." << '\n';
    std::cout << std::setw(partialCommandLength) << "-n" << std::setw(fullCommandLength) << "--new" << "Create a new file with specified name (literally)." << '\n';
    std::cout << std::setw(partialCommandLength) << "-c++" << std::setw(fullCommandLength) << "--c++" << "Create a C++ file with predefined code." << '\n';
    std::cout << std::setw(partialCommandLength) << "-j" << std::setw(fullCommandLength) << "--java" << "Create a Java file with predefined code." << '\n';
    std::cout << std::setw(partialCommandLength) << "-e" << std::setw(fullCommandLength) << "--extension" << "Create a file with specified extension." << '\n';
    std::cout << std::setw(partialCommandLength+fullCommandLength) << " " << "Sintax mdscode -e cpp -t mytemplate.cpp hello world" << '\n';
    std::cout << std::setw(partialCommandLength+fullCommandLength) << " " << "(optional -t stands for template, the specified template must be in MdsCode directory)" << '\n';
    std::cout << std::setw(partialCommandLength) << "-b" << std::setw(fullCommandLength) << "--build" << "Compile the specified file. (Binary file is located in MdsCode directory)" << '\n';
    std::cout << std::setw(partialCommandLength) << "-r" << std::setw(fullCommandLength) << "--run" << "Execute the mds binary file in MdsCode directory" << '\n';
    std::cout << std::setw(partialCommandLength+fullCommandLength) << " " << "-ri -ro -rio are valid parameters, i = input and o = output making reference to the IO files in MdsDirectory." << '\n';
    std::cout << std::setw(partialCommandLength+fullCommandLength) << " " << "Add -j if you want to execute a Java file. (Filename is not needed MdsCode take care of that)" << '\n';
    std::cout << std::setw(partialCommandLength+fullCommandLength) << " " << "Fullname commands: --run_with_input, --run_with_output, --run_with_io." << '\n';
    std::cout << std::setw(partialCommandLength) << "-x" << std::setw(fullCommandLength) << "--export" << "Copy the source code file to a certain directory." << '\n';
    std::cout << std::setw(partialCommandLength+fullCommandLength) << " " << "mdscode -x [filename] -p [export directory] -name [new name]. -p and -name are optional and their order do not matter." << '\n';
    std::cout << std::setw(partialCommandLength+fullCommandLength) << " " << "In -name flag just need to specify the name without extension." << '\n';
    std::cout << std::setw(partialCommandLength) << "-io" << std::setw(fullCommandLength) << "--input_output" << "Creates input and output files." << '\n';
    std::cout << std::setw(partialCommandLength) << "-c" << std::setw(fullCommandLength) << "--config" << "Create mdscode configuration file." << '\n';
    std::cout << std::setw(partialCommandLength) << "-cc" << std::setw(fullCommandLength) << "--c++_tpl" << "Creates default C++ template." << '\n';
    std::cout << std::setw(partialCommandLength) << "-cj" << std::setw(fullCommandLength) << "--java_tpl" << "Creates default Java template." << '\n';
    std::cout << std::setw(partialCommandLength) << "-v" << std::setw(fullCommandLength) << "--version" << "Displays the current version." << '\n';
    std::cout << std::setw(partialCommandLength) << "-h" << std::setw(fullCommandLength) << "--help" << "Show this help." << '\n';
    std::cout << '\n';
    std::cout << "This is an open source software feel free to use it, modified it and add your own features" << '\n';
    std::cout << "Please tell me your recommendations and how can I improve it." << '\n';
    std::cout << "I code this command to handle the creation of files quickly when I'm participanting in programming contest." << '\n';
    std::cout << "I hope this command is useful for you like it is for me :)" << '\n';
    std::cout.flush();
}

void displayLogo() {
    std::vector<std::string> mdscodeLogo =  {
        "     ____    ____       ____      _______       _______   ________   ____     _______",
        "    /    \\  /    \\     |    \\    |  _____|     | ______| |   __   | |    \\   | ______|",
        "   /  /\\  \\/  /\\  \\    |  _  \\   | |______     | |       |  |  |  | |  _  \\  | |_____",
        "  /  /  \\    /  \\  \\   | | \\  \\  |______ |     | |       |  |  |  | | | \\  \\ | ______|",
        " /  /    \\__/    \\  \\  | |_/  /  ______| |     | |______ |  |__|  | | |_/  / | |______",
        "/__/              \\__\\ |_____/   |_______|     |_______| |________| |_____/  |_______|",
    };
    for (int i = 0; i<mdscodeLogo.size(); i++) {
        std::string logoSegment = "\e[1;32m"+mdscodeLogo[i]+"\e[0m";
        std::cout << logoSegment << '\n';
    }
    std::cout << std::endl;
}

#endif
