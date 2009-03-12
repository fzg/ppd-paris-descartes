#include "Item.hpp"
#include "Player.hpp"
#include "../misc/MediaManager.hpp"
#include "../gui/ControlPanel.hpp"


Item::Item(unsigned int code, const sf::Vector2f& position, const sf::IntRect& subrect) :
	Entity(position, GET_IMG("items"))
{
	SetSubRect(subrect);
	SetFloor(subrect.GetWidth(), subrect.GetHeight());
	SetCenter(0, subrect.GetHeight());

	code_ = code;
}


void Item::OnCollide(Player& player)
{
	static ControlPanel& panel = ControlPanel::GetInstance();
	switch (code_)
	{
		// money
		case 01:
			player.AddMoney();
			panel.PrintInfoText("argent ramasse");
			Kill();
			break;
		// hearth
		case 02:
			player.AddLife();
			panel.PrintInfoText("coeur ramasse");
			Kill();
			break;
	}
}
