#include "Infobox.hpp"

// TileInfobox::TileInfobox(sf::Font font, float windowX, float windowSizeY, unordered_map<string,int> data) : font_(font), windowSizeX_(windowSizeX), windowSizeY_(windowSizeY), data_(data) {
// Infobox::Infobox(sf::Font font, float windowSizeX, float windowSizeY, int data, std::shared_ptr<GUIContext> &gui_context_) : font_(font), windowSizeX_(windowSizeX), windowSizeY_(windowSizeY), data_(data), gui_context_(gui_context_) {

Infobox::Infobox(int charSize, sf::Font font, float windowSizeX, float windowSizeY, string infoboxStatus)
: charSize_(charSize), font_(font), windowSizeX_(windowSizeX), windowSizeY_(windowSizeY), infoboxStatus_(infoboxStatus) {

}

Infobox::Infobox(int charSize, sf::Font font, float windowSizeX, float windowSizeY, string infoboxStatus, string locType)
: charSize_(charSize), font_(font), windowSizeX_(windowSizeX), windowSizeY_(windowSizeY), infoboxStatus_(infoboxStatus), locType_(locType) {

}

Infobox::Infobox(int charSize, sf::Font font, float windowSizeX, float windowSizeY, string infoboxStatus, string locType, int* tileStats, int* tileMissions) 
: charSize_(charSize), font_(font), windowSizeX_(windowSizeX), windowSizeY_(windowSizeY), infoboxStatus_(infoboxStatus), locType_(locType), tileStats_(tileStats), tileMissions_(tileMissions)  {

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
    initBodyText();

    if (infoboxStatus_ == Data::intro) {
        scrollable_ = true;
        string updatedIntro = replaceText(Data::introText, Data::locPh, locType_);
        makeScrollable(wrapText(replaceText(updatedIntro, Data::cityPh, "Baltimore")));
        bodyText_.setString(getBoundedString(0));
        createScrollText();

    } else if (infoboxStatus_ == Data::reclaimedTile) {
        bodyText_.setString(wrapText(replaceText(Data::reclaimedBody, Data::locPh, locType_)));
    
    } else if (infoboxStatus_ == Data::wildTile) {
        createMissionsLink();

        string wildTileInfoTextUpdated = replaceBodyText(locType_, Data::tileStatDescs[tileStats_[0]], Data::tileStatDescs[tileStats_[1]], Data::tileStatDescs[tileStats_[2]] );
        string wildTileInfoTextUpdWrap = wrapText(wildTileInfoTextUpdated);
        bodyText_.setString(wildTileInfoTextUpdWrap);

    } else if (infoboxStatus_ == Data::missionChoice) {
        // bodyText_.setString("Choose a mission at the church here.\nYou can scout the area to learn more,\nscavenge for food, kill zombies,\nor recruit survivors.");
        // string bodyTextWrapped = wrapText(Data::dummyText);
        // string bodyTextWrappedScrollable = makeScrollable(bodyTextWrapped);

        // bodyText_.setString(bodyTextWrapped);
    }
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
    Textlink *closeLink = new Textlink("Close (Esc)", font_, charSize_, Data::onClickClose);
    auto closeLiterals = Data::calculateLiterals(105, 155);
    closeLink->setPosition(windowSizeX_ * closeLiterals.first, windowSizeY_ * closeLiterals.second);
    links_.push_back(closeLink);
}

void Infobox::createScrollText() {
    scrollText_.setString("Scroll with W/S");
    scrollText_.setFont(font_);
    scrollText_.setCharacterSize(charSize_);
    scrollText_.setFillColor(sf::Color::Black);
    scrollText_.setLineSpacing(2.f);
    auto bodyTextLiterals = Data::calculateLiterals(510, 155);
    scrollText_.setPosition(windowSizeX_ * bodyTextLiterals.first, windowSizeY_ * bodyTextLiterals.second);
}

void Infobox::createMissionsLink() {
    Textlink *missionsLink = new Textlink("See missions", font_, charSize_, Data::onClickCreateMissionChoice);
    auto missionLiterals = Data::calculateLiterals(445, 635);
    missionsLink->setPosition(windowSizeX_ * missionLiterals.first, windowSizeY_ * missionLiterals.second);
    links_.push_back(missionsLink);
}

