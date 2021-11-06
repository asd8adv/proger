#pragma once
#include "buttonManager.h"
#include "drawable.h"
#include "goal.h"
#include "wallClock.h"
#include "messages.h"

class Player :public  NotificationObject {
	GoalBlock goals_;
	playerMessage msg_;
public:
	Player();

	void init();

	void setGoalsPosition(sf::Vector2f pos);

	void draw(sf::RenderWindow& wnd);

	void addParamValue(playerParams param, int count);

	void printMessage(const std::string& str, float time = 10);

	void update(float dt);

	void onEvent(EVENT ev) override;

	void drink();

	void job();
};
