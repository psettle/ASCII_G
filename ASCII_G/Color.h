#ifndef ASCII_COLOR_H
#define ASCII_COLOR_H

namespace asciig {

	typedef int ColorCode;

	class Color {
	public:
		//text colors
		const static ColorCode BLACK = 30;
		const static ColorCode RED = 31;
		const static ColorCode GREEN = 32;
		const static ColorCode YELLOW = 33;
		const static ColorCode BLUE = 34;
		const static ColorCode MAGENTA = 35;
		const static ColorCode CYAN = 36;
		const static ColorCode WHITE = 37;
		//background colors
		const static ColorCode BLACK_BG = 40;
		const static ColorCode RED_BG = 41;
		const static ColorCode GREEN_BG = 42;
		const static ColorCode YELLOW_BG = 43;
		const static ColorCode BLUE_BG = 44;
		const static ColorCode MAGENTA_BG = 45;
		const static ColorCode CYAN_BG = 46;
		const static ColorCode WHITE_BG = 47;
		//control constants
		const static ColorCode RESET = 0;
		const static ColorCode BOLD = 1;
		const static ColorCode UNDERLINE = 4;
	};
}

#endif