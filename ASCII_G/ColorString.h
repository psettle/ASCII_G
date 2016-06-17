//TODO: implement string class that keeps colors indexed, should 
#ifndef ASCII_COLORSTRING_H
#define ASCII_COLORSTRING_H


#include<string>
#include"Color.h"
#include<vector>
#include<stdarg.h>


namespace asciig {
	struct ColorChar {
		ColorChar(char c, int count = 0, ...) {
			this->c = c;
			va_list arguments;
			va_start(arguments, count);
		
			//add arguments to to the list
			for (int i = 0; i < count; i++) {
				this->mods.push_back(va_arg(arguments, ColorCode));
			}

			va_end(arguments);
		}

		ColorChar(char c, std::vector<ColorCode> mods) {
			this->c = c;
			this->mods = mods;
		}

		ColorChar() {

		}
		char c;
		std::vector<ColorCode> mods;
	};

	class ColorString : public std::vector<ColorChar> {
	public:
		//output overload
		friend std::ostream& operator<<(std::ostream& os, ColorString& s) {

			//foreach char
			for (int i = 0; i < s.size(); i++) {

				//build color for each char
				std::string query;
				for (int j = 0; j < s.at(i).mods.size(); j++) {
					query += std::to_string(s.at(i).mods.at(j));

					if (j != s.at(i).mods.size() - 1) {
						query += ";";
					}
				}

				query = (std::string)"\x1b[" + query + (std::string)"m";
				//output the char
				os << query << s.at(i).c << "\x1b[0m";

			}

			return os;
		}

		ColorString(const int size, const char default) 
			: vector<ColorChar>()
		{
			for (int i = 0; i < size; i++) {
				this->push_back(ColorChar(default));
			}
		}

		ColorString(const char* other, int count = 0, ...) {
			va_list args;
			va_start(args, count);

			this->buildColored(other, count, args);

			va_end(args);
		}

		ColorString(std::string other, int count = 0, ...) {
			va_list args;
			va_start(args, count);
			
			this->buildColored(other, count, args);

			va_end(args);
		}

		void buildColored(std::string source, int count, va_list args) {
			std::vector<ColorCode> mods;
			//add arguments to the query
			for (int i = 0; i < count; i++) {
				mods.push_back(va_arg(args, ColorCode));
			}

			for (int i = 0; i < source.length(); i++) {
				this->push_back(ColorChar(source.at(i), mods));
			}
		}

		ColorString() {

		}

		ColorString& replace(const int pos, const int length, const ColorString& other) {
			int other_index = 0;
			for (int i = pos; i < length + pos && i < this->size(); i++) {
				this->at(i) = other.at(other_index);
				other_index++;
			}
			return *this;
		}

		int length() {
			return this->size();
		}

	private:		
	};

}

#endif