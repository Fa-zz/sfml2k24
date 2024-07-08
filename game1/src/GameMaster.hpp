#pragma once
#include "SFML/Graphics.hpp"
#include "GUI.hpp"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class GameMaster {
public:
	GameMaster(GUI& gui);
	~GameMaster();
    void infoboxMaster(float mouseX, float mouseY, bool clicked);
	void setGUI(GUI& gui);
private:
    GUI& gui_;
	string linkData_[2];
};