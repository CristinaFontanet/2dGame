#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"


using namespace std;

TileMap *TileMap::createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	TileMap *map = new TileMap(levelFile, minCoords, program);
	
	return map;
}

TileMap::TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program){
	coordR = minCoords;
	programR = program;
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
}

TileMap::~TileMap() {
	if(map != NULL)
		delete map;
}


void TileMap::render() const {
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * mapSize.x * mapSize.y);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::loadLevel(const string &levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;	
	fin.open(levelFile.c_str());
	if(!fin.is_open())
		return false;
	getline(fin, line);
	if(line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);
	
	//map = new int[mapSize.x * mapSize.y];
	//for(int j=0; j<mapSize.y; j++) {
	map = new std::pair<int,int> [mapSize.x * mapSize.y];
	materials = { COAL,DIAMOND,WOOD,TUSK,GOLD,ROCK };
	for(int j=0; j<mapSize.y; j++)
	{
		getline(fin, line);
		stringstream ss(line);
		string field;
		for(int i=0; i<mapSize.x; i++)
		{
			getline(ss, field, ',');
			stringstream fs(field);
			int f = 0;
			fs >> f;
			switch (f) {
				case -1:
					map[j*mapSize.x + i].first= 0;
					map[j*mapSize.x + i].second= 0;
					break;
				case 5:	//tierra con cesped
					map[j*mapSize.x + i].first = 6;
					map[j*mapSize.x + i].second = 1;
					break;
				case 11:	//tierraText1
					map[j*mapSize.x + i].first = 13;
					map[j*mapSize.x + i].second = 1;
					break;
				case 12: //tierraText2
					map[j*mapSize.x + i].first = 14;
					map[j*mapSize.x + i].second = 1;
					break;
				case 37: //piedra 1
					map[j*mapSize.x + i].first = 43;
					map[j*mapSize.x + i].second = 2;
					break;
				case 4:	//piedra 2
					map[j*mapSize.x + i].first = 5;
					map[j*mapSize.x + i].second = 2;
					break;
				case 16: //carbon
					map[j*mapSize.x + i].first = 19;
					map[j*mapSize.x + i].second = 3;
					break;
				case 78: //oro
					map[j*mapSize.x + i].first = 90;
					map[j*mapSize.x + i].second = 4;
					break;
				case 99: //diam
					map[j*mapSize.x + i].first = 114;
					map[j*mapSize.x + i].second = 6;
					break;
				case 94: //FIn
					map[j*mapSize.x + i].first = 108;
					map[j*mapSize.x + i].second = -1;
					break;
			}
		}
	}
	fin.close();
	
	return true;
}

void TileMap::prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program) {
	int tile, nTiles = 0;
	glm::vec2 posTile, texCoordTile[2], halfTexel;	
	halfTexel = glm::vec2(0.5f / tilesheet.width(),0.5f / tilesheet.height())*18.f;
	//halfTexel = glm::vec2(0.f);
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i].first;
			if(tile != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				texCoordTile[0] = glm::vec2(float((tile-1)%8) / tilesheetSize.x, float((tile-1)/8) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				texCoordTile[0] += halfTexel;
				texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	ntilesVBO = nTiles;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
}

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool TileMap::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = pos.x / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	if (x <= 0) return true;
	for(int y=y0; y<=y1; y++)
	{
		if(map[y*mapSize.x+x].first != 0)
			return true;
	}
	
	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	if (x >= 300) return true;
	for(int y=y0; y<=y1; y++)
	{
		if(map[y*mapSize.x+x].first != 0)
			return true;
	}
	
	return false;
}

bool TileMap::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY , const bool bLeft, const int marg) const {
	int x0, x1, y;
	if(bLeft) {
		x0 = pos.x / tileSize;
		x1 = (pos.x + size.x - 1) / tileSize;
	}
	else {
		x0 = (pos.x+marg) / tileSize;
		x1 = (pos.x+marg + size.x - 1) / tileSize;
	}
	y = (pos.y + size.y - 1) / tileSize;
	for(int x=x0; x<=x1; x++)
	{
		if(map[y*mapSize.x+x].first != 0) {
			if(*posY - tileSize * y + size.y <= 5) {
				*posY = tileSize * y - size.y;
				return true;
			}
		}
	}
	
	return false;
}

