#pragma once
#include <SFML/Graphics.hpp>
#include "drawable.h"

class playerMessage : public Drawable {
	using Base = Drawable;
	float visibleTime_ = 0;
	sf::Font fnt_;
	sf::Text Text_;

	std::string getFontResourceName() {
		return "res/impact.ttf";
	}
public:
	playerMessage();

	void update(float dt);

	void printMessage(const sf::String& str, float time = 5);

	void virtual draw(sf::RenderWindow& wnd) override;

};