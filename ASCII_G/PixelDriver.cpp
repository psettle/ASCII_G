#include"PixelDriver.h"

namespace asciig {

	PixelDriver::PixelDriver(const size_t width, const size_t height)
		: width(width), height(height), output(height, ColorString(width, ' ')),
		console(GetStdHandle(STD_OUTPUT_HANDLE))
	{
		//return the cursor to the root
		std::cout << "\r";

		CONSOLE_SCREEN_BUFFER_INFO SBinfo;

		GetConsoleScreenBufferInfo(this->console, &SBinfo);

		this->root_y = SBinfo.dwCursorPosition.Y;

		//print the initial window to clear the space
		for (size_t line = 0; line < this->output.size(); line++) {
			std::cout << this->output.at(line) << std::endl;
		}
	}

	PixelDriver& PixelDriver::putsXY(const size_t x, const size_t y, const ColorString& s) {
		if (x >= this->width || y >= this->height) {
			return *this;
		}
		//how many character will fit?
		size_t charCount = 0;
		if (x + s.length() < this->width) {
			//then all of them will fit
			charCount = s.length();
		}
		else {
			//then we can fit width - x + 1
			charCount = this->width - x + 1;
		}

		//now we have to update output
		this->output.at(y).replace(x, charCount, s).resize(this->width);

		gotoXY(0, y);

		return *this;
	}

	void PixelDriver::resize(const size_t width, const size_t height) {
		this->clearWindow();
		//restructure the data
		this->output.resize(height, ColorString(width, ' '));
		for (size_t line = 0; line < this->output.size(); line++) {
			this->output.at(line).resize(width, ColorChar(' '));
		}

		this->width = width;
		this->height = height;

		this->printFullWindow();
	}

	void PixelDriver::printFullWindow() {
		this->gotoXY(0, 0);
		for (size_t line = 0; line < this->height; line++) {	
			std::cout << this->output.at(line) << std::endl;
		}
	}

	void PixelDriver::clearWindow() {
		
		this->gotoXY(0, 0);
		for (unsigned int i = 0; i < this->output.size(); i++) {
			for (unsigned int j = 0; j < this->output.at(i).size(); j++) {
				std::cout << " ";
			}
			std::cout << std::endl;
		}
	}

	void PixelDriver::gotoXY(const size_t x, const size_t y) {
		this->cursor.X = x;
		this->cursor.Y = this->root_y + y;
		SetConsoleCursorPosition(this->console, this->cursor);
	}
}