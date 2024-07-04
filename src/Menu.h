#ifndef DA_RAILWAYS_MENU_H
#define DA_RAILWAYS_MENU_H

#include <iostream>
#include "Data.h"

using namespace std;

/**
 * @class Menu
 * @details The class that is responsible for the interaction between the user and the data.
 * @details It's the UI of this project.
 */
class Menu {
    Data data;
public:
    /**
     * @details Constructor of the Menu class.
     * @details Calls the SelectGraphMenu method to start the program.
     */
    Menu();
    /**
     * @details Void method that prints the title of the program.
     * @details Time Complexity: O(1)
     */
    static void printTitle();
    /**
     * @details Void method that verifies if the user's input is valid.
     * @details Time Complexity: O(1)
     * @param inputs Integer vector with the possible inputs
     * @return Integer input of the user
     */
    static int getUserInput(vector<int> inputs);
    /**
     * @details Void method that verifies if the user's input is valid, for a string input.
     * @details Time Complexity: O(1)
     * @return String input of the user
     */
    static string getUserTextInput();
    /**
     * @details Void method that "cleans" the screen
     * @details Time Complexity: O(1)
     */
    static void clearScreen();
    /**
     * @details Void method that prints a string with a maximum line length
     * @details Time Complexity: O(1)
     * @param s string to be printed
     * @param linelength Size of the line
     */
    static void Print(const string &s, int linelength);
    /**
     * @details Normal method that prints the Select Graph menu options to the user.
     * @details Time Complexity: O(1)
     */
    void SelectGraphMenu();
    /**
     * @details Normal method that prints the Main menu options to the user.
     * @details Time Complexity: O(1)
     */
    void MainMenu();
    /**
     * @details Normal method that prints the Node menu options to the user.
     * @details Time Complexity: O(1)
     */
    void NodeInfo();
    /**
     * @details Normal method that prints the Max Flow menu options to the user.
     * @details Time Complexity: O(1)
     */
    void MaxFlowMenu();
    /**
     * @details Normal method that prints the Water Network menu options to the user.
     * @details Time Complexity: O(1)
     */
    void WaterNetworkMenu();
    /**
     * @details Normal method that prints the Resiliency menu options to the user.
     * @details Time Complexity: O(1)
     */
    void ResiliencyMenu();
};

#endif //DA_RAILWAYS_MENU_H
