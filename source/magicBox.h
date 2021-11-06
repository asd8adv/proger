#pragma once
#include <random>  
#include <memory>
#include <string>
#include <algorithm>
#include <iostream>
#include <ctime> 
#include <SFML/Graphics.hpp>


enum class Dir
{
	bot,
	top,
	left,
	rigth
};




struct BaseObject {
public:
	int x;
	int y;
	int height;
	int width;
	void set(int X, int Y, int W, int H) {
		x = X;
		y = Y;
		height = H;
		width = W;
	}
};


static bool isCollision(const BaseObject& rectFirst, const BaseObject& rectSecond) {
	return	rectFirst.x < rectSecond.x + rectSecond.width &&
		rectFirst.x + rectFirst.width > rectSecond.x &&
		rectFirst.y < rectSecond.y + rectSecond.height &&
		rectFirst.y + rectFirst.height > rectSecond.y;
}

static bool isCollision(const BaseObject& rectFirst, sf::Vector2f point) {
	return	rectFirst.x < point.x&& point.x < rectFirst.x + rectFirst.width &&
		rectFirst.y < point.y&& point.y < rectFirst.y + rectFirst.height;
}

class randomize {
	int32_t min_;
	int32_t max_;

	std::unique_ptr<std::mt19937> rand_;
public:
	randomize(int32_t min, int32_t max) :min_(min), max_(max) {
		if (min > max)std::cerr << "error min/max value\n";
		rand_ = std::make_unique<std::mt19937>(std::mt19937(time(0)));
	}

	randomize(int32_t max) :min_(0), max_(max) {
		if (0 > max)std::cerr << "error min/max value\n";
		rand_ = std::make_unique<std::mt19937>(std::mt19937(time(0)));
	};

	int32_t get() {
		auto res = (*rand_)() % (max_ - min_ + 1);
		return min_ + res;
	}

};
