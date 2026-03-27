#pragma once
class GameObject
{
public:
	GameObject();
	~GameObject();
	void GameIcremeantStars();
	unsigned long long GetStars() { return stars; };
private:
	unsigned long long stars;
	
};

