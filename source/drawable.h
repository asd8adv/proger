#pragma once
#include <SFML/Graphics.hpp>
#include "notificator.h"
#include "magicBox.h"
#include <functional>


class Drawable :public NotificationObject {
protected:
    sf::Image img_;
    sf::Texture tex_;
    sf::Sprite Sprite_;
    bool visible_;
public:
	Drawable() {};
	Drawable(const std::string& resourcename, bool isUseMask = false);

	void setVisible(bool vsbl);
	void setScale(sf::Vector2f scale);
	virtual void setPosition(sf::Vector2f pos);
    
	sf::Vector2f getPosition();

	virtual void checkColision(sf::Vector2i value) {
		return;
	}
	virtual void pressed() {
		return;
	}

	virtual void draw(sf::RenderWindow& wnd);
};





