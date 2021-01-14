#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>

namespace mds {
    extern void printInColor(
            std::string messageInColor,
            std::string foregroundColor = "Default",
            std::string restOfMessage = "",
            std::string backgroundColor = "Default",
            std::string modifier = "bold");
}

#endif
