#include "drawable.h"

/*****************
*****Drawable*****
*****************/

Drawable::Drawable(const std::string& resourcename, bool isUseMask) :visible_(true) {
	if (resourcename.size() != 0) {
		img_.loadFromFile(resourcename);
		if (isUseMask)
			img_.createMaskFromColor(sf::Color(100, 100, 100));
		tex_.loadFromImage(img_);
		Sprite_.setTexture(tex_);
	}
}

void Drawable::draw(sf::RenderWindow& wnd) {
	if (visible_) {
		wnd.draw(Sprite_);
	}
}

void Drawable::setVisible(bool vsbl) {
	visible_ = (vsbl);
}
void Drawable::setPosition(sf::Vector2f pos) {
	Sprite_.setPosition(pos);
}

sf::Vector2f Drawable::getPosition() {
	return Sprite_.getPosition();
}

void Drawable::setScale(sf::Vector2f scale) {
	Sprite_.setScale(scale);
}

/*****************
**DrawableButton**
*****************/
DrawableButton::DrawableButton(const std::string& resourcename, const std::string& contourResourcename, bool isUseMask, bool contourIsUseMask) :
	Base(resourcename, isUseMask),
	contourDiff({ 0,0 }),
	contour_(contourResourcename, contourIsUseMask) {
	auto size = Base::img_.getSize();
	object::height = size.y;
	object::width = size.x;
}

void DrawableButton::setContourDiff(sf::Vector2f pos) {
	contourDiff = pos;
}

void DrawableButton::setPosition(sf::Vector2f pos) {
	Base::setPosition(pos);
	contour_.setPosition({ pos.x + contourDiff.x,pos.y + contourDiff.y });
	object::x = pos.x;
	object::y = pos.y;
}

void DrawableButton::checkColision(sf::Vector2i value) {
	Base::hovered_ = isCollision(*this, sf::Vector2f(value));
	updateContour();
}

void DrawableButton::draw(sf::RenderWindow& wnd) {
	if (Base::visible_) {
		Base::draw(wnd);
		contour_.draw(wnd);
	}
}

void DrawableButton::updateContour() {
	contour_.setVisible(Base::hovered_);
}
/*****************
*****DrawableBar*****
*****************/

DrawableBar::DrawableBar() :
	bar_(),
	empty_(bar_.getBarResource(Bar::state::empty), bar_.getBarSelectedFrame(), false, true),
	half_(bar_.getBarResource(Bar::state::half), bar_.getBarSelectedFrame(), false, true),
	full_(bar_.getBarResource(Bar::state::full), bar_.getBarSelectedFrame(), false, true)
{
	curState_ = Bar::state::empty;
}

bool DrawableBar::empty() {
	return curState_ == Bar::state::empty;
}

void DrawableBar::setLessState() {
	auto st = int(curState_) - 1;
	st = st > 0 ? st : 0;
	setCurrentState(Bar::state(st));
}

void DrawableBar::setCurrentState(int st) {
	curState_ = Bar::state(st);
	updateBar();
}

void DrawableBar::setCurrentState(Bar::state st) {
	curState_ = st;
	updateBar();
}

void DrawableBar::updateBar() {
	empty_.setVisible(curState_ == Bar::state::empty);
	half_.setVisible(curState_ == Bar::state::half);
	full_.setVisible(curState_ == Bar::state::full);
}

void DrawableBar::draw(sf::RenderWindow& wnd) {
	empty_.draw(wnd);
	half_.draw(wnd);
	full_.draw(wnd);
}

void DrawableBar::setPosition(sf::Vector2f pos) {
	empty_.setPosition(pos);
	half_.setPosition(pos);
	full_.setPosition(pos);
}

void DrawableBar::checkColision(sf::Vector2i value) {
	empty_.checkColision(value);
	half_.checkColision(value);
	full_.checkColision(value);
}


void DrawableBar::setContourDiff(sf::Vector2f pos) {
	empty_.setContourDiff(pos);
	half_.setContourDiff(pos);
	full_.setContourDiff(pos);
}


