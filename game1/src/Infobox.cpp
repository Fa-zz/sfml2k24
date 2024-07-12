#include "Infobox.hpp"

// TileInfobox::TileInfobox(sf::Font font, float windowX, float windowSizeY, unordered_map<string,int> data) : font_(font), windowSizeX_(windowSizeX), windowSizeY_(windowSizeY), data_(data) {
// Infobox::Infobox(sf::Font font, float windowSizeX, float windowSizeY, int data, std::shared_ptr<GUIContext> &gui_context_) : font_(font), windowSizeX_(windowSizeX), windowSizeY_(windowSizeY), data_(data), gui_context_(gui_context_) {

Infobox::Infobox(int charSize, sf::Font font, float windowSizeX, float windowSizeY, string infoboxStatus)
: charSize_(charSize), font_(font), windowSizeX_(windowSizeX), windowSizeY_(windowSizeY), infoboxStatus_(infoboxStatus) {

}

Infobox::Infobox(int charSize, sf::Font font, float windowSizeX, float windowSizeY, string infoboxStatus, string infoboxType, int* tileStats, int* tileMissions) 
: charSize_(charSize), font_(font), windowSizeX_(windowSizeX), windowSizeY_(windowSizeY), infoboxStatus_(infoboxStatus), infoboxType_(infoboxType), tileStats_(tileStats), tileMissions_(tileMissions)  {

}

void Infobox::pause() {
    isPaused_ = true;
}

