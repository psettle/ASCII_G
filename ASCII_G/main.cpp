#include"ColorString.h"
#include"PixelDriver.h"

int main() {
	asciig::PixelDriver p(20, 20);
	asciig::PixelDriver q(20, 20);
	p.putsXY(5, 5, asciig::ColorString("hello", 1, asciig::Color::GREEN));
	q.putsXY(5, 5, asciig::ColorString("hello", 1, asciig::Color::GREEN));

	q.resize(1, 1);
}