#include "player.h"

Player::Player() : NotificationObject() {
}

void Player::init() {
	statistics_ = std::make_shared<PlayerStatistics>();
	msg_ = std::make_shared<playerMessage>();
	subcribe(EVENT::day_is_change);
}

void Player::drawMsg(sf::RenderWindow& wnd) {
	msg_->draw(wnd);
}

void Player::printMessage(const std::string & str, float time) {
	msg_->printMessage(str, time);
}

void Player::update(float dt) {
	msg_->update(dt);
}

void Player::onEvent(EVENT ev){
	if (ev == EVENT::day_is_change) {
		msg_->printMessage(L"новый день!!!");
		statistics_->addParamValue(playerParams::stress, -15);
		statistics_->addParamValue(playerParams::alco, -20);
	}
	if (ev == EVENT::drink_alco) {
		drink();
	}
}


int Player::getPlayerStats(stats stat) {
	auto stats = StaticData::GetInstance()->getStats(playerSpecific);
	int bonus = 0;
	auto bonuses = playerbonus[stat];
	if(playerbonus.count(stat))	{
		auto vec = playerbonus[stat];
		for (auto it : vec) {
			bonus += it;
		}
	}
	return bonus + stats->getStat(stat);
}

std::shared_ptr<PlayerStatistics> Player::getStatistics() {
	return statistics_;
}

void Player::drink() {
	if (WallClock::GetInstance()->isHaveTime()) {
		statistics_->addParamValue(playerParams::alco, 10);
		statistics_->addParamValue(playerParams::stress, -5);
		WallClock::GetInstance()->nextTimeZone();
	}
	else {
		msg_->printMessage("enough alcohol for today");
	}
}

void Player::job() {
	if (WallClock::GetInstance()->isHaveTime()) {
		statistics_->addParamValue(playerParams::stress, 15);
		statistics_->addParamValue(playerParams::reputation, 1);
		WallClock::GetInstance()->nextTimeZone();
	}
	else {
		msg_->printMessage("not job!!!");
	}
}


std::shared_ptr<playerMessage> Player::getMessagePrinter() {
	return msg_;
}
