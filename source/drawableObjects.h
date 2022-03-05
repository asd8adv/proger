#pragma once
#include <SFML/Graphics.hpp>
#include "button.h"
#include "drawable.h"

class DrawableButton :public BaseButton, public Drawable {
	using Base = BaseButton;
	using object = BaseObject;
	Drawable contour_;
protected:
	sf::Vector2f contourDiff;
	std::function<void()> callback_;
public:
	DrawableButton(const std::string& resourcename, const std::string& contourResourcename, bool isUseMask = false, bool contourIsUseMask = false);

	void setContourDiff(sf::Vector2f pos);

	virtual void setPosition(sf::Vector2f pos) override;

	void setVisible(bool value);

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

	void setContourDiff(sf::Vector2f pos);

};