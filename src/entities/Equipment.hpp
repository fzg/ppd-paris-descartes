#ifndef EQUIPMENT_HPP
#define EQUIPMENT_HPP

#include "Item.hpp"


class Equipment: public Item
{
public:
	Equipment(int type_id, const sf::Vector2f& position, const sf::IntRect& subrect);

	void OnCollide(Player& player);
private:
};


#endif /* EQUIPMENT_HPP */
