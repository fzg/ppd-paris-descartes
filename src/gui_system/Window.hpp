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

    class Window: public sf::Drawable
    {
    public:
        Window();
        Window(const Window& other);
        virtual ~Window();

        /// Callback du gestionnaire de fen�tre
        virtual int WindowCallback(const Control::ControlID id, const int p1, void *p2){return 0;};

        /// Gestion des evenements concernant la fen�tre
        int ManageEvent(const sf::Event& event);

        /// D�termine si un contr�le de la fen�tre a le focus
        /// @return true si un contr�le a le focus, sinon false
		bool HasFocus() const;

    protected:
        /// R�cup�re un contr�le � partir de son id
        Control *GetFromID(Control::ControlID id);

        /// Associe un entier � un control
        void BindIntTo(Control::ControlID id, int *ptr);

        /// Associe un char � un control
        void BindCharTo(Control::ControlID id, char *ptr);

        /// R�cup�re le contenu du composant selon son type
        /// @param[in] id Identifiant du contr�le
        /// @return Texte � r�cuperer
        std::string & GetControlText(Control::ControlID id);

        /// Change le contenu d'un composant
        /// @param[in] id Identifiant du contr�le
        /// @param[in] s Texte � placer
        void SetControlText(Control::ControlID id, const std::string &s);

        /// Charge une fen�tre � partir d'un fichier xml
        /// @param[in] xmlfile Nom du fichier XML � ouvrir
        void Load(const std::string& xmlfile);

        /// D�chargement de tout les composants
        void UnLoad();

        /// Affichage de la fen�tre
		virtual void Render(sf::RenderTarget& app) const;

    private:


        /// R�cup�rer le contr�le sous la souris
        /// @param[in] x: position absolue x
        /// @param[in] y: position absolue y
        /// @return le contr�le sous la souris, NULL si aucun
		Control* GetUnderMouse(int x, int y);

        /// Image de fond de la fen�tre
        sf::Sprite background_;

        /// Position de la fen�tre
        sf::IntRect rect_;

        /// Composants de la fen�tre
        std::vector<Control*> controls_;
        /// contr�le qui a le focus
        Control* active_;
        /// contr�le sous la souris
        Control* hover_;
    };
}

#endif
