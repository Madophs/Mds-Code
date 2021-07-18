#include <iostream>

namespace Globals {

    std::string HOME_DIR_PATH = getenv("HOME");

    std::string MDS_DIR_PATH = HOME_DIR_PATH + "/MdsCode";

    std::string INPUT_FILE_PATH = MDS_DIR_PATH + "/input.txt";

    std::string OUTPUT_FILE_PATH = MDS_DIR_PATH + "/output.txt";

    std::string TEMPLATE_DIR_PATH = MDS_DIR_PATH + "/templates";

    std::string SOURCE_DIR_PATH = MDS_DIR_PATH + "/source";

    std::string BIN_DIR_PATH = MDS_DIR_PATH + "/bin";

    std::string CONFIG_FILE_PATH = MDS_DIR_PATH + "/mdscode.conf";

    std::string USER = getenv("USER");

    std::string EXPORTS_DIR_PATH = MDS_DIR_PATH + "/exports";

    std::string CWD = getenv("PWD");
};
