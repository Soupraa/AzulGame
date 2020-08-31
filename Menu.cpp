#include "Menu.h"

Menu::Menu(){

}

std::string Menu::displayMainMenu(){
    std::string mainMenu = "";
    mainMenu += "Menu\n";
    mainMenu += "----\n";
    mainMenu += "1.New Game\n";
    mainMenu += "2.Load Game\n";
    mainMenu += "3.Credits(show student information)\n";
    mainMenu += "4.Game Instructions\n";
    mainMenu += "5.Quit\n> ";

    return mainMenu;

}

std::string Menu::displayStudentInfo(){
    std::string displayStudentInfo = "";
    displayStudentInfo  += "\n----------------------------------\n";
    displayStudentInfo  += "Richard Gao\n";
    displayStudentInfo  += "Student ID: s3784324\n";
    displayStudentInfo  += "Email: s3784324@student.rmit.edu.au\n\n";
    displayStudentInfo  += "-------------------------------------\n";

    return displayStudentInfo;
    
}

 std::string Menu::displayWelcomeMessage(){
     std::string displayWelcomMessage = "";
     displayWelcomMessage += "Welcome to Azul!\n";
     displayWelcomMessage += "-------------------\n";
     
     return displayWelcomMessage;


 }