int TileMap::tileToMaterial(int x, int y) {
	int material = map[x, y].first;
	if (material == 6 || material == 13 || material ==14) return TUSK;
	if (material == 43 || material == 5 ) return ROCK;
	if (material == 19 ) return COAL;
	if (material == 90) return GOLD;
	if (material == 114) return DIAMOND;
	return NONE;
}

bool TileMap::addMaterial(int posx, int posy, int playerX, int playerY, int material, int range) {
	int x =  posx / tileSize;
	int y =  posy / tileSize;
	int xplay = playerX / tileSize;
	int yplay = playerY / tileSize;
	if ((y == yplay || y == (yplay+1)) && (x == xplay || x == (xplay-1) || x == (xplay+1))) return false;
	if (abs(x - xplay) > range || abs(y - yplay) > range) return false;
	if (map[y*mapSize.x + x].first != 0 || (map[y*mapSize.x + x-1].first == 0 && map[(y-1)*mapSize.x + x-1].first == 0 && map[(y-1)*mapSize.x + x].first == 0 && map[(y-1)*mapSize.x + x+1].first == 0 && map[y*mapSize.x + x+1].first == 0 && map[(y+1)*mapSize.x + x+1].first == 0 && map[(y+1)*mapSize.x + x].first == 0 && map[(y+1)*mapSize.x + x-1].first == 0)) {
		return false;
	}
	for each (int mat in materials) {
		if (material == mat) {
			map[y*mapSize.x + x].first = material;
			map[y*mapSize.x + x].second = 2;
			addVertices(material, x, y);
			return true;
		}
	}
	return false;
}

int TileMap::dig(int posx, int posy, int playerX, int playerY, int range, int dmg) {
	int x = posx / tileSize;
	int y = posy / tileSize;
	int xplay = playerX / tileSize;
	int yplay = playerY / tileSize;
	if (abs(x - xplay) > range || abs(y - yplay) > range) return NONE;
	if (map[y*mapSize.x + x].first != 0) {
		map[y*mapSize.x + x].second-= dmg;
		if (map[y*mapSize.x + x].second <= 0) {
			int material = tileToMaterial(x, y);
			map[y*mapSize.x + x].second = 0;
			map[y*mapSize.x + x].first = 0;
			deleteVertices(x, y);
			return material;
		}
	}
	return NONE;
}

void TileMap::addVertices(int material, int x, int y) {
	deleteVertices(x, y);
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height())*18.f;
	posTile = glm::vec2(coordR.x + x* tileSize, coordR.y +y *tileSize);
	texCoordTile[0] = glm::vec2(float((material-1) % 8) / tilesheetSize.x, float((material - 1) / 8) / tilesheetSize.y);
	texCoordTile[1] = texCoordTile[0] + tileTexSize;
	texCoordTile[0] += halfTexel;
	texCoordTile[1] -= halfTexel;
	// First triangle
	vertices.push_back(posTile.x); vertices.push_back(posTile.y);
	vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
	vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
	vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
	vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
	vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
	// Second triangle
	vertices.push_back(posTile.x); vertices.push_back(posTile.y);
	vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
	vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
	vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
	vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
	vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);

	ntilesVBO++;
	actualizarVBO();
}


void TileMap::deleteVertices(int x, int y) {
	int ntilesIiciales = ntilesVBO;
	glm::vec2 posTile = glm::vec2(coordR.x + x * tileSize, coordR.y + y* tileSize);
	vector<float>::iterator it;
	for (it = vertices.begin(); it < vertices.end(); it += 24) {
			if (*it == posTile.x && *(it + 1) == posTile.y) {
				for (int j = 0; j < 24; j++) it = vertices.erase(it);
				ntilesVBO--;
				break;
			}
	}
	if(ntilesVBO < ntilesIiciales) actualizarVBO();
}

void TileMap::actualizarVBO() {
	free();
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * ntilesVBO * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = programR.bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = programR.bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	render();
}