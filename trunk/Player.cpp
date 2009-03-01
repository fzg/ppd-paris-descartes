#include <iostream>
#include <cstring>

#include "Player.hpp"
#include "Game.hpp"
#include "MediaManager.hpp"
#include "Tileset.hpp"
#include "Zone.hpp"

#define SPEED         120
#define FALL_DELAY    1
#define DEFAULT_LIVES 3


Player::Player(const sf::Vector2f& pos, const sf::Input& input) :
	Entity(pos, GET_IMG("player")),
	Animated(&GET_ANIM("player_walk_bottom"), *this),
	input_(input),
	panel_(ControlPanel::GetInstance())
{
	// valeurs magiques... surface de contact au sol
	SetFloor(28, 20);
	
	// Animations de marche
	walk_anims_[UP]		= &GET_ANIM("player_walk_top");
	walk_anims_[DOWN]	= &GET_ANIM("player_walk_bottom");
	walk_anims_[LEFT]	= &GET_ANIM("player_walk_left");
	walk_anims_[RIGHT]	= &GET_ANIM("player_walk_right");
	
	fall_anim_ = &GET_ANIM("player_fall");
	
	// Subrects d'immobilité
	subrects_not_moving_[UP]	= sf::IntRect(0,   0, 32,  48);
	subrects_not_moving_[DOWN]	= sf::IntRect(0,  48, 32,  96);
	subrects_not_moving_[LEFT]	= sf::IntRect(0,  96, 32, 144);
	subrects_not_moving_[RIGHT]	= sf::IntRect(0, 144, 32, 196);
	
	// attribution des touches de déplacement
	move_keys_[UP] = sf::Key::Up;
	move_keys_[DOWN] = sf::Key::Down;
	move_keys_[LEFT] = sf::Key::Left;
	move_keys_[RIGHT] = sf::Key::Right;
	
	// le joueur est de face par défaut
	current_dir_ = DOWN;
	was_moving_ = false;
	SetSubRect(subrects_not_moving_[DOWN]);
	
	SetCenter(0, subrects_not_moving_[DOWN].GetHeight());
	
	lives_ = DEFAULT_LIVES;
	max_lives_ = DEFAULT_LIVES;
	money_ = 42;
	locked_ = false;
	falling_ = false;
	
	panel_.SetLives(lives_);
	panel_.SetRupees(money_);
}


void Player::OnEvent(sf::Key::Code key)
{
	// <DEBUG HACK>
	switch (key)
	{
		// position
		case sf::Key::Space:
			std::cout << " [Player] position: " << GetPosition().x << ", " << GetPosition().y << ";\n"; 
			break;
		// + 1 slot
		case sf::Key::S:
			++max_lives_;
			ControlPanel::GetInstance().AddLifeSlot();
			std::cout << " [Player] added life slot to panel.\n";
			break;
		// +1 vie
		case sf::Key::L:
			if (lives_ < max_lives_)
			{
				++lives_;
				ControlPanel::GetInstance().SetLives(lives_);
				std::cout << " [Player] Added life to panel.\n";
			}
			break;
		// -1 vie (Z comme Ziane :D)
		case sf::Key::Z:
			--lives_;
			ControlPanel::GetInstance().SetLives(lives_);
			std::cout << " [Player] Took away life from panel.\n";
			if (lives_ == 0)
			{
				puts("you're dead, bastard!");
				Kill();
			}
			break;
		// afficher la tile sous nos pieds
		case sf::Key::T:
		{
			int i = (int)GetPosition().x + GetFloorWidth() / 2;
			int j = (int) GetPosition().y - GetFloorHeight() / 2;
	
			i /= Tile::SIZE;
			j /= Tile::SIZE;
		
			int tile = zone_->GetTileAt(i, j);
			Tile::Effect effect = Tileset::GetInstance().GetEffect(tile);
			std::cout << " [Player] à la tile id: " << tile
				<< ", pos: (" << i << ", " << j << "), label: ";
			if (effect == Tile::HOLE)
			{
				puts("Trou");
			}
			else if (effect == Tile::WATER)
			{
				puts("Eau");
			}
			else if (effect == Tile::DEFAULT)
			{
				puts("Default");
			}
			else if (effect == Tile::TELEPORT)
			{
				puts("Téléport");
			}
		}
			break;
		default:
			break;
			
	}
	// </DEBUG HACK>
}


