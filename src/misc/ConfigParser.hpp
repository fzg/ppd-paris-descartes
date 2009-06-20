#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <cassert>

/**
 * Parseur de fichiers de configuration
 * Un fichier de configuration est composé de sections,
 * chaque section contient un ensemble de paires (élément, valeur)
 */
class ConfigParser
{
public:
	ConfigParser();

	/**
	 * Ouvrir un fichier de configuration
	 * @param[in] filename: nom du fichier à ouvrir
	 * @return true si le fichier a été chargé, sinon false
	 */
	bool LoadFromFile(const char* filename);

	/**
	 * Sauvegarder la configuration dans un fichier
	 * @param[in] filename: nom du fichier à écrire
	 * @return true si le document a été écrit, sinon false
	 */
	bool SaveToFile(const char* filename) const;

	/**
	 * Placer le curseur interne sur une section
	 * Si la section n'existe pas, elle sera créée
	 * @param[in] section: nom de la section
	 */
	void SeekSection(const char* section);

	/**
	 * Récupérer la valeur d'un élément
	 * @param[in] item: nom de l'élément
	 * @param[out] value: valeur de l'élément
	 * @return true si l'élément existe, sinon false
	 */
	bool ReadItem(const char* item, std::string& value);

	template <typename T>
	bool ReadItem(const char* item, T& value)
	{
		std::string strvalue;
		if (ReadItem(item, strvalue))
		{
			std::istringstream iss(strvalue);
			iss >> value;
			return true;
		}
		return false;
	}

	/**
	 * Modifier ou créer un élément
	 * @param[in] item: nom de l'élément
	 * @param[in] value: valeur de l'élément
	 */
	template <typename T>
	void WriteItem(const char* item, const T& value)
	{
		assert(cursor_ != NULL);
		std::ostringstream oss;
		oss << value;
		(*cursor_)[item] = oss.str();
	}

private:
	/**
	 * Parcourir toutes les sections du documents
	 * @param[in] content: tout le document
	 */
	void Parse(const std::string& content);

	typedef std::map<std::string, std::string> Properties;

	/**
	 * Parcourir les propriétés d'une section du document
	 * @param[in] content: contenu de la section
	 * @param[out] props: propriétés de la section
	 */
	void ParseProperties(const std::string& content, Properties& props);

	typedef std::map<std::string, Properties> Sections;

	Sections sections_;
	Properties* cursor_;
};

#endif // CONFIGPARSER_HPP

