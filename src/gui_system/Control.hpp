#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <string>
#include <SFML/Graphics.hpp>

namespace gui{
    class Control: public sf::Drawable{
    public:
		enum { UNDEFINED = -1 };

        typedef unsigned int ControlID;
        typedef sf::Vector2f ControlPos;

        /// Etat du control
        enum State{
            NORMAL=0x100,
            ON_FOCUS=0x010,
            ON_HOVER=0x001
        };

        Control(const ControlID id, const ControlPos& pos, const std::string& s="");
        virtual ~Control();

        /// R�cup�re le texte du contr�le
        /// @return Texte du control
        virtual std::string GetText() const{
            return text_;
        }

        /// Place un texte
        virtual void SetText(const std::string s){
            text_ = s;
        }

        /// Permet d'associ� un int au control
        void LinkInt(int *);

        /// Permet d'associ� un char au control
        void LinkChar(char *);

        /// Changement d'�tat du contr�le
        /// @param[in] s Etat du contr�le
        inline void SetState(State s){
            curr_state_ = s;
        }

        /// R�cup�re la zone du widget
        inline const sf::IntRect& GetRect() const {
            return rect_;
        }
        /// R�cup�re son identifiant
        inline ControlID GetID() const{
            return id_;
        }

        /// Change le sprite du contr�le qui le peu
        virtual void ChangeSprite(const sf::Sprite& nimg);

        /// Callback �v�nement texte saisi
        /// @param[in] unicode: caract�re re�u
        virtual void OnTextEntered(sf::Uint32 unicode);

        /// Callback �v�nement touche press�e
        /// @param[in] key: touche appuy�e
		virtual void OnKeyPressed(sf::Key::Code key);

		/// Mise � jour du control
        virtual void Update(){}
    protected:
        /// Identifiant du contr�le
        ControlID id_;

        /// Zone du contr�le
        sf::IntRect rect_;

        /// Etat courant du contr�le
        State curr_state_;

        /// Etats r�alisable par le contr�le
        int accepted_states_;

        /// Mode du control
        enum Mode{
            PLAIN, LINKED_INT, LINKED_CHAR
        };

        /// Mode du label
        Mode mode_;

        /// Pointeur du mode linked
        void *ptr_;

        /// Texture du contr�le
        mutable std::string text_;
	private:
		virtual void Render(sf::RenderTarget& app) const = 0;
    };
}

#endif
