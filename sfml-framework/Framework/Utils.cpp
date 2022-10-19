#include "Utils.h"

random_device Utils::rd;
mt19937 Utils::gen(Utils:: rd());

void Utils::SetOrigin(Text& obj, Origins origin)
{
	FloatRect rect = obj.getLocalBounds();
	Vector2f originpos;
	originpos.x = rect.width * ((int)origin % 3) * 0.5f;
	originpos.y = rect.height * ((int)origin / 3) * 0.5f;
	obj.setOrigin(originpos);	
}

void Utils::SetOrigin(Sprite& obj, Origins origin)
{
	FloatRect rect = obj.getLocalBounds();
	Vector2f originpos;
	originpos.x = rect.width * ((int)origin % 3) * 0.5f;
	originpos.y = rect.height * ((int)origin / 3) * 0.5f;
	obj.setOrigin(originpos);
}

void Utils::SetOrigin(Shape& obj, Origins origin)
{
	FloatRect rect = obj.getLocalBounds();
	Vector2f originpos;
	originpos.x = rect.width * ((int)origin % 3) * 0.5f;
	originpos.y = rect.height * ((int)origin / 3) * 0.5f;
	obj.setOrigin(originpos);
}

void Utils::SetOrigin(Transformable& obj, Origins origin)
{
}

int Utils::Range(int min, int maxExclude)	// 20 40 넣으면 20~39 나옴.
{
	//0~19 
	return (gen() % (maxExclude - min)) + min;
}

float Utils::RandomRange(float min, int max) //얘는 max 포함되게.
{
	return min + static_cast<float>(rand()) * static_cast<float>(max - min) / RAND_MAX;
}

float Utils::Magnitude(const Vector2f& vec) //벡터의 길이
{
	return sqrt(vec.x * vec.x + vec.y * vec.y); 
}
float Utils::SqrMagnitude(const Vector2f& vec) //벡터의 길이 제곱 안한거. 크기 비교
{
	return (vec.x * vec.x + vec.y * vec.y);
}

Vector2f Utils::Normalize(const Vector2f& vec) //벡터 정규화
{
	float mag = Magnitude(vec);
	
	if (mag == 0)
		return vec;
	return vec / mag;
}
