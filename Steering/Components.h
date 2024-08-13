#pragma once

#include "Vec2.h"
#include "SFML/Graphics.hpp"

class CTransform
{
public:
	Vec2 pos = { 0.0, 0.0 };
	Vec2 velocity = { 0.0, 0.0 };
	double angle = 0.0;

	CTransform(Vec2 dataPos, Vec2 dataVelocity, float dataAngle)
		: pos(dataPos), velocity(dataVelocity), angle(dataAngle) {}
};
class CShape
{
public:
	sf::CircleShape circle;
	CShape(float radius, int points, const sf::Color fill, const sf::Color outline, float thickness)
		: circle(radius, points)
	{
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);
	}
};