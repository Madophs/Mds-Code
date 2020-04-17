#include <iostream>

void printInColor(std::string messageInColor,
            std::string foregroundColor,
            std::string restOfMessage,
            std::string backgroundColor,
            std::string modifier){
    std::string finalMessage = "";

    if(modifier == "reset"){
        finalMessage = "\e[0";
    }else if(modifier == "bold"){
        finalMessage = "\e[1";    
    }else if(modifier == "underline"){
        finalMessage = "\e[4";
    }else if(modifier == "inverse"){
        finalMessage = "\e[7";
    }else{
        std::cout<<"\e[1;31mError: \e[0mmodifier not found.\n";
        exit(EXIT_FAILURE);
    }

    if(foregroundColor == "black"){
        finalMessage += ";30";        
    }else if(foregroundColor == "red"){
        finalMessage += ";31";
    }else if(foregroundColor == "green"){
        finalMessage += ";32";
    }else if(foregroundColor == "yellow"){
        finalMessage += ";33";
    }else if(foregroundColor == "blue"){
        finalMessage += ";34";
    }else if(foregroundColor == "magenta"){
        finalMessage += ";35";
    }else if(foregroundColor == "cyan"){
        finalMessage += ";36";
    }else if(foregroundColor == "white"){
        finalMessage += ";37";
    }else{
        if(foregroundColor != "Default"){
            std::cout<<"\e[1;31mError: \e[0mforeground color not found.\n";
            exit(EXIT_FAILURE);
        }
    }

    if(backgroundColor == "black"){
        finalMessage += ";40";        
    }else if(backgroundColor == "red"){
        finalMessage += ";41";
    }else if(backgroundColor == "green"){
        finalMessage += ";42";
    }else if(backgroundColor == "yellow"){
        finalMessage += ";43";
    }else if(backgroundColor == "blue"){
        finalMessage += ";44";
    }else if(backgroundColor == "magenta"){
        finalMessage += ";45";
    }else if(backgroundColor == "cyan"){
        finalMessage += ";46";
    }else if(backgroundColor == "white"){
        finalMessage += ";47";
    }else{
        if(backgroundColor != "Default"){
            std::cout<<"\e[1;31mError: \e[0mbackground color not found.\n";
            exit(EXIT_FAILURE);
        }
    }

    finalMessage += "m" + messageInColor + "\e[0m" + restOfMessage;
    std::cout<<finalMessage;
}