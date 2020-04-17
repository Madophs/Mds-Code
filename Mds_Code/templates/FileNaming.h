#ifndef FILENAMING_H
#define FILENAMING_H

#include <sstream>
#include <regex>
#include <fstream>
#include "Message.h"
#include "Globals.h"

using namespace std;

class FileNaming {
    public:
        FileNaming(const FileNaming &) = delete;
        static void removeNonAlphabeticalCharacters(string &);
        static void removeNumbers(string &);
        static void capitalizeEveryWord(string &);
        static void problemNumberToEndOfFilename(string &);
        static void separateFilenameWithUnderscores(string &);
        static void applyAllFormats(string &);
        static FileNaming &get();
    private:
        bool RemoveNonAlphabeticalCharacters {true};
        bool ProblemNumberToEndOfFilename {true};
        bool SeparateFilenameWithUnderscores {true};
        bool CapitalizeEveryWord {true};
        bool RemoveNumbers {true};
        bool ChangeLettersToEnglishAlphabet {true};
        FileNaming();
        bool isTrue(string);
        void readFilenameSection();
        void interRemoveNonAlphabeticalCharacters(string &);
        void interRemoveNumbers(string &);
        void interCapitalizeEveryWord(string &);
        void interProblemNumberToEndOfFilename(string &);
        void interSeparateFilenameWithUnderscores(string &);
};

#endif