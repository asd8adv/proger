#pragma once
#include <functional>
#include <utility>
#include <SFML/Graphics.hpp>
#include "magicBox.h"

class HoveredObject {
protected:
	bool hovered_ = 0;
	float hoverScale_ = 1.05f;
public:
	std::function<void()> callbackHover_;
	std::function<void()> callbackUnhover_;

	virtual void hovering() 
	{};
};

class BaseButton :public BaseObject, public HoveredObject
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
	State state_ = State::enabled;
	float scale_ = 1.0f;

	bool enabled_ = 1;
	bool visible_ = 1;
	bool scaled_ = 0;
	std::function<void()> callback_;

public:
	BaseButton(const std::string& resourceName, bool isUseMask = false);

	template<typename F>
	void setCallback(F&& f) {
		callback_ = std::forward<F>(f);
	}
	virtual void hovering() override;
	virtual void onHovering() {};
	virtual void onHoveringEnd() {};
	virtual void setState(State state);
	virtual void setScale(float scale);
	virtual void setSize(sf::Vector2u size);
	virtual void setPosition(sf::Vector2f pos);
	virtual void setDefaultColor();
	virtual void setGreyColor();

	virtual sf::Vector2f getPosition();
	virtual sf::Vector2u getSize();
	float getScale();

	virtual void update(float dt);
	void updateState();

	virtual bool checkHover(sf::Vector2f pos);

	void pressed();

	virtual void restorePosition();

	virtual void draw(sf::RenderWindow& wind);
};


class BigButton : public BaseButton
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
	BigButton(const std::string& resourceName, const sf::String& text, const sf::Vector2f& pos, bool isUseMask = false);

	void onHovering() override;
	void onHoveringEnd() override;

	virtual void setScale(float scale) override;
	virtual void setPosition(sf::Vector2f pos);
	virtual void setSize(sf::Vector2f size);
	virtual void setTextDeltaPosition(sf::Vector2f pos);

	virtual void update(float dt) override;
	void updateTextPos(sf::Vector2f size);


	virtual void hovering() override;
	virtual bool checkHover(sf::Vector2f pos) override;

	virtual void restorePosition() override;

	virtual void draw(sf::RenderWindow& wind) override;
};

/*
* todo
class iconButton :BaseButton {

};
*/