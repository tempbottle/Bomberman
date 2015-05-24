//
// AssetManager.cpp for Bomberman in /home/chambo_e/epitech/cpp_bomberman/src/bomberman/
//
// Made by Emmanuel Chambon
// Login   <chambo_e@epitech.eu>
//
// Started on  Fri May 22 18:04:57 2015 Emmanuel Chambon
// Last update Sun May 24 05:05:32 2015 Emmanuel Chambon
//

#include "manager/AssetManager.hh"

AssetManager::AssetManager()
{
	std::vector<std::future<void>>	f;

	f.push_back(std::async(std::launch::async, std::bind(&AssetManager::loadBoardHandler, this)));
	f.push_back(std::async(std::launch::async, std::bind(&AssetManager::loadThemeHandler, this)));

	for (auto i = f.begin(); i != f.end(); i++)
		i->get();

    // Themes
    // Models
    // Scores
    // Saves
	// Sounds
	// Settings
}

AssetManager::~AssetManager()
{

}

void 			AssetManager::loadBoardHandler()
{
	std::shared_ptr<BoardHandler> handler = std::make_shared<BoardHandler>();

	std::lock_guard<std::mutex> guard(_mutex);
	_assets["boards"] = handler;
}

void 			AssetManager::loadThemeHandler()
{
	std::shared_ptr<ThemeHandler> handler = std::make_shared<ThemeHandler>();

	std::lock_guard<std::mutex> guard(_mutex);
	_assets["themes"] = handler;
}

AAsset           &AssetManager::operator[](std::string const &at)
{
	if (_assets.find(at) == _assets.end())
		throw std::out_of_range("Out of range on AssetManager");
	return *_assets[at];
}