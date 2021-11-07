#pragma once
#include <SFML/Graphics.hpp>
#include "notificator.h"

class Drawable :NotificationObject {
protected:
    sf::Image img_;
    sf::Texture tex_;
    sf::Sprite Sprite_;
    bool visible_;
public:
	Drawable(const std::string& resourcename, bool isUseMask = false);

	void setVisible(bool vsbl);
	void setScale(sf::Vector2f scale);
	void virtual setPosition(sf::Vector2f pos);
    
	sf::Vector2f getPosition();

	void virtual draw(sf::RenderWindow& wnd);
};
