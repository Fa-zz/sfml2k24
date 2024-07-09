#include "GameMaster.hpp"

GameMaster::GameMaster(GUI& gui, World& world) : gui_(gui), world_(world) { 
    // *linkData_ = "";
}

GameMaster::~GameMaster() { }

void GameMaster::initInfobox(float mouseX, float mouseY) {
    if (gui_.getGUIStackEmpty()) {
        gui_.initInfobox(world_.getGroundTileAtPos(mouseY, mouseX)->getTileStatus());
    }
}

void GameMaster::addMissionInfobox() {
    gui_.addMissionInfobox();
}

void GameMaster::infoboxMaster(float mouseX, float mouseY, bool clicked) {
    gui_.setMouseInfo(mouseX, mouseY, clicked);
    linkData_ = gui_.getClickData();
    cout << "infoboxMaster Link data: " << linkData_ << endl;
    if (linkData_ == Data::onClickClose) {
        gui_.popCurrentState();
    } else if (linkData_ == Data::onClickCreateMissionChoice) {
        addMissionInfobox();
    }
    linkData_ = "";
}
