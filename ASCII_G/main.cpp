#include"ColorString.h"
#include"PixelDriver.h"
#include"Frame.h"
#include"Image.h"
#include<thread>

int main() {
	asciig::PixelDriver p(4, 4);
	
	asciig::Frame* video[5];

	asciig::Image image;

	image.addLine(asciig::ColorString(">   ", 1, asciig::Color::GREEN_BG));
	image.addLine(asciig::ColorString(">   ", 1, asciig::Color::GREEN_BG));
	image.addLine(asciig::ColorString(">   ", 1, asciig::Color::GREEN_BG));
	image.addLine(asciig::ColorString(">   ", 1, asciig::Color::GREEN_BG));
	
	video[0] = new asciig::Image(image);

	image.at(0) = asciig::ColorString(" >  ");

	video[1] = new asciig::Image(asciig::ColorString("abcd\nefgh\nhijk\nlmno", 2, asciig::Color::MAGENTA_BG, asciig::Color::WHITE));

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