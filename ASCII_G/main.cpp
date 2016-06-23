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
	
		GraphicObject go(0, 0);

		PixelDriver pd(5, 5);

		ChangeMap f1(ColorString(" \b\b \n\b\b\b\b\n\b\b\b\b\n \b\b ", 1, Color::GREEN_BG));

		ChangeMap f2(ColorString("\b \b\b\n\b\b\b \n \b\b\b\n\b\b \b", 1, Color::GREEN_BG));

		ChangeMap f3(ColorString("\b\b \b\n \b\b\b\n\b\b\b \n\b \b\b", 1, Color::GREEN_BG));

		go.addFrame(0, f1);

		go.addFrame(1, f2);

		go.addFrame(2, f3);

		Routine r;

		r.push_back(0);

		r.push_back(1);

		r.push_back(2);

		Image black = Image("     \n     \n     \n     \n     \n");

		go.addRoutine(0, r, true);

		for (int i = 0; i < 1000; i++) {

			black.runFrame(pd, false);
			go.printSelf(pd, false);
			pd.printFullWindow();
			std::this_thread::sleep_for(std::chrono::milliseconds(80));
			go.setPosition(1, 0);

			black.runFrame(pd, false);
			go.printSelf(pd, false);
			pd.printFullWindow();
			std::this_thread::sleep_for(std::chrono::milliseconds(80));
			go.setPosition(1, 1);

			black.runFrame(pd, false);
			go.printSelf(pd, false);
			pd.printFullWindow();
			std::this_thread::sleep_for(std::chrono::milliseconds(80));
			go.setPosition(0, 1);

			black.runFrame(pd, false);
			go.printSelf(pd, false);
			pd.printFullWindow();
			std::this_thread::sleep_for(std::chrono::milliseconds(80));
			go.setPosition(0, 0);
		}
		
		
}