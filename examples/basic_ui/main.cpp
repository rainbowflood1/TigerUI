#include <TigerUI/TigerUI.hpp>

TigerUI tui;

void command(std::string command) {
	// Now you can clear and update elements
	tui.Draw();
}

int main() {
	// Elements that do not update
	tui.DrawBGBox(0.1f, 0.1f, 0.9f, 0.9f, 0x1A1A1AFF);
	tui.DrawTextColorBox(0.1f, 0.1f, 0.9f, 0.9f, 0x1A1AFFFF);
	tui.Text("Hello world!", 0.5, 0.5);
	tui.DrawTextColorBox(0.6f, 0.1f, 0.9f, 0.9f, 0xFFFFFFFF);
	tui.Text("Commands to use:\nThere are no commands available right now.", 0.8, 0.2);
	tui.CommandListener(&command);

	return 0;
}
