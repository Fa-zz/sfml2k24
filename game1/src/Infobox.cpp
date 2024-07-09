#include "Infobox.hpp"

// TileInfobox::TileInfobox(sf::Font font, float windowSizeX, float windowSizeY, unordered_map<string,int> data) : font_(font), windowSizeX_(windowSizeX), windowSizeY_(windowSizeY), data_(data) {
// Infobox::Infobox(sf::Font font, float windowSizeX, float windowSizeY, int data, std::shared_ptr<GUIContext> &gui_context_) : font_(font), windowSizeX_(windowSizeX), windowSizeY_(windowSizeY), data_(data), gui_context_(gui_context_) {
Infobox::Infobox(sf::Font font, float windowSizeX, float windowSizeY, string infoboxType) : font_(font), windowSizeX_(windowSizeX), windowSizeY_(windowSizeY), infoboxType_(infoboxType) {

}

void Infobox::pause() {
    isPaused_ = true;
}

void Infobox::start() {
    isPaused_ = false;
}

void Infobox::init() {
    infoBox_ = new sf::RectangleShape();
    infoBox_->setOutlineThickness(10);
    infoBox_->setFillColor(sf::Color(32, 178, 170));
    infoBox_->setOutlineColor(sf::Color(70, 90, 70));

    auto infoboxSizeLiterals = Data::calculateLiterals(1000, 600);
    infoBox_->setSize(sf::Vector2f(windowSizeX_ * infoboxSizeLiterals.first, windowSizeY_ * infoboxSizeLiterals.second));
    auto infoboxPosLiterals = Data::calculateLiterals(200, 200);
    infoBox_->setPosition(windowSizeX_ * infoboxPosLiterals.first, windowSizeY_ * infoboxPosLiterals.second);

    infoText_.setFont(font_);
    infoText_.setCharacterSize(15);
    Textlink *closeLink = new Textlink("Close", font_, 15, Data::onClickClose);
    auto closeLiterals = Data::calculateLiterals(230, 220);
    closeLink->setPosition(windowSizeX_ * closeLiterals.first, windowSizeY_ * closeLiterals.second);
    links_.push_back(closeLink);

    if (infoboxType_ == Data::wildTile) {
        Textlink *missionsLink = new Textlink("See missions", font_, 20, Data::onClickCreateMissionChoice);
        auto missionLiterals = Data::calculateLiterals(445, 635);
        missionsLink->setPosition(windowSizeX_ * missionLiterals.first, windowSizeY_ * missionLiterals.second);
        links_.push_back(missionsLink);

        infoText_.setString("This is a Church.\nFood: Low\nSurvivors: Medium\nZombies: High\n");
        auto infoTextLiterals = Data::calculateLiterals(398, 365);
        infoText_.setPosition(windowSizeX_ * infoTextLiterals.first, windowSizeY_ * infoTextLiterals.second);
    } else if (infoboxType_ == Data::missionChoice) {
        infoText_.setString("Choose a mission at the church here.\nYou can scout the area to learn more,\nscavenge for food, kill zombies,\nor recruit survivors.");
        auto infoTextLiterals = Data::calculateLiterals(205, 365-50);
        infoText_.setPosition(windowSizeX_ * infoTextLiterals.first, windowSizeY_ * infoTextLiterals.second);
    }
}

void Infobox::loop(sf::RenderTarget& rt) {
    if (!isPaused_) {
        render(rt);
        processInput();
        update();
    }
}

Infobox::~Infobox() {
    if (infoBox_)
        delete infoBox_;
    // for (auto & element : optionsText_) {
    //     delete element;
    // }
    for (auto& link : links_) {
        delete link;
    }
}

void Infobox::processInput() {
    selectedIndex_ = -1;

    for (int i = 0; i < links_.size(); ++i) {
        auto& link = links_[i];
        if (link->getText().getGlobalBounds().contains(mousePosX_, mousePosY_)) {
            link->setColor(1);
            selectedIndex_ = i;
        } else {
            link->setColor(0);
        }
    }

    if (clicked_ && selectedIndex_ != -1) {
        linkData_ = links_[selectedIndex_]->getOnClick();
        clicked_ = false;
    }
}

void Infobox::update() {

}

void Infobox::render(sf::RenderTarget& rt) {
    rt.draw(*infoBox_);
    rt.draw(infoText_);
    for (auto& link : links_) {
        rt.draw(link->getText());
    }
    // rt.draw(optionText_);
}

void Infobox::mouseInfo(float x, float y, bool clicked) {
    mousePosX_ = x;
    mousePosY_ = y;
    clicked_ = clicked;
    processInput();
    // for (int i = 0; i < 2; i++) {
    //     // cout << "Data: " << data[i] << endl;
    //     data[i] = linkData_[i];
    //     linkData_[i] = "";
    // }
}

string Infobox::getData() {
    string data;
    data = linkData_;
    linkData_ = "";
    return data;
    // return linkData_;
}

void Infobox::loop(const sf::Time& deltaTime) { }
void Infobox::update(const sf::Time& deltaTime) { }
void Infobox::render() { }
