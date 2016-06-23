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

	ChangeMap::ChangeMap(const ColorString& source, const size_t x, const size_t y) {
		std::vector<ColorString> lines = source.explode();

		for (size_t line = 0; line < lines.size(); line++) {
			size_t start_pos = 0;
			size_t pos = 0;
			for (; pos < lines.at(line).size(); pos++) {
				if (lines.at(line).at(pos) == '\b' && start_pos != pos) {
					this->push_back(Change(lines.at(line).substr(start_pos, pos - start_pos), start_pos, line));
					start_pos = pos + 1;
				} else if (lines.at(line).at(pos) == '\b') {
					start_pos++;
				}
			}

			if (lines.at(line).at(pos - 1) != '\b' && start_pos != pos) {
				this->push_back(Change(lines.at(line).substr(start_pos, pos - start_pos), start_pos, line));
			}
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