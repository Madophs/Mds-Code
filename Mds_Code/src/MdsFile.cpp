#include "MdsFile.h"
#include "Utils.h"
#include <cstdlib>
#include <fstream>

// Constructor
mds::MdsFile::MdsFile(std::string filename, std::string fileExtension /* = "" */) {
    this->m_filename = filename;
    this->m_fileExtension = fileExtension;
}

// Destructor
mds::MdsFile::~MdsFile() {
    // Now doing this can causes a memory leak
    if (this->m_file.is_open())
        this->m_file.close();
}

std::ofstream& mds::MdsFile::get() {
    return m_file;
}

// Returns the filename
std::string mds::MdsFile::getFilename() const {
    return this->m_filename;
}

// Return the filename with extension (if available)
std::string mds::MdsFile::getFullFilename() const {
    if (m_fileExtension.empty()) return m_filename;
    return m_filename + "." + m_fileExtension; }

// Creates the file at the give path
void mds::MdsFile::create(std::string path /* = "" */) {
    std::string fullFilename = this->m_filename;

    if (!m_fileExtension.empty()) fullFilename+="."+m_fileExtension;

    // If path its specified we create the file in the given directory
    if (!path.empty()) fullFilename = path+"/"+fullFilename;

    if (!mds::fileExists(fullFilename)) {
        // If file doesn't exist just create a new one
        // So let's create it
        m_file.open(fullFilename, std::ios::out);
    } else {
        std::string decision;
        std::cout << "File already exists, overwrite? (y,n)" << std::endl;
        std::cin >> decision;
        std::transform(decision.begin(), decision.end(), decision.begin(), ::tolower);

        if (decision == "y" || decision == "yes") {
            m_file.open(fullFilename, std::ios::out);
        }
    }
}

// It creates a file with content (source code)
// from another file (pathToFile)
// strPattern: its a specific string or pattern that
// will be replaced by filename i.e. this its useful when working
// with Java files which both classname and filename should be the same
void mds::MdsFile::createFileWithContent(std::string pathToFile, std::string strPattern) {
    std::vector<int> pattern = kmpPreprocess(strPattern);
    std::string fullFilename = m_filename;
    if (!m_fileExtension.empty()) fullFilename+="."+m_fileExtension;

    if (mds::fileExists(pathToFile)) {
        std::ifstream fileWithContent(pathToFile);
        if (!mds::fileExists(fullFilename)) { // If file doesn't exists, let't create it
            m_file.open(fullFilename, std::ios::out);
            std::string line;
            // Get line by line and replace strPattern by the filename, if neccesary
            while (getline(fileWithContent,line)) {
                mds::kmpReplace(line,strPattern,m_filename,pattern);
                m_file << line << "\n";
            }
        } else {
            std::string decision;
            std::cout << "File already exists, overwrite? (y,n)" << std::endl;
            std::cin >> decision;
            transform(decision.begin(), decision.end(), decision.begin(),::tolower);
            if (decision == "y" || decision == "yes") {
                m_file.open(fullFilename, std::ios::out);
                std::string line;
                // Get line by line and replace strPattern by the filename, if neccesary
                while(getline(fileWithContent,line)) {
                    mds::kmpReplace(line,strPattern,m_filename,pattern);
                    m_file << line << "\n";
                }
            }
        }
    } else {
        printInColor("Error: ","red","file does not exists.\n");
        exit(EXIT_FAILURE);
    }
}

// Create the file at MdsCode directory
// usually found in $HOME/MdsCode
void mds::MdsFile::createAtMdsCodeDirectory() {
    std::string fullFilenameWithPath = Globals::MDS_DIR_PATH+"/"+this->getFullFilename();
    m_file.open(fullFilenameWithPath);
}

// Set the file extension
void mds::MdsFile::setExtension(std::string fileExtension) {
    this->m_fileExtension = fileExtension;
}

// Add a line
void mds::MdsFile::addLine(std::string line, char eolChar /*= '\n'*/) {
    m_file << line << eolChar;
}

// Add a carrage return
void mds::MdsFile::addCR() {
    m_file << "\n";
}

// Close the file
void mds::MdsFile::close() {
    if (m_file.is_open())
        m_file.close();
}
