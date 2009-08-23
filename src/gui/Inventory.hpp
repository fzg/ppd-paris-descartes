#ifndef WININVENTORY_HPP
#define WININVENTORY_HPP

#include "../gui_system/Window.hpp"
#include "../core/InputController.hpp"
#include "../entities/Equipment.hpp"


class Inventory: public gui::Window
{
public:
	Inventory();
	~Inventory();

	/** Retours de l'inventaire */
	enum
	{
		_CLOSE = 101
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
	bool HasItem(Item::Type type);

	/**
	 * G�re les �venements claviers relatifs au curseur et � l'assignation des touches
	 * @param[in]event :l'�venement clavier
	 */
	void OnEvent(input::Action action);

	/**
	 * Vider l'inventaire
	 */
	void Clear();

	/**
	 * Assigner le premier objet
	 */
	void SetItem1Type(int type);

	/**
	 * Obtenir le type du premier objet assign�
	 */
	int GetItem1Type() const;

	/**
	 * Assigner le deuxi�me objet
	 */
	void SetItem2Type(int type);

	/**
	 * Obtenir le type du deuxi�me objet assign�
	 */
	int GetItem2Type() const;

	/**
	 * Assigner le troisi�me objet
	 */
	void SetItem3Type(int type);

	/**
	 * Obtenir le type du troisi�me objet assign�
	 */
	int GetItem3Type() const;

	/**
	 * Remplir le stock � partir d'une cha�ne d'id
	 */
	void StockFromString(const std::string& str);

	/**
	 * Obtenir le contenu du stock sous forme d'une cha�ne d'id
	 */
	std::string StockToString() const;

private:
	// inherited
	void Render(sf::RenderTarget&) const;

	void PlaceItem(Equipment* item, int x, int y);

	int WindowCallback(gui::Control::ControlID id);

	static void ClearItem(Equipment*& item);

	// setter g�n�rique
	static void SetItem(Equipment*& item, int inttype);

	// getter g�n�rique
	static int GetItemType(const Equipment* item);

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

#endif // WININVENTORY_HPP
