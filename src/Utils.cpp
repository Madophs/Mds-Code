#include "Utils.h"
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

namespace mds {
    void kmpReplace(std::string &line, std::string &search,
            std::string replaceString, std::vector<int> &pattern) {
        int i = 0, j = 0;
        std::vector<std::pair<int,int>> indexes;
        while(i < line.length()) {
            while(j>=0 && line[i] != search[j]) j = pattern[j];
            ++j,++i;
            if(j == search.length()) {
                line.replace(i-j,j,replaceString);
                i = 0, j = 0;
            }
        }
    }

    std::vector<int> kmpPreprocess(std::string line) {
        std::vector<int> pattern(line.length()+1, 0);
        pattern[0] = -1;
        int j = -1, i = 0;
        while(i<line.length()) {
            while(j > -1 && line[j] != line[i]) j = pattern[j];
            ++j, ++i;
            pattern[i] = j;
        }
        return pattern;
    }

    bool fileExists(std::string pathToFile) {
        std::ifstream file;
        file.open(pathToFile.c_str(), std::ios_base::in);
        if (!file.is_open())
            return false;
        file.close();
        return true;
    }

    bool dirExists(std::string dir) {
        int fd = open(dir.c_str(), O_DIRECTORY);
        if (fd != 0) {
            return false;
        }
        close(fd);
        return true;
    }

} // namespace mds
