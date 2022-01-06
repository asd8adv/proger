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

class DrawableButton :public Drawable, BaseObject {
	using Base = Drawable;
	using object = BaseObject;
	Drawable contour_;
protected:
	sf::Vector2f contourDiff;
	bool isHovered_;
	std::function<void()> callback_;
public:
	DrawableButton(const std::string& resourcename, const std::string& contourResourcename, bool isUseMask = false, bool contourIsUseMask = false);

	template<typename F>
	void setCallback(F&& f) {
		callback_ = std::forward<F>(f);
	}

	virtual void pressed() override;

	void setContourDiff(sf::Vector2f pos);

	virtual void setPosition(sf::Vector2f pos) override;
	
	virtual void checkColision(sf::Vector2i value) override;

	virtual void draw(sf::RenderWindow& wnd) override;

	void updateContour();
};


struct Bar {
	enum class state : int {
		empty = 0,
		half = 1,
		full = 2
	};
	const std::string getBarResource(state st) const {
		switch (st) {
		case state::full:
			return "res/nw/mini_bar_full.png";
		case state::half:
			return "res/nw/mini_bar_half.png";
		case state::empty:
		default:
			return "res/nw/mini_bar_empty.png";
		}
	}

	const std::string getBarSelectedFrame() {
		return "res/nw/mini_bar_selected.png";
	};

};

class DrawableBar : public Drawable {
	Bar bar_;
	DrawableButton empty_;
	DrawableButton half_;
	DrawableButton full_;
	Bar::state curState_;
public:
	DrawableBar();

	bool empty();

	void setLessState();

	void setCurrentState(int st);

	void setCurrentState(Bar::state st);

	void updateBar();

	virtual void draw(sf::RenderWindow& wnd) override;

	virtual void setPosition(sf::Vector2f pos) override;

	virtual void checkColision(sf::Vector2i value) override;

};



