#include <TigerUI/TigerUI.hpp>

TigerUI tui;

void command(std::string command) {
	tui.Draw();
}

int main() {
	tui.DrawBGBox(0.1f, 0.1f, 0.9f, 0.9f, 0x1A1A1AFF);
	tui.DrawTextColorBox(0.1f, 0.1f, 0.9f, 0.9f, 0x1A1AFFFF);
	tui.Text("Hello world!", 0.5, 0.5);
	tui.CommandListener(&command);

	return 0;
}
