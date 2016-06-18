#ifndef ASCIIG_IMAGE_H
#define ASCIIG_IMAGE_H

#include"Frame.h"

namespace asciig {

	/*
		Fully redefines the pixels for a window, will fail if the image size doesn't match
		the window size
	*/
	class Image : public Frame {
	public:
		Image(std::vector<ColorString> source) {
			this->image = source;
		}
		/*
			Applies this frame to the window
		*/
		void runFrame(PixelDriver& window) {
			//check image size
			if (this->image.size() != window.getHeight()) {
				exit(1);
			}

			for (size_t line = 0; line < this->image.size(); line++) {
				if (this->image.at(line).length() != window.getWidth()) {
					exit(1);
				}
			}
			//run the frame
			for (size_t line = 0; line < this->image.size(); line++) {
				window.putsXY(0, line, this->image.at(line));
			}
		}
	private:
		/*
			Container for the image data
		*/
		std::vector<ColorString> image;
	};

}

#endif