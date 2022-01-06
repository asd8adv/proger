#include <SFML/Graphics.hpp>
#include <memory>
#include <exception>
#include <map>
#include <algorithm>

#include "drawable.h"
#include "buttonManager.h"


enum class window_type : int {
	play_window = 1,
	main_menu
};

class BaseWindow {
	using drawablePtr = std::shared_ptr<Drawable>;
protected:
	std::vector<drawablePtr> drawObjects_;
	bool visible = false;
	int wndNumber = -1;
public:
	BaseWindow(int num);
	BaseWindow(window_type wind);

	virtual void show();
	virtual void close();
	virtual void checkColision(sf::Vector2i pos);
	virtual void onPressed();
	virtual void draw(sf::RenderWindow& wind);

	int getWindowId();
	void addDrawableObject(drawablePtr draw);
};

class ContextWindow : public BaseWindow {
	using Base = BaseWindow;
	Drawable bg;
public:
	ContextWindow(int num, std::string& backFileName, bool isUseMask)
		:Base(num), bg(backFileName, isUseMask)
	{}
	//Next time on... XD
};


class WindowManager {
	using windowPtr = std::shared_ptr<BaseWindow>;
	std::map<window_type, windowPtr> windows_;
	std::shared_ptr <ButtonManager> buttonManager;
	int currentWindow_ = -1;
	WindowManager() {
		buttonManager = std::make_shared<ButtonManager>();
	};
public:
	WindowManager(WindowManager& other) = delete;
	void operator=(const WindowManager&) = delete;

	static WindowManager* GetInstance();

	void setCurrentWnbNum(int value);
	//end singleton metodsa

	void addWindow(windowPtr window);
	windowPtr getCurrentWindow();
	windowPtr getWindow(window_type windId);
	void draw(sf::RenderWindow& wind);
	int getCurrentWnbNum() const;
	std::shared_ptr<ButtonManager> getButtonManager();
	void mousePressed(sf::Vector2i pos);
	void checkColision(sf::Vector2i pos);

protected:
	void onCurrentWindowChanged();
};