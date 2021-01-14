#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include "MdsFile.h"

namespace mds {
void createMdsCodeDirectory();

void createIOFiles();

void removeMdsCodeDirectory();

void createDefaultCplusplusTemplate();

void createDefaultJavaTemplate();

void createConfigfile();

void setupDefaultEnvironment();
}
#endif
