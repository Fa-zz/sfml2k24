/*
	GameMaster handles the backend game logic and sends it to the front end

	Also serves as an interface for some of the game States to interface with inner States and other GUI elements
*/

#pragma once
#include "SFML/Graphics.hpp"
#include "GUI.hpp"
#include "Terrain.hpp"
// #include "World.hpp"
#include <string>
#include <vector>
#include <utility>
#include <cstdlib>
#include <iostream>
using namespace std;

class GameMaster {
public:
	GameMaster(GUI& gui);
	~GameMaster();
	void initGame();
	void addIntroInfobox();
	void addTileInfobox(float mouseX, float mouseY);
    void infoboxMaster(float mouseX, float mouseY, bool clicked, bool scrollDown, bool scrollUp);
	void popCurrentInfobox();
	void setGUI(GUI& gui);
	void genTiles(int height, int width);
	void mapMode(int mapMode);
	Terrain& getGroundTileAtPos(int y, int x); // Y AND X
	sf::Vector2u getStartingLoc();
	int getPopulation();
private:
	sf::Texture groundTexture_;
	vector<vector<Terrain*>> groundTiles_;
	sf::Vector2u startingLoc_ = {1000,1000}; // X AND Y
	vector<pair<int, int>> wildTilesCoords; // Y AND X
	int height_, width_;
    GUI& gui_;
	// World* world_;
	string linkData_;
	int loadTerrainTextures();
	int* getRandomStatsArray();
	// int population_;
	// void addMissionInfobox();
};