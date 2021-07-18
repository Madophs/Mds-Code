#!/bin/bash
if hash mdscode 2>/dev/null; then
    echo "Updating MdsCode binary file..."
    sudo g++ -std=c++14 templates/*.cpp mds_code.cpp -o "run" 2> $HOME/MdsCode/.build_messages.txt
    build_result=$(cat $HOME/MdsCode/.build_messages.txt)
    if [[ -z $build_result ]]; then
        sudo mv run /usr/bin/mdscode
        sudo rm /usr/share/man/man1/mdscode.1.gz
        sudo install -g 0 -o 0 -m 0644 mdscode.1 /usr/share/man/man1/
        sudo gzip /usr/share/man/man1/mdscode.1
        echo "MdsCode was updated"
    else
        echo "Errors in compilation"
        g++ -std=c++14 mds_code.cpp
        echo "Unable to update: error in the project found."
    fi
else
    echo "Installing..."
    sudo g++ -std=c++14 templates/*.cpp mds_code.cpp -o "/usr/bin/mdscode"
    if hash mdscode 2>/dev/null; then
        sudo install -g 0 -o 0 -m 0644 mdscode.1 /usr/share/man/man1/
        sudo gzip /usr/share/man/man1/mdscode.1
        mdscode --setup
        mdscode
        echo "MdsCode was successfully installed."
    else
        echo "Unable to install, errors occurred during installation"
    fi
fi