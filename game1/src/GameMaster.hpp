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

struct Mission {
	string missionObjective;
	vector<int> missionUndertakers;
	int missionY, missionX;
	string danger, daysToTake;
	Mission () {}
	Mission (string objective, vector<int> undertakers, int y, int x, string dang, string days) : missionObjective(objective), missionUndertakers(undertakers), missionY(y), missionX(x), danger(dang), daysToTake(days) { }
	void clear() {
		missionObjective="";
		missionUndertakers.clear();
		missionY=0,missionX=0;
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
	void updateInfobox(float mouseX, float mouseY, vector<string> linkData, bool clicked, bool scrollDown, bool scrollUp);
	bool getInfoboxStackEmpty();
	void popCurrentInfobox();
	void popAllInfoboxes();
	Infobox* getCurrentInfobox();
	void createInfobox();
	int calcDanger();
	int calcDangerDecRate();
	void updateTileMissions(int y, int x);
	void passTileType(string tileType);
	// void passMission(string mission);
	void passMissionInfo();
	void passMissionInfoDirect(string mission, string danger, string days);
	bool customJobComparator(Person& p1, Person& p2, std::string& priorityJob);
	void passPeopleString();
	void passInput(float x, float y, bool clicked, bool scrollDown, bool scrollUp);
	Terrain& getGroundTileAtPos(int y, int x); // Y AND X
	sf::Vector2u getStartingLoc();
	int getPopulationNum();
	std::__1::__wrap_iter<Person *> IDtoPerson(int targetID);
    void setWindowSize(sf::Vector2u windowSize);
private:
	std::shared_ptr<GMContext> gmcontext_;
	sf::Texture groundTexture_;
	vector<vector<Terrain*>> worldTiles_;
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
	vector<int> currSelected_;
	vector<Mission> activeMissions_;
	// string linkData_;
	vector<string> linkData_;
	vector<string> maleNames_;
	vector<string> femaleNames_;
	vector<Person> people_;
	bool choosingPeople_ = false;
	string priorityJob_;
	// unordered_map<int, Person*> personMap_; 
	const int DAYS_TO_TAKE_ = 3;
	int danger_, dangerDecRate_, selectedID_, selectedIndex_;
	string strDays_, strDanger_;
	int lastID_ = 0;
	int loadTerrainTextures();
	int* getRandomStatsArray();
	string getPeopleList();
	// int population_;
	// void addMissionInfobox();
};