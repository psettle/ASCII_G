#include"ColorString.h"
#include"PixelDriver.h"
#include"Frame.h"
#include"Image.h"
#include"ChangeMap.h"
#include<thread>
#include"Animation.h"

using namespace asciig;

int main() {
		Animation animation(10, 1);

		std::vector<ChangeMap> changes(9);

		animation.addImage(Image(">         "));

		for (size_t i = 0; i < changes.size(); i++) {
			changes[i].addChange(Change("=", i, 0));
			changes[i].addChange(Change(">", i + 1, 0));
			animation.addChangeMap(changes[i]);
		}

	
		

		int i = 0;
		while (1) {
			animation.runAnimation(0);
			std::cout << i++;
		}
}