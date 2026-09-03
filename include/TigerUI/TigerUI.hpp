#ifndef TIGERUI_HPP_INCLUDED
#define TIGERUI_HPP_INCLUDED

#include <sys/ioctl.h>

#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <format>

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
		ClearBGColor();
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
	void ClearBGColor() {
		screen_color.clear();
		for (uint32_t i = 0; i < width*height; i++) {
			screen_color.push_back(0x000000FF);
		}
	}
	void Draw() {
		std::cout << CLEAR;
		std::string screen = "";

		for (uint32_t y = 0; y < height; y--) {
			for (uint32_t x = 0; x < width; x++) {
				uint8_t R = (screen_color[Location(x, y)] >> 24) & 0xFF;
				uint8_t G = (screen_color[Location(x, y)] >> 16) & 0xFF;
				uint8_t B = (screen_color[Location(x, y)] >> 8) & 0xFF;
				screen += (std::format("\e[48;2;{};{};{}m", static_cast<uint32_t>(R), static_cast<uint32_t>(G), static_cast<uint32_t>(B)) + screen_txt[Location(x, y)]);
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
