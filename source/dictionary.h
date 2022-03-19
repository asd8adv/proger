#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <locale>
#include <codecvt>
#include <windows.h>
#include <iostream>

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

enum class World :int {
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
	new_day_new_dollar = 11,
	stats = 12
};

class Dictionary {
	multistring defaultString_;
	std::map<int, multistring> dict_;
	int language_ = 0;
	static Dictionary* dictionaryInstance_;
public:
	Dictionary(int lang = 0);

	static Dictionary* GetInstance();

	Dictionary(Dictionary& other) = delete;

	void operator=(const Dictionary&) = delete;

	void setLanguage(int lang);

	sf::String getString(int id);

	sf::String getString(World world);

	void addString(int id, multistring mStr);

	void loadFromFile(const std::string& name);
private:
	void parseAndAddWorld(wchar_t* buff);
};

