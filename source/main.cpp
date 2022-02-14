#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <deque>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <source_location>

#include "windows.h"
#include "notificator.h"
#include "magicBox.h"
#include "buttonManager.h"
#include "wallClock.h"
#include "player.h"
#include "calendar.h"
#include "dictionary.h"
#include "windowManager.h"


const int language=1;//1 rus, 0 eng


void initPlayWindow(std::shared_ptr<BaseWindow> playWindow, std::shared_ptr<Player> me) {
	//bg
	auto bg = std::make_shared<Drawable>("res/nw/back.png");
	//cal
	auto cal = std::make_shared<Calendar>(sf::Vector2f({ 1170, 260 }), false);
	//man1 
	auto man1 = std::make_shared<Drawable>("res/nw/man_1.png", true);
	man1->setPosition({ 750,450 });
	//bar
	auto bar = std::make_shared<DrawableBar>();
	bar->setContourDiff({ -8, -8 });
	bar->setPosition({ 1300,745 });
	bar->setCurrentState(Bar::state::full);
	//selectedBook
	auto selectedBook = std::make_shared<DrawableButton>("res/nw/books_table.png", "res/nw/book_selected.png", true, true);
	selectedBook->setCallback([] {
		WindowManager::GetInstance()->setCurrentWnbNum(int(window_type::bookcase));
		std::cout << "u are umniy\n";
	});
	selectedBook->setContourDiff(sf::Vector2f( -8, -8 ));
	selectedBook->setPosition({ 1343, 167 });
	//WallTimer
	auto WallTimer = std::make_shared<WallClockDrawable>();
	WallTimer->init();
	WallTimer->setPosition({ 30,10 });
	WallTimer->setScale({ 0.65,0.65 });
	//inits button manager

	auto buttonMan = WindowManager::GetInstance()->getButtonManager();

	auto btn_drink = std::make_shared<BigButton>("res/BGBtn_1.png", Dictionary::GetInstance()->getString(World::drink), sf::Vector2f{ 1380,680 }, true);
	btn_drink->setCallback([btn_drink ,me, bar]() {
		if(!bar->empty()){
			me->drink();
			bar->setLessState();
			btn_drink->setDefaultColor();
			if(bar->empty())
				btn_drink->setGreyColor();
		}
		else {
			btn_drink->setGreyColor();
		}
		});
	btn_drink->setSize({ 160, 80 });
	btn_drink->setTextDeltaPosition({ 14, 22 });

	auto btn_skipDay = std::make_shared<BigButton>("res/BGBtn_1.png", Dictionary::GetInstance()->getString(World::next_day), sf::Vector2f{ 1190,540 }, true);
	btn_skipDay->setCallback([me, cal]() {
		cal->nextDay();
		});
	btn_skipDay->setSize({ 160, 80 });
	btn_skipDay->setTextDeltaPosition({ 14, 22 });

	auto btn_job = std::make_shared<BigButton>("res/BGBtn_1.png", Dictionary::GetInstance()->getString(World::job), sf::Vector2f{ 1750,400 }, true);
	btn_job->setCallback([me]() {
		me->job();
		});

	btn_job->setSize({ 160, 80 });
	btn_job->setTextDeltaPosition({ 60, 22 });

	buttonMan->addButton(btn_job, 1);
	buttonMan->addButton(btn_skipDay, 1);
	buttonMan->addButton(selectedBook, 1);
	buttonMan->addButton(btn_drink, 1);
	//add all nodes
	playWindow->addDrawableObject(bg);
	playWindow->addDrawableObject(cal);
	playWindow->addDrawableObject(man1);
	playWindow->addDrawableObject(bar);
	playWindow->addDrawableObject(selectedBook);
	playWindow->addDrawableObject(WallTimer);
}

void initBookWindow(std::shared_ptr<BaseWindow> bookWindow) {
	//bg
	auto bg = std::make_shared<Drawable>("res/nw/back_book.png");
	//cal


	auto buttonMan = WindowManager::GetInstance()->getButtonManager();

	auto btn_back = std::make_shared<BigButton>("res/nw/l_arrow.png", "", sf::Vector2f{ 0, 0 }, true);
	btn_back->setCallback([]() {
		WindowManager::GetInstance()->setCurrentWnbNum(int(window_type::play_window));
	});

	btn_back->setSize({ 120, 100 });
	//btn_back->setTextDeltaPosition({ 60, 22 });

	buttonMan->addButton(btn_back, 3);
	//add all nodes
	bookWindow->addDrawableObject(bg);

};

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "the Proger");
	Dictionary::GetInstance()->setLanguage(language);
	Dictionary::GetInstance()->loadFromFile("res/info.txt");

	auto playWindow = std::make_shared<BaseWindow>(window_type::play_window);
	auto bookWindow = std::make_shared<BaseWindow>(window_type::bookcase);
	auto me = std::make_shared<Player>();
	me->init();
	initPlayWindow(playWindow, me);
	initBookWindow(bookWindow);
	auto wndManager = WindowManager::GetInstance();
	wndManager->addWindow(playWindow);
	wndManager->addWindow(bookWindow);
	wndManager->setCurrentWnbNum(1);
    //todo add screen time for updates

	sf::Clock clock;

    while (window.isOpen()){

        float time = clock.getElapsedTime().asSeconds();
        float animtime = clock.getElapsedTime().asMicroseconds();
        animtime /= 800;
        clock.restart();
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
					auto pos = sf::Mouse::getPosition(window);
					wndManager->mousePressed({ pos.x,pos.y });
                }

            }
        }

        if (event.type = sf::Event::MouseMoved) {
            auto pos = sf::Mouse::getPosition(window);
			wndManager->checkColision({ pos.x,pos.y });
        }

        me->update(-time);

        window.clear();
		WindowManager::GetInstance()->draw(window);
        me->draw(window);
        window.display();
    }

    return 0;
}