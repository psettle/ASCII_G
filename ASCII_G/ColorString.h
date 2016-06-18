#ifndef ASCIIG_COLORSTRING_H
#define ASCIIG_COLORSTRING_H


#include<string>
#include"Color.h"
#include<vector>
#include<stdarg.h>
#include"ColorChar.h"


namespace asciig {
	/*
		Similar to the string class, except each character has an 
		associated color setting
	*/
	class ColorString : public std::vector<ColorChar> {
	public:

		/*
			Builds an empty ColorString
		*/
		ColorString() {}	

		/*
			Creates a ColorString filled with size characters of the default specified
			with the given colors
		*/
		ColorString(const size_t size, const char default, const size_t count = 0, ...);

		/*
			Creates a colorstring with other as contents, and count modifiers from asciig::Color
		*/
		ColorString(const char* other, const size_t count = 0, ...);

		/*
			Creates a colorstring with other as contents, and count modifiers from asciig::Color
		*/
		ColorString(const std::string& other, const size_t count = 0, ...);


		/*
			Replaces this strings contents with other, starting at pos for length characters
		*/
		ColorString& replace(const size_t pos, const size_t length, const ColorString& other);

		/*
			Returns the number of characters in this string
		*/
		size_t length() const { return this->size(); }

		/*
			Returns true if this and other have all the same ColorCharacters, false otherwise
		*/
		bool operator==(const ColorString& other) const;

		/*
			Returns true if this and other have any different ColorCharaters, or are of different length,
			false otherwise
		*/
		bool operator !=(const ColorString& other) const;

		/*
			Outputs operator for the while string
		*/
		friend std::ostream& operator<<(std::ostream& os, const ColorString& s);	
	private:

		/*
			pushes all of source onto this string with count modifiers from args
		*/
		void buildColored(const std::string& source, const size_t count, va_list args);

	};

}

#endif