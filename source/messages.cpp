#include "messages.h"

/************************
***class playerMessage***
************************/

playerMessage::playerMessage() :Base("res/dialog.png", true) {
	Base::setPosition({ 1480,20 });
	Base::setVisible(0);
	Base::setScale({ 0.7,0.7 });
	fnt_.loadFromFile(getFontResourceName());
	Text_.setFont(fnt_);
	Text_.setPosition({ Base::getPosition().x + 10, Base::getPosition().y + 20 });
	Text_.setColor(sf::Color::Black);
	Text_.setCharacterSize(42);
	Base::visible_ = false;
}

void playerMessage::update(float dt) {
	visibleTime_ -= dt;
	if (visibleTime_ > 0) {
		Base::visible_ = true;
	}
	else {
		visibleTime_ = 0;
		Base::visible_ = false;
	}
}

void playerMessage::printMessage(const sf::String& str, float time) {
	Text_.setString(str);
	visibleTime_ = time;
}

void playerMessage::draw(sf::RenderWindow& wnd) {
	Base::draw(wnd);
	if (Base::visible_)
		wnd.draw(Text_);
}
