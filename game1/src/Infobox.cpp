#include "Infobox.hpp"

// TileInfobox::TileInfobox(sf::Font font, float windowX, float windowSizeY, unordered_map<string,int> data) : font_(font), windowSizeX_(windowSizeX), windowSizeY_(windowSizeY), data_(data) {
// Infobox::Infobox(sf::Font font, float windowSizeX, float windowSizeY, int data, std::shared_ptr<GUIContext> &gui_context_) : font_(font), windowSizeX_(windowSizeX), windowSizeY_(windowSizeY), data_(data), gui_context_(gui_context_) {
Infobox::Infobox(int charSize, sf::Font font, float windowSizeX, float windowSizeY, string infoboxType)
: charSize_(charSize), font_(font), windowSizeX_(windowSizeX), windowSizeY_(windowSizeY), infoboxType_(infoboxType) {
}

Infobox::Infobox(int charSize, sf::Font font, float windowSizeX, float windowSizeY, string infoboxType, string locType)
: charSize_(charSize), font_(font), windowSizeX_(windowSizeX), windowSizeY_(windowSizeY), infoboxType_(infoboxType), locType_(locType) {
}

Infobox::Infobox(int charSize, sf::Font font, float windowSizeX, float windowSizeY, string infoboxType, string locType, int* tileStats, int* tileMissions)
: charSize_(charSize), font_(font), windowSizeX_(windowSizeX), windowSizeY_(windowSizeY), infoboxType_(infoboxType), locType_(locType), tileStats_(tileStats), tileMissions_(tileMissions) {
}

void Infobox::pause() {
    isPaused_ = true;
}

void Infobox::start() {
    isPaused_ = false;
}
// INIT INFOBOX
void Infobox::init() {
}

void Infobox::createInfobox() {
    createBox();
    initBodyText();
    initHeaderText();
    createCloseLink();

    if (infoboxType_ == Data::intro) {
        string updatedIntro = replaceText(Data::introText, Data::locPh, locType_);
        makeScrollableBody(wrapText(replaceText(updatedIntro, Data::cityPh, "Baltimore")));
        bodyText_.setString(getBoundedString(0));
        headerText_.setString("OUR STORY SO FAR");

    } else if (infoboxType_ == Data::reclaimedTile) {
        headerText_.setString("BALTIMORE");
        bodyText_.setString(wrapText(replaceText(Data::reclaimedBody, Data::locPh, locType_)));
    
    } else if (infoboxType_ == Data::wildTile) {
        string locUpper = locType_;
        Data::uppercaseString(locUpper);
        headerText_.setString(locUpper);
        createMissionsLink();
        string wildTileInfoTextUpdated = replaceBodyText(locType_, Data::tileStatDescs[tileStats_[0]], Data::tileStatDescs[tileStats_[1]], Data::tileStatDescs[tileStats_[2]] );
        string wildTileInfoTextUpdWrap = wrapText(wildTileInfoTextUpdated);
        bodyText_.setString(wildTileInfoTextUpdWrap);

    } else if (infoboxType_ == Data::missionChoice) {
        headerText_.setString("CHOOSE MISSION");
        string bodyTextWrapped = wrapText(replaceText(Data::missionsBody, Data::locPh, locType_));
        bodyText_.setString(bodyTextWrapped);

        int missionLinkY = 450;
        for (int i = 0; i < Data::numTileMissions; i++) {
            string linkText = Data::tileMissionsText[i];
            vector<string> onClick;
            cout << "Infobox.cpp tileMissions: " << tileMissions_[i] << endl;
            if (tileMissions_[i] == 0) {
                onClick.push_back(Data::onClickNone);
            } else {
                onClick.push_back(Data::onClickCreatePersonChoice);
                onClick.push_back(Data::tileMissionsText[i]);
            }

            Textlink *missionLink = new Textlink(linkText, font_, charSize_, onClick);
            auto missLiterals = Data::calculateLiterals(102, missionLinkY);
            missionLink->setPosition(windowSizeX_ * missLiterals.first, windowSizeY_ * missLiterals.second);
            links_.push_back(missionLink);
            missionLinkY += 50;
        }    
    } else if (infoboxType_ == Data::personChoice) {
        string missUpper = currMission_;
        Data::uppercaseString(missUpper);
        headerText_.setString(missUpper + " MISSION");

        string updatedDanger = replaceText(Data::personChoiceBody, Data::dangPh, danger_);
        string updatedDays = replaceText(updatedDanger, Data::dayPh, days_);
        string bodyTextWrapped = wrapText(updatedDays);
        bodyText_.setString(bodyTextWrapped);

        makeScrollableLinks(peopleString_);

    }
    readyToDraw_ = true;
}

// CREATE INFOBOX
void Infobox::createBox() {
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
    vector<string> onClick = {Data::onClickClose};
    Textlink *closeLink = new Textlink("Close (Esc)", font_, charSize_, onClick);
    auto closeLiterals = Data::calculateLiterals(105, 155);
    closeLink->setPosition(windowSizeX_ * closeLiterals.first, windowSizeY_ * closeLiterals.second);
    links_.push_back(closeLink);
}

