#!bin/bash
if hash mdscode 2>/dev/null; then
    echo "Unistalling..."
    sudo unlink /usr/bin/mdscode
    sudo rm /usr/share/man/man1/mdscode.1.gz
    echo "MdsCode was successfully uninstalled."
else
    echo "MdsCode is not installed."
fi