#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <string>
#include <SFML/Graphics.hpp>

namespace gui{
    class Control: public sf::Drawable{
    public:
        /**
        * Typedef
        */
        typedef unsigned int ControlID;
        typedef sf::Vector2f ControlPos;

        Control();
        Control(const ControlID id, const ControlPos& pos);
        virtual ~Control();

        /** R�cup�re la zone du widget */
        inline const sf::IntRect& GetRect() const {
            return rect_;
        }
        /** R�cup�re son identifiant */
        inline ControlID GetID() const{
            return id_;
        }

        /** Change le sprite du contr�le qui le peu */
        virtual void ChangeSprite(sf::Sprite nimg){}
    protected:
        /** Identifiant du contr�le */
        ControlID id_;
        /**
        * Zone du contr�le
        */
        sf::IntRect rect_;
	private:
		virtual void Render(sf::RenderTarget& app) const = 0;
    };
}

#endif