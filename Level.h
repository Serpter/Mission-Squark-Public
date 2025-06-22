#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <functional>
#include "Renderable.h"
#include "Simulatable.h"

class Player;

class Level : public Renderable, public Simulatable
{
public:
	// Constructors and Destructors
	Level();
	~Level() = default;

private:
	// Members
	int TileSize = 100;
	int GridWidth = 128; // MUST match interpreting width of array size
	int GridHeight = 16; // MUST match interpreting height of array size

	std::vector<std::array<int, 128 * 16>> Maps;
	std::vector<sf::Vector2f> StartPositions;
	std::vector<bool> Completions;
	int CurrentMapIndex = 0;
	std::vector<sf::Vector2i> PoppedBalloonsData;

	sf::Texture TileTL; // 1
	sf::Texture TileTC; // 2
	sf::Texture TileTR; // 3
	sf::Texture TileML; // 4
	sf::Texture TileMC; // 5
	sf::Texture TileMR; // 6
	sf::Texture TileBL; // 7
	sf::Texture TileBC; // 8
	sf::Texture TileBR; // 9
	sf::Texture TileRunwayPlat; // L = 10 = runway platform
	sf::Texture TileRunwaySupport;// S = 11 = runway support
	// F = 12 = trigger level completed
	sf::Texture Balloon; // 13

	Player* CurrentPlayer;
	bool PendingProgressFlag;
	int PoppedBalloons;

public:
	// Methods
	void SetMapIndex(int mapNum);
	void SetPlayerRef(Player* player);

public:
	// Type Methods
	int GetMapIndex();
	int GetTileAtWorldPosition(sf::Vector2f worldPosition);
	sf::Vector2f GetTileCoordAtWorldPosition(sf::Vector2f worldPosition);
	sf::Vector2f GetPlayerStartPos(int mapNum);

public:
	// Wrapped Functions
	std::function<void(int)> BalloonsUpdated;
	std::function<void(void)> LevelCollided;

public:
	// Inherited via Renderable
	sf::Vector2f GetPosition() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	// Inherited via Simulatable
	void Step() override;
};
