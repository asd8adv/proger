#pragma once
#include "drawable.h"
#include "notificator.h"

enum class playerParams {
	stress = 0,
	alco = 1,
	reputation,//in work 
	burnout
};


struct goal : public Drawable {
protected:
	using Base = Drawable;
	std::string getSpriteResourceName() {
		return "res/ss.png";
	}

	std::string getFontResourceName() {
		return "res/impact.ttf";
	}
public:
	sf::String description_;
	sf::Font fnt_;
	sf::Text goalText_;
	int current_;
	int required_;
	bool goalEnd_;


	goal();
	goal(int cur, int req);

	virtual void setPosition(sf::Vector2f pos);

	void setDescription(sf::String desc);

	void updateDescription();

	virtual void draw(sf::RenderWindow& wnd);

	bool increment(int value);

	bool isGoalEnd();
};


struct jobGoal :public goal, NotificationObject {
	using Base = goal;
public:
	jobGoal() :Base(0, 50)
	{

	}

	virtual void onEvent(EVENT ev) override {
		if (ev == EVENT::week_is_change) {
			if (Base::goalEnd_) {

			}
			else {

			}
			//todo
		}
	}

};

//настройка баланса(лол)
struct GoalBlock {
	goal stress;
	goal alcoholism;
	goal reputation;
	goal burnout;

	GoalBlock();

	void setPosition(sf::Vector2f pos);

	void addParamValue(playerParams param, int count);

	void draw(sf::RenderWindow& wnd);


};
