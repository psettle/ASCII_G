#ifndef ASCIIG_ANIMATION_H
#define ASCIIG_ANIMATION_H
#include<vector>
#include"Frame.h"
#include"Image.h"
#include"PixelDriver.h"
#include<memory>
#include<thread>


namespace asciig {
	class Animation : public std::vector<std::unique_ptr<Frame>> {
	public:
		Animation(const size_t width, const size_t height)
			: window(width, height)
		{
			this->window = window;
		}

		void runAnimation(const size_t speed) {
			for (size_t frame = 0; frame < this->size(); frame++) {
				this->at(frame)->runFrame(this->window);
				std::this_thread::sleep_for(std::chrono::milliseconds(speed));
			}
		}

		void addImage(const Image& frame) {
			this->push_back(std::unique_ptr<Frame>(new Image(frame)));
		}

		void addImage(const Image* frame) {
			this->push_back(std::unique_ptr<Frame>(new Image(*frame)));
		}


	
	private:
		PixelDriver window;
	};
}

#endif