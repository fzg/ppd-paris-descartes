#include "Game.hpp"

#include "Enemy.hpp"
#include "Splash.hpp"

#define APP_WIDTH  (Tile::SIZE * Zone::WIDTH)
#define APP_HEIGHT (Tile::SIZE * Zone::HEIGHT)
#define APP_BPP    32
#define APP_FPS    60
#define APP_TITLE  "PPD"


Game& Game::GetInstance()
{
	static Game self;
	return self;
}


Game::Game() :
	panel_		(ControlPanel::GetInstance())
{
	app_.Create(sf::VideoMode(APP_WIDTH, APP_HEIGHT, APP_BPP), APP_TITLE);
	app_.SetFramerateLimit(APP_FPS);

	player_ = new Player(sf::Vector2f(200, 200), app_.GetInput());

	for (int i = 0; i < GAME_HEIGHT; ++i)
	{
		for (int j = 0; j < GAME_WIDTH; ++j)
		{
			zones_[i][j] = new Zone();
		}
	}

	// chargement des zones (avec ajout de quelques items)
	zones_[0][0]->Load("data/map/zone1.txt", app_);
	zones_[0][0]->PlaceStaticItem(10, 2);
	zones_[0][0]->PlaceStaticItem(10, 4);
	zones_[0][0]->PlaceStaticItem(5, 11);
	zones_[0][0]->PlaceStaticItem(5, 10);
	zones_[0][0]->PlaceStaticItem(15, 2);
	zones_[0][0]->PlaceStaticItem(17, 2);
	zones_[0][0]->PlaceStaticItem(16, 8);
	zones_[0][0]->AddEntity(new Enemy(sf::Vector2f(110, 90)));
	zones_[0][0]->AddEntity(new Enemy(sf::Vector2f(110, 200)));
	zones_[0][0]->AddEntity(new Enemy(sf::Vector2f(400, 200)));
	zones_[0][0]->AddEntity(new Enemy(sf::Vector2f(320, 350)));
	
	zones_[0][1]->Load("data/map/zone2.txt", app_);
	zones_[0][1]->PlaceStaticItem(12, 7);
	zones_[0][1]->PlaceStaticItem(14, 7);
	zones_[0][1]->PlaceStaticItem(12, 9);
	zones_[0][1]->PlaceStaticItem(14, 9);

	zones_[1][0]->Load("data/map/zone3.txt", app_);
	zones_[1][0]->AddEntity(new Enemy(sf::Vector2f(200, 200)));

	zones_[1][1]->Load("data/map/zone4.txt", app_);
	zones_[1][1]->PlaceStaticItem(10, 11);


	cds_zone_.x = 0;
	cds_zone_.y = 0;

	active_zone_ = NULL;
	next_zone_ = NULL;
	
	panel_.SetRupees(42);
}


Game::~Game()
{
	for (int i = 0; i < GAME_HEIGHT; ++i)
	{
		for (int j = 0; j < GAME_WIDTH; ++j)
		{
			delete zones_[i][j];
		}
	}
	SetMusic(-1);	// What about a shared Defines.h file which would
					// state, say, "#define UNDEF" -1 ?
}


void Game::Run()
{
	sf::Event event;
	bool running = true;

	active_zone_ = zones_[cds_zone_.y][cds_zone_.x];
	next_zone_ = active_zone_;
	active_zone_->AddEntity(player_);
	Entity::SetActiveZone(active_zone_);

	float frametime;
	
#ifndef NO_SPLASH
	if (sf::PostFX::CanUsePostFX())
	{
		Splash s(app_);
		s.Run();
	}
#endif

#ifdef DUMB_MUSIC
	SetMusic(active_zone_->GetMusic());
#endif

	
	while (running)
	{
		while (app_.GetEvent(event))
		{
			if (event.Type == sf::Event::Closed)
			{
				running = false;
			}
			else
			{
				player_->OnEvent(event);
			}
		}
		frametime = app_.GetFrameTime();
		active_zone_->Update(frametime);
		
		active_zone_->Show(app_);
		panel_.Show(app_, frametime); // On pourrait faire un Update, mais a priori
									  // "Anim" seulement quand ne reste qu'une vie
		app_.Display();
		
		// si demande de changement de zone
		if (next_zone_ != active_zone_)
		{
			active_zone_->RemoveEntity(player_);
			active_zone_ = next_zone_;
			active_zone_->AddEntity(player_);
			Entity::SetActiveZone(active_zone_);
		}
	}
	app_.Close();
	
}


void Game::ChangeZone(Direction dir)
{
	int x = cds_zone_.x;
	int y = cds_zone_.y;
	sf::Vector2f pos = player_->GetPosition();

	switch (dir)
	{
		case UP:
			--y;
			pos.y = Zone::HEIGHT * Tile::SIZE;
			break;
		case DOWN:
			++y;
			pos.y = 0 + player_->GetFloorHeight();
			break;
		case LEFT:
			--x;
			pos.x = (Zone::WIDTH * Tile::SIZE) - player_->GetFloorWidth();
			break;
		case RIGHT:
			++x;
			pos.x = 0;
			break;
	}
	// est-ce qu'une zone existe aux nouvelles coordonnées ?
	if (x >= 0 && x < GAME_WIDTH && y >= 0 && y < GAME_HEIGHT)
	{
		printf("-> Changement de zone en [%d][%d]\n", y, x);
		next_zone_ = zones_[y][x];
		player_->SetPosition(pos);
		cds_zone_.x = x;
		cds_zone_.y = y;
#ifdef DUMB_MUSIC
		SetMusic(next_zone_->GetMusic());
#endif
	}
}

#ifdef DUMB_MUSIC
void Game::SetMusic(short val)
{

	static Music* music_ = NULL;
	static short current_music_index_ = -1;

std::cerr << "SetMusic\n\tCur: " << current_music_index_ << "\t New: " << val << "\n";
	
	if (val > 0 && val != current_music_index_)
	{
		if (music_ != NULL)
		{
			music_->Stop();
			delete music_;
			music_ = NULL;
		}
		music_ = GET_MUSIC(val);
		music_->Play();
		current_music_index_ = val;
	}
	else if (val == -1 && music_ != NULL)	// -1 <=> NO_MUSIC.
	{
		music_->Stop();
		delete music_;
		music_ = NULL;
	}
	current_music_index_ = val;
}
#endif

