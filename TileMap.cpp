#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"
#include <ctime>
#include "Constants.h"

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
	if(map != nullptr)
		delete map;
}

void TileMap::render() const {
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0,  6*ntilesVBO);
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
	materials = { COAL,DIAMOND,WOOD,TUSK,GOLD,ROCK,LIM, BELL};
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
				case 0: //ogre
					posEnemies.push_back(glm::vec2(i, j-2)); // aseguramos que caigan del cielo y no se queden atascados 
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
					map[j*mapSize.x + i].second = 3;
					break;
				case 4:	//piedra 2
					map[j*mapSize.x + i].first = 5;
					map[j*mapSize.x + i].second = 3;
					break;
				case 16: //carbon
					map[j*mapSize.x + i].first = 19;
					map[j*mapSize.x + i].second = 2;
					break;
				case 78: //oro
					map[j*mapSize.x + i].first = 90;
					map[j*mapSize.x + i].second = 5;
					break;
				case 99: //diam
					map[j*mapSize.x + i].first = 114;
					map[j*mapSize.x + i].second = 7;
					break;
				case 94: //FIn
					map[j*mapSize.x + i].first = 1;
					map[j*mapSize.x + i].second = INT16_MAX;
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

bool TileMap::collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY, const bool bLeft, const int marg) const {
	int x0, x1, y;
	if (bLeft) {
		x0 = pos.x / tileSize;
		x1 = (pos.x + size.x - 1) / tileSize;
	}
	else {
		x0 = (pos.x + marg) / tileSize;
		x1 = (pos.x + marg + size.x - 1) / tileSize;
	}
	y = (pos.y + size.y/2) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		if (map[y*mapSize.x + x].first != 0) {
			return true;
		}
	}

	return false;
}

int TileMap::tileToMaterial(int x, int y) {
	int material = map[y*mapSize.x + x].first;
	if (material == 6 || material == 13 || material ==14) return TUSK;
	if (material == 43 || material == 5 ) return ROCK;
	if (material == 19 ) return COAL;
	if (material == 90) return GOLD;
	if (material == 114) return DIAMOND;
	if (material == BELL) return BELL;
	return NONE;
}

bool TileMap::addMaterial(int posx, int posy, int playerX, int playerY, int material, int range) {
	int x =  posx / tileSize;
	int y =  posy / tileSize;
	int xplay = playerX / tileSize;
	int yplay = playerY / tileSize;
	if ((y == yplay || y == (yplay+1)) && (x == xplay || x == (xplay-1) || x == (xplay+1))) return false;
	if (abs(x - xplay) > range || (abs(y - yplay) > range && abs(y - yplay-1)> range)) return false;
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

int  TileMap::getTileSize() {
	return tileSize;
}

vector<glm::vec2> TileMap::getEnemiesPos() {
	return posEnemies;
}

glm::vec2 TileMap::getMapSize() {
	return mapSize;
}

void TileMap::createCaveAt(int x, int y) {
	vector< vector< bool > > cellMap(CAVE_WIDTH, vector<bool>(CAVE_HEIGHT, false));
	cellMap = initCaves(cellMap);
	for (int i = 0; i<4; i++) {
		cellMap = caveStep(cellMap);
	}
	// ahora aplicamos la "plantilla" a una zona del mapa 
	for (int i = 0; i < cellMap.size(); ++i) {
		for (int j = 0; j < cellMap[0].size(); ++j) {
			if (!cellMap[i][j] || ( j == 0)) {
				map[(j+y)*mapSize.x + (i+x)].first = 0;
				map[(j+y)*mapSize.x + (i+x)].second = 0;
				deleteVertices(i+x, j+y);
			}
		}
	}

	bellItem = placeBellItem(cellMap);
	addVertices(BELL, bellItem.x + x, bellItem.y + y);
	int x2 = x + bellItem.x;
	int y2 = y + bellItem.y;
	map[(y2)*mapSize.x +  x2].first = BELL;
	map[(y2)*mapSize.x +  x2].second = 1;

}
//generamos una "cueva" de unos 19x50 tiles 
vector< vector <bool > > TileMap::initCaves(vector< vector <bool > > map) {
	srand(time(0));
	for (int x = 0; x < map.size(); x++) {
		for (int y = 0; y < map[x].size(); y++) {
			double r = ((double)rand() / (RAND_MAX));
			if (r < 0.2) {
				map[x][y] = true;
			}
		}
	}
	return map;
}


vector< vector <bool > >  TileMap::caveStep(vector< vector <bool > > oldMap) {
	vector< vector< bool > > newMap(CAVE_WIDTH, vector<bool>(CAVE_HEIGHT, false));
	//Loop over each row and column of the map
	for (int x = 0; x<oldMap.size(); x++) {
		for (int y = 0; y<oldMap[0].size(); y++) {
			int nbs = vecinosVivos(oldMap, x, y);
			if (oldMap[x][y]) { // si esta viva y tiene muy pocos vecinos la matamos
				if (nbs < 1) {
					newMap[x][y] = false;
				}
				else {
					newMap[x][y] = true;
				}
			} 
			else { // si esta muerta miramos si tiene vecinos para hacer nacer una nueva driller
				if (nbs > 3) {
					newMap[x][y] = true;
				}
				else {
					newMap[x][y] = false;
				}
			}
		}
	}
	return newMap;
}


int  TileMap::vecinosVivos(vector< vector <bool > > map, int x, int y) {
	int count = 0;
	for (int i = -1; i<2; i++) {
		for (int j = -1; j<2; j++) {
			int neighbourX = x + i;
			int neighbourY = y + j;
			if (i == 0 && j == 0) {
				//Wtf no podemos ser vecinos nuestros 
			}
			//miramos si estamos en los limites
			else if (neighbourX < 0 || neighbourY < 0 || neighbourX >= map.size() || neighbourY >= map[0].size()) {
				count = count + 1;
			}
			//Si es true hay vecino
			else if (map[neighbourX][neighbourY]) {
				count = count + 1;
			}
		}
	}
	return count;
}


bool TileMap::nextBool(double probability)
{
	return rand() <  probability * ((double)RAND_MAX + 1.0);
}

glm::vec2 TileMap::placeBellItem(vector< vector <bool > > map) {
	int xT = 0;
	int yT = 0;
	for (int x = 0; x < map.size(); x++) {
		for (int y = 0; y < map[0].size(); y++) {
			if (!map[x][y]) {
				int nbs = vecinosVivos(map, x, y);
				if (nbs >= 5) { // mas de 5 vecinos vivos
					if (y > yT) {
						xT = x;
						yT = y;
					}
				}
			}
		}
	}
	return glm::vec2(xT, yT);
}