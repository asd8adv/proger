#include "buttonManager.h"

ButtonManager::ButtonManager():selectedScreenId_(0){
}

void ButtonManager::setScreenId(int id) {
	selectedScreenId_ = id;
}

void ButtonManager::addButton(std::shared_ptr<BaseButton> btn, int id) {
	if (buttonsMap_.find(id) == buttonsMap_.end()) {
		buttonsMap_.emplace(id, std::make_shared<buttons>());
	}
	buttonsMap_[id].get()->push_back(btn);
	setScreenId(id);
}

void ButtonManager::checkColision(sf::Vector2i pos) {
	if (!buttonsMap_.size())
		return;
	if (!buttonsMap_.count(selectedScreenId_))
		return;
	std::for_each(buttonsMap_[selectedScreenId_].get()->begin(), buttonsMap_[selectedScreenId_].get()->end(), [pos](std::shared_ptr<BaseButton> btn) {
		btn->checkHover(sf::Vector2f(pos));
		});
}

void ButtonManager::update(float dt) {
	if (!buttonsMap_.size())
		return;
	if (!buttonsMap_.count(selectedScreenId_))
		return;
	std::for_each(buttonsMap_[selectedScreenId_].get()->begin(), buttonsMap_[selectedScreenId_].get()->end(), [dt](std::shared_ptr<BaseButton> btn) {
		btn->update(dt);
		});
}

void ButtonManager::mousePressed() {
	if (!buttonsMap_.size())
		return;
	if (!buttonsMap_.count(selectedScreenId_))
		return;
	std::for_each(buttonsMap_[selectedScreenId_].get()->begin(), buttonsMap_[selectedScreenId_].get()->end(), [](std::shared_ptr<BaseButton> btn) {
		btn->pressed();
		});
}

void ButtonManager::draw(sf::RenderWindow& wind) {
	if (!buttonsMap_.size())
		return;
	if (!buttonsMap_.count(selectedScreenId_))
		return;
	for (auto btn : *(buttonsMap_[selectedScreenId_]))
		btn->draw(wind);
};