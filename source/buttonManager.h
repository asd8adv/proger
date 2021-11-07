#pragma once
#include "button.h"
#include <vector>
#include <map>
#include <memory>
#include <algorithm>



class ButtonManager
{
	using buttons = std::vector<std::shared_ptr<BaseButton>>;
	int selectedScreenId_;
	std::map<int, std::shared_ptr<buttons>> buttonsMap_ ;// key - its id window, value - its vector<button> for this window 
public:
	ButtonManager();

	void setScreenId(int id);

	void addButton(std::shared_ptr<BaseButton> btn, int id);

	void checkColision(sf::Vector2i pos);

	void update(float dt);
	
	void mousePressed();

	virtual void draw(sf::RenderWindow& wind);

private:

};