#pragma once
#include <functional>
#include <utility>
#include <SFML/Graphics.hpp>
#include "magicBox.h"

class BaseButton :public BaseObject
{
public:
	enum class State {
		enabled = 0,
		pressed,
		disabled,
		unvisible
	};
protected:
	sf::Image img_;
	sf::Texture tex_;
	sf::Sprite sprite_;
	sf::Vector2u size_;
	sf::Vector2f pos_;
	State state_=State::enabled;
	float scale_=1.0f;

	//float borderScale_;
	bool enabled_=1;
	bool visible_=1;
	bool isHovered_=0;
	bool isScaled=0;
	float scaleTime_ = 0.5f;
	float hoverScale_ = 1.05f;
	const float SCALETIME_ = 0.5f;
	std::function<void()> callback_;

public:
	BaseButton(const std::string& resourceName, bool isUseMask = false) {
		img_.loadFromFile(resourceName);
		if (isUseMask)
			img_.createMaskFromColor(sf::Color(100, 100, 100));
		tex_.loadFromImage(img_);
		sprite_.setTexture(tex_);
		size_ = tex_.getSize();
	}

	template<typename F>
	void setCallback(F&& f) {
		callback_= std::forward<F>(f) ;
	}


	virtual void setState(State state) {
		state_ = state;
	}
	
	virtual void setScale(float scale) {
		scale_ = scale;
	}

	float getScale() {
		return scale_;
	}

	void virtual setSize(sf::Vector2u size) {
		size_=size;
	}

	virtual void setPosition(sf::Vector2f pos) {
		sprite_.setPosition(pos);
		pos_ = pos;
	}


	sf::Vector2f virtual getPosition() {
		return pos_;
	}

	sf::Vector2u virtual getSize() {
		return size_;
	}

	void updateScale(float dt) {
		if(isScaled){
			scaleTime_ -= dt;
			if (scaleTime_ > 0.3f) {
				scale_ = 1+0.5-scaleTime_;
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

	virtual void setDefaultColor() {
		sprite_.setColor(sf::Color(255, 255, 255, 255));
	}
	
	virtual void setGreyColor() {
		sprite_.setColor(sf::Color(128, 128, 128, 255));
	}

	virtual void update(float dt) {
		updateState();
		//updateScale(dt);
	}

	void pressed() {
		if(isHovered_)
			callback_();
	}

	void updateState() {
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
	
	virtual bool checkHover(sf::Vector2f pos) {
		return false;
	}
	
	void virtual draw(sf::RenderWindow& wind) {
		wind.draw(sprite_);
	}

	virtual void hovering(bool isHover) {
		if(isHover){
			if(state_==State::enabled){
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

	void virtual restorePosition() {
		sprite_.setPosition(pos_);
	}

};


class bigButton : public BaseButton
{
	using Base = BaseButton;

	std::string getFontResourceName() {
		return "res/impact.ttf";
	}
	sf::String description_;
	sf::Font fnt_;
	sf::Text text_;
	sf::Vector2f textDPos_;
public:
	bigButton(const std::string& resourceName, const sf::String& text, const sf::Vector2f& pos, bool isUseMask = false) :description_(text), Base(resourceName, isUseMask) {
		Base::setPosition(pos);
		fnt_.loadFromFile(getFontResourceName());
		text_.setString(description_);
		text_.setFont(fnt_);
		updateTextPos(sf::Vector2f(Base::getSize()));
	}

	virtual void setScale(float scale) override {
		if (scale != scale_) {
			Base::setScale(scale);
		}
	}

	virtual void update(float dt) {
		Base::update(dt);
		setScale(scale_);
	}

	virtual void draw(sf::RenderWindow& wind) override {
		Base::draw(wind);
		wind.draw(text_);
	}

	virtual void setPosition(sf::Vector2f pos){
		Base::setPosition(pos);
		setScale(scale_);
	}

	virtual void setTextDeltaPosition(sf::Vector2f pos) {
		textDPos_ = pos;
		sf::Vector2f size(Base::getSize());
		updateTextPos(size);
	}

	void updateTextPos(sf::Vector2f size) {
		auto scale = Base::getScale();
		auto iconPos = Base::getPosition();
		//iconPos *= scale;
		auto dPos = textDPos_;
		dPos *= scale;
		text_.setPosition(iconPos + dPos);
	}

	virtual void setSize(sf::Vector2f size) {
		Base::setSize({ unsigned(size.x),unsigned(size.y) });
		auto iconPos = Base::getPosition();
		updateTextPos(size);
		BaseObject::set(iconPos.x, iconPos.y, size.x, size.y);
	}

	virtual void hovering(bool isHover) override {
		Base::hovering(isHover);
		if (isHovered_) {
			text_.setColor(sf::Color::Red);
		}
		else {
			text_.setColor(sf::Color::Black);
		}
		sf::Vector2f size(Base::getSize());
		updateTextPos(size);
	}

	void virtual restorePosition() override {
		Base::restorePosition();
		sf::Vector2f size(Base::getSize());
		updateTextPos(size);
	}

	virtual bool checkHover(sf::Vector2f pos) override{//to do rename
		auto haveCollision = isCollision(*this, pos);
		if (haveCollision) {
			if(isHovered_!= haveCollision){
				isHovered_ = true;
				hovering(true);
			}
			return haveCollision;
		}
		isHovered_ = false;
		hovering(false);
		return haveCollision;
	}



};