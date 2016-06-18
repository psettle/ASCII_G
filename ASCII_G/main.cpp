#include"ColorString.h"
#include"PixelDriver.h"
#include"Frame.h"
#include"Image.h"
#include<thread>

int main() {
	asciig::PixelDriver p(4, 4);
	
	asciig::Frame* video[5];

	std::vector<asciig::ColorString> image;
	image.push_back(asciig::ColorString(">   ", 1, asciig::Color::GREEN_BG));
	image.push_back(asciig::ColorString(">   ", 1, asciig::Color::GREEN_BG));
	image.push_back(asciig::ColorString(">   ", 1, asciig::Color::GREEN_BG));
	image.push_back(asciig::ColorString(">   ", 1, asciig::Color::GREEN_BG));
	
	video[0] = new asciig::Image(image);

	image.at(0) = asciig::ColorString(" >  ");

	video[1] = new asciig::Image(image);

	image.at(1) = asciig::ColorString(" >  ");

	video[2] = new asciig::Image(image);

	image.at(2) = asciig::ColorString(" >  ");

	video[3] = new asciig::Image(image);

	image.at(3) = asciig::ColorString(" >  ");

	video[4] = new asciig::Image(image);

	for (int i = 0; i < 5; i++) {
		video[i]->runFrame(p);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	
}