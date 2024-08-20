/*
	GameMaster handles the backend game logic and sends it to the front end

	Also serves as an interface for some of the game States to interface with inner States and other GUI elements
*/

#pragma once
#include "SFML/Graphics.hpp"
#include "Data.hpp"
#include "GUI.hpp"
#include "Terrain.hpp"
#include "Person.hpp"
#include "StateMachine.hpp"
#include "State.hpp"
#include "Infobox.hpp"
#include <string>
#include <vector>
// #include <unordered_map>
#include <fstream>
#include <utility>
#include <cstdlib>
#include <cctype>
#include <iostream>
using namespace std;

struct GMContext {
    std::unique_ptr<Engine::StateMachine> stateMachine_;
    GMContext() {
        stateMachine_ = std::make_unique<Engine::StateMachine>();
    }
};

class GameMaster {
public:
	GameMaster(GUI& gui);
	~GameMaster();
	void initGame();
	void initPeople();
	void genTiles(int height, int width);
	void mapMode(int mapMode);
	// void addIntroInfobox();
	// void addTileInfobox(float mouseX, float mouseY, string status, bool create);
	void addInfobox(float mouseX, float mouseY, string status, bool create);
	void updateInfobox(float mouseX, float mouseY, bool clicked, bool scrollDown, bool scrollUp);
	bool getInfoboxStackEmpty();
	void popCurrentInfobox();
	Infobox* getCurrentInfobox();
	void createInfobox();
	float calcDanger();
	float calcDangerDecRate();
	void updateTileMissions(int y, int x);
	void passTileType(string tileType);
	// void passMission(string mission);
	void passMissionInfo();
	bool customJobComparator(Person& p1, Person& p2, std::string& priorityJob);
	void passPeopleString();
	void passInput(float x, float y, bool clicked, bool scrollDown, bool scrollUp);
	Terrain& getGroundTileAtPos(int y, int x); // Y AND X
	sf::Vector2u getStartingLoc();
	int getPopulationNum();
    void setWindowSize(sf::Vector2u windowSize);
private:
	std::shared_ptr<GMContext> gmcontext_;
	sf::Texture groundTexture_;
	vector<vector<Terrain*>> groundTiles_;
	sf::Vector2u windowSize_;
	int charSize_;
	sf::Font font_;
	sf::Vector2u startingLoc_ = {1000,1000}; // X AND Y
	vector<pair<int, int>> wildTilesCoords; // Y AND X
	int height_, width_;
    GUI& gui_;
	// World* world_;
	int currX_, currY_;
	string currMission_;
	// string linkData_;
	vector<string> linkData_;
	vector<string> maleNames_;
	vector<string> femaleNames_;
	vector<Person> people_;
	string priorityJob_;
	// unordered_map<int, Person*> personMap_; 
	int daysToTake_ = 3;
	float danger_, dangerDecRate_;
	int lastID_ = 0;
	int loadTerrainTextures();
	int* getRandomStatsArray();
	string getPeopleList();
	// int population_;
	// void addMissionInfobox();
};