void Infobox::initHeaderText() {
    headerText_.setFont(font_);
    headerText_.setCharacterSize(charSize_);
    headerText_.setFillColor(sf::Color::Black);
    auto bodyTextLiterals = Data::calculateLiterals(410, 200);
    headerText_.setPosition(windowSizeX_ * bodyTextLiterals.first, windowSizeY_ * bodyTextLiterals.second);
}

void Infobox::createScrollText() {
    drawScrollText_ = true;
    scrollText_.setString("Scroll with W/S");
    scrollText_.setFont(font_);
    scrollText_.setCharacterSize(charSize_);
    scrollText_.setFillColor(sf::Color::Black);
    scrollText_.setLineSpacing(2.f);
    auto bodyTextLiterals = Data::calculateLiterals(510, 155);
    scrollText_.setPosition(windowSizeX_ * bodyTextLiterals.first, windowSizeY_ * bodyTextLiterals.second);
}

void Infobox::createMissionsLink() {
    vector<string> onClick = {Data::onClickCreateMissionChoice};
    Textlink *missionsLink = new Textlink("See missions", font_, charSize_, onClick);
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
// Destructor
Infobox::~Infobox() {
    if (infoboxRect_)
        delete infoboxRect_;
    // for (auto & element : optionsText_) {
    //     delete element;
    // }
    for (int i = 0; i < links_.size(); i++) {
        delete links_[i];
    }
    if (scrollableLinks_) {
        for (int i = 0; i < scrollLinksVec_.size(); i++) {
            delete scrollLinksVec_[i];
        }
    }
}
// PROCESS INPUT
void Infobox::processInput() {
    // Handle input for links. Link color changes when hovered over. Link data acquired when clicked
    selectedIndex_ = -1;
    int linkVecClicked = -1;
    for (int i = 0; i < links_.size(); ++i) {
        auto& link = links_[i];
        if (link->getText().getGlobalBounds().contains(mousePosX_, mousePosY_)) {
            link->setColor(1);
            selectedIndex_ = i;
            linkVecClicked = 0;
        } else {
            link->setColor(0);
        }
    }
    if (scrollLinksVec_.size() > 0) {
        for (int i = startingLink_; i <= endingLink_; ++i) {
            auto& link = scrollLinksVec_[i];
            if (link->getText().getGlobalBounds().contains(mousePosX_, mousePosY_)) {
                link->setColor(1);
                selectedIndex_ = i;
                linkVecClicked = 1;
            } else {
                link->setColor(0);
            }
        }
    }
    // get onClick data on from link
    if (clicked_ && selectedIndex_ != -1) {
        if (linkVecClicked == 0 )
            linkData_ = links_[selectedIndex_]->getOnClick();
        else if (linkVecClicked == 1 )
            linkData_ = scrollLinksVec_[selectedIndex_]->getOnClick();
        clicked_ = false;
    } else {
        linkData_.push_back("placeholder");
    }
    // Handle input for scrollable text and links.
    if (scrollableBody_ || scrollableLinks_) {
        if (scrollableBody_) {
            if (scrollDown_) {
                bodyText_.setString(getBoundedString(1));
            } else if (scrollUp_) {
                bodyText_.setString(getBoundedString(-1));
            }
        } else if (scrollableLinks_) {
            if (scrollDown_) {
                bindLinksVec(1);
            } else if (scrollUp_) {
                bindLinksVec(-1);
            }
        }
        scrollDown_ = false;
        scrollUp_ = false;
    }
}

void Infobox::setInput(float x, float y, bool clicked, bool scrollDown, bool scrollUp) {
    mousePosX_ = x;
    mousePosY_ = y;
    clicked_ = clicked;
    scrollDown_ = scrollDown;
    scrollUp_ = scrollUp;
    processInput();
}

void Infobox::update() {
    if (reachedEndOfScroll_) {
        scrollText_.setString("Reached end");
    } else {
        scrollText_.setString("Scroll with W/S");
        scrollText_.setFillColor(sf::Color::Blue);
    }

}
// RENDER ALL
void Infobox::render(sf::RenderTarget& rt) {
    int addBy = 50;
    int offset = 0;
    int y = 350;
    if (readyToDraw_) {
        rt.draw(*infoboxRect_);
        rt.draw(bodyText_);
        rt.draw(headerText_);
        if (drawScrollText_)
            rt.draw(scrollText_);
        if (scrollLinksVec_.size() > 0) {
            // rt.draw(scrollLinksVec_[0]->getText());
            for (int i = startingLink_; i <= endingLink_; i++) {
                auto linkLiterals = Data::calculateLiterals(102, y+offset);
                scrollLinksVec_[i]->setPosition(windowSizeX_ * linkLiterals.first, windowSizeY_ * linkLiterals.second);
                rt.draw(scrollLinksVec_[i]->getText());
                offset += addBy;
            }
        }
        for (auto& link : links_) {
            rt.draw(link->getText());
        }
    }
}

vector<string> Infobox::getData() {
    vector<string> data;
    data = linkData_;
    // cout << "Data: " << data << endl;
    linkData_.clear();
    return data;
    // return linkData_;
}

void Infobox::setMissions(int* missionsArr) {
    for (int i = 0; i < Data::numTileMissions; i++) {
        tileMissions_[i] = missionsArr[i];
    }
}

// void Infobox::setMission(string mission) {
//     currMission_ = mission;
// }

void Infobox::setLoc(string loc) {
    locType_ = loc;
}

void Infobox::setMissionInfo(string mission, string danger, string days) {
    currMission_ = mission;
    danger_ = danger;
    days_ = days;
}

void Infobox::setPopulation(string people) {
    peopleString_ = people;
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

void Infobox::makeScrollableBody(string scrollMe) {
    // Create and populate the scrollTextVec_ object
    scrollableBody_ = true;
    createScrollText();
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
            scrollTextVec_.push_back(line);
            line = "";
        }
    }
    if (!line.empty()) {
        scrollTextVec_.push_back(line);
    }
}

