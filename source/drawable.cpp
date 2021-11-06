#include "drawable.h"

Drawable::Drawable(const std::string& resourcename, bool isUseMask) :visible_(true) {
	if (resourcename.size() != 0) {
		img_.loadFromFile(resourcename);
		if (isUseMask)
			img_.createMaskFromColor(sf::Color(100, 100, 100));
		tex_.loadFromImage(img_);
		Sprite_.setTexture(tex_);
	}
}

void Drawable::draw(sf::RenderWindow& wnd) {
	if (visible_) {
		wnd.draw(Sprite_);
	}
}

void Drawable::setVisible(bool vsbl) {
	visible_ = (vsbl);
}
void Drawable::setPosition(sf::Vector2f pos) {
	Sprite_.setPosition(pos);
}

sf::Vector2f Drawable::getPosition() {
	return Sprite_.getPosition();
}

void Drawable::setScale(sf::Vector2f scale) {
	Sprite_.setScale(scale);
}