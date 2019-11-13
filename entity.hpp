#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include "game.hpp"

class Entity
{
private:
	float _radius;

public:
	sf::CircleShape circle;
	
	Entity();
	Entity(const float& radius);
	virtual ~Entity();
};

#endif
