#include <TigerUI/TigerUI.hpp>

TigerUI tui;

void command(std::string command) {
	// Now you can clear and update elements
	tui.Draw();
}

int main() {
	// Elements that do not update
	
	// Change the background
	tui.BG = 0x101010FF;
	tui.ClearBGColor();
	// Change the background in a area
	tui.DrawBGBox(0.1f, 0.1f, 0.9f, 0.9f, 0x1A1A1AFF);
	// Change the text color in an area
	tui.DrawTextColorBox(0.1f, 0.1f, 0.9f, 0.9f, 0x1A1AFF00);
	tui.DrawTextColorBox(0.6f, 0.1f, 0.9f, 0.9f, 0xFFFFFF01);
	// Draw text
	tui.Text("Hello world!\nHello world!\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!", 0.5, 0.5);
	tui.Text("Commands to use:\nThere are no commands available right now.", 0.8, 0.2);
	// Listen for commands
	tui.CommandListener(&command);

	return 0;
}
