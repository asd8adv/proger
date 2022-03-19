#pragma once
#include "buttonManager.h"
#include "drawable.h"
#include "goal.h"
#include "wallClock.h"
#include "messages.h"
#include "staticData.h"

enum class playerType {
	cpp = 1,
	js,
	python
};


//

/*
void Player::setGoalsPosition(sf::Vector2f pos) {
	goals_.setPosition(pos);
}

void Player::addParamValue(playerParams param, int count) {
	goals_.addParamValue(param, count);
}

*/

class Player :public  NotificationObject {
	std::shared_ptr<PlayerStatistics> statistics_;
	std::shared_ptr<playerMessage> msg_;
	std::string playerSpecific = "cpp";// progpamm lang cpp/python/js
	std::map<stats, std::vector<int>> playerbonus;
public:
	Player();

	void init();

	void drawMsg(sf::RenderWindow& wnd);

	void printMessage(const std::string& str, float time = 10);

	void update(float dt);

	void onEvent(EVENT ev) override;

	int getPlayerStats(stats stat);

	std::shared_ptr<PlayerStatistics> getStatistics();

	void drink();

	void job();

	std::shared_ptr<playerMessage> getMessagePrinter();
};
