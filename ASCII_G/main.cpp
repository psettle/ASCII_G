#include"ColorString.h"
#include"PixelDriver.h"
#include"Frame.h"
#include"Image.h"
#include"ChangeMap.h"
#include<thread>
#include"Animation.h"
#include"GraphicObject.h"

using namespace asciig;

int main() {
	
		GraphicObject a;

		PixelDriver b(7, 7);

		ChangeMap d;
		d.addChange(Change("Hello", 0, 0));

		d.addChange(Change("Hello", 5, 5));

		a.addFrame(0, d);

		a.addFrame(1, d);

		a.addFrame(2, d);

		a.addFrame(3, d);

		Routine c;

		c.push_back(0);

		c.push_back(1);

		c.push_back(2);

		c.push_back(3);
		auto start = std::chrono::high_resolution_clock::now();
		a.addRoutine(0, c, true);
		for (int i = 0; i < 1000; i++) {
			a.printSelf(b, false);
			a.printSelf(b, false);
			a.printSelf(b, false);
			a.printSelf(b, false);
			b.printFullWindow();
		}
		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>((std::chrono::high_resolution_clock::now() - start)).count() / 4000.0 << std::endl;
		
}