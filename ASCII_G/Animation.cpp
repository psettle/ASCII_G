#include"Animation.h"

namespace asciig {
	Animation::Animation(const size_t width, const size_t height)
		: window(width, height)
	{
		this->window = window;
	}

	void Animation::runAnimation(const size_t speed) {
		for (size_t frame = 0; frame < this->size(); frame++) {
			this->at(frame)->runFrame(this->window);
			std::this_thread::sleep_for(std::chrono::milliseconds(speed));
		}
	}

	void Animation::addImage(const Image& frame) {
		this->push_back(std::unique_ptr<Frame>(new Image(frame)));
	}
}