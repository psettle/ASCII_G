#include"ColorString.h"
#include"PixelDriver.h"

int main() {
	asciig::PixelDriver p(20, 20);

	p.putsXY(5, 5, asciig::ColorString("      ", 1, asciig::Color::GREEN_BG));
}