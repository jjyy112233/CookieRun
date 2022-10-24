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
	ifstream f("config/data/episode1.json");
	json data = json::parse(f);

	episodeMap = data;
}

const map<string,MapData>& FileManager::GetEpisode(string episode)
{
    return episodeMap[episode];
}
