#pragma once
#include <iostream>
using namespace std;
namespace DataSettings {
    inline const float playerSpeed = 50.f;

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
}