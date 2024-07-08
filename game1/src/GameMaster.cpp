#include "GameMaster.hpp"

GameMaster::GameMaster(GUI& gui) : gui_(gui) { }

GameMaster::~GameMaster() { }

void GameMaster::infoboxMaster(float mouseX, float mouseY, bool clicked) {
    // cout << "You've reached infoboxMaster" << endl;
    if (gui_.getGUIStackEmpty()) {
        gui_.initInfobox(1);
    } else {
        gui_.setMouseInfo(mouseX, mouseY, clicked, linkData_);
    }

    if (linkData_[0] == "close") {
        gui_.popCurrentState();
    }
    // for (int i = 0; i < 2; i++) {
    //     linkData_
    // }
    // }

}