// #pragma once
// #include <iostream>
// #include <vector>
// #include "SFML/Graphics.hpp"
// #include "Command.cpp"
// using namespace std;

// /*
//     Creates commands (see bind function), dispatches commands (see handleInput)
// */

// class InputHandler {
// public:
//     ~InputHandler();
//     InputHandler();  // Calls binding function
//     Command* handleInput(); // Command dispatcher, returns commands depending on keystrokes
//     // Command* specifiedOutput(int code);
//     void freeRoamBind();  // Binds commands to specific keys
// private:
//     // Possible commands
//     Command* right_;   // move in these directions, by default binded to arrow keys. 
//     Command* left_;
//     Command* up_;
//     Command* down_;
//     vector<Command*> commands_;  // holds all commands for freeing mem
// };