#pragma once
#include "SFML/Graphics.hpp"
#include "Data.hpp"
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Textlink {
public:
	Textlink(string stringText, sf::Font font, int size, vector<string> onClick);
	~Textlink();
	// void setText();
	// void setOnClick();
	sf::Text& getText();
	vector<string> getOnClick();
	void setPosition(float x, float y);
	void setUnderline();
	void setColor(int i);
	void setSelected(bool selected);
	
private:
	sf::Font font_;
    sf::Text text_;
    vector<string> onClick_;
	bool selected_;
};