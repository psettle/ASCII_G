#ifndef ASCIIG_COLORCHAR_H
#define ASCIIG_COLORCHAR_H

#include"Color.h"
#include<vector>
#include<stdarg.h>
#include<iostream>

namespace asciig {
	/*
		Similar to char type, but holds a list of colors to modify with
	*/
	class ColorChar {
	public:
		/*
			Default ctor, creates a garbage char with no mods
		*/
		ColorChar() {}

		/*
			Copy ctor
		*/
		ColorChar(const ColorChar& other);

		/*
			Builds a ColorChar with count ColorCode modifiers
		*/
		ColorChar(const char c, const size_t count = 0, ...);

		/*
			Builds a ColorChar from a character and a list of modifiers
		*/
		ColorChar(const char c, const std::vector<ColorCode>& mods);

		/*
			Copies a colorchar into another
		*/
		ColorChar& operator=(const ColorChar&);

		/*
			Compares for same character (ignores colors)
		*/
		bool operator==(const char other) const { return this->character == other; }

		/*
			Compares for different character (ignores colors)
		*/
		bool operator!=(const char other) const { return this->character != other; }

		/*
			Compares for same character and colors
		*/
		bool operator==(const ColorChar& other) const;

		/*
			Compares for different character or colors
		*/
		bool operator!=(const ColorChar& other) const;

		/*
			Prints the character with its modifiers
		*/
		friend std::ostream& operator<<(std::ostream& os, const ColorChar& c);

	private:

		/*
			The character this class represents
		*/
		char character;

		/*
			A vector of color codes from asciig::Color
			represents how to change the character
		*/
		std::vector<ColorCode> mods;
	};

}

#endif
