#include"ChangeMap.h"

namespace asciig {
	ChangeMap::ChangeMap(const ChangeMap& other) {
		for (size_t change = 0; change < other.size(); change++) {
			this->push_back(other.at(change));
		}
	}

	ChangeMap::ChangeMap(const std::vector<Change>& other) {
		for (size_t change = 0; change < other.size(); change++) {
			this->push_back(other.at(change));
		}
	}

	ChangeMap::ChangeMap(const Image& image, const size_t x, const size_t y) {
		for (size_t line = 0; line < image.size(); line++) {
			this->push_back(Change(image.at(line), x, y + line));
		}
	}

	void ChangeMap::runFrame(PixelDriver& window, const bool print) const {
		for (size_t change = 0; change < this->size(); change++) {
			this->at(change).applyChange(window);
		}
		if (print) {
			window.printFullWindow();
		}
	}

	void ChangeMap::reAlign(const size_t x, const size_t y) {
		for (size_t change = 0; change < this->size(); change++) {
			this->at(change).move(x, y);
		}
	}
}