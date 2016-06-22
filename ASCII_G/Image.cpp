#include"Image.h"

namespace asciig {
	Image::Image(const std::vector<ColorString>& source) {
		for (size_t line = 0; line < source.size(); line++) {
			this->addLine(source.at(line));
		}
	}

	Image::Image(const Image& source) {
		for (size_t line = 0; line < source.size(); line++) {
			this->push_back(source.at(line));
		}
	}

	Image::Image(const ColorString& source) {
		size_t line_start = 0;
		for (size_t pos = 0; pos < source.length(); pos++) {
			if (source.at(pos) == '\n') {
				this->addLine(source.substr(line_start, pos - line_start));
				line_start = pos + 1;
			}
		}
		ColorString last_string = source.substr(line_start);
		if (last_string.length() != 0) {
			this->addLine(source.substr(line_start));
		}	
	}

	void Image::runFrame(PixelDriver& window, const bool print) const {
		//run the frame
		for (size_t line = 0; line < this->size(); line++) {
			window.putsXY(0, line, this->at(line));
		}
		if (print) {
			window.printFullWindow();
		}
		
	}
}