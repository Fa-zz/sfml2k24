#include "GameMaster.hpp"

GameMaster::GameMaster(GUI& gui, World& world) : gui_(gui), world_(world) { }

GameMaster::~GameMaster() { }

void GameMaster::infoboxMaster(float mouseX, float mouseY, bool clicked) {
    if (gui_.getGUIStackEmpty()) {
        gui_.initInfobox(world_.getGroundTileAtPos(mouseX, mouseY)->getTileStatus());
    } else {
        gui_.setMouseInfo(mouseX, mouseY, clicked, linkData_);
    }
    string linkDataString = linkData_[0] + " " + linkData_[1];
    cout << linkDataString << endl;
    if (linkDataString == Data::onClickClose) {
        gui_.popCurrentState();
    }
    linkData_[0] = "";
    linkData_[1] = "";
    // for (int i = 0; i < 2; i++) {
    //     linkData_
    // }
    // }

}