void Player::Update(float frametime)
{
	if (locked_)
		return;
	
	static Game& game = Game::GetInstance();
	static int tile;
	static float fall_timer;
	
	int i = (int) GetPosition().x + GetFloorWidth() / 2;
	int j = (int) GetPosition().y - GetFloorHeight() / 2;
		
	i /= Tile::SIZE;
	j /= Tile::SIZE;
	
	if (!falling_)
	{
		bool moved = false;
		int dx, dy;
		sf::FloatRect rect;
		
		// Chûte-t'on ?
		tile = zone_->GetTileAt(i, j);
		Tile::Effect effect = Tileset::GetInstance().GetEffect(tile);

		if (effect == Tile::HOLE)
		{
			puts(" [Player] falling...");
			falling_ = true;
			Animated::Change(fall_anim_, *this);
			fall_timer = FALL_DELAY;
			return;
		}
		
		if (effect == Tile::TELEPORT)
		{
			Zone::Teleporter tp;
			if (zone_->GetTeleport(i, j, tp))
			{
				puts(" [Player] a activé un téléporteur !");
				game.Teleport((ZoneContainer::MapName) tp.zone_container,
					tp.zone_coords, tp.tile_coords);
				return;
			}
		}
		
		// déplacement
		Direction new_dir;
		for (int dir = 0; dir < COUNT_DIRECTION; ++dir)
		{
			if (input_.IsKeyDown(move_keys_[dir]))
			{
				moved = true;
				new_dir = (Direction) dir;
				dx = dy = 0;
				switch (dir)
				{
					case UP:
						dy = -SPEED;
						break;
					case DOWN:
						dy = SPEED;
						break;
					case LEFT:
						dx = -SPEED;
						break;
					case RIGHT:
						dx = SPEED;
						break;
					default:
						break;
				}
				sf::Vector2f pos = GetPosition();
				pos.x += dx * frametime;
				pos.y += dy * frametime;
			
				rect.Left = pos.x;
				rect.Bottom = pos.y;
				rect.Right = pos.x + GetFloorWidth();
				rect.Top = pos.y - GetFloorHeight();
				
				// on vérifie si on doit changer de zone
				if (rect.Left < 0)
				{
					game.ChangeZone(ZoneContainer::LEFT);
					break;
				}
				else if (rect.Top < 0) 
				{
					game.ChangeZone(ZoneContainer::UP);
					break;
				}
				else if (rect.Right > Zone::WIDTH * Tile::SIZE)
				{
					game.ChangeZone(ZoneContainer::RIGHT);
					break;
				}
				else if (rect.Bottom > Zone::HEIGHT * Tile::SIZE)
				{
					game.ChangeZone(ZoneContainer::DOWN);
					break;
				}
				
				if (zone_->CanMove(this, rect))
				{
					SetPosition(pos);
				}
			}
		}
		// si on a bougé
		if (moved)
		{
			if (new_dir != current_dir_)
			{
				current_dir_ = new_dir;
				Animated::Change(walk_anims_[new_dir], *this);
			}
			Animated::Update(frametime, *this);
			was_moving_ = true;
		}
		else if (was_moving_)
		{
			was_moving_ = false;
			SetSubRect(subrects_not_moving_[current_dir_]);
		}
	}
	else
	{	// En cours de chûte...

		fall_timer -= frametime;
		Animated::Update(frametime, *this);
		if (fall_timer <= 0)
		{
			Zone::Teleporter tp;
			if (zone_->GetTeleport(i, j, tp))
			{
				game.Teleport((ZoneContainer::MapName) tp.zone_container,
					tp.zone_coords, tp.tile_coords);
			}
			else
			{
				--lives_;
				panel_.SetLives(lives_);
				SetPosition(Tile::SIZE, 8 * Tile::SIZE);
			}
			Animated::Change(walk_anims_[current_dir_], *this);
			falling_ = false;
		}
	}
}


void Player::Lock()
{
	locked_ = true;
}


void Player::Unlock()
{
	locked_ = false;
}


void Player::AddLife()
{
	++lives_;
	panel_.SetLives(lives_);
}


void Player::AddMoney()
{
	++money_;
	panel_.SetRupees(money_);
}

