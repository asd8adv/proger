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


int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "the Proger");
	Dictionary::GetInstance()->setLanguage(language);
	Dictionary::GetInstance()->loadFromFile("res/info.txt");
	auto playWindow = std::make_shared<BaseWindow>(window_type::play_window);

	auto me = std::make_shared<Player>();
	me->init();
	auto WallTimer = std::make_shared<WallClockDrawable>();
	WallTimer->init();
	auto bg = std::make_shared<Drawable>("res/nw/back.png");
	auto selectedBook = std::make_shared<DrawableButton>("res/nw/books_table.png", "res/nw/book_selected.png", true, true);
	
	selectedBook->setCallback([]{
		std::cout << "u are umniy\n";
		});
	selectedBook->setContourDiff({ -3, -3 });
	auto man1 = std::make_shared<Drawable>("res/nw/man_1.png", true);
	auto bar = std::make_shared<DrawableButton>("res/nw/mini_bar_0.png", "res/nw/mini_bar_selected.png", false, true);
    auto cal = std::make_shared<Calendar>(sf::Vector2f({ 1170, 260 }), false);

    WallTimer->setPosition({ 30,10 });
    WallTimer->setScale({ 0.65,0.65 });
    
	selectedBook->setPosition({ 1343, 167 });
    man1->setPosition({ 750,450 });
    bar->setPosition({ 1269,745 });

	auto buttonMan = WindowManager::GetInstance()->getButtonManager();

    auto btn_drink = std::make_shared<bigButton>("res/BGBtn_1.png", Dictionary::GetInstance()->getString(World::drink), sf::Vector2f{ 120,500 }, true);
    btn_drink->setCallback([&me]() {
        me->drink();
	});
	btn_drink->setSize({ 160, 80 });
	btn_drink->setTextDeltaPosition({ 14, 22 });
	
    auto btn_skipDay = std::make_shared<bigButton>("res/BGBtn_1.png", Dictionary::GetInstance()->getString(World::next_day), sf::Vector2f{ 1190,540 }, true);
    btn_skipDay->setCallback([&me, &cal]() {
        cal->nextDay();
    });
	btn_skipDay->setSize({ 160, 80 });
	btn_skipDay->setTextDeltaPosition({ 14, 22 });

    auto btn_job = std::make_shared<bigButton>("res/BGBtn_1.png", Dictionary::GetInstance()->getString(World::job), sf::Vector2f{ 1750,400 }, true);
	btn_job->setCallback([&me, &cal]() {
		me->job();
    });

	btn_job->setSize({ 160, 80 });
	btn_job->setTextDeltaPosition({ 60, 22 });

	//buttonMan->addButton(btn_job, 1);
    buttonMan->addButton(btn_skipDay, 1);
    //buttonMan->addButton(btn_drink, 1);
    sf::Clock clock;

	playWindow->addDrawableObject(bg);
	playWindow->addDrawableObject(cal);
	playWindow->addDrawableObject(man1);
	playWindow->addDrawableObject(bar);
	playWindow->addDrawableObject(selectedBook);
	playWindow->addDrawableObject(WallTimer);
	WindowManager::GetInstance()->addWindow(playWindow);
	WindowManager::GetInstance()->setCurrentWnbNum(1);
    //todo add screen time for updates
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
					WindowManager::GetInstance()->mousePressed({ pos.x,pos.y });
                }

            }
        }

        if (event.type = sf::Event::MouseMoved) {
            auto pos = sf::Mouse::getPosition(window);
            buttonMan->checkColision({ pos.x,pos.y });
			selectedBook->checkColision({ pos.x,pos.y });
			bar->checkColision({ pos.x,pos.y });
        }

        me->update(-time);

        window.clear();
		WindowManager::GetInstance()->draw(window);
        buttonMan->draw(window);
        me->draw(window);
        window.display();
    }

    return 0;
}