#include "calendar.h"


Calendar::Calendar(sf::Vector2f pos, bool isUseMask) :
	Base(getSpriteResourceName(), isUseMask),
	week(1),
	day(1)
{
	Base::setPosition(pos);
	fnt.loadFromFile(getFontResourceName());
	setDate(1, 1, false);
	dayText_.setFont(fnt);
	weekText_.setFont(fnt);
	dayText_.setCharacterSize(42);
	weekText_.setCharacterSize(42);
	dayText_.setPosition(pos.x + 70, pos.y + 180);
	weekText_.setPosition(pos.x + 70, pos.y + 60);
	dayText_.setFillColor(sf::Color::Black);
	weekText_.setFillColor(sf::Color::Black);
}

void Calendar::nextDay() {
	if (day == 7) {
		setDay(1, true);
		setWeek(week + 1, true);
	}
	else {
		setDay(day + 1, true);
	}

}
void Calendar::setDate(int week, int day, bool change) {
	setWeek(week, change);
	setDay(day, change);
}

void Calendar::setWeek(int value, bool change) {
	week = value;
	if (change)
		onWeekChange();
	weekText_.setString(std::to_string(week));
}

void Calendar::setDay(int value, bool change) {
	day = value;
	if (change)
		onDayChange();
	dayText_.setString(std::to_string(day));
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