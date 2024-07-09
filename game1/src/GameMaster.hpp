#pragma once
#include "SFML/Graphics.hpp"
#include "GUI.hpp"
#include "World.hpp"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class GameMaster {
public:
	GameMaster(GUI& gui, World& world);
	~GameMaster();
	void initInfobox(float mouseX, float mouseY);
    void infoboxMaster(float mouseX, float mouseY, bool clicked);
	void setGUI(GUI& gui);
private:
    GUI& gui_;
	World& world_;
	// string linkData_[2];
	string linkData_;
	void addMissionInfobox();
};