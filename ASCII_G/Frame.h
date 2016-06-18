#ifndef ASCIIG_FRAME_H
#define ASCIIG_FRAME_H

#include"PixelDriver.h"

namespace asciig {

	/*
		abstract representing a frame in an animation
	*/
	class Frame {
	public:
		/*
			Applies this frame to the window
		*/
		virtual void runFrame(PixelDriver& window) = 0;
	};

}

#endif