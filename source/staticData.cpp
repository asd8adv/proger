#include "staticData.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>



/************************
*****class StaticData*****
************************/

StaticData::StaticData()
{}


StaticData* StaticData::GetInstance() {
	if (StaticDataInstance_ == nullptr) {
		StaticDataInstance_ = new StaticData();
	}
	return StaticDataInstance_;
}

void StaticData::init() {
	std::ifstream data("staticdata.txt");
	if (data.is_open()) {
		std::string strData="";
		std::string line="";
		while (getline(data, line)) {
			strData += line;
		}
		
		parseStats(strData);
	}
}

bool StaticData::verifyPos(int pos) {
	bool isBadPos = pos == std::string::npos;
	if (isBadPos)
		std::cerr << "parse error";
	return isBadPos;
}
void StaticData::parseStats(std::string& str) {
	auto curr = str.find("start stats");
	curr += 11;
	auto endStats = str.find("end stats");
	
	if (verifyPos(curr)) return;
	if (verifyPos(endStats)) return;
	while (curr < endStats && curr != std::string::npos) {
		curr = str.find("start ", curr);
		if (curr == std::string::npos) return;
		curr += 6;
		auto name = str.find("*", curr);
		if (name == std::string::npos) return;
		std::string strName = str.substr(curr, name-curr);
		auto next = name + strName.size() + 1;
		next = str.find("end " + strName, next);
		bool isLast = (next == std::string::npos)||(next>endStats);
		curr += strName.size() + 1;
		std::string statics = str.substr(curr, next - curr-1);
		auto currentStat = stats_.emplace(strName, std::make_shared<playerStats>()).first->second;
		auto setValue = [](std::string str, const std::regex reg, int& value) {
			std::smatch res;
			if (std::regex_search(str, res, reg)) {
				for (auto&& e : res) {
					std::string a = e;
					bool isCorrect = true;
					for (auto it : a) {
						if (std::isdigit(it) == 0) {
							isCorrect = false;
							break;
						}
						if (isCorrect)
							value = std::stoi(a);
					}
				}
			}
		};

		const std::regex stress("stressLimit=([0-9]*)");
		const std::regex alco("alcoLimit=([0-9]*)");
		const std::regex burnout("burnoutLimit=([0-9]*)");
		const std::regex soft("softSkills=([0-9]*)");
		const std::regex algo("algorithms=([0-9]*)");
		const std::regex math("math=([0-9]*)");

		int value = 0;;
		setValue(statics, stress, value);
		currentStat->setStat(stats::stressLimit, value);
		setValue(statics, alco, value);
		currentStat->setStat(stats::alcoLimit, value);
		setValue(statics, burnout, value);
		currentStat->setStat(stats::burnoutLimit, value);
		setValue(statics, soft, value);
		currentStat->setStat(stats::softSkills, value);
		setValue(statics, algo, value);
		currentStat->setStat(stats::algoritms, value);
		setValue(statics, math, value);
		currentStat->setStat(stats::math, value);

		if (isLast)break;
		curr = next;
	}



}


StaticData* StaticData::StaticDataInstance_ = nullptr;;


