#pragma once
#include "SFML/Graphics.hpp"
#include "GUI.hpp"
#include "Terrain.hpp"
#include "World.hpp"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class GameMaster {
public:
	GameMaster(GUI& gui);
	~GameMaster();
	void initGame();
	void initInfobox(float mouseX, float mouseY);
    void infoboxMaster(float mouseX, float mouseY, bool clicked);
	void setGUI(GUI& gui);
	Terrain& getGroundTileAtPos(int y, int x);
private:
	int height_, width_;
    GUI& gui_;
	World* world_;
	// string linkData_[2];
	string linkData_;
	void addMissionInfobox();
};