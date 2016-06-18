#ifndef ASCIIG_FRAME_H
#define ASCIIG_FRAME_H

#include"PixelDriver.h"

namespace asciig {

	/*
		abstract class representing a frame in an animation
	*/
	class Frame {
	public:
		/*
			Applies this frame to the window
		*/
		virtual void runFrame(PixelDriver& window) const = 0;

		/*
			Destructor defined to prevent memory leaks in child classes
		*/
		virtual ~Frame() {};
	};

}

#endif