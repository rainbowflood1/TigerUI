#ifndef TIGERUI_HPP_INCLUDED
#define TIGERUI_HPP_INCLUDED

#include <sys/ioctl.h>
#include <string>


class TigerUI {
public:
	int width;
	int height;
	std::string screen_txt = "";

	TigerUI() {
		struct winsize ws;
		ioctl(TIOCGWINSZ, 0, ws);
		height = ws.ws_row;
		width = ws.ws_col;
		for (uint32_t i = 0; i < width*height; i++) {
			screen_txt += " ";
		}
	}
	void Draw() {
		
	}
};


#endif
