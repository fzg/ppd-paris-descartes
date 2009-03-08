#ifndef DECL_HPP
#define DECL_HPP

#include <SFML/Network.hpp>

class Player{
public:
    Player(int px=0, int py=0){
        x = px;
        y = py;
    }

    // D�dicasse � Ziane
    int x, y;
};

sf::Packet& operator<<(sf::Packet& p, const Player& pl){
        return p << pl.x << pl.y;
}
sf::Packet& operator>>(sf::Packet& p, Player& pl){
        return p >> pl.x >> pl.y;
}

#endif
