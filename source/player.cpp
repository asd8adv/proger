#include "player.h"

Player::Player() : NotificationObject() {
}

void Player::init() {
	subcribe(EVENT::day_is_change);
}

void Player::setGoalsPosition(sf::Vector2f pos) {
	goals_.setPosition(pos);
}

void Player::draw(sf::RenderWindow& wnd) {
	goals_.draw(wnd);
	msg_.draw(wnd);
}

void Player::addParamValue(playerParams param, int count) {
	goals_.addParamValue(param, count);
}

void Player::printMessage(const std::string & str, float time) {
	msg_.printMessage(str, time);
}

void Player::update(float dt) {
	msg_.update(dt);
}

void Player::onEvent(EVENT ev) {
	if (ev == EVENT::day_is_change) {
		msg_.printMessage(L"новый день!!!");
		addParamValue(playerParams::stress, -15);
		addParamValue(playerParams::alco, -20);
	}
	if (ev == EVENT::drink_alco) {
		drink();
	}

}

void Player::drink() {
	if (WallClock::GetInstance()->isHaveTime()) {
		addParamValue(playerParams::alco, 10);
		addParamValue(playerParams::stress, -5);
		WallClock::GetInstance()->nextTimeZone();
	}
	else {
		msg_.printMessage("enough alcohol for today");
	}
}

void Player::job() {
	if (WallClock::GetInstance()->isHaveTime()) {
		addParamValue(playerParams::stress, 15);
		addParamValue(playerParams::reputation, 1);
		WallClock::GetInstance()->nextTimeZone();
	}
	else {
		msg_.printMessage("not job!!!");
	}
}