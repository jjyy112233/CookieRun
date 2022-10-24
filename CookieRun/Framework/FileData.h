#pragma once
#include <vector>
#include <map>
#include <string>
#include <nlohmann/json.hpp> //아니 nlohmann 이거 설치하라고 이;거"
#include <SFML/System/Vector2.hpp>

using json = nlohmann::json;
using namespace std;

enum class FileTypes
{
	EpisodeInfo,
	HitBoxInfo,
	CookieHitBox,
};


namespace sf {
	void to_json(json& j, const Vector2f& p);
	void from_json(const json& j, Vector2f& p);
}

namespace ns {
	struct CircleInfo
	{
		float rad;
		sf::Vector2f pos;
	};
	void to_json(json& j, const CircleInfo& c);
	void from_json(const json& j, CircleInfo& c);
}

namespace ns {
	struct BackInfo
	{
		string path;
		float speed;
	};
	void to_json(json& j, const BackInfo& b);
	void from_json(const json& j, BackInfo& b);
}

	struct MapData
	{
		vector<ns::BackInfo> backInfo; // background path
		string bottomPath;		//bottom block path
		vector<int> bottomPos;	//bottom block draw position
		map<string, vector<sf::Vector2f>> obstacles; //obstacles draw path, draw position
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(MapData, backInfo, bottomPath, bottomPos, obstacles)
	};

	struct HitBoxInfo
	{
		string id;
		vector<ns::CircleInfo> circles;    // rad, pos
		vector<sf::Vector2f> rectangls;  //  size , pos
		vector <sf::Vector2f> points; //point
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(HitBoxInfo, id, circles, rectangls, points)
	};

	struct CookieHitBox
	{
		string type;
		vector<ns::CircleInfo> circles;    // rad, pos
		vector<sf::Vector2f> rectangls;  //  size , pos
		vector <sf::Vector2f> points; //point
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(CookieHitBox, type, circles, rectangls, points)
	};

