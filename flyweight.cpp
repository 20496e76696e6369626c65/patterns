#include <iostream>
#include <memory>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <time.h>

namespace flyweight
{
	constexpr size_t WIDTH{ 1000 };
	constexpr size_t HEIGHT{ 1000 };

	struct Texture {};

	Texture GRASS_TEXTURE;
	Texture HILL_TEXTURE;
	Texture RIVER_TEXTURE;

	class Terrain
	{
	public:
		Terrain(int movementCost, bool isWater, Texture texture) :
			movementCost_(movementCost),
			isWater_(isWater),
			texture_(texture) {};
		int getMovementCost() const		  { return movementCost_; }
		bool isWater() const			  { return isWater_; }
		const Texture& getTexture() const { return texture_; }
	private:
		int		movementCost_;
		bool	isWater_;
		Texture texture_;
	};

	class World
	{
	public:
		World() :
			grassTerrain_(1, false, GRASS_TEXTURE),
			hillTerrain_(3, false, HILL_TEXTURE),
			riverTerrain_(2, true, RIVER_TEXTURE)
		{}

		void generateTerrain()
		{
			for (int x = 0; x < WIDTH; x++)
			{
				for (int y = 0; y < HEIGHT; y++)
				{
					if (std::rand() % 10 == 0)
					{
						tiles_[x][y] = &hillTerrain_;
					}
					else
					{
						tiles_[x][y] = &grassTerrain_;
					}
				}
			}

			int x = rand() % WIDTH;
			for (int y = 0; y < HEIGHT; y++)
			{
				tiles_[x][y] = &riverTerrain_;
			}
		}

		const Terrain& getTile(int x, int y) const
		{
			return *tiles_[x][y];
		}
	private:
		Terrain grassTerrain_;
		Terrain hillTerrain_;
		Terrain riverTerrain_;
		Terrain* tiles_[WIDTH][HEIGHT];
	};

	void flyweight_main()
	{
		World world;
		int cost = world.getTile(2, 3).getMovementCost();
	}
}