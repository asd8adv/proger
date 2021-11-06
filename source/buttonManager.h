#pragma once
#include "button.h"
#include <vector>
#include <map>
#include <memory>
#include <algorithm>


using buttons = std::vector<std::shared_ptr<BaseButton>>;

class ButtonManager
{
	int selectedScreenId;
	std::map<int, std::shared_ptr<buttons>> buttonsMap ;// key - its id window, value - its vector<button> for this window 
public:
	ButtonManager() {
	}
	void setScreenId(int id) {
		selectedScreenId = id;
	}
	void addButton(std::shared_ptr<BaseButton> btn, int id) {
		if (buttonsMap.find(id) == buttonsMap.end()) {
			buttonsMap.emplace(id, std::make_shared<buttons>());
		}
		buttonsMap[id].get()->push_back(btn);
		setScreenId(id);
	}

	void checkColision(sf::Vector2i pos) {
		buttonsMap[selectedScreenId].get();
		std::for_each(buttonsMap[selectedScreenId].get()->begin(), buttonsMap[selectedScreenId].get()->end(), [pos](std::shared_ptr<BaseButton> btn) {
			btn->checkHover(sf::Vector2f(pos));
		});
	}

	void update(float dt) {
		std::for_each(buttonsMap[selectedScreenId].get()->begin(), buttonsMap[selectedScreenId].get()->end(), [dt](std::shared_ptr<BaseButton> btn) {
			btn->update(dt);
		});
	}
	
	void mousePressed() {
		std::for_each(buttonsMap[selectedScreenId].get()->begin(), buttonsMap[selectedScreenId].get()->end(), [](std::shared_ptr<BaseButton> btn) {
			btn->pressed();
			});
	}

	virtual void draw(sf::RenderWindow& wind) {
		for(auto btn: *(buttonsMap[selectedScreenId]))
			btn->draw(wind);
	};

private:

};