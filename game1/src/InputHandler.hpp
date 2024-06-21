#pragma once
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "Command.cpp"
using namespace std;

class InputHandler {
public:
    ~InputHandler();
    InputHandler();
    Command* handleInput();
    // Command* specifiedOutput(int code);
    void freeRoamBind();
private:
    Command* right_;
    Command* left_;
    Command* up_;
    Command* down_;
    vector<Command*> commands_;
};