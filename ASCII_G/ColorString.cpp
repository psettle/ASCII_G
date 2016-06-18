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
}