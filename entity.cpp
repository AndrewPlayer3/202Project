#include "entity.hpp"

Entity::Entity() 
	: _radius(100.f)
{
	circle.setRadius(_radius);
}

Entity::Entity(const float& radius)
	: _radius(radius)
{
	circle.setRadius(_radius);
}

Entity::~Entity() {
	//delete this;
}