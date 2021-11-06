#include "goal.h"

/*********************************
***********struct goal************
*********************************/

goal::goal() :current(0), required(0), goalEnd(0), Base("")
{
	fnt.loadFromFile(getFontResourceName());
	goalText.setFont(fnt);
	goalText.setColor(sf::Color::Black);
}

goal::goal(int cur, int req) :current(cur), required(req), goalEnd(0), Base("")
{
	fnt.loadFromFile(getFontResourceName());
	goalText.setFont(fnt);
	goalText.setColor(sf::Color::Black);
}

void goal::setPosition(sf::Vector2f pos) {
	goalText.setPosition(pos);
}


void goal::setDescription(std::string desc) {
	description = desc;
	updateDescription();
}
void goal::updateDescription() {
	std::string str = description;
	str += " ";
	str += std::to_string(current);
	str += "/";
	str += std::to_string(required);
	goalText.setString(str);
}

bool goal::isGoalEnd() {
	return goalEnd;
}

bool goal::increment(int value) {
	current += value;
	if (current > required) {
		current = required;
		goalEnd = true;
	}
	else {
		goalEnd = false;
	}
	if (current < 0) {
		current = 0;
	}
	updateDescription();
	return goalEnd;
}

void goal::draw(sf::RenderWindow& wnd) {
	if (visible_) {
		Base::draw(wnd);
		wnd.draw(goalText);
	}
}

/*********************************
**********struct jobGoal**********
*********************************/


/*********************************
*********struct GoalBlock*********
*********************************/



GoalBlock::GoalBlock() :
	stress(0, 100), 
	alcoholism(0, 100), 
	reputation(20, 100), 
	burnout(0, 80) 
{
	setPosition({ 200, 40 });
	stress.setDescription("stress");
	alcoholism.setDescription("alcoholism");
	reputation.setDescription("reputation");
	burnout.setDescription("burnout");
}

void GoalBlock::setPosition(sf::Vector2f pos) {
	stress.setPosition(pos);
	pos += {0, 28};
	alcoholism.setPosition(pos);
	pos += {0, 28};
	reputation.setPosition(pos);
	pos += {0, 28};
	burnout.setPosition(pos);
}

void GoalBlock::draw(sf::RenderWindow& wnd) {
	stress.draw(wnd);
	alcoholism.draw(wnd);
	reputation.draw(wnd);
	burnout.draw(wnd);
}

void GoalBlock::addParamValue(playerParams param, int count) {
	switch (param)
	{
	case playerParams::stress:
		if (stress.increment(count)) {
			Notificator::GetInstance()->notifListerens(EVENT::full_stress);
			addParamValue(playerParams::burnout, 10);
		}
		break;
	case playerParams::alco:
		if (alcoholism.increment(count)) {
			Notificator::GetInstance()->notifListerens(EVENT::full_alco);
		}
		break;
	case playerParams::reputation:
		if (reputation.increment(count)) {
			//Notificator::GetInstance()->notifListerens(EVENT::);
		}
		break;
	case playerParams::burnout:
		if (burnout.increment(count)) {
			//Notificator::GetInstance()->notifListerens(EVENT::);
		}
		break;
	default:
		break;
	}
}
