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
			Builds a single frame GraphicObject
		*/
		GraphicObject(const size_t x = 0, const size_t y = 0) {
			this->frame_active = false;
			this->routine_active = false;
			this->x = x;
			this->y = y;
		}

		/*
			Addes a changemap into the list of frames
		*/
		void addFrame(const size_t key, const ChangeMap& frame, const bool setActive = false) { 
			std::map<size_t, ChangeMap>::emplace(key, frame); 
			if (setActive) {
				this->active_frame = key;
				this->frame_active = true;
				this->routine_active = false;
			}
			
		}

		/*
			Adds a routine to the list of routines
		*/
		void addRoutine(const size_t key, Routine& routine, const bool setActive = false) { 
			//check that all the keys on the iterator are valid before adding it
			for (Routine::iterator it = routine.begin(); it != routine.end(); it++) {
				if (std::map<size_t, ChangeMap>::find(*it) == std::map<size_t, ChangeMap>::end()) {
					//if the key from the routine isnt in the map of changes, done do anything
					return;
				}
			}
			
			std::map<size_t, Routine>::emplace(key, routine);
			if (setActive) {
				this->active_routine = key;
				this->routine_active = true;
				this->frame_active = false;
				this->it = std::map<size_t, Routine>::at(key).begin();
			}
		}

		/*
			Sets a frame as active
		*/
		void setFrame(const size_t key) {
			if (std::map<size_t, ChangeMap>::find(key) != std::map<size_t, ChangeMap>::end()) {
				this->active_frame = key;
				this->frame_active = true;
				this->routine_active = false;
			}
		}

		/*
			Sets a routine as active
		*/
		void setRoutine(const size_t key) {
			if (std::map<size_t, Routine>::find(key) != std::map<size_t, Routine>::end()) {
				this->active_routine = key;
				this->it = std::map<size_t, Routine>::at(key).begin();
				this->frame_active = false;
				this->routine_active = true;
			}
		}

		/*
			Prints this object to the window at its x and y
			(this function manages the animation loop || showing the set frame)

		*/
		void printSelf(PixelDriver& window, const bool updateWindow = true) {
			ChangeMap next = this->getNextChangeMap();
			next.reAlign(this->x, this->y);
			next.runFrame(window, updateWindow);
		}

		/*
			Sets the position of the object on the window (0, 0) is top left
		*/
		void setPosition(const size_t x, const size_t y) {
			this->x = x;
			this->y = y;
		}
	private:
		/*
			Gets the next changemap to display
		*/
		const ChangeMap getNextChangeMap() {
			if (this->frame_active) {
				return std::map<size_t, ChangeMap>::at(this->active_frame);
			} else if (this->routine_active) {
				size_t toReturn = *(this->it);
				this->it++;
				if (it == std::map<size_t, Routine>::at(this->active_routine).end()) {
					this->it = std::map<size_t, Routine>::at(this->active_routine).begin();
				}
				return std::map<size_t, ChangeMap>::at(toReturn);
			} else {
				return ChangeMap();
			}		 
		}
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