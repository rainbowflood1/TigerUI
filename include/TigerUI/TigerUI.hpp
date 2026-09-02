#ifndef TIGERUI_HPP_INCLUDED
#define TIGERUI_HPP_INCLUDED

#include <sys/ioctl.h>

#include <iostream>
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
		ioctl(0, TIOCGWINSZ, &ws);
		height = ws.ws_row;
		width = ws.ws_col;
		ClearTXT();
	}
	void Text(std::string str, uint32_t x, uint32_t y) {
		for (uint32_t i = 0; i < str.length(); i++) {
			screen_txt[Location(x, y)+i] = str[i];
		}
	}
	void ClearTXT() {
		screen_txt = "";
		for (uint32_t i = 0; i < width*height; i++) {
			screen_txt += " ";
		}
	}
	void Draw() {
		std::cout << CLEAR;
		std::string screen = "";


		for (uint32_t y = height; y < 0; y--) {
			for (uint32_t x = 0; x < width; x++) {
				screen += screen_txt[Location(x, y)];
			}
			screen += "\n";
		}


		std::cout << screen;
	}
	uint32_t Location(uint16_t x, uint16_t y) {
		return (y * width) + x;
	}
};


#endif
