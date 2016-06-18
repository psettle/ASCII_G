#include"ColorString.h"
#include"PixelDriver.h"

int main() {
	asciig::PixelDriver p(20, 20);
	asciig::PixelDriver q(20, 20);
	p.putsXY(5, 5, asciig::ColorString("hello", 1, asciig::Color::GREEN));
	
	asciig::ColorString helo = asciig::ColorString("Bye bye", 2, asciig::Color::BLACK, asciig::Color::GREEN_BG);
	if (helo == helo) {
		p.putsXY(0, 0, helo);
	}
	
}