string Infobox::getBoundedString(int upd) {
    string result = "";

    // Update starting and ending lines with bounds checking
    if ((startingLine_ + upd >= 0) && (endingLine_ + upd < scrollTextVec_.size())) {
        startingLine_ += upd;
        endingLine_ += upd;
        reachedEndOfScroll_ = false;
    } else {
        // Prevent updating if it goes out of bounds
        if (startingLine_ + upd < 0) {
            startingLine_ = 0;
            endingLine_ = min((int)scrollTextVec_.size() - 1, endingLine_ - startingLine_);
        } else if (endingLine_ + upd >= scrollTextVec_.size()) {
            endingLine_ = scrollTextVec_.size() - 1;
            startingLine_ = max(0, endingLine_ - (endingLine_ - startingLine_));
            reachedEndOfScroll_ = true;
        }
    }

    // Ensure starting and ending lines are within bounds
    startingLine_ = max(0, min(startingLine_, (int)scrollTextVec_.size() - 1));
    endingLine_ = max(0, min(endingLine_, (int)scrollTextVec_.size() - 1));

    // Append lines within the visible range
    for (int i = startingLine_; i <= endingLine_; ++i) {
        result += scrollTextVec_[i];
    }

    // cout << "String shown: " << result << endl;
    return result;
}
void Infobox::bindLinksVec(int upd) {
    // Update starting and ending links with bounds checking
    if ((startingLink_ + upd >= 0) && (endingLink_ + upd < scrollLinksVec_.size())) {
        startingLink_ += upd;
        endingLink_ += upd;
        reachedEndOfScroll_ = false;
    } else {
        // Prevent updating if it goes out of bounds
        if (startingLink_ + upd < 0) {
            startingLink_ = 0;
            endingLink_ = min((int)scrollLinksVec_.size() - 1, endingLink_ - startingLink_);
        } else if (endingLink_ + upd >= scrollLinksVec_.size()) {
            endingLink_ = scrollLinksVec_.size() - 1;
            startingLink_ = max(0, endingLink_ - (endingLink_ - startingLink_));
            reachedEndOfScroll_ = true;
        }
    }

    // Ensure starting and ending links are within bounds
    startingLink_ = max(0, min(startingLink_, (int)scrollLinksVec_.size() - 1));
    endingLink_ = max(0, min(endingLink_, (int)scrollLinksVec_.size() - 1));
}
void Infobox::makeScrollableLinks(string scrollMe) {
    cout << " Scroll me: " << scrollMe << endl;
    // Create and populate the scrollLinksVec_ object
    // Similar to makeScrollableBody except this fn. creates Textlink objects at each line, which it then adds to scrollLinksVec_ object
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
            // Textlink is created
            vector<string> onClickPerson = {Data::onClickSelect, to_string(i)};
            Textlink* link = new Textlink(line, font_, charSize_, onClickPerson);
            scrollLinksVec_.push_back(link);
            line = "";
        }
    }
    if (!line.empty()) {
        vector<string> onClickPerson = {Data::onClickSelect, to_string(scrollMe.length()-1)};
        Textlink* link = new Textlink(line, font_, charSize_, onClickPerson);
        scrollLinksVec_.push_back(link);
    }
    // Set endingLink_
    if (scrollLinksVec_.size() > 7) {
        endingLink_ = 7;
        scrollableLinks_ = true;
        createScrollText();
    } else if (scrollLinksVec_.size() <= 7) {
        endingLink_ = scrollLinksVec_.size() - 1;
    }
}

void Infobox::loop(const sf::Time& deltaTime) { }
void Infobox::update(const sf::Time& deltaTime) { }
void Infobox::render() { }
// void Infobox::helloWorld(int x) { }