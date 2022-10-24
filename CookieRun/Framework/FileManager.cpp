#include "FileManager.h"
#include <fstream>
#include <iostream>

FileManager::FileManager()
{

}

FileManager::~FileManager()
{
}

void FileManager::LoadAll()
{
	ifstream ep1_f("config/data/episode1.json");
	json ep1_d = json::parse(ep1_f);
	episodeMap = ep1_d;
	ep1_f.close();

	ifstream hitbox("config/data/hitBox.json");
	json hit_d = json::parse(hitbox);
	hitBoxMap = hit_d;
	hitbox.close();
}

const map<string,MapData>& FileManager::GetEpisode(string episode)
{
    return episodeMap[episode];
}
const HitBoxInfo& FileManager::GetHitBox(string name)
{
	return hitBoxMap[name];
}