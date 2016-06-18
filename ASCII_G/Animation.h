#ifndef ASCIIG_ANIMATION_H
#define ASCIIG_ANIMATION_H
#include<vector>
#include"Frame.h"
#include"Image.h"
#include"PixelDriver.h"
#include<memory>
#include<thread>
#include<fstream>

//TDOD add change mask frame type
namespace asciig {
	/*
		Container class for Frame objects, also easy execution for a sequence of frames
	*/
	class Animation : private std::vector<std::unique_ptr<Frame>> {
	public:
		/*
			Creates a new animation with the given width and height
		*/
		Animation(const size_t width, const size_t height);
	
		/*
			Runs the animation with speed # of milliseconds between each frame
		*/
		void runAnimation(const size_t speed);

		/*
			Adds an Image to the last frame of the animation
		*/
		void addImage(const Image& frame);

	private:
		/*
			Connection to the console, manages updating the console output
		*/
		PixelDriver window;
	};
}

#endif