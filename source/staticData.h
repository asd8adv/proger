#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>


enum class stats :int {
	stressLimit,
	alcoLimit,
	burnoutLimit,
	softSkills,
	algoritms,
	math,
};

struct playerStats {
	std::map<stats, int> value_;

	int getStat(stats stat) {
		auto it = value_.find(stat);
		if (it != value_.end()){
			return it->second;
		}
		return 0;
	}
	void setStat(stats stat, int value) {
		value_[stat] = value;
	}
};


class StaticData {
	static StaticData* StaticDataInstance_;
	std::map<std::string, std::shared_ptr<playerStats>> stats_;


	StaticData();
public:
	StaticData(StaticData& other) = delete;

	void operator=(const StaticData&) = delete;

	void init();

	std::shared_ptr<playerStats> getStats(std::string& playerSpecific) {
		if (stats_.count(playerSpecific)) {
			return stats_[playerSpecific];
		}
	}

	static StaticData* GetInstance();
private:
	void parseStats(std::string& str);
	bool verifyPos(int pos);//true for bad possition
};


