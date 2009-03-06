#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>

#include "Control.hpp"

/*
    Il existe deux types de fen�tres. Les fen�tres "bloquantes" qui contienne
dans leurs code une m�thode pour r�cup�r� les events. Et une fen�tre non-bloquante
qui s'intercale dans le syst�me d'event du jeu. Grace � cette proc�dure, le jeu continue
alors que la fen�tre s'affiche.
*/

/* TODO: Passage en forme canonique */

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
	void ManageEvent(const sf::Event& event);
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

};

#endif
