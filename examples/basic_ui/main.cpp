#include <TigerUI/TigerUI.hpp>

TigerUI tui;

void command(std::string command) {
	// Now you can clear and update elements
	tui.Draw();
}

int main() {
	// Elements that do not update
	tui.DrawBGBox(0.1f, 0.1f, 0.9f, 0.9f, 0x1A1A1AFF);
	tui.DrawTextColorBox(0.1f, 0.1f, 0.9f, 0.9f, 0x1A1AFF00);
	tui.Text("Hello world!\nHello world!\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!", 0.5, 0.5);
	tui.DrawTextColorBox(0.6f, 0.1f, 0.9f, 0.9f, 0xFFFFFF01);
	tui.Text("Commands to use:\nThere are no commands available right now.", 0.8, 0.2);
	tui.CommandListener(&command);

	return 0;
}
