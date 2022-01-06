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
	void virtual setPosition(sf::Vector2f pos);
    
	sf::Vector2f getPosition();

	void virtual checkColision(sf::Vector2i value) {
		return;
	}
	void virtual pressed() {
		return;
	}

	void virtual draw(sf::RenderWindow& wnd);
};

class DrawableButton :public Drawable, BaseObject {
	using Base = Drawable;
	using object = BaseObject;
	Drawable contour_;
protected:
	sf::Vector2f contourDiff;
	bool visible_;
	bool isHovered_;
	std::function<void()> callback_;
public:
	DrawableButton(const std::string& resourcename, const std::string& contourResourcename, bool isUseMask = false, bool contourIsUseMask = false) :
		Base(resourcename, isUseMask),
		contourDiff({ 0,0 }), 
		contour_(contourResourcename, contourIsUseMask) {
		auto size = img_.getSize();
		object::height = size.y;
		object::width = size.x;
	}

	template<typename F>
	void setCallback(F&& f) {
		callback_ = std::forward<F>(f);
	}

	void virtual pressed() override {
		if (isHovered_)
			callback_();
	}

	void setContourDiff(sf::Vector2f pos) {
		contourDiff = pos;
	}

	void virtual setPosition(sf::Vector2f pos) override {
		Base::setPosition(pos);
		contour_.setPosition({ pos.x + contourDiff.x,pos.y + contourDiff.y });
		object::x = pos.x;
		object::y = pos.y;
	}
	
	void virtual checkColision(sf::Vector2i value) override {
		isHovered_ = isCollision(*this, sf::Vector2f(value));
		updateContour();
	}

	void virtual draw(sf::RenderWindow& wnd) override {
		Base::draw(wnd);
		contour_.draw(wnd);
	}

	void updateContour() {
		contour_.setVisible(isHovered_);
	}

};

