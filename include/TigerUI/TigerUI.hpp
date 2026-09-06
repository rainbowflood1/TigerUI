#ifndef TIGERUI_HPP_INCLUDED
#define TIGERUI_HPP_INCLUDED

#include <sys/ioctl.h>

#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <functional>
#include <sstream>
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
	Color BG = 0x000000FF;
	
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
	void Text(std::string str, float x, float y, bool centered = true) {
		uint16_t newlines = 0;
		uint16_t x_pos = 0;

		uint32_t x_character_cell_pos = (int) std::round(x*width);
		uint32_t y_character_cell_pos = (int) std::round(y*height);
		std::vector<std::string> text_newlines;
		std::string text = "";
		std::stringstream strstreammessage(str);
		while (std::getline(strstreammessage, text, '\n')) {
			text_newlines.push_back(text);
		}
	
		for (std::string string_fragments : text_newlines) {
			uint32_t str_size = string_fragments.length();
			for (uint32_t i = 0; i < str_size; i++) {
				x_pos++;

				char string = string_fragments[i];

				uint32_t x_character_translation = x_character_cell_pos + x_pos;
				if (centered == true) {
					x_character_translation -= (int) std::round(str_size*0.5);
				}

				uint32_t y_character_translation = y_character_cell_pos+newlines;

				// Ignore replacing a character on screen_txt with a position outside the screen
				if (x_character_translation < width && x_character_translation > 0 && y_character_translation < height && y_character_cell_pos > 0) {
					screen_txt[Location(x_character_translation, y_character_translation)] = string;
				}
			}
			x_pos = 0;
			// This value is used to move the text down when there is a newline
			newlines++;
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
			screen_color.push_back(BG);
		}
	}
	void ClearTextColor() {
		screen_text_color.clear();
		for (uint32_t i = 0; i < width*height; i++) {
			screen_text_color.push_back(0xFFFFFF00);
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
				uint32_t cell_location_index = Location(x, y);
				uint8_t BG_R = (screen_color[cell_location_index] >> 24) & 0xFF;
				uint8_t BG_G = (screen_color[cell_location_index] >> 16) & 0xFF;
				uint8_t BG_B = (screen_color[cell_location_index] >> 8) & 0xFF;

				uint8_t TXT_R = (screen_text_color[cell_location_index] >> 24) & 0xFF;
				uint8_t TXT_G = (screen_text_color[cell_location_index] >> 16) & 0xFF;
				uint8_t TXT_B = (screen_text_color[cell_location_index] >> 8) & 0xFF;
				uint8_t TXT_TYPE = screen_text_color[cell_location_index] & 0xFF;

				// Change appearance of the text
				screen += "\e[" + std::to_string(TXT_TYPE) + "m";
				// Change the background color
			       	screen += (std::string) "\e[48;2;" + std::to_string(BG_R) + (std::string) ";" + std::to_string(BG_G) + (std::string) ";" + std::to_string(BG_B) + (std::string) "m";
				// Change the text color
			        screen += (std::string) "\e[38;2;" + std::to_string(TXT_R) + (std::string) ";" + std::to_string(TXT_G) + (std::string) ";" + std::to_string(TXT_B) + (std::string) "m";
				// Print out the text
				screen += screen_txt[cell_location_index];
			}
			screen += "\n";
		}
		std::cout << screen << "\e[0m> ";
	}
	uint32_t Location(uint16_t x, uint16_t y) {
		return (y * width) + x;
	}
};


#endif
