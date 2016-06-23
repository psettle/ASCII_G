#include"GraphicObject.h"

namespace asciig {
	GraphicObject::GraphicObject(const size_t x, const size_t y) {
			this->frame_active = false;
			this->routine_active = false;
			this->x = x;
			this->y = y;
	}

	void GraphicObject::addFrame(const size_t key, const ChangeMap& frame, const bool setActive) {
		std::map<size_t, ChangeMap>::emplace(key, frame);
		if (setActive) {
			this->active_frame = key;
			this->frame_active = true;
			this->routine_active = false;
		}
	}

	void GraphicObject::addRoutine(const size_t key, Routine& routine, const bool setActive) {
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

	void GraphicObject::setFrame(const size_t key) {
		if (std::map<size_t, ChangeMap>::find(key) != std::map<size_t, ChangeMap>::end()) {
			this->active_frame = key;
			this->frame_active = true;
			this->routine_active = false;
		}
	}

	void GraphicObject::setRoutine(const size_t key) {
		if (std::map<size_t, Routine>::find(key) != std::map<size_t, Routine>::end()) {
			this->active_routine = key;
			this->it = std::map<size_t, Routine>::at(key).begin();
			this->frame_active = false;
			this->routine_active = true;
		}
	}

	void GraphicObject::printSelf(PixelDriver& window, const bool updateWindow) {
		ChangeMap next = this->getNextChangeMap();
		next.reAlign(this->x, this->y);
		next.runFrame(window, updateWindow);
	}

	void GraphicObject::setPosition(const size_t x, const size_t y) {
		this->x = x;
		this->y = y;
	}

	ChangeMap& GraphicObject::getNextChangeMap() {
		if (this->frame_active) {
			return std::map<size_t, ChangeMap>::at(this->active_frame);
		}
		else if (this->routine_active) {
			size_t toReturn = *(this->it);
			this->it++;
			if (it == std::map<size_t, Routine>::at(this->active_routine).end()) {
				this->it = std::map<size_t, Routine>::at(this->active_routine).begin();
			}
			return std::map<size_t, ChangeMap>::at(toReturn);
		}
		else {
			return ChangeMap();
		}
	}
}