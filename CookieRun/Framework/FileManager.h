#pragma once
#include <vector>
#include <map>
#include <string>
#include "../3rd/Singleton.h"
#include <SFML/System/Vector2.hpp>

using namespace std;
using namespace sf;

enum class FileTypes
{
	EpisodeInfo,
	HitBoxInfo,
	CookieHitBox,
};

struct Episode
{
	vector<string> backPaths; // background path
	vector<int> backSpeed;		// background speed
	string bottomPath;		//bottom block path
	vector<int> bottomPos;	//bottom block draw position
	map<string, vector<Vector2f>> obstacles; //obstacles draw path, draw position
};

struct HitBoxInfo
{
	vector<int[2]> circles;   // rad, pos
	vector<int[2]> rectangls; // size , pos
	vector<vector<int>> points; //point
};

struct CookieHitBox
{
	vector<int[2]> circles;    // now animation hitBox
	vector<int[2]> rectangls;  // 
	vector<vector<int>> points; 
};

class FileManager : public Singleton<FileManager>
{
private:
	map<string, Episode> episodeMap; //find by path
	map<string, HitBoxInfo> hitBoxMap; //find by path
	map<string, map<string, CookieHitBox>> cookieInfo; //find by cookie name and cookie state. return now animation hitbox
	//cookieInfo[Jungle][Jump]
public:
	FileManager();
	~FileManager();


};


#define FILE_MGR (FileManager::GetInstance())