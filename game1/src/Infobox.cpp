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
    Textlink *closeLink = new Textlink("Close", font_, 15, Data::onClickClose);
    closeLink->setPosition(windowSizeX_ * .1597f, windowSizeY_ * .2444f);
    links_.push_back(closeLink);

    if (infoboxType_ == Data::wildTile) {
        Textlink *missionsLink = new Textlink("See missions", font_, 20, Data::onClickCreateMissionChoice);
        missionsLink->setPosition(windowSizeX_ * .309027f, windowSizeY_ * .7055f);
        links_.push_back(missionsLink);

        infoText_.setFont(font_);
        infoBox_ = new sf::RectangleShape();
        infoBox_->setOutlineThickness(10);
        infoBox_->setFillColor(sf::Color(32, 178, 170));
        infoBox_->setOutlineColor(sf::Color(70, 90, 70));

        infoBox_->setSize(sf::Vector2f(windowSizeX_ * .6944f, windowSizeY_ * .6667f)); // size x = 1000, size y = 600
        infoBox_->setPosition(windowSizeX_ * .1388f, windowSizeY_ * 0.2222f); // pos x = 200, pos y = 200

        infoText_.setCharacterSize(20);
        infoText_.setString("This is a Church.\nFood: Low\nSurvivors: Medium\nZombies: High\n");
        infoText_.setPosition(windowSizeX_ * .277, windowSizeY_ * 0.40555);
        // optionText_.setFont(font_);
        // optionText_.setCharacterSize(20);
        // optionText_.setString("See missions");
        // optionText_.setPosition(windowSizeX_ * .309027f, windowSizeY_ * .7055f);
        // pos x = 230, 220
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
    std::cout << "Processing Input... Mouse Position: (" << mousePosX_ << ", " << mousePosY_ << ")" << std::endl;
    selectedIndex_ = -1; // Reset selectedIndex_ before processing

    for (int i = 0; i < links_.size(); ++i) {
        auto& link = links_[i];
        std::cout << "Checking link " << i << " at position (" 
                  << link->getText().getPosition().x << ", " 
                  << link->getText().getPosition().y << ") with bounds: "
                  << link->getText().getGlobalBounds().left << ", "
                  << link->getText().getGlobalBounds().top << ", "
                  << link->getText().getGlobalBounds().width << ", "
                  << link->getText().getGlobalBounds().height << std::endl;

        if (link->getText().getGlobalBounds().contains(mousePosX_, mousePosY_)) {
            link->setColor(1);
            selectedIndex_ = i;
            std::cout << "Link " << i << " selected with data: " 
                      << link->getOnClick() << std::endl;
        } else {
            link->setColor(0);
        }
    }

    if (clicked_ && selectedIndex_ != -1) {
        linkData_ = links_[selectedIndex_]->getOnClick();
        std::cout << "Link clicked: " << linkData_ << std::endl;
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
}

void Infobox::loop(const sf::Time& deltaTime) { }
void Infobox::update(const sf::Time& deltaTime) { }
void Infobox::render() { }
