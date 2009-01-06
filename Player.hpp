#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Animated.hpp"
#include "Entity.hpp"

/**
 * Joueur contrôlable par l'utilisateur
 */
class Player: public Entity, public Animated
{
	public:
		Player(const sf::Vector2f& pos, const sf::Input& input);
		
		/**
		 * Gérer un évènement
		 */
		void OnEvent(const sf::Event& event);
	
		void Move(float frametime);

		/**
		 * @brief Déplacer l'entité, si possible et en gérant le changement de zone
		 * @param[in] direction
		 * @param[in] frametime
		 * @return true si le déplacement a été effectué
		 */
		bool Move(Direction dir, float frametime);

		/**
		 * @brief Déplace l'entité vers le haut, si possible, tout en gérant les
		 * changement de zone
		 * @return true si déplacement est effectué
		 */
		//bool MoveUp(float frametime);

		/**
		 * @brief Déplace l'entité vers la droite, si possible, tout en gérant les
		 * changement de zone
		 * @return true si déplacement est effectué
		 */
		//bool MoveRight(float frametime);

		/**
		 * @brief Déplace l'entité vers le bas, si possible, tout en gérant les
		 * changement de zone
		 * @return true si déplacement est effectué
		 */
		//bool MoveDown(float frametime);

		/**
		 * @brief Déplace l'entité vers la gauche, si possible, tout en gérant les
		 * changement de zone
		 * @return true si déplacement est effectué
		 */
		//bool MoveLeft(float frametime);

		/**
		 * @brief Déplace l'entité au hasard, si possible, tout en gérant les
		 * changement de zone
		 * @return true si déplacement est effectué
		 */
		//bool MoveRandomly(float frametime);*/

	private:
		/**
		 * Met à jour le subrect du joueur (uniquement si nécessaire)
		 * @param[in] dir: direction prise
		 * @param[in] moving: true si le joueur bouge
		 */
		void UpdateSubRect(Direction dir, bool moving = true);
		
		
		/**
		 * Détermine si deux directions forment une diagonale valide
		 * Par convention, si dir1 == dir2, renvoie false.
		 * @param[in] dir1
		 * @param[in] dir2
		 */
		 bool IsDiag(Direction dir1, Direction dir2);
		 
		 
		// Keycodes des mouvements
		sf::Key::Code move_keys_[COUNT_DIRECTION];
		
		// Animations de déplacement
		Animation* walk_anims_[COUNT_DIRECTION];
		
		// Subrects du sprite immobile
		sf::IntRect subrects_not_moving_[COUNT_DIRECTION];
		
		Direction current_dir_;
		const sf::Input& input_;
};

#endif /* guard PLAYER_HPP */
