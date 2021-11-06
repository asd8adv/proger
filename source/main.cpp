#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <deque>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <source_location>
#include <fstream>
#include <locale>
#include <codecvt>

#include "windows.h"
#include "notificator.h"
#include "magicBox.h"
#include "buttonManager.h"
#include "wallClock.h"
#include "player.h"
#include "calendar.h"

const int language=1;//1 rus, 0 eng

struct multistring {
	sf::String rusStr;
	sf::String engStr;

	multistring() {
	}

	multistring(const sf::String& eng, const sf::String& rus) :engStr(eng), rusStr(rus) {
	}
	
	sf::String& getString(int lang) {
		if (lang == 1)
			return rusStr;
		return engStr;
	}

};

enum class World:int {
	game = 1,
	drink = 2,
	job = 3,
	next_day = 4,
	day = 5,
	week = 6,
	stress = 7,
	alcoholism = 8,
	reputation = 9,
	burnout = 10,
	new_day_new_dollar = 11


};

class dictionary{
	multistring defaultString_;
	std::map<int, multistring> dict_;
	int language_ = 0;
public:
	dictionary(int lang = 0) :
		defaultString_("not found", "не найдено"),
		language_(lang)
	{}

	sf::String getString(int id) {
		auto it=dict_.find(id);
		if (it != dict_.end())
			return it->second.getString(language_);
		return defaultString_.getString(language_);
	}

	sf::String getString(World world) {
		return getString(int(world));
	}


	void addString(int id, multistring mStr) {
		dict_[id] = mStr;
	}

	void loadFromFile(const std::string& name) {
		//return;
		std::fstream f;
		char str[1024];
		wchar_t wch[512];
		std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
		f.imbue(loc);
		f.open("res/info.txt", std::ios::in);
		if (f)
		{
			while (f.getline(str, 1024)) {
				MultiByteToWideChar(CP_UTF8, 0, str, 1024, wch, 512);
				parseAndAddWorld(wch);
			}
			f.close();
		}
	}

private:
	void parseAndAddWorld(wchar_t* buff) {
		std::wstring wstr(buff);
		int num = 0;
		std::wstring rus;
		std::wstring eng;
		size_t it1 = 0;
		size_t it2 = 0;

		it2 = wstr.find(L" ");
		if (it1 == std::wstring::npos || it2 == std::wstring::npos) {
			std::cerr << "bad dictionary file"<< "\n";
			return;
		}
		num = std::stoi(wstr.substr(it1, it2));

		it1 = wstr.find(L"{") + 1;
		it2 = wstr.find(L"}");
		if (it1 == std::wstring::npos || it2 == std::wstring::npos) {
			std::cerr << "bad dictionary file" << "\n";
			return;
		}
		eng = wstr.substr(it1, it2 - it1);
		wstr = wstr.substr(it2 + 1, wstr.size() - it2 - 1);

		it1 = wstr.find(L"{") + 1;
		it2 = wstr.find(L"}");
		if (it1 == std::wstring::npos || it2 == std::wstring::npos) {
			std::cerr << "bad dictionary file" << "\n";
			return;
		}
		rus = wstr.substr(it1, it2 - it1);
		addString(num, { eng, rus});
	}
};


int main(){
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "the Proger");

	dictionary dict(language);
	dict.loadFromFile("res/info.txt");

    auto me = std::make_shared<Player>();
    me->init();
    auto WallTimer = std::make_shared<WallClockDrawable>();
    WallTimer->init();
    Drawable bg("res/bg.png");
    Drawable kover("res/kover.png");
    Drawable stol("res/stol.png",true);
    Drawable peka("res/stol.png", true);
    Drawable man1("res/man_1.png", true);
    Drawable man2("res/man_2.png", true);
    Drawable pk("res/pk.png", true);
    Drawable bar("res/minibar.png", true); 
    Calendar cal({ 20, 150 });
    WallTimer->setPosition({ 30,10 });
    WallTimer->setScale({ 0.65,0.65 });
    kover.setScale({ 0.7, 0.7 });
    kover.setPosition({ 600, 50 });
    stol.setScale({ 0.5,0.5 });
    stol.setPosition({ 1200,430 });
    man1.setPosition({ 1350,230 });
    pk.setPosition({ 1350,330 });
    pk.setScale({ 0.35,0.35 });
    man1.setScale({ 1.2,1.2 });
    man2.setPosition({ 500,400 });
    man2.setVisible(0);
    bar.setPosition({ 100,580 });

    ButtonManager buttonMan;
    auto btn_drink = std::make_shared<bigButton>("res/BGBtn_1.png", dict.getString(World::drink), sf::Vector2f{ 120,500 }, true);
    btn_drink->setCallback([&me]() {
        me->drink();
	});
	btn_drink->setSize({ 160, 80 });
	btn_drink->setTextDeltaPosition({ 14, 22 });
		
    auto btn_skipDay = std::make_shared<bigButton>("res/BGBtn_1.png", dict.getString(World::next_day), sf::Vector2f{ 20,400 }, true);
    btn_skipDay->setCallback([&me, &cal]() {
        cal.nextDay();
    });
	btn_skipDay->setSize({ 160, 80 });
	btn_skipDay->setTextDeltaPosition({ 14, 22 });

    auto btn_job = std::make_shared<bigButton>("res/BGBtn_1.png", dict.getString(World::job), sf::Vector2f{ 1750,400 }, true);
	btn_job->setCallback([&me, &cal]() {
		me->job();
    });

	btn_job->setSize({ 160, 80 });
	btn_job->setTextDeltaPosition({ 60, 22 });

	buttonMan.addButton(btn_job, 1);
    buttonMan.addButton(btn_skipDay, 1);
    buttonMan.addButton(btn_drink, 1);
    sf::Clock clock;

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
                    buttonMan.mousePressed();
                }

            }
        }


        if (event.type = sf::Event::MouseMoved) {
            auto pos = sf::Mouse::getPosition(window);
            buttonMan.checkColision({ pos.x,pos.y });
        }

        me->update(time);

        window.clear();
        bg.draw(window);
        kover.draw(window);
        stol.draw(window);
        pk.draw(window);
        cal.draw(window);
        man1.draw(window);
        man2.draw(window);
        buttonMan.draw(window);
        me->draw(window);
        bar.draw(window);
        WallTimer->draw(window);
        window.display();
    }

    return 0;
}