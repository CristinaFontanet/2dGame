#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "OwnTexture.h"
#include "ShaderProgram.h"

using namespace std;


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class TileMap
{

public:

	#define ROCK 43
	#define TUSK 14
	#define WOOD 17
	#define COAL 11
	#define GOLD 78
	#define DIAMOND 114
	#define LIM 108
	#define NONE 0
	#define BELL 76
	// Tile maps can only be created inside an OpenGL context
	static TileMap *createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

	TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);
	~TileMap();

	void render() const;
	void free();
	
	int getTileSize() const { return tileSize; }

	bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const;

	int tileToMaterial(int x, int y);

	bool addMaterial(int posx, int posy, int playerX, int playerY, int material, int range);


	int dig(int posx, int posy, int playerX, int playerY, int range, int dmg);

	void actualizarVBO();

	int getTileSize();

	vector<glm::vec2> getEnemiesPos();

	glm::vec2 getMapSize();

	void createCaveAt(int x, int y);

	void addVertices(int material,int x, int y);

	void deleteVertices(int x, int y);

	bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY, const bool bLeft,const int marg) const;

	bool collisionMoveUp(const glm::ivec2 & pos, const glm::ivec2 & size, int * posY, const bool bLeft, const int marg) const;

	
private:
	bool loadLevel(const string &levelFile);
	void prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program);
	vector<vector<bool>> initCaves(vector<vector<bool>> map);
	vector<vector<bool>> caveStep(vector<vector<bool>> oldMap);
	int vecinosVivos(vector<vector<bool>> map, int x, int y);
	bool nextBool(double probability);
	glm::vec2 placeBellItem(vector<vector<bool>> map);
	


private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	OwnTexture tilesheet;
	glm::vec2 tileTexSize;
	pair<int,int> *map;
	vector<int> materials;
	glm::vec2 coordR;
	glm::vec2 bellItem;
	ShaderProgram programR;
	int ntilesVBO;
	vector<float> vertices;
	vector<glm::vec2> posEnemies;
};

#endif // _TILE_MAP_INCLUDE


