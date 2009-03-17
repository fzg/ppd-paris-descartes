#ifndef WININVENTORY_HPP
#define WININVENTORY_HPP

#include "../gui_system/Window.hpp"
#include "../core/InputController.hpp"

class Equipment;

class WinInventory : public gui::Window
{
public:
    WinInventory();
    ~WinInventory();

    /** Retours de l'inventaire */
    enum
    {
        _CLOSE=101
    };

    /**
    Permet d'ajouter un item � l'inventaire
    @return 1 Si l'inventaire est plein
    */
    int AddItem(Equipment* item);

    /**
    * Permet de savoir si un item est deja pr�sent dans l'inventaire
    * @return: true si il y est
    */
    bool HasItem(int id);

    /**
    * G�re les �venements claviers relatifs au curseur et � l'assignation des touches
    * @param[in]event :l'�venement clavier
    */
    void OnEvent(input::Action action);

    /**
    * Permet de connaitre l'ID du premier objet assignable
    * @return: l'ID ou si non assign�
    */
    int GetItem1ID();

     /**
    * Permet de connaitre l'ID du deuxi�me objet assignable
    * @return: l'ID ou si non assign�
    */
    int GetItem2ID();

    /**
    * Permet de connaitre l'ID du troisi�me objet assignable
    * @return: l'ID ou si non assign�
    */
    int GetItem3ID();



private:
    void Render(sf::RenderTarget&) const;


    int WindowCallback(const gui::Control::ControlID id, const int p1, void *p2);

    /** Identifiant du slot principale */


    enum{
        ID_SLOT=9000, ITEM_N=15, WIDTH = 5, HEIGHT = 3, SLOT_SIZE = 60, OFFSET_X=20, OFFSET_Y=40, PADDX=15, PADDY=15
    };
    struct Cursor
	{
		sf::Sprite sprite;
		sf::Vector2i coords;
	};
	Cursor cursor_;
    /** Liste des �quipements */
	Equipment** items_;
    int last_item_;
    int item1_;
    int item2_;
    int item3_;
};

#endif
