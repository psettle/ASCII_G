#include"ColorChar.h"
#include<string>

//opening of the control character for console output
#define __OPEN_COLOR__ "\x1b["
//control character to reset font settings
#define __CLOSE_COLOR__ "\x1b[0m"

namespace asciig {

	ColorChar::ColorChar(const ColorChar& other) {
		this->character = other.character;
		this->mods = other.mods;
	}

	ColorChar& ColorChar::operator=(const ColorChar& other) {
		this->character = other.character;
		this->mods = other.mods;
		return *this;
	}

	ColorChar::ColorChar(const char c, const size_t count, ...) {
		this->character = c;
		va_list arguments;
		va_start(arguments, count);

		//add arguments to to the list
		for (size_t code = 0; code < count; code++) {
			this->mods.push_back(va_arg(arguments, ColorCode));
		}

		va_end(arguments);
	}

	ColorChar::ColorChar(const char c, const std::vector<ColorCode>& mods) {
		this->character = c;
		this->mods = mods;
	}

	

	bool ColorChar::operator==(const ColorChar& other) const{
		if (this->character != other.character) {
			return false;
		}
		if (this->mods != other.mods) {
			return false;
		}

		return true;
	}

	ColorChar::operator std::string() {
		std::string query;
		for (size_t mod = 0; mod < mods.size(); mod++) {
			query += std::to_string(mods.at(mod));

			if (mod != mods.size() - 1) {
				query += ";";
			}
		}

		query = __OPEN_COLOR__ + query + "m";
		//output the char
		return  query + character + __CLOSE_COLOR__;
	}

	bool ColorChar::operator!=(const ColorChar& other) const {
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& os, const ColorChar& c) {
		std::string query;
		for (size_t mod = 0; mod < c.mods.size(); mod++) {
			query += std::to_string(c.mods.at(mod));

			if (mod != c.mods.size() - 1) {
				query += ";";
			}
		}

		query = __OPEN_COLOR__ + query + "m";
		//output the char
		return os << query << c.character << __CLOSE_COLOR__;
	}

}