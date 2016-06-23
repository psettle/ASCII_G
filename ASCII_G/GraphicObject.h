#ifndef ASCIIG_GRAPHICOBJECT_H
#define ASCIIG_GRAPHICOBJECT_H

#include"ChangeMap.h"
#include"Routine.h"
#include<map>

namespace asciig {

	/*
		This is a base class for creating more complex 2d graphics, 
		Each Changemap is frame of the graphic object's animations, with x,y relative to the
		top left corner of the sprite, the active frame can be set for the class
	*/
	class GraphicObject : private std::map<size_t, ChangeMap>, private std::map<size_t, Routine> {
	public:

		/*
			Builds a single frame GraphicObject at an x and y position
		*/
		GraphicObject(const size_t x = 0, const size_t y = 0);

		/*
			Addes a changemap into the list of frames
		*/
		void addFrame(const size_t key, const ChangeMap& frame, const bool setActive = false);

		/*
			Adds a routine to the list of routines
		*/
		void addRoutine(const size_t key, Routine& routine, const bool setActive = false);

		/*
			Sets a frame as active
		*/
		void setFrame(const size_t key);

		/*
			Sets a routine as active
		*/
		void setRoutine(const size_t key);

		/*
			Prints this object to the window at its x and y
			(this function manages the animation loop || showing the set frame)

		*/
		void printSelf(PixelDriver& window, const bool updateWindow = true);

		/*
			Sets the position of the object on the window (0, 0) is top left
		*/
		void setPosition(const size_t x, const size_t y);
	private:
		/*
			Gets the next changemap to display
		*/
		ChangeMap& getNextChangeMap();

		/*
			If this is true, the active frame will show every frame
		*/
		bool frame_active;

		/*
			If this is true, the active routine will play every frame
		*/
		bool routine_active;

		/*
			The routine that is currently being run
		*/
		size_t active_routine;

		/*
			Iterator on the routine
		*/
		Routine::iterator it;

		/*
			The index of the currently shown frame (routines take priority if routine_active is set
		*/
		size_t active_frame;

		/*
			x position of the object
		*/
		size_t x;

		/*
			y position of the object
		*/
		size_t y;
	};

}
#endif