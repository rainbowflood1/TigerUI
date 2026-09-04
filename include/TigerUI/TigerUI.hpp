#ifndef TIGERUI_HPP_INCLUDED
#define TIGERUI_HPP_INCLUDED

#include <sys/ioctl.h>

#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
//#include <format>
#include <functional>
#include <cmath>

#define CLEAR (std::string) "\ec"

typedef uint32_t Color;

class TigerUI {
public:
	int width;
	int height;
	std::string screen_txt = "";
	std::vector<uint32_t> screen_color;
	std::vector<uint32_t> screen_text_color;
	bool stop = false;
	
	TigerUI() {
		struct winsize ws;
		ioctl(0, TIOCGWINSZ, &ws);
		height = ws.ws_row-1;
		width = ws.ws_col;
		ClearTXT();
		ClearBGColor();
		ClearTextColor();
	}
	~TigerUI() {
		std::cout << "\e[0m";
	}
	void Text(std::string str, float x, float y) {
		uint16_t newlines = 0;
		uint16_t x_pos = 0;

		uint32_t str_size = str.length();
		for (uint32_t i = 0; i < str_size; i++) {
			x_pos++;
			char string = str[i];

			if (string == '\n') {
				// The text x axis position starts back to 0 when there is a newline character
				x_pos = 0;
				// This value is used to move the text down when there is a newline
				newlines++;
				continue;
			}
			screen_txt[Location((int) std::round(x*width)+(x_pos - (int)std::round(str_size*0.5)), (int) std::round(y*height)+newlines)] = str[i];
		}
	}
	void ClearConsole() {
		std::cout << CLEAR;
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
	void ClearTextColor() {
		screen_text_color.clear();
		for (uint32_t i = 0; i < width*height; i++) {
			screen_text_color.push_back(0xFFFFFFFF);
		}
	}
	void DrawBGBox(float x1, float y1, float x2, float y2, Color color) {
		for (uint32_t x = (int) std::round(x1*width); x < (int) std::round(x2*width); x++) {
			for (uint32_t y = (int) std::round(y1*height); y < (int) std::round(y2*height); y++) {
				screen_color[Location(x, y)] = color;
			}
		}
	}
	void DrawTextColorBox(float x1, float y1, float x2, float y2, Color color) {
		for (uint32_t x = (int) std::round(x1*width); x < (int) std::round(x2*width); x++) {
			for (uint32_t y = (int) std::round(y1*height); y < (int) std::round(y2*height); y++) {
				screen_text_color[Location(x, y)] = color;
			}
		}
	}
	void CommandListener(std::function<void(std::string)> commandlistenerfunction) {
		std::string command = "";
		while (stop == false) {
			ClearConsole();
			commandlistenerfunction(command);
			std::getline(std::cin, command);
		}
	}
	void Draw() {
		std::cout << "\e[0m" << CLEAR;
		std::string screen = "";

		for (uint32_t y = 0; y < height; y++) {
			for (uint32_t x = 0; x < width; x++) {
				uint8_t BG_R = (screen_color[Location(x, y)] >> 24) & 0xFF;
				uint8_t BG_G = (screen_color[Location(x, y)] >> 16) & 0xFF;
				uint8_t BG_B = (screen_color[Location(x, y)] >> 8) & 0xFF;

				uint8_t TXT_R = (screen_text_color[Location(x, y)] >> 24) & 0xFF;
				uint8_t TXT_G = (screen_text_color[Location(x, y)] >> 16) & 0xFF;
				uint8_t TXT_B = (screen_text_color[Location(x, y)] >> 8) & 0xFF;
				//screen += (std::format("\e[48;2;{};{};{}m", static_cast<uint32_t>(BG_R), static_cast<uint32_t>(BG_G), static_cast<uint32_t>(BG_B)) + std::format("\e[38;2;{};{};{}m", static_cast<uint32_t>(TXT_R), static_cast<uint32_t>(TXT_G), static_cast<uint32_t>(TXT_B)) + screen_txt[Location(x, y)]);
				
				
				screen += (std::string) "\e[48;2;" + std::to_string(static_cast<uint32_t>(BG_R)) + (std::string) ";" + std::to_string(static_cast<uint32_t>(BG_G)) + (std::string) ";" + std::to_string(static_cast<uint32_t>(BG_B)) + (std::string) "m" + (std::string) "\e[38;2;" + std::to_string(static_cast<uint32_t>(TXT_R)) + (std::string) ";" + std::to_string(static_cast<uint32_t>(TXT_G)) + (std::string) ";" + std::to_string(static_cast<uint32_t>(TXT_B)) + (std::string) "m" + screen_txt[Location(x, y)];
			}
			screen += "\n";
		}
		std::cout << screen << std::endl << "\e[0m> ";
	}
	uint32_t Location(uint16_t x, uint16_t y) {
		return (y * width) + x;
	}
};


#endif
