#ifndef MDS_UTILS_H
#define MDS_UTILS_H

#include <vector>
#include <iostream>

namespace mds {
    // Find and replace
    void kmpReplace(std::string &line, std::string &search,
            std::string replaceString, std::vector<int> &pattern);

    // It should be called before kmpReplace
    std::vector<int> kmpPreprocess(std::string line);

    bool fileExists(std::string pathToFile);
} // namespace mds

#endif
