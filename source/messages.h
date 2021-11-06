#pragma once
#include <SFML/Graphics.hpp>
#include "drawable.h"

class playerMessage : public Drawable {
	using Base = Drawable;
	float visibleTime = 0;
	sf::Font fnt;
	sf::Text Text_;

	std::string getFontResourceName() {
		return "res/impact.ttf";
	}
public:
	playerMessage() :Base("res/dialog.png", true) {
		Base::setPosition({ 1480,20 });
		Base::setVisible(0);
		Base::setScale({ 0.7,0.7 });
		fnt.loadFromFile(getFontResourceName());
		Text_.setFont(fnt);
		Text_.setPosition({ Base::getPosition().x + 10, Base::getPosition().y + 20 });
		Text_.setColor(sf::Color::Black);
		Text_.setCharacterSize(42);
		Base::visible_ = false;
	}

	void update(float dt) {
		visibleTime -= dt;
		if (visibleTime > 0) {
			Base::visible_ = true;
		}
		else {
			visibleTime = 0;
			Base::visible_ = false;
		}
	}

	void printMessage(const sf::String& str, float time = 5) {
		Text_.setString(str);
		visibleTime = time;
	}

	void virtual draw(sf::RenderWindow& wnd) override {
		Base::draw(wnd);
		if (Base::visible_)
			wnd.draw(Text_);
	}

};