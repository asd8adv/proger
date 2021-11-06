#include "wallClock.h"

/************************
*****class WallClock*****
************************/


WallClock::WallClock() : selectedClock_(0), clockCount_(5)
{}

void WallClock::nextTimeZone() {
	if (clockCount_ > selectedClock_) {
		selectedClock_++;
		Notificator::GetInstance()->notifListerens(EVENT::time_zone_next);
	}
	Notificator::GetInstance()->notifListerens(EVENT::time_is_up);
}

bool WallClock::isHaveTime() {
	return selectedClock_ != clockCount_ - 1;
}

void WallClock::dayChange() {
	selectedClock_ = 0;
}

WallClock* WallClock::GetInstance() {
	if (WallClockInstance == nullptr) {
		WallClockInstance = new WallClock();
	}
	return WallClockInstance;
}

WallClock* WallClock::WallClockInstance = nullptr;;


/************************
*class WallClockDrawable*
************************/


WallClockDrawable::WallClockDrawable() :selectedClock_(0) {
	clocks_.reserve(8);
	clocks_.emplace_back(std::make_shared<Drawable>("res/time0.png", true));
	clocks_.emplace_back(std::make_shared<Drawable>("res/time14.png", true));
	clocks_.emplace_back(std::make_shared<Drawable>("res/time24.png", true));
	clocks_.emplace_back(std::make_shared<Drawable>("res/time34.png", true));
	clocks_.emplace_back(std::make_shared<Drawable>("res/time44.png", true));
}
void WallClockDrawable::init() {
	subcribe(EVENT::time_zone_next);
	subcribe(EVENT::day_is_change);
}

WallClockDrawable::~WallClockDrawable() {
	subcribe(EVENT::time_zone_next, false);
	subcribe(EVENT::day_is_change, false);
}

void WallClockDrawable::draw(sf::RenderWindow& wind) {
	if (clocks_.size() > selectedClock_) {
		clocks_[selectedClock_]->draw(wind);
	}
}

void WallClockDrawable::onEvent(EVENT ev) {
	if (ev == EVENT::time_zone_next) {
		selectedClock_++;
	}
	if (ev == EVENT::day_is_change) {
		selectedClock_ = 0;
		WallClock::GetInstance()->dayChange();
	}
}

void WallClockDrawable::setPosition(sf::Vector2f vec) {
	for (auto it : clocks_) {
		it->setPosition(vec);
	}
}

void WallClockDrawable::setScale(sf::Vector2f vec) {
	for (auto it : clocks_) {
		it->setScale(vec);
	}
}
