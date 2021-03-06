#ifndef ASCIIG_CHANGEMAP_H
#define ASCIIG_CHANGEMAP_H

#include"Frame.h"
#include"Change.h"
#include"Image.h"

namespace asciig {

	/*
		A list of changes to a window, this is a faster way to modify a window than using a full image
	*/
	class ChangeMap : public Frame, public std::vector<Change> {
	public:
		/*
			Creates an empty ChangeMap
		*/
		ChangeMap() {}

		/*
			Copt ctor
		*/
		ChangeMap(const ChangeMap& other);

		/*
			Copies a vector of changes
		*/
		ChangeMap(const std::vector<Change>& other);

		/*
			Sets image as the required change at the given x and y
		*/
		ChangeMap(const Image& image, const size_t x, const size_t y);

		/*
			Adds a new change to the map
		*/
		void addChange(const Change& change) { this->push_back(change); }

		/*
			Applies this changemap to the window
		*/
		void runFrame(PixelDriver& window) const;

		/*
			Calls parent destructors
		*/
		~ChangeMap() {}
	};
}

#endif