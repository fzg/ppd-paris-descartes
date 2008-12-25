#ifndef MEDIAMANAGER_HPP
#define MEDIAMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <string>

/**
 * Gestionnaire de ressource (singleton)
 */
class MediaManager
{
public:
	/**
	 * Récupérer l'instance unique
	 * @return référence sur le gestionnaire de ressources
	 */
	static MediaManager& GetInstance();
	
	/**
	 * Récupérer une image
	 * @param[in] key: identifiant de l'image
	 * @return référence sur l'image
	 */
	const sf::Image& GetImage(const char* key) const;
	
	/**
	 * Récupérer un buffer audio
	 * @param[in] key: identifiant du buffer
	 * @return référence sur le buffer
	 */
	const sf::SoundBuffer& GetSoundBuf(const char* key) const;
	
private:
	/**
	 * Initialisation (chargement des images)
	 */
	MediaManager();
	
	MediaManager(const MediaManager& other);
	MediaManager& operator=(const MediaManager& other);
	
	std::map<std::string, sf::Image> images_;
	std::map<std::string, sf::SoundBuffer> sounds_;
};


// fonctions inline pour alléger la syntaxe

inline const sf::Image& GET_IMG(const char* key)
{
	return MediaManager::GetInstance().GetImage(key);
}

inline const sf::SoundBuffer& GET_SOUNDBUF(const char* key)
{
	return MediaManager::GetInstance().GetSoundBuf(key);
}

#endif /* guard MEDIAMANAGER_HPP */

