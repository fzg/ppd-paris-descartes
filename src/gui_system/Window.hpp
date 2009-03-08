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
namespace gui{
    enum ID
    {
        IDEXIT = 7771, IDCONFIRM
    };

    class Window{
    public:
        Window();
        Window(const Window& other);
        virtual ~Window();

        /**
        * Callback du gestionnaire de fen�tre
        */
        virtual int WindowCallback(Control::ControlID id){return 0;};

        /**
        * Affichage de la fen�tre
        */
        void Show(sf::RenderTarget& app);

        /**
        * Gestion des evenements concernant la fen�tre
        */
        void ManageEvent(const sf::Event& event);
    protected:
        /**
        * Charge une fen�tre � partir d'un fichier xml
        * param[in] xmlfile Nom du fichier XML � ouvrir
        */
        void Load(const std::string& xmlfile);

        /**
        * D�chargement de tout les composants
        */
        void UnLoad();
    private:

        /**
        * Image de fond de la fen�tre
        */
        sf::Sprite background_;

        /**
        * Position de la fen�tre
        */
        sf::IntRect rect_;

        /**
        * Composants de la fen�tre
        */
        std::vector<Control*> controls_;
    };
}

#endif
