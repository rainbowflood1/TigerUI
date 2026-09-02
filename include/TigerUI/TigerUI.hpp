#ifndef TIGERUI_HPP_INCLUDED
#define TIGERUI_HPP_INCLUDED

#include <sys/ioctl.h>
#include <cstdint>
#include <string>
#include <vector>

#define CLEAR (std::string) "\e[2Jm"


class TigerUI {
public:
	int width;
	int height;
	std::string screen_txt = "";
	std::vector<uint32_t> screen_color;

	TigerUI() {
		struct winsize ws;
		ioctl(TIOCGWINSZ, 0, ws);
		height = ws.ws_row;
		width = ws.ws_col;
		ClearTXT();
	}
	void Text(std::string str, uint32_t x, uint32_t y) {
		for (uint32_t i = 0; i < str.length(); i++) {
			screen_txt[(y * height) + (x+i)] = str[i];
		}
	}
	void ClearTXT() {
		screen_txt = "";
		for (uint32_t i = 0; i < width*height; i++) {
			screen_txt += " ";
		}
	}
	void Draw() {
		
	}
};


#endif
