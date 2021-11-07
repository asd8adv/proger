#include "button.h"

/***************************
******class BaseButton******
***************************/

BaseButton::BaseButton(const std::string& resourceName, bool isUseMask) {
	img_.loadFromFile(resourceName);
	if (isUseMask)
		img_.createMaskFromColor(sf::Color(100, 100, 100));
	tex_.loadFromImage(img_);
	sprite_.setTexture(tex_);
	size_ = tex_.getSize();
}

void BaseButton::setState(State state) {
	state_ = state;
}

void BaseButton::setScale(float scale) {
	scale_ = scale;
}

float BaseButton::getScale() {
	return scale_;
}

void BaseButton::setSize(sf::Vector2u size) {
	size_ = size;
}

void BaseButton::setPosition(sf::Vector2f pos) {
	sprite_.setPosition(pos);
	pos_ = pos;
}


sf::Vector2f BaseButton::getPosition() {
	return pos_;
}

sf::Vector2u BaseButton::getSize() {
	return size_;
}

void BaseButton::updateScale(float dt) {
	if (scaled_) {
		scaleTime_ -= dt;
		if (scaleTime_ > 0.3f) {
			scale_ = 1 + 0.5 - scaleTime_;
		}
		if (scaleTime_ > 0.2f && scaleTime_ < 0.3f) {
			scale_ = 1.2;
		}
		if (scaleTime_ < 0.2f) {
			scale_ = 1 + scaleTime_;
		}
	}
	else {
		scaleTime_ = SCALETIME_;
		scale_ = 1;
	}
}

void BaseButton::setDefaultColor() {
	sprite_.setColor(sf::Color(255, 255, 255, 255));
}

void  BaseButton::setGreyColor() {
	sprite_.setColor(sf::Color(128, 128, 128, 255));
}

void BaseButton::update(float dt) {
	updateState();
	//updateScale(dt);
}

void BaseButton::pressed() {
	if (hovered_)
		callback_();
}

void BaseButton::updateState() {
	switch (state_) {
	case BaseButton::State::enabled:
		setDefaultColor();
		enabled_ = true;
		visible_ = true;
		break;
	case BaseButton::State::pressed:
		setDefaultColor();
		if (enabled_ && visible_)
			callback_();//???
		break;
	case BaseButton::State::disabled:
		setGreyColor();
		enabled_ = false;
		visible_ = true;
		break;
	case BaseButton::State::unvisible:
		setDefaultColor();//допилить

		enabled_ = false;
		visible_ = false;
		break;
	default:
		break;
	};

}

bool BaseButton::checkHover(sf::Vector2f pos) {
	return false;
}

void BaseButton::draw(sf::RenderWindow& wind) {
	wind.draw(sprite_);
}

void BaseButton::hovering(bool isHover) {
	if (isHover) {
		if (state_ == State::enabled) {
			setScale(hoverScale_);
			auto basePos = sprite_.getPosition();
			sprite_.setScale(hoverScale_, hoverScale_);
			auto baseSize = size_;
			if (scale_ > 1.0f) {
				auto dpos = sf::Vector2f(size_.x * (scale_ - 1.0) * 0.5f, size_.y * (scale_ - 1.0) * 0.5f);
				sprite_.setPosition(basePos - dpos);
			}
		}
	}
	else {
		setScale(1.0f);
		sprite_.setScale(scale_, scale_);
		restorePosition();
	}
}

void BaseButton::restorePosition() {
	sprite_.setPosition(pos_);
}

/***************************
******class bigButton******
***************************/

bigButton::bigButton(const std::string& resourceName, const sf::String& text, const sf::Vector2f& pos, bool isUseMask) :description_(text), Base(resourceName, isUseMask) {
	Base::setPosition(pos);
	fnt_.loadFromFile(getFontResourceName());
	text_.setString(description_);
	text_.setFont(fnt_);
	updateTextPos(sf::Vector2f(Base::getSize()));
}

void bigButton::bigButton::setScale(float scale) {
	if (scale != scale_) {
		Base::setScale(scale);
	}
}

void bigButton::update(float dt) {
	Base::update(dt);
	setScale(scale_);
}

void bigButton::draw(sf::RenderWindow& wind) {
	Base::draw(wind);
	wind.draw(text_);
}

void bigButton::setPosition(sf::Vector2f pos) {
	Base::setPosition(pos);
	setScale(scale_);
}

void bigButton::setTextDeltaPosition(sf::Vector2f pos) {
	textDPos_ = pos;
	sf::Vector2f size(Base::getSize());
	updateTextPos(size);
}

void bigButton::updateTextPos(sf::Vector2f size) {
	auto scale = Base::getScale();
	auto iconPos = Base::getPosition();
	//iconPos *= scale;
	auto dPos = textDPos_;
	dPos *= scale;
	text_.setPosition(iconPos + dPos);
}

void bigButton::setSize(sf::Vector2f size) {
	Base::setSize({ unsigned(size.x),unsigned(size.y) });
	auto iconPos = Base::getPosition();
	updateTextPos(size);
	BaseObject::set(iconPos.x, iconPos.y, size.x, size.y);
}

void bigButton::hovering(bool isHover) {
	Base::hovering(isHover);
	if (hovered_) {
		text_.setColor(sf::Color::White);
	}
	else {
		text_.setColor(sf::Color::Black);
	}
	sf::Vector2f size(Base::getSize());
	updateTextPos(size);
}

void bigButton::restorePosition() {
	Base::restorePosition();
	sf::Vector2f size(Base::getSize());
	updateTextPos(size);
}

bool bigButton::checkHover(sf::Vector2f pos) {//to do rename
	auto haveCollision = isCollision(*this, pos);
	if (haveCollision) {
		if (hovered_ != haveCollision) {
			hovered_ = true;
			hovering(true);
		}
		return haveCollision;
	}
	hovered_ = false;
	hovering(false);
	return haveCollision;
}