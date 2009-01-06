#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "Zone.hpp"
#include "Player.hpp"
#include "ControlPanel.hpp"


class Game
{
	public:
		static Game& GetInstance();

		/**
		 * Lancer l'application
		 */
		void Run();

		enum Direction
		{
			UP, DOWN, LEFT, RIGHT
		};

		/**
		 * Demander un changement de zone
		 * @param[in] dir: direction souhaitée
		 */
		void ChangeZone(Direction dir);
		
		inline sf::RenderWindow& GetWind() {
			return app_;
		}

	private:
		Game();
		Game(const Game&);
		~Game();

		enum
		{
			// dimensions du jeu en nombre de zones
			GAME_WIDTH = 2, GAME_HEIGHT = 2
		};

		Zone* zones_[GAME_HEIGHT][GAME_WIDTH];
		sf::Vector2i cds_zone_; // coordonnées de la zone courante
		
		Zone* active_zone_;
		Zone* next_zone_;
		Player* player_;
		
		ControlPanel& panel_;
		
		sf::RenderWindow app_;
};

#endif /* guard GAME_HPP */

