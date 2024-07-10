#include "GameMaster.hpp"

void GameMaster::initGame() {
    world_ = new World();
    width_ = Data::worldWidth;
    height_ = Data::worldHeight;
    world_->genTiles(height_, width_);
}

GameMaster::GameMaster(GUI& gui) : gui_(gui) { 

}

GameMaster::~GameMaster() { 
    delete world_;
}

Terrain& GameMaster::getGroundTileAtPos(int y, int x) {
    if (world_->getGroundTileAtPos(y, x) != nullptr) {
        return *(world_->getGroundTileAtPos(y, x));
    } else {
        cerr << "Nullptr found" << endl;
    }
}

void GameMaster::initInfobox(float mouseX, float mouseY) {
    if (gui_.getGUIStackEmpty()) {
        // cout << "Tile status: " << world_->getGroundTileAtPos(mouseY, mouseX)->getTileStatus() << endl;
        gui_.initInfobox(
            world_->getGroundTileAtPos(mouseY, mouseX)->getTileStatus(),
            world_->getGroundTileAtPos(mouseY, mouseX)->getTileType(),
            world_->getGroundTileAtPos(mouseY, mouseX)->getTileStats(), 
            world_->getGroundTileAtPos(mouseY, mouseX)->getTileMissions()
        );
    }
}

void GameMaster::addMissionInfobox() {
    gui_.addMissionInfobox();
}

void GameMaster::infoboxMaster(float mouseX, float mouseY, bool clicked) {
    gui_.setMouseInfo(mouseX, mouseY, clicked);
    linkData_ = gui_.getClickData();
    // cout << "infoboxMaster Link data: " << linkData_ << endl;
    if (linkData_ == Data::onClickClose) {
        gui_.popCurrentState();
    } else if (linkData_ == Data::onClickCreateMissionChoice) {
        addMissionInfobox();
    }
    linkData_ = "";
}
