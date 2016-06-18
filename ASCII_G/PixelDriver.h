#ifndef ASCIIG_PIXELDRIVER_H
#define ASCIIG_PIXELDRIVER_H
#include<vector>
#include<Windows.h>
#include"ColorString.h"
#include<iostream>

namespace asciig {

	/*
		Low level mask for controling the console window
	*/
	class PixelDriver {
	public:
		/*
			Creates a new Pixel Driver  with given width and height
			NOTE: this class depends on a constant number of lines on the console before it
			they can be stacked so long as they are not resized
		*/
		PixelDriver(const size_t width, const size_t height);

		/*
			Puts as much of s into the frame as possible at the specified x, y
		*/
		PixelDriver& putsXY(const size_t x, const size_t y, const ColorString& s); 

		/*
			Grows or shrinks the 'window' to the new height and width, data may be lost, and new spaces will be filled with black black space
		*/
		void resize(const size_t width, const size_t height);

		/*
			Clears and reprints the entire window content
		*/
		void printFullWindow();

		/*
			Clears this window
		*/
		void clearWindow();

		/*
			Returns the width of the window
		*/
		size_t getWidth() const { return this->width; }

		/*
			Returns the height of the window
		*/
		size_t getHeight() const { return this->height; }

	private:
		/*
			Moves the cursor to the given x and y
		*/
		void gotoXY(const size_t x, const size_t y);

		/*
			The current content of this window, several rows of strings
		*/
		std::vector<ColorString> output;
		
		/*
			The width of the window (in characters)
		*/
		size_t width;

		/*
			The heightof this window (in lines)
		*/
		size_t height;

		/*
			This initial location of the cursor
		*/
		size_t root_y;

		/*
			Connection to the console window
		*/
		HANDLE console;

		/*
			Connection to the cursor
		*/
		COORD cursor;
	};
}

#endif
