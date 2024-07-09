#pragma once
#include <iostream> 
#include <sstream> 
#include <string> 
using namespace std; 

namespace Data {
    //    sf::Vector2i res1 = {1440, 900};
    //    sf::Vector2i res2 = {800, 600};

    inline const float res1x = 1440.f;
    inline const float res1y = 900.f;
    inline const float res2x = 800.f;
    inline const float res2y = 600.f;

    inline const float playerSpeed = 100.f;

    inline const string reclaimedTile = "reclaimedTile";
    inline const string wildTile = "wildTile";
    inline const string missionChoice = "missionChoice";
    inline const string personChoice = "personChoice";
    inline const string activeTile = "activeTile";

    inline const string onClickClose = "close stack";
    inline const string onClickAccept = "accept stack";
    inline const string onClickSelect = "select";
    inline const string onClickCreateReclaimedTile = "create " + reclaimedTile;
    inline const string onClickCreateWildTile = "create " + wildTile;
    inline const string onClickCreateMissionChoice = "create " + missionChoice;
    inline const string onClickCreatePersonChoice = "create " + personChoice;
    inline const string onClickCreateActiveTile = "create " + activeTile;

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

    // inline const void splitString(string& input, char delimiter, string arr[]) {
    //     // Creating an input string stream from the input string 
    //     istringstream stream(input); 
    
    //     // Temporary string to store each token 
    //     string token; 

    //     int index = 0; 

    //     // Read tokens from the string stream separated by the 
    //     // delimiter 
    //     while (getline(stream, token, delimiter)) { 
    //         // Add the token to the array 
    //         arr[index++] = token; 
    //     } 
    // } 
}