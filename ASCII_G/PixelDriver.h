#ifndef PIXELDRIVER_H
#define PIXELDRIVER_H
#include<vector>
#include<Windows.h>
#include"ColorString.h"
#include"iostream"

namespace asciig {
	class PixelDriver {
	public:
		PixelDriver(int width, int height)
			: width(width), height(height), output(height, ColorString(width, ' ')),
			console(GetStdHandle(STD_OUTPUT_HANDLE))
		{
			//return the cursor to the root
			std::cout << "\r";

			CONSOLE_SCREEN_BUFFER_INFO SBinfo;

			GetConsoleScreenBufferInfo(this->console, &SBinfo);

			this->root_y = SBinfo.dwCursorPosition.Y;

			for (int i = 0; i < this->output.size(); i++) {
				std::cout << this->output.at(i) << std::endl;
			}



		}

		/*
		Puts as much of s into the frame as possible at the specified x, y
		*/
		PixelDriver& putsXY(int x, int y, ColorString s) {
			if (x >= this->width || y >= this->height) {
				return *this;
			}
			//how many character will fit?
			int charCount = 0;
			if (x + s.length() < this->width) {
				//then all of them will fit
				charCount = s.length();
			} else {
				//then we can fit width - x + 1
				charCount = this->width - x + 1;
			}
			
			//now we have to update output
			this->output.at(y).replace(x, charCount, s).resize(this->width);

			gotoXY(0, y);
			
			for (int i = y; i < this->output.size(); i++) {
				std::cout << this->output.at(i) << std::endl;
			}

			return *this;
		}
	private:
		void gotoXY(int x, int y) {
			this->cursor.X = x;
			this->cursor.Y = this->root_y + y;
			SetConsoleCursorPosition(this->console, this->cursor);
		}

		std::vector<ColorString> output;

		int width;
		int height;

		int root_y;

		HANDLE console;
		COORD cursor;
	};
}

#endif
