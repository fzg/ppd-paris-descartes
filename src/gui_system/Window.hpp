#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include "../misc/MediaManager.hpp"
#include "Control.hpp"

class Window{
public:
    Window();
    Window(const Window& other);
    ~Window();

    /**
    * Chare une fen�tre � partir d'un fichier xml
    * param[in] xmlfile Nom du fichier XML � ouvrir
    */
    void Load(const std::string& xmlfile);

    /**
    * Affichage de la fen�tre
    */
	void Show(sf::RenderTarget& app);

	/**
	* Gestion des evenements concernant la fen�tre
	*/
	void ManageEvent(sf::Event event);
private:
    /**
    * Image de fond de la fen�tre
    */
    sf::Sprite background_;

    /**
    * Position de la fen�tre
    */
    sf::Vector2f position_;

    /**
    * Control composant la fen�tre
    */
    std::vector<Control*> controls_;

	#ifdef _DEBUG
	bool _dbg;
	#endif
};

#endif
