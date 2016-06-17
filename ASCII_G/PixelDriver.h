#ifndef PIXELDRIVER_H
#define PIXELDRIVER_H
#include<vector>
#include<Windows.h>
#include"ColorString.h"
#include"iostream"

namespace asciig {
	class PixelDriver {
	public:
		/*
			Creates a new Pixel Driver  with given width and height
			NOTE: this class depends on a constant number of lines on the console before it
			they can be stacked so long as they are not resized
		*/
		PixelDriver(int width, int height)
			: width(width), height(height), output(height, ColorString(width, ' ')),
			console(GetStdHandle(STD_OUTPUT_HANDLE))
		{
			//return the cursor to the root
			std::cout << "\r";

			CONSOLE_SCREEN_BUFFER_INFO SBinfo;

			GetConsoleScreenBufferInfo(this->console, &SBinfo);

			this->root_y = SBinfo.dwCursorPosition.Y;

			for (unsigned int i = 0; i < this->output.size(); i++) {
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
			
			for (unsigned int i = y; i < this->output.size(); i++) {
				std::cout << this->output.at(i) << std::endl;
			}

			return *this;
		}
		/*
			Grows or shrinks the 'window' to the new height and width, data may be lost, and new spaces will be filled with black black space
		*/
		void resize(int width, int height) {
			this->clearWindow();
			//restructure the data
			this->output.resize(height, ColorString(width, ' '));
				for (unsigned int i = 0; i < this->output.size(); i++) {
				this->output.at(i).resize(width, ColorChar(' '));
			}

			this->width = width;
			this->height = height;

			this->printFullWindow();
		}

		/*
			Clears and reprints the entire window content
		*/
		void printFullWindow() {
			this->putsXY(0, 0, "");
		}

		void clearWindow() {
			this->gotoXY(0, 0);
			for (unsigned int i = 0; i < this->output.size(); i++) {
				for (unsigned int j = 0; j < this->output.at(i).size(); j++) {
					std::cout << " ";
				}
				std::cout << "\n";
			}
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
