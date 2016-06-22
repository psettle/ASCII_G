#ifndef ASCIIG_CHANGE_H
#define ASCIIG_CHANGE_H

#include"Frame.h"

namespace asciig {

	/*
	Description of a single change to a window
	*/
	class Change {
	public:
		/*
			Constructor that sets a string and a location to replace it at
		*/
		Change(const ColorString& replacement, const size_t x, const size_t y) {
			this->replacement = replacement;
			this->x = x;
			this->y = y;
		}

		/*
			Applies this change to the provided window
		*/
		void applyChange(PixelDriver& window) const {
			window.putsXY(this->x, this->y, this->replacement);
		}

		/*
			Moves this change by x and y
		*/
		void move(const size_t x, const size_t y) {
			this->x += x;
			this->y += y;
		}

	private:

		/*
			Characters to replace on the window
		*/
		ColorString replacement;

		/*
			x position at which to replace the characters
		*/
		size_t x;

		/*
			y position at which to replace the characters
		*/
		size_t y;
	};
}
#endif