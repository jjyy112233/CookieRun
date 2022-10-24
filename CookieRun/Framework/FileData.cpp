#include "FileData.h"

void ns::to_json(json& j, const BackInfo& b)
{
    j = json{ {"path", b.path}, {"speed", b.speed} };
}

void ns::from_json(const json& j, BackInfo& b)
{
    j.at("path").get_to(b.path);
    j.at("speed").get_to(b.speed);
}

void sf::to_json(json& j, const Vector2f& p)
{
    j = json{ {"x", p.x}, {"y", p.y} };
}

void sf::from_json(const json& j, Vector2f& p)
{
    j.at("x").get_to(p.x);
    j.at("y").get_to(p.y);
}

void ns::to_json(json& j, const CircleInfo& c)
{
    j = json{ {"rad", c.rad}, {"pos", c.pos} };
}

void ns::from_json(const json& j, CircleInfo& c)
{
    j.at("rad").get_to(c.rad);
    j.at("pos").get_to(c.pos);
}
