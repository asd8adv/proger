#include "calendar.h"


Calendar::Calendar(sf::Vector2f pos, bool isUseMask) :
	Base(getSpriteResourceName(), isUseMask),
	week_(1),
	day_(1)
{
	Base::setPosition(pos);
	fnt_.loadFromFile(getFontResourceName());
	setDate(1, 1, false);
	dayText_.setFont(fnt_);
	weekText_.setFont(fnt_);
	dayText_.setCharacterSize(42);
	weekText_.setCharacterSize(42);
	dayText_.setPosition(pos.x + 50, pos.y + 195);
	weekText_.setPosition(pos.x + 50, pos.y + 95);
	dayText_.setFillColor(sf::Color::Black);
	weekText_.setFillColor(sf::Color::Black);
}

void Calendar::nextDay() {
	if (day_ == 7) {
		setDay(1, true);
		setWeek(week_ + 1, true);
	}
	else {
		setDay(day_ + 1, true);
	}

}
void Calendar::setDate(int week, int day, bool change) {
	setWeek(week, change);
	setDay(day, change);
}

void Calendar::setWeek(int value, bool change) {
	week_ = value;
	if (change)
		onWeekChange();
	weekText_.setString(std::to_string(week_));
}

void Calendar::setDay(int value, bool change) {
	day_ = value;
	if (change)
		onDayChange();
	dayText_.setString(std::to_string(day_));
}

void Calendar::draw(sf::RenderWindow& wnd) {
	Base::draw(wnd);
	wnd.draw(dayText_);
	wnd.draw(weekText_);
}

void Calendar::onWeekChange() {
	Notificator::GetInstance()->notifListerens(EVENT::week_is_change);
}

void Calendar::onDayChange() {
	Notificator::GetInstance()->notifListerens(EVENT::day_is_change);
}