#include "dictionary.h"


Dictionary::Dictionary(int lang) :
	defaultString_("not found", "не найдено"),
	language_(lang)
{}

Dictionary* Dictionary::dictionaryInstance_ = nullptr;

Dictionary* Dictionary::GetInstance() {
	if (dictionaryInstance_ == nullptr)
		dictionaryInstance_ = new Dictionary();
	return dictionaryInstance_;
}

void Dictionary::setLanguage(int lang) {
	language_ = lang;
}

sf::String Dictionary::getString(int id) {
	auto it = dict_.find(id);
	if (it != dict_.end())
		return it->second.getString(language_);
	return defaultString_.getString(language_);
}

sf::String Dictionary::getString(World world) {
	return getString(int(world));
}

void Dictionary::addString(int id, multistring mStr) {
	dict_[id] = mStr;
}

void Dictionary::loadFromFile(const std::string& name) {
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

void Dictionary::parseAndAddWorld(wchar_t* buff) {
	std::wstring wstr(buff);
	int num = 0;
	std::wstring rus;
	std::wstring eng;
	size_t it1 = 0;
	size_t it2 = 0;

	it2 = wstr.find(L" ");
	if (it1 == std::wstring::npos || it2 == std::wstring::npos) {
		std::cerr << "bad Dictionary file" << "\n";
		return;
	}
	num = std::stoi(wstr.substr(it1, it2));

	it1 = wstr.find(L"{") + 1;
	it2 = wstr.find(L"}");
	if (it1 == std::wstring::npos || it2 == std::wstring::npos) {
		std::cerr << "bad Dictionary file" << "\n";
		return;
	}
	eng = wstr.substr(it1, it2 - it1);
	wstr = wstr.substr(it2 + 1, wstr.size() - it2 - 1);

	it1 = wstr.find(L"{") + 1;
	it2 = wstr.find(L"}");
	if (it1 == std::wstring::npos || it2 == std::wstring::npos) {
		std::cerr << "bad Dictionary file" << "\n";
		return;
	}
	rus = wstr.substr(it1, it2 - it1);
	addString(num, { eng, rus });
}

