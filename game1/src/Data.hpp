#pragma once
#include <iostream> 
#include <sstream> 
#include <string>
#include <algorithm>
#include <cctype>

using namespace std; 

namespace Data {
    //    sf::Vector2i res1 = {1440, 900};
    //    sf::Vector2i res2 = {800, 600};

    inline const float res1x = 1440.f;
    inline const float res1y = 900.f;
    inline const float res2x = 800.f;
    inline const float res2y = 600.f;

    inline const float useResX = res2x;
    inline const float useResY = res2y;
    // inline const int charSize = 20;

    inline const int worldWidth = 50;
    inline const int worldHeight = 25;

    inline const float playerSpeed = 100.f;

    inline const string fontAssetPath = "assets/prstartk.ttf";
    inline const string characterTexturePath = "assets/characters.png";
    inline const string groundTexturePath = "assets/groundtiles.png";
    inline const string mNamesPath = "data/maleNames.txt";
    inline const string fNamesPath = "data/femaleNames.txt";

    inline const string intro = "intro";
    inline const string wildTile = "wildTile";
    inline const string reclaimedTile = "reclaimedTile";
    inline const string undiscoveredTile = "undiscoveredTile";
    inline const string missionChoice = "missionChoice";
    inline const string personChoice = "personChoice";
    inline const string activeTile = "activeTile";
    inline const string populationInfo = "populationInfo";

    inline const int numTileType = 8;
    inline const int numTileStatus = 3;
    inline const int numTileStats = 3;
    inline const int numTileStatStates = 4;
    inline const int numTileMissions = 5;
    inline const string tileStatus[numTileStatus] = {wildTile, reclaimedTile, undiscoveredTile};
    inline const string tileStatDescs[numTileStatStates] = {"none", "low", "medium", "high"};
    inline const string tileTypes[numTileType] = {"apartment", "church", "park", "school", "restaurant", "gas station", "office", "police HQ"};
    inline const string tileStats[numTileStats] = {"Food", "Zombies", "Survivors"};
    inline const string tileMissionsText[numTileMissions] = {"Scout area", "Scavenge for food", "Kill zombies", "Recruit survivors", "Reclaim"};
    
    inline const string locPh = "LOCPLACEHOLDER";
    inline const string cityPh = "CITYPLACEHOLDER";
    inline const string foodPh = "FOODPLACEHOLDER";
    inline const string zomPh = "ZOMBIESPLACEHOLDER";
    inline const string survPh = "SURVIVORSPLACEHOLDER";
    inline const string missPh = "MISSPLACEHOLDER";
    inline const string dangPh = "DANGPLACEHOLDER";
    inline const string dayPh = "DAYPLACEHOLDER";

    inline const int numJobs = 5;
    inline const string jobLeader = "leader";
    inline const string jobSoldier = "soldier";
    inline const string jobScavenger = "scavenger";
    inline const string jobBuilder = "builder";
    inline const string jobSurvivor = "survivor";
    inline const string jobs[numJobs] = {jobLeader, jobSoldier, jobScavenger, jobBuilder, jobSurvivor};
    inline const int startingPopNum = 50;

