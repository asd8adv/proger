#include "goal.h"
#include "dictionary.h"
/*********************************
***********struct goal************
*********************************/

goal::goal() :current_(0), required_(0), goalEnd_(0), Base("")
{
	fnt_.loadFromFile(getFontResourceName());
	goalText_.setFont(fnt_);
	goalText_.setColor(sf::Color::Black);
}

goal::goal(int cur, int req) :current_(cur), required_(req), goalEnd_(0), Base("")
{
	fnt_.loadFromFile(getFontResourceName());
	goalText_.setFont(fnt_);
	goalText_.setColor(sf::Color::Black);
}

void goal::setPosition(sf::Vector2f pos) {
	goalText_.setPosition(pos);
}


void goal::setDescription(sf::String desc) {
	description_ = desc;
	updateDescription();
}

void goal::updateDescription() {
	sf::String str = description_;
	str += L" ";
	str += sf::String(std::to_string(current_));
	str += L"/";
	str += sf::String(std::to_string(required_));
	goalText_.setString(str);
}

bool goal::isGoalEnd() {
	return goalEnd_;
}

bool goal::increment(int value) {
	current_ += value;
	if (current_ > required_) {
		current_ = required_;
		goalEnd_ = true;
	}
	else {
		goalEnd_ = false;
	}
	if (current_ < 0) {
		current_ = 0;
	}
	updateDescription();
	return goalEnd_;
}

void goal::draw(sf::RenderWindow& wnd) {
	if (visible_) {
		Base::draw(wnd);
		wnd.draw(goalText_);
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
	stress.setDescription(Dictionary::GetInstance()->getString(World::stress));
	alcoholism.setDescription(Dictionary::GetInstance()->getString(World::alcoholism));
	reputation.setDescription(Dictionary::GetInstance()->getString(World::reputation));
	burnout.setDescription(Dictionary::GetInstance()->getString(World::burnout));
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
