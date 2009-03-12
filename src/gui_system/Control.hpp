#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <string>
#include <SFML/Graphics.hpp>

namespace gui{
    class Control: public sf::Drawable{
    public:
		enum { UNDEFINED = -1 };

        /**
        * Typedef
        */
        typedef unsigned int ControlID;
        typedef sf::Vector2f ControlPos;

        /**
        * Etat du control
        */
        enum State{
            NORMAL=0x100,
            ON_FOCUS=0x010,
            ON_HOVER=0x001
        };

        Control(const ControlID id, const ControlPos& pos);
        virtual ~Control();

        /** Changement d'�tat du contr�le */
        inline void SetState(State s){
            curr_state_ = s;
        }

        /** R�cup�re la zone du widget */
        inline const sf::IntRect& GetRect() const {
            return rect_;
        }
        /** R�cup�re son identifiant */
        inline ControlID GetID() const{
            return id_;
        }

        /** Change le sprite du contr�le qui le peu */
        virtual void ChangeSprite(const sf::Sprite& nimg);

		/**
		 * Callback �v�nement texte saisi
		 * @param[in] unicode: caract�re re�u
		 */
        virtual void OnTextEntered(sf::Uint32 unicode);

		/**
		 * Callback �v�nement touche press�e
		 * @param[in] key: touche appuy�e
		 */
		virtual void OnKeyPressed(sf::Key::Code key);

    protected:
        /** Identifiant du contr�le */
        ControlID id_;
        /**
        * Zone du contr�le
        */
        sf::IntRect rect_;

        /**
        * Etat courant du contr�le
        */
        State curr_state_;

        /**
        * Etats r�alisable par le contr�le
        */
        int accepted_states_;
	private:
		virtual void Render(sf::RenderTarget& app) const = 0;
    };
}

#endif