    inline const string introText = "It's been 6 months since the outbreak. People watched with horror on their smartphones as it struck country after country, the same stories: riots, panic, violence. Ordinary people giving into a kind of madness the world had never seen before. It was terrifying, but it made for great entertainment. See, we assumed it would stay in the third world, like we were special somehow, and it wouldn't be able to hurt us here.\n\nWhen the parasite made its way, inevitably, to the western world, the explanations varied for the first victims. Depending on their background, some were chalked up as mental health victims, some as savage migrants, or alien terrorists. Most met their end by the police, the evidence covered up, incidents to mention and quickly brush past in the evening news. Topics avoided like contagious disease, even as the sight of armored police carriers in our neighborhoods increased, even as economies crashed like dead birds falling out of the sky.\n\nThis parasite doesn't discriminate. The bread riots spread it even faster. It's everywhere now. Our city, Baltimore, collapsed a week ago. We watched the National Guard leave a week ago, and they've blocked off all roads in and out. No one knows what they're up to, but we don't have faith that they're coming back. Now it's just us, trapped in here with drones flying over us, others that are just as or more desperate, and the living dead.\n\nWe're not going to give up. 7 of us have decided to stick together. We've put up some walls and barbed wire to block off an abandoned LOCPLACEHOLDER. The dead are restless outside our walls. And our food and supplies won't last forever. The government and military were never on our side - we can only trust each other. But we're going to reclaim CITYPLACEHOLDER, block by block.";
    inline const string wildBody1 = "This is a LOCPLACEHOLDER that we've scouted. Here's what we know is here.\n\nFood: FOODPLACEHOLDER.\nZombies: ZOMBIESPLACEHOLDER.\nSurvivors: SURVIVORSPLACEHOLDER.";
    inline const string reclaimedBody = "This LOCPLACEHOLDER is reclaimed and within our walls. Some of our people are living here, and we're using it to store food and other supplies. Make sure we have guards on our walls.";
    inline const string missionsBody = "Choose a mission at the unreclaimed LOCPLACEHOLDER here. You can scout the area to learn more, scavenge for food, kill zombies, or recruit survivors.";
    inline const string personChoiceBody = "Choose who you want on this mission.\nDanger: DANGPLACEHOLDER%. Days to take: DAYPLACEHOLDER";    
    inline const string activeTileBody = "Current mission: MISSPLACEHOLDER.\nDanger: DANGPLACEHOLDER%.\nWill take: DAYPLACEHOLDER days\n\nOn mission:\n";
    // inline const string dummyText = "One thousand pounds of cheese for one flower! That may sound like an unfair trade, but it happened once. Tulips were first grown in Holland in the 1600s. Many rich people enjoyed planting them in their gardens. They were willing to pay a lot of money for the tulip bulbs, which looked like small onions. Traders drove up the prices. They began to buy up the tulips to sell them later for more money. Other people enjoyed collecting rare types of tulips.\n\nSoon, tulip bulbs were worth thousands of silver coins. People sold everything they had to buy them. The prices went up so quickly that people thought they would be able to get rich by selling the tulips later.";


    inline const string notLink = "";
    inline const string onClickClose = "close stack";
    inline const string onClickAccept = "accept stack";
    inline const string onClickSelect = "select";
    inline const string onClickCreateReclaimedTile = "create " + reclaimedTile;
    inline const string onClickCreateWildTile = "create " + wildTile;
    inline const string onClickCreateMissionChoice = "create " + missionChoice;
    inline const string onClickCreatePersonChoice = "create " + personChoice;
    inline const string onClickCreateActiveTile = "create " + activeTile;
    inline const string onClickNone = "none";

    inline const void updateView(float playerCenterX, float playerCenterY, int viewWidth, int viewHeight, int tileWidth, int tileHeight, int worldWidth, int worldHeight, float* clampedCenterX, float* clampedCenterY) {
        // sf::Vector2f playerCenter = cMgr.getPlayerCenter();
        // sf::Vector2f viewSize = view.getSize();
        float halfViewWidth = viewWidth / 2.0f;
        float halfViewHeight = viewHeight / 2.0f;

        // Define the view's bounds in the tile map
        float viewMinX = halfViewWidth;
        float viewMinY = halfViewHeight;
        float viewMaxX = worldWidth * tileWidth - halfViewWidth;
        float viewMaxY = worldHeight * tileHeight - halfViewHeight;

        // Clamp the view center to ensure it doesn't go outside the tile boundaries
        *clampedCenterX = max(viewMinX, min(playerCenterX, viewMaxX));
        *clampedCenterY = max(viewMinY, min(playerCenterY, viewMaxY));

        // Update the view center
        // view.setCenter(clampedCenterX, clampedCenterY);
        // cout << "Player center x: " << playerCenter.x << " player center y: " << playerCenter.y << endl;
    }

    inline const pair<float, float> calculateLiterals(float desiredSizeX, float desiredSizeY) {
        float factorX = desiredSizeX / 1440.f;
        float factorY = desiredSizeY / 900.f;
        return make_pair(factorX, factorY);
    }

    inline const int getRandNum(int lb, int ub) { // inclusive of lb and ub
        return rand() % (ub - lb + 1) + lb;
    }

    inline const void lowercase(string& data) {
        std::transform(data.begin(), data.end(), data.begin(),
            [](unsigned char c){ return std::tolower(c); });
    }

    inline const void uppercaseString(string& str) {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    }
}