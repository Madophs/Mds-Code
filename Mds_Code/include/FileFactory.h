#ifndef FILEFACTORY_H
#define FILEFACTORY_H

#include <sstream>
#include <regex>
#include <fstream>
#include "Message.h"
#include "Globals.h"
#include "MdsFile.h"

namespace mds {
/*
 * This class implements file naming convention and creation based on configurations
 */
class FileFactory {
    public:
        FileFactory(const FileFactory &) = delete;
        static void removeNonAlphabeticalCharacters(std::string &);
        static void removeNumbers(std::string &);
        static void capitalizeEveryWord(std::string &);
        static void problemNumberToEndOfFilename(std::string &);
        static void separateFilenameWithUnderscores(std::string &);
        static void applyAllFormats(std::string &);
        static void createSourceCodeFile(std::string filename,
                std::string fileExtension,
                std::string templateName = "",
                unsigned int index = 2);
        static FileFactory &get();
    private:
        bool RemoveNonAlphabeticalCharacters {true};
        bool ProblemNumberToEndOfFilename {true};
        bool SeparateFilenameWithUnderscores {true};
        bool CapitalizeEveryWord {true};
        bool RemoveNumbers {true};
        bool ChangeLettersToEnglishAlphabet {true};
        FileFactory();
        bool isTrue(std::string);
        void readFilenameSection();
        void interRemoveNonAlphabeticalCharacters(std::string &);
        void interRemoveNumbers(std::string &);
        void interCapitalizeEveryWord(std::string &);
        void interProblemNumberToEndOfFilename(std::string &);
        void interSeparateFilenameWithUnderscores(std::string &);
        void interCreateSourceCodeFile(std::string& filename,
                std::string& fileExtension,
                std::string& templateName,
                unsigned int& index);
};
} // namespace mds

#endif
