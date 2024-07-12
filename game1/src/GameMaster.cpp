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

void GameMaster::addIntroInfobox() {
    if (gui_.getGUIStackEmpty()) {
        gui_.addIntroInfobox();
    }
}

void GameMaster::addTileInfobox(float mouseX, float mouseY) {
    if (gui_.getGUIStackEmpty()) {
        gui_.addTileInfobox(
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

void GameMaster::infoboxMaster(float mouseX, float mouseY, bool clicked, bool scrollDown, bool scrollUp) {
    linkData_ = gui_.getClickData();
    if (linkData_ == Data::onClickClose) {
        gui_.popCurrentState();
    } else if (linkData_ == Data::onClickCreateMissionChoice) {
        addMissionInfobox();
    }
    linkData_ = "";
    gui_.passInput(mouseX, mouseY, clicked, scrollDown, scrollUp);
}

void GameMaster::popCurrentInfobox() { gui_.popCurrentState(); }