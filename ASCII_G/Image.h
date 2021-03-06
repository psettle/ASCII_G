#ifndef ASCIIG_IMAGE_H
#define ASCIIG_IMAGE_H

#include"Frame.h"

namespace asciig {

	/*
		Fully redefines the pixels for a window, will fail if the image size doesn't match
		the window size
	*/
	class Image : public Frame, public std::vector<ColorString> {
	public:
		/*
			Creates an empty image
		*/
		Image() {}

		/*
			Copies an image
		*/
		Image(const Image& other);

		/*
			Creates an image from a source character map
		*/
		Image(const std::vector<ColorString>& source);

		/*
			Creates an image from a single string, lines are parsed at \n
		*/
		Image(const ColorString& source);

		/*
			Adds a line to the image
		*/
		void addLine(const ColorString& line) { this->push_back(line); }

		/*
			Applies this frame to the window, if image is too small old buffer will stay
			any part of the image that is too big will be cut off
		*/
		void runFrame(PixelDriver& window) const;

		/*
			Calls parent destructors
		*/
		~Image() {}
	};

}

#endif