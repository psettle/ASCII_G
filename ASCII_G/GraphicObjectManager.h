#ifndef ASCIIG_GRAPHICOBJECTMANAGER_H
#define ASCIIG_GRAPHICOBJECTMANAGER_H

#include"GraphicObject.h"
#include<memory>
#include<thread>

namespace asciig {
	class GraphicObjectManager : private std::map<size_t, GraphicObject> {
	public:
		/*
			Creates a new object manager

			if type == "framerate", then framerate is used as frames per second
			else if type == "delay", then framerate is used as milliseconds between frames instead of framerate
			else framerate is used as frames per second
		*/
		GraphicObjectManager(const size_t width, const size_t height, const size_t framerate, Image background, std::string type = "framerate")
			: window(width, height), background(background)
		{
			if (type == "framerate") {
				this->frame_delay = floor(1000.0 / framerate);
			} else if (type == "delay") {
				this->frame_delay = framerate;
			} else {
				this->frame_delay = floor(1000.0 / framerate);
			}
		}

		/*
			Adds a new GraphicObject ( or subclass ) to this 
		*/
		void addObject(const size_t key, const GraphicObject& object) {
			std::map<size_t, GraphicObject>::emplace(key, object);
		}

		/*
			get an object to change its state
		*/
		GraphicObject& at(const size_t key) {
			return std::map<size_t, GraphicObject>::at(key);
		}

		/*
			Starts the processor running
		*/
		void start() { this->last_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()); }

		/*
			runs the next frame after at least the minimum delay for the framerate has elapsed
		*/
		void runFrame() {
			//wait until time >= last_time + frame_delay
			std::chrono::milliseconds time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

			while (this->last_time + std::chrono::milliseconds(this->frame_delay) > time) {
				time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}

			for (std::map<size_t, GraphicObject>::iterator it = this->begin(); it != this->end(); it++) {
				it->second.printSelf(this->window, false);
			}
			this->window.printFullWindow();
		}
	private:
		/*
			number of milliseconds between frames
		*/
		size_t frame_delay;

		/*
			last time a frame was run
		*/
		std::chrono::milliseconds last_time;

		/*
			Graphics manager
		*/
		PixelDriver window;

		/*
			Background to be set every frame
		*/
		Image background;
	};
}

#endif
