#include"ColorString.h"
#include"PixelDriver.h"
#include"Frame.h"
#include"Image.h"
#include<thread>
#include"Animation.h"

using namespace asciig;

int main() {
		Animation animation(10, 1);

		animation.addImage(Image(">         "));
		animation.addImage(Image("=>        "));
		animation.addImage(Image("==>       "));
		animation.addImage(Image("===>      "));
		animation.addImage(Image("====>     "));
		animation.addImage(Image("=====>    "));
		animation.addImage(Image("======>   "));
		animation.addImage(Image("=======>  "));
		animation.addImage(Image("========> "));
		animation.addImage(Image("=========>"));

		while(1)
		animation.runAnimation(100);
}