void Infobox::initBodyText() {
    bodyText_.setFont(font_);
    bodyText_.setCharacterSize(charSize_);
    bodyText_.setFillColor(sf::Color::Black);
    bodyText_.setLineSpacing(2.f);
    auto bodyTextLiterals = Data::calculateLiterals(102, 300-50);
    bodyText_.setPosition(windowSizeX_ * bodyTextLiterals.first, windowSizeY_ * bodyTextLiterals.second);
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
    if (scrollable_) {
        if (scrollDown_) {
            bodyText_.setString(getBoundedString(1));
        } else if (scrollUp_) {
            bodyText_.setString(getBoundedString(-1));
        }
        scrollDown_ = false;
        scrollUp_ = false;
    }
}

void Infobox::update() {

}
// RENDER ALL
void Infobox::render(sf::RenderTarget& rt) {
    rt.draw(*infoboxRect_);
    rt.draw(bodyText_);
    if (scrollable_)
        rt.draw(scrollText_);
    for (auto& link : links_) {
        rt.draw(link->getText());
    }
    // rt.draw(optionText_);
}

void Infobox::handleInput(float x, float y, bool clicked, bool scrollDown, bool scrollUp) {
    mousePosX_ = x;
    mousePosY_ = y;
    clicked_ = clicked;
    scrollDown_ = scrollDown;
    scrollUp_ = scrollUp;
    processInput();
}

string Infobox::getData() {
    string data;
    data = linkData_;
    linkData_ = "";
    return data;
    // return linkData_;
}

string Infobox::replaceText(string stringToReplace, string placeHolderText, string replaceWith) {
    while (stringToReplace.find(placeHolderText) != string::npos)
        stringToReplace.replace(stringToReplace.find(placeHolderText), placeHolderText.length(), replaceWith);
    return stringToReplace;
}

// string Infobox::replaceIntroText() {
//     string loc = "LOCPLACEHOLDER";
//     string city = "CITYPLACEHOLDER";
//     string replaceLoc = locType_;
//     string intro = Data::introText;
//     while (intro.find(loc) != string::npos)
//         intro.replace(intro.find(loc), loc.length(), replaceLoc);
//     while (intro.find(city) != string::npos)
//         intro.replace(intro.find(city), city.length(), "Baltimore");

//     return intro;
// }

string Infobox::replaceBodyText(string replaceLoc, string replaceFood, string replaceZombies, string replaceSurvivors) {
    string wildTileInfoTextUpdated = Data::wildBody1;
    string loc = "LOCPLACEHOLDER";
    string food = "FOODPLACEHOLDER";
    string zomb = "ZOMBIESPLACEHOLDER";
    string surv = "SURVIVORSPLACEHOLDER";

    wildTileInfoTextUpdated.replace(wildTileInfoTextUpdated.find(loc), loc.length(), replaceLoc);
    wildTileInfoTextUpdated.replace(wildTileInfoTextUpdated.find(food), food.length(), replaceFood);
    wildTileInfoTextUpdated.replace(wildTileInfoTextUpdated.find(zomb), zomb.length(), replaceZombies);
    wildTileInfoTextUpdated.replace(wildTileInfoTextUpdated.find(surv), surv.length(), replaceSurvivors);

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

void Infobox::makeScrollable(string scrollMe) {
    // Create and populate the addBodyBackend_ object
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
            bodyTextBackend_.push_back(line);
            line = "";
        }
    }
    if (!line.empty()) {
        bodyTextBackend_.push_back(line);
    }
}

string Infobox::getBoundedString(int upd) {
    string result = "";

    // Update starting and ending lines with bounds checking
    if ((startingLine_ + upd >= 0) && (endingLine_ + upd < bodyTextBackend_.size())) {
        startingLine_ += upd;
        endingLine_ += upd;
    } else {
        // Prevent updating if it goes out of bounds
        if (startingLine_ + upd < 0) {
            startingLine_ = 0;
            endingLine_ = min((int)bodyTextBackend_.size() - 1, endingLine_ - startingLine_);
        } else if (endingLine_ + upd >= bodyTextBackend_.size()) {
            endingLine_ = bodyTextBackend_.size() - 1;
            startingLine_ = max(0, endingLine_ - (endingLine_ - startingLine_));
        }
    }

    // Ensure starting and ending lines are within bounds
    startingLine_ = max(0, min(startingLine_, (int)bodyTextBackend_.size() - 1));
    endingLine_ = max(0, min(endingLine_, (int)bodyTextBackend_.size() - 1));

    // Append lines within the visible range
    for (int i = startingLine_; i <= endingLine_; ++i) {
        result += bodyTextBackend_[i];
    }

    // cout << "String shown: " << result << endl;
    return result;
}

void Infobox::loop(const sf::Time& deltaTime) { }
void Infobox::update(const sf::Time& deltaTime) { }
void Infobox::render() { }
// void Infobox::helloWorld(int x) { }