void Infobox::start() {
    isPaused_ = false;
}
// INIT TEXTBOX
void Infobox::init() {
    createInfobox();

    createCloseLink();

    createBodyText();

    if (infoboxStatus_ == Data::wildTile) {
        Textlink *missionsLink = new Textlink("See missions", font_, charSize_, Data::onClickCreateMissionChoice);
        auto missionLiterals = Data::calculateLiterals(445, 635);
        missionsLink->setPosition(windowSizeX_ * missionLiterals.first, windowSizeY_ * missionLiterals.second);
        links_.push_back(missionsLink);

        string wildTileInfoTextUpdated = replaceBodyText(infoboxType_,Data::tileStatDescs[tileStats_[0]], Data::tileStatDescs[tileStats_[1]], Data::tileStatDescs[tileStats_[2]] );
        string wildTileInfoTextUpdWrap = wrapText(wildTileInfoTextUpdated);
        bodyText_.setString(wildTileInfoTextUpdWrap);
        // auto bodyTextLiterals = Data::calculateLiterals(398, 365-50);

    } else if (infoboxStatus_ == Data::missionChoice) {
        // bodyText_.setString("Choose a mission at the church here.\nYou can scout the area to learn more,\nscavenge for food, kill zombies,\nor recruit survivors.");
        string bodyTextWrapped = wrapText(Data::dummyText);
        string bodyTextWrappedScrollable = makeScrollable(bodyTextWrapped);

        bodyText_.setString(bodyTextWrapped);
        // auto bodyTextLiterals = Data::calculateLiterals(102, 265-50);
        // bodyText_.setPosition(windowSizeX_ * bodyTextLiterals.first, windowSizeY_ * bodyTextLiterals.second);
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
    if (infoboxRect_)
        delete infoboxRect_;
    // for (auto & element : optionsText_) {
    //     delete element;
    // }
    for (auto& link : links_) {
        delete link;
    }
}
// PROCESS INPUT
void Infobox::processInput() {
    // Handle input for links. Link color changes when hovered over. Link data acquired when clicked
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
    // Handle input for scrollable text and options.
}

void Infobox::update() {

}

void Infobox::render(sf::RenderTarget& rt) {
    rt.draw(*infoboxRect_);
    rt.draw(bodyText_);
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
}

string Infobox::getData() {
    string data;
    data = linkData_;
    linkData_ = "";
    return data;
    // return linkData_;
}
// CREATE INFOBOX
void Infobox::createInfobox() {
    infoboxRect_ = new sf::RectangleShape();
    infoboxRect_->setOutlineThickness(10);
    infoboxRect_->setFillColor(sf::Color(32, 178, 170));
    infoboxRect_->setOutlineColor(sf::Color(70, 90, 70));
    // auto infoboxSizeLiterals = Data::calculateLiterals(1010, 600);
    auto infoboxSizeLiterals = Data::calculateLiterals(1250, 600);
    infoboxRect_->setSize(sf::Vector2f(windowSizeX_ * infoboxSizeLiterals.first, windowSizeY_ * infoboxSizeLiterals.second));
    auto infoboxPosLiterals = Data::calculateLiterals(100, 150);
    infoboxRect_->setPosition(windowSizeX_ * infoboxPosLiterals.first, windowSizeY_ * infoboxPosLiterals.second);
}

void Infobox::createCloseLink() {
    Textlink *closeLink = new Textlink("Close", font_, charSize_, Data::onClickClose);
    auto closeLiterals = Data::calculateLiterals(105, 155);
    closeLink->setPosition(windowSizeX_ * closeLiterals.first, windowSizeY_ * closeLiterals.second);
    links_.push_back(closeLink);
}

void Infobox::createBodyText() {
    bodyText_.setFont(font_);
    bodyText_.setCharacterSize(charSize_);
    bodyText_.setFillColor(sf::Color::Black);
    bodyText_.setLineSpacing(2.f);
    auto bodyTextLiterals = Data::calculateLiterals(102, 265-50);
    bodyText_.setPosition(windowSizeX_ * bodyTextLiterals.first, windowSizeY_ * bodyTextLiterals.second);
}

string Infobox::replaceBodyText(string replaceLoc, string replaceFood, string replaceSurvivors, string replaceZombies) {
    string wildTileInfoTextUpdated = Data::wildTileBodyText;
    string loc = "LOCPLACEHOLDER";
    string food = "FOODPLACEHOLDER";
    string surv = "SURVIVORSPLACEHOLDER";
    string zomb = "ZOMBIESPLACEHOLDER";

    wildTileInfoTextUpdated.replace(wildTileInfoTextUpdated.find(loc), loc.length(), replaceLoc);
    wildTileInfoTextUpdated.replace(wildTileInfoTextUpdated.find(food), food.length(), replaceFood);
    wildTileInfoTextUpdated.replace(wildTileInfoTextUpdated.find(surv), surv.length(), replaceSurvivors);
    wildTileInfoTextUpdated.replace(wildTileInfoTextUpdated.find(zomb), zomb.length(), replaceZombies);

    return wildTileInfoTextUpdated;
}

sf::String Infobox::wrapText(sf::String string){
    unsigned currentOffset = 0;
    bool firstWord = true;
    std::size_t wordBegining = 0;

    for (std::size_t pos(0); pos < string.getSize(); ++pos) {
        auto currentChar = string[pos];
        if (currentChar == '\n'){
            currentOffset = 0;
            firstWord = true;
            continue;
        } else if (currentChar == ' ') {
            wordBegining = pos;
            firstWord = false;
        }

        auto glyph = font_.getGlyph(currentChar, charSize_, false);
        currentOffset += glyph.advance;
        currentOffset += font_.getKerning(string[pos-1], currentChar, charSize_);

        if (!firstWord && currentOffset > infoboxRect_->getGlobalBounds().width -15.f) {
            pos = wordBegining;
            string[pos] = '\n';
            firstWord = true;
            currentOffset = 0;
        }
    }
        return string;
}

string Infobox::makeScrollable(string scrollMe) {
    string line;
    for (int i = 0; i < scrollMe.length(); i++) {
        if (scrollMe[i] != '\n') {
            line += scrollMe[i]; // add character to line if it isn't paragraph break
        } else {
            line += scrollMe[i]; // when reach paragraph break, add it
            if (i + 1 < scrollMe.length() && scrollMe[i + 1] == '\n') { // add next break if it follows as well
                line += scrollMe[i + 1];
                i += 1;
            }
            addBodyBackend_.push_back(line);
            line = "";
        }
    }

    if (!line.empty()) {
        addBodyBackend_.push_back(line);
    }

    return scrollMe;
}

void Infobox::loop(const sf::Time& deltaTime) { }
void Infobox::update(const sf::Time& deltaTime) { }
void Infobox::render() { }
