#ifndef MDSFILE_H
#define MDSFILE_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Message.h"
#include "Globals.h"

using namespace std;

class MdsFile {
    public:
        MdsFile(string, string = "");
        string getFilename() const;
        void create(string = "");
        void createAtMdsCodeDirectory();
        void createFileWithContent(string, string = "{{classname}}");
        vector<int> kmpPreprocess(string);
        void kmpReplace(string &,string &,string,vector<int> &);
        void setExtension(string);
        void addText(string);
        void addNewLine();
        void close();
    private:
        string filename;
        string fileExtension;
        ofstream file;
};

#endif