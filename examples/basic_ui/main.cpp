#include <TigerUI/TigerUI.hpp>

int main() {
	TigerUI tui;
	tui.DrawBGBox(0.1f, 0.1f, 0.9f, 0.9f, 0x1A1A1AFF);
	tui.Text("Hello world!", 0.5, 0.5);
	tui.Draw();

	return 0;
}
