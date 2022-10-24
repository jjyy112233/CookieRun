#pragma once
#include "../3rd/Singleton.h"
#include "FileData.h"

class FileManager : public Singleton<FileManager>
{
private:
	map<string, map<string, MapData>> episodeMap; //find by path
	map<string, HitBoxInfo> hitBoxMap; //find by path
	map<string, map<string, CookieHitBox>> cookieInfo; //find by cookie name and cookie state. return now animation hitbox
	//cookieInfo[Jungle][Jump]
public:
	FileManager();
	~FileManager();

	void LoadAll();
	const map<string, MapData>& GetEpisode(string name);
};

#define FILE_MGR (FileManager::GetInstance())