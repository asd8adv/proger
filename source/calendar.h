#pragma once
#include "drawable.h"

class Calendar : public Drawable {
	using Base = Drawable;
	int week;
	int day;
	sf::Font fnt;
	sf::Text dayText_;
	sf::Text weekText_;

	std::string getSpriteResourceName() {
		return "res/calendar.png";
	}

	std::string getFontResourceName() {
		return "res/impact.ttf";
	}

public:
	Calendar(sf::Vector2f pos, bool isUseMask = false);

	void nextDay();

	void setDate(int week, int day, bool change = true);

	void setWeek(int value, bool change);

	void setDay(int value, bool change);

	void draw(sf::RenderWindow& wnd);

	void onWeekChange();

	void onDayChange();

};