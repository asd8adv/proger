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
	State state_ = State::enabled;
	float scale_ = 1.0f;

	bool enabled_ = 1;
	bool visible_ = 1;
	bool hovered_ = 0;
	bool scaled_ = 0;
	float scaleTime_ = 0.5f;
	float hoverScale_ = 1.05f;
	const float SCALETIME_ = 0.5f;
	std::function<void()> callback_;

public:
	BaseButton(const std::string& resourceName, bool isUseMask = false);

	template<typename F>
	void setCallback(F&& f) {
		callback_ = std::forward<F>(f);
	}

	virtual void setState(State state);
	virtual void setScale(float scale);
	void virtual setSize(sf::Vector2u size);
	virtual void setPosition(sf::Vector2f pos);
	virtual void setDefaultColor();
	virtual void setGreyColor();

	sf::Vector2f virtual getPosition();
	sf::Vector2u virtual getSize();
	float getScale();

	virtual void update(float dt);
	void updateScale(float dt);
	void updateState();

	virtual bool checkHover(sf::Vector2f pos);
	virtual void hovering(bool isHover);

	void pressed();

	void virtual restorePosition();

	void virtual draw(sf::RenderWindow& wind);
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
	bigButton(const std::string& resourceName, const sf::String& text, const sf::Vector2f& pos, bool isUseMask = false);

	virtual void setScale(float scale) override;
	virtual void setPosition(sf::Vector2f pos);
	virtual void setSize(sf::Vector2f size);
	virtual void setTextDeltaPosition(sf::Vector2f pos);

	virtual void update(float dt) override;
	void updateTextPos(sf::Vector2f size);

	virtual void hovering(bool isHover) override;
	virtual bool checkHover(sf::Vector2f pos) override;

	void virtual restorePosition() override;

	virtual void draw(sf::RenderWindow& wind) override;
};