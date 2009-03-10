#include "../gui/Inventory.hpp"
#include "../misc/MediaManager.hpp"
#include "../entities/Equipment.hpp"

// origine de l'inventaire
#define OFFSET_X ((640 - (WIDTH * SLOT_SIZE)) / 2.0)
#define OFFSET_Y ((480 - (HEIGHT * SLOT_SIZE)) / 2.0)


Inventory::Inventory()
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			slots_[i][j].SetImage(GET_IMG("inventory-slot"));
			slots_[i][j].SetPosition(j * SLOT_SIZE + OFFSET_X, i * SLOT_SIZE + OFFSET_Y);
			items_[i][j] = NULL;
		}
	}
	cursor_.coords.x = 0;
	cursor_.coords.y = 0;
	cursor_.sprite.SetImage(GET_IMG("inventory-cursor"));
	cursor_.sprite.SetPosition(OFFSET_X, OFFSET_Y);
}


Inventory::~Inventory()
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if (items_[i][j] != NULL)
			{
				delete items_[i][j];
			}
		}
	}
}


void Inventory::OnEvent(sf::Key::Code code)
{
	int x = cursor_.coords.x;
	int y = cursor_.coords.y;
	bool valid = false;
	switch (code)
	{
		case sf::Key::Up:
			valid = (--y >= 0);
			break;
		case sf::Key::Down:
			valid = (++y < HEIGHT);
			break;
		case sf::Key::Left:
			valid = (--x >= 0);
			break;
		case sf::Key::Right:
			valid = (++x < WIDTH);
			break;
		default:
			break;
	}
	if (valid)
	{
		cursor_.coords.x = x;
		cursor_.coords.y = y;
		cursor_.sprite.SetX(x * SLOT_SIZE + OFFSET_X);
		cursor_.sprite.SetY(y * SLOT_SIZE + OFFSET_Y);
	}
}


void Inventory::Show(sf::RenderWindow& app) const
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			app.Draw(slots_[i][j]);
			if (items_[i][j] != NULL)
			{
				app.Draw(*items_[i][j]);
			}
		}
	}
	app.Draw(cursor_.sprite);
}


void Inventory::AddItem(Equipment* item)
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if (items_[i][j] == NULL)
			{
				items_[i][j] = item;
				int x = (j * SLOT_SIZE) + (SLOT_SIZE - item->GetSize().x) / 2;
				int y = (i * SLOT_SIZE) + (SLOT_SIZE - item->GetSize().y) / 2 + item->GetSize().y;
				item->SetPosition(OFFSET_X + x, OFFSET_Y + y);
				printf("item ajouté en [%d][%d]\n", i, j);
				return;
			}
		}
	}
	puts("inventaire plein");
}