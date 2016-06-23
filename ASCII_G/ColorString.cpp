#include"ColorString.h"

namespace asciig {

	ColorString::ColorString(const char* other, const size_t count, ...) {
		va_list args;
		va_start(args, count);

		this->buildColored(other, count, args);

		va_end(args);
	}



	ColorString::ColorString(const size_t size, const char default, const size_t count, ...)
	{
		//build the mods vector...
		va_list arguments;
		va_start(arguments, count);

		std::vector<ColorCode> mods;

		//add arguments to to the list
		for (size_t code = 0; code < count; code++) {
			mods.push_back(va_arg(arguments, ColorCode));
		}

		va_end(arguments);

		//push the character onto the string
		for (size_t pos = 0; pos < size; pos++) {
			this->push_back(ColorChar(default, mods));
		}
	}

	ColorString::ColorString(const std::string& other, const size_t count, ...) {
		va_list args;
		va_start(args, count);

		this->buildColored(other, count, args);

		va_end(args);
	}

	ColorString& ColorString::replace(const size_t pos, const size_t length, const ColorString& other) {
		size_t other_index = 0;
		for (size_t index = pos; index < length + pos && index < this->size(); index++) {
			this->at(index) = other.at(other_index);
			other_index++;
		}
		return *this;
	}

	ColorString ColorString::substr(const size_t start, const size_t length) const {
		ColorString toReturn;
		for (size_t pos = start; pos < start + length && pos < this->length(); pos++) {
			toReturn.push_back(this->at(pos));
		}
		return toReturn;
	}

	ColorString ColorString::substr(const size_t start) const {
		ColorString toReturn;
		for (size_t pos = start; pos < this->length(); pos++) {
			toReturn.push_back(this->at(pos));
		}
		return toReturn;
	}

	std::vector<ColorString> ColorString::explode(const char delimiter) const{
		std::vector<ColorString> lines;

		size_t start_index = 0;
		size_t pos = 0;
		for (; pos < this->size(); pos++) {
			if (this->at(pos) == delimiter) {
				lines.push_back(this->substr(start_index, pos - start_index));
				start_index = pos + 1;
			}
		}

		if (this->at(pos - 1) != delimiter) {
			lines.push_back(this->substr(start_index, pos - start_index));
			start_index = pos;
		}


		return lines;
	}

	ColorString& ColorString::operator+=(const ColorString& other) {
		return *this = *this + other;
 	}

	ColorString::operator std::string() {
		std::string toReturn = "";
		for (size_t pos = 0; pos < this->length(); pos++) {
			toReturn += this->at(pos);
		}
		//splice out redundant escape codes?
		return toReturn;
	}

	bool ColorString::operator==(const ColorString& other) const {

		if (this->length() != other.length()) {
			return false;
		}

		for (size_t pos = 0; pos < this->length(); pos++) {
			if (!(this->at(pos) == other.at(pos))) {
				return false;
			}
		}

		return true;
	}

	bool ColorString::operator !=(const ColorString& other) const {
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& os, const ColorString& s) {

		//foreach char
		for (size_t pos = 0; pos < s.size(); pos++) {
			os << s.at(pos);
		}

		return os;
	}

	void ColorString::buildColored(const std::string& source, const size_t count, va_list args) {
		std::vector<ColorCode> mods;
		//add arguments to the query
		for (size_t code = 0; code < count; code++) {
			mods.push_back(va_arg(args, ColorCode));
		}

		for (size_t index = 0; index < source.length(); index++) {
			this->push_back(ColorChar(source.at(index), mods));
		}
	}

	ColorString operator+(const ColorString& lhs, const ColorString& rhs) {
		ColorString toReturn = lhs;

		for (size_t pos = 0; pos < rhs.length(); pos++) {
			toReturn.push_back(rhs.at(pos));
		}

		return toReturn;
	}
}