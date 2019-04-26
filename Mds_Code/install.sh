#!bin/bash
mkdir -p "$HOME/.MdsCode"
sudo install -g 0 -o 0 -m 0644 mdscode.1 /usr/share/man/man1/
sudo gzip /usr/share/man/man1/mdscode.1
if hash mdscode 2>/dev/null; then
    echo "Updating MdsCode binary file..."
    g++ -std=c++14 mds_code.cpp -o "$HOME/.MdsCode/mdscode"
    echo "MdsCode was updated"
else
    echo "Installing..."
    g++ -std=c++14 mds_code.cpp -o "$HOME/.MdsCode/mdscode"
    sudo ln -s "$HOME/.MdsCode/mdscode" /usr/bin/mdscode
    echo "MdsCode was successfully installed."
fi