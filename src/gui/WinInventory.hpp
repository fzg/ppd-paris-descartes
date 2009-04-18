#ifndef WININVENTORY_HPP
#define WININVENTORY_HPP

#include "../gui_system/Window.hpp"
#include "../core/InputController.hpp"

class Equipment;

class WinInventory: public gui::Window
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
	 * Ajouter un objet dans l'inventaire
	 * @param item: objet � ajouter
	 * @return true si ok, false si inventaire plein ou doublon
	 */
	bool AddItem(Equipment* item);

	/**
	 * Savoir si un item est deja pr�sent dans l'inventaire
	 * @return true s'il y est
	 */
	bool HasItem(int id);

	/**
	 * G�re les �venements claviers relatifs au curseur et � l'assignation des touches
	 * @param[in]event :l'�venement clavier
	 */
	void OnEvent(input::Action action);

	/**
	 * Permet de connaitre l'ID du premier objet assignable
	 * @return l'ID ou 0 si non assign�
	 */
	int GetItem1ID() const;

	 /**
	 * Permet de connaitre l'ID du deuxi�me objet assignable
	 * @return l'ID ou 0 si non assign�
	 */
	int GetItem2ID() const;

	/**
	 * Permet de connaitre l'ID du troisi�me objet assignable
	 * @return l'ID ou 0 si non assign�
	 */
	int GetItem3ID() const;

private:
	/// inherited
	void Render(sf::RenderTarget&) const;

	void PlaceItem(Equipment* item, int x, int y);

	int WindowCallback(const gui::Control::ControlID id, const int p1, void *p2);

	/** Identifiant du slot principale */
	enum
	{
		COUNT_W = 5, COUNT_H = 3
	};

	struct Cursor
	{
		sf::Sprite sprite;
		sf::Vector2i coords;
	};
	Cursor cursor_;

	Equipment* items_[COUNT_H][COUNT_W];

	Equipment* item1_;
	Equipment* item2_;
	Equipment* item3_;
};

#endif
