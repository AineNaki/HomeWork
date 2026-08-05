#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "UI.h"

namespace ArkanoidGame
{
	class Menu
	{
	public:
		void Init(UI& ui);
		void Draw(sf::RenderWindow& window, const sf::Sprite& menuBg);

		int GetSelectedItem() const { return selectedItem; }
		void MoveUp();
		void MoveDown();

	private:
		int selectedItem = 0;
		std::vector<sf::Text> menuItems;
	};
}