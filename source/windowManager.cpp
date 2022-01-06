#include "windowManager.h"

class WindowManager;
WindowManager* windowManager = nullptr;
/***************
***BaseWindow***
***************/

BaseWindow::BaseWindow(int num) :wndNumber(num)
{};

BaseWindow::BaseWindow(window_type wind) :wndNumber(static_cast<int>(wind))
{};

void BaseWindow::show() {
	visible = true;
}

void BaseWindow::close() {
	visible = false;
}

int BaseWindow::getWindowId() {
	return wndNumber;
}

void BaseWindow::checkColision(sf::Vector2i pos) {
	std::for_each(drawObjects_.begin(), drawObjects_.end(), [pos](drawablePtr obj) {
		obj->checkColision(pos);
	});
}

void BaseWindow::onPressed() {
	std::for_each(drawObjects_.begin(), drawObjects_.end(), [](drawablePtr obj) {
		obj->pressed();
	});
}

void BaseWindow::draw(sf::RenderWindow& wind) {
	if (!visible)
		return;
	for (auto it : drawObjects_) {
		it->draw(wind);
	}
}

void BaseWindow::addDrawableObject(drawablePtr draw) {
	drawObjects_.push_back(draw);
}

/******************
***WindowManager***
******************/

 WindowManager* WindowManager::GetInstance() {
	if (windowManager == nullptr)
		windowManager = new WindowManager();
	return windowManager;
}

void WindowManager::setCurrentWnbNum(int value) {
	if (currentWindow_ >= 0) {
		getCurrentWindow()->close();
	}
	currentWindow_ = value;
	onCurrentWindowChanged();
	getCurrentWindow()->show();
}

void WindowManager::addWindow(windowPtr window) {
	if (!window)
		return;
	auto id = static_cast<window_type>(window->getWindowId());
	windows_.emplace(id, window);
}

std::shared_ptr<BaseWindow> WindowManager::getCurrentWindow() {
	return getWindow(window_type(currentWindow_));
}

std::shared_ptr<BaseWindow> WindowManager::getWindow(window_type windId) {
	auto it = windows_.find(windId);
	if (it != windows_.end()) {
		return it->second;
	}
	std::string text = ("not find windId = ");
	text += std::to_string(static_cast<int>(windId));
	throw std::invalid_argument(text);
	return nullptr;
}

void WindowManager::draw(sf::RenderWindow& wind) {
	getCurrentWindow()->draw(wind);
	buttonManager->draw(wind);
}


int WindowManager::getCurrentWnbNum() const {
	return currentWindow_;
}



std::shared_ptr<ButtonManager> WindowManager::getButtonManager() {
	return buttonManager;
}


void WindowManager::checkColision(sf::Vector2i pos) {
	buttonManager->checkColision(pos);
	getCurrentWindow()->checkColision(pos);
}

void WindowManager::mousePressed(sf::Vector2i pos) {
	buttonManager->mousePressed();
}

void WindowManager::onCurrentWindowChanged() {
	buttonManager->setScreenId(currentWindow_);
}