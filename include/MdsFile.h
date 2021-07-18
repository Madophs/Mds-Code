#ifndef MDSFILE_H
#define MDSFILE_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Message.h"
#include "Globals.h"
#include "Utils.h"

namespace mds {

    /*
     * This class handles file creation
     */
    class MdsFile {
        public:
            // Constructor
            MdsFile(std::string filename, std::string fileExtension = "");

            // Destructor
            // It just close the file if opened
            ~MdsFile();

            std::ofstream& get();

            // Filename
            std::string getFilename() const;

            // Filename with extension
            std::string getFullFilename() const;

            // Create file at the give path
            void create(std::string path = "");

            // Create the file at ~/MdsCode
            void createAtMdsCodeDirectory();

            // Create the file with the content of the specified file
            void createFileWithContent(std::string pathToFile, std::string strPattern= "{{classname}}");

            // Set file extension
            void setExtension(std::string);

            // Writes the line to the file
            void addLine(std::string line, char eolchar = '\n');

            // Appends a Carriage return
            void addCR();

            // Close the file
            void close();
        private:
            std::string m_filename;
            std::string m_fileExtension;
            std::ofstream m_file;
    };
} // mds

#endif
