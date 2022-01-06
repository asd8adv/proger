#pragma once
#include "notificator.h"
#include "drawable.h"

class WallClock {
	int selectedClock_;
	const int clockCount_;
	static WallClock* WallClockInstance_;


	WallClock();
public:
	WallClock(WallClock& other) = delete;

	void operator=(const WallClock&) = delete;

	void nextTimeZone();

	bool isHaveTime();

	void  dayChange();

	static WallClock* GetInstance();

};

class WallClockDrawable : public Drawable {
	using ptrDrawable = std::shared_ptr<Drawable>;
	std::vector<ptrDrawable> clocks_;
	int selectedClock_;
public:
	WallClockDrawable();

	~WallClockDrawable();

	void init();

	void draw(sf::RenderWindow& wind);

	void virtual onEvent(EVENT ev)override;

	void setPosition(sf::Vector2f vec);

	void setScale(sf::Vector2f vec);
};
