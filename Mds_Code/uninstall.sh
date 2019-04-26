#!bin/bash
if hash mdscode 2>/dev/null; then
    echo "Unistalling..."
    sudo unlink /usr/bin/mdscode
    echo "MdsCode was successfully uninstalled."
else
    echo "MdsCode is not installed."
fi