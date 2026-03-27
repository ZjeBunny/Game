#include "../include/GameObject.hpp"
double multiplier = 1.0;

GameObject::GameObject() : stars(0)
{
}

GameObject::~GameObject()
{
}

void GameObject::GameIcremeantStars() {
	int starsFromClick = 1 * multiplier;
	stars += starsFromClick;
}