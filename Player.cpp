
#include <stdio.h>
#include "Player.h"
#include "common_parametrs.h"

Player* PlayerInit(int hp, int score, int life, float x, float y, bool is_die, bool is_jump, bool upToPlatform, bool bossFight, int killEnemy, Weapon* weapon, Bonus* bonus, bool level1_complete, bool level2_complete, bool level3_complete)
{
	Player* player = (Player*)malloc(sizeof(Player));
	player->hp = hp;
	player->score = score;
	player->life = life;
	player->killEnemy = killEnemy;
	player->x = x;
	player->y = y;
	player->is_jump = is_jump;
	player->is_die = is_die;
	player->upToPlatform = upToPlatform;
	player->bossFight;
	player->weapon = weapon;
	player->bonus = bonus;
	player->level1_complete = level1_complete;
	player->level2_complete = level2_complete;
	player->level3_complete = level3_complete;
	return player;
}

mainPhysics* PhysInit(float speed, float gravity)
{
	mainPhysics* mainPhys = (mainPhysics*)malloc(sizeof(mainPhysics));
	mainPhys->gravity = gravity;
	mainPhys->speed = speed;
	return mainPhys;
}
Enemy* EnemyInit(int hp, float x, float y, bool is_die, bool is_jump, EnemyType type)
{
	Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));
	enemy->hp = hp;
	enemy->x = x;
	enemy->y = y;
	enemy->is_die = is_die;
	enemy->is_jump = is_jump;
	enemy->type = type;
	return enemy;
}

Bullet* BulletInit(float x, float y, float speed, bool right, bool left, bool up, bool down, bool firstBullet, bool shotAngleUp, bool shotAngleDown)
{
	Bullet* bullet = (Bullet*)malloc(sizeof(Bullet));
	bullet->x = x;
	bullet->y = y;
	bullet->up = up;
	bullet->right = right;
	bullet->left = left;
	bullet->down = down;
	bullet->speed = speed;
	bullet->shotAngleUp = shotAngleUp;
	bullet->shotAngleDown = shotAngleDown;
	bullet->firstBullet = firstBullet;
	return bullet;
}

Rocket* RocketInit(float x, float y, float speed, float angle, Uint32 lifeTime)
{
	Rocket* rocket = (Rocket*)malloc(sizeof(Rocket));
	rocket->x = x;
	rocket->y = y;
	rocket->speed = speed;
	rocket->angle = angle;
	rocket->lifeTime = lifeTime;
	return rocket;
}

SDL_FRect* checkCollision(SDL_FRect* playerRect, SDL_FRect* CollisArray, int& sizeArray)
{
	SDL_FRect* CollisRect = NULL;
	for (int i = 0; i < sizeArray; i++)
	{
		if (SDL_HasIntersectionF(playerRect, &CollisArray[i]))
		{
			CollisRect = &CollisArray[i];
			break;
		}
	}
	return CollisRect;
}


void PlayerMove(Player* player, float& last_y, float& new_y, float& dy, int& dt, bool& isup,
	bool& isdown, bool& isleft, bool& isright, mainPhysics* mainPhys, SDL_FRect* playerRect, SDL_FRect* CollisArray, int& sizeArray, SlopePlatform* platform, int& sizePoint)
{
	SDL_FRect* CollisRect = checkCollision(playerRect, CollisArray, sizeArray);
	if (SDL_HasIntersectionF(playerRect, CollisRect))
	{
		if (CollisRect->h != 5)
		{
			player->upToPlatform = 0;
			if (playerRect->y + playerRect->h - 10 > CollisRect->y)
			{
				player->y += mainPhys->gravity * dt / 1000;
				player->is_jump = 1;
				isup = 0;
			}
			last_y = player->y;
			player->is_jump = 0;
			dy = 0;
		}
		else
		{
			if (playerRect->y + playerRect->h <= CollisRect->y + CollisRect->h && !isup)
			{
				player->upToPlatform = 1;
			}

			if (player->upToPlatform == 1)
			{
				last_y = player->y;
				player->is_jump = 0;
				dy = 0;
				if ((playerRect->y + playerRect->h) - (CollisRect->y + CollisRect->h) > 10)
				{
					player->y += mainPhys->gravity * dt / 1000;
					player->y += mainPhys->gravity * dt / 1000;
					player->is_jump = 1;
					isup = 0;
				}
			}
		}
	}
	if (sizePoint > 0)
	{
		SDL_FPoint* point[1000];
		for (int i = 0; i < 1000; i++)
			point[i] = NULL;
		int count = 0;
		for (int i = 0; i < sizePoint; i++)
		{
			if (player->x > platform[i].x2 && player->x < platform[i].x1)
			{
				count = platform[i].x1 - platform[i].x2;

				for (int k = 0; k < count; k++)
				{
					point[k]->x = platform[i].x2 + k;
					point[k]->y = platform[i].y2 - 0.305 * k;
				}
			}
		}
		for (int k = 0; k < count; k++)
			if (SDL_PointInFRect(point[k], playerRect))
			{
				player->y -= mainPhys->gravity * dt / 10000;
				last_y = player->y;
				player->is_jump = 0;
				dy = 0;
			}
	}

	if (isup)
	{
		if (player->is_jump == 0)
		{
			player->upToPlatform = 0;
			player->y -= mainPhys->gravity * dt / 1000;
			new_y = player->y;
			dy = last_y - new_y;
			if (dy >= 300)
			{
				isup = 0;
			}
		}
		else
		{
			player->upToPlatform = 1;
			player->y += mainPhys->gravity * dt / 1000;
		}

	}
	else
	{
		player->is_jump = 1;
		if (!SDL_HasIntersectionF(playerRect, CollisRect))
			player->y += mainPhys->gravity * dt / 1000;
		if (SDL_HasIntersectionF(playerRect, CollisRect))
			if (CollisRect->h == 5)
				if (playerRect->y + playerRect->h >= CollisRect->y + CollisRect->h)
					player->y -= mainPhys->gravity * dt / 1000;

	}
	if (isdown)
	{
		if (SDL_HasIntersectionF(playerRect, CollisRect))
			if (CollisRect->h == 5.0)
			{
				player->y += 9;
			}
	}
	if (isleft)
	{
		player->x -= mainPhys->speed * dt / 1000;
		if (SDL_HasIntersectionF(playerRect, CollisRect))
		{
			if (playerRect->y + playerRect->h - 10 > CollisRect->y && CollisRect->h != 5)
			{
				player->x += mainPhys->speed * dt / 1000;
				player->is_jump = 1;
			}
		}

	}
	if (isright)
	{
		player->x += mainPhys->speed * dt / 1000;

		if (SDL_HasIntersectionF(playerRect, CollisRect))
		{
			if (playerRect->y + playerRect->h - 10 > CollisRect->y && CollisRect->h != 5)
			{
				player->x -= mainPhys->speed * dt / 1000;
				player->is_jump = 1;
			}
		}
	}
	if (player->y > 1000)
		player->is_die = 1;

}

void EnemyMove(Enemy* enemy, SDL_FRect* enemyRadius, SDL_FRect* playerRect, SDL_FRect* enemyRect, mainPhysics* mainPhys, SDL_FRect* CollisArray, int& sizeArray, int& dt,
	float& last_enemy_y, float& new_enemy_y, float& dy_enemy, Player* player, int& newtime, int direction_enemy)
{
	Uint32 lastShotTimeEnemy = 0;
	SDL_FRect* CollisRect = checkCollision(enemyRect, CollisArray, sizeArray);
	if (SDL_HasIntersectionF(enemyRect, CollisRect))
	{
		if (enemyRect->y + enemyRect->h - 10 > CollisRect->y)
		{
			enemy->y += mainPhys->gravity * dt / 1000;
			enemy->is_jump = 1;
		}
		else
		{
			enemy->is_jump = 0;
			last_enemy_y = enemy->y;
			dy_enemy = 0;
			enemy->is_jump_right = 0;
			enemy->is_jump_left = 0;
		}

		if (enemyRect->x + enemyRect->w >= CollisRect->x + CollisRect->w)
		{
			enemy->x += (mainPhys->speed - 50) * dt / 1000;
			enemy->y -= mainPhys->gravity * dt / 1000;
			enemy->is_jump_right = 1;
			enemy->is_jump = 1;
		}
		if (enemyRect->x <= CollisRect->x)
		{
			enemy->x -= (mainPhys->speed - 50) * dt / 1000;
			enemy->y -= mainPhys->gravity * dt / 1000;
			enemy->is_jump_left = 1;
			enemy->is_jump = 1;
		}
	}
	else if (enemy->is_jump == 0) enemy->y += mainPhys->gravity * dt / 1000;

	if (enemy->is_jump == 1)
	{
		enemy->y -= mainPhys->gravity * dt / 1000;
		new_enemy_y = enemy->y;
		dy_enemy = last_enemy_y - new_enemy_y;
		if (dy_enemy >= 300)
		{
			enemy->is_jump = 0;
		}
	}
	if (enemy->is_jump_right)
	{
		enemy->x += (mainPhys->speed - 50) * dt / 1000;
	}
	if (enemy->is_jump_left)
	{
		enemy->x -= (mainPhys->speed - 50) * dt / 1000;
	}
	if (!enemy->is_jump_right && !enemy->is_jump_left)
		if (SDL_HasIntersectionF(enemyRadius, playerRect))
		{
			if (enemy->type == Zombie)
			{
				if (playerRect->x + playerRect->w <= enemyRect->x)
				{
					direction_enemy = DIR_LEFT;
					enemy->x -= (mainPhys->speed - 50) * dt / 1000;
				}
				if (playerRect->x + playerRect->w >= enemyRect->x + enemyRect->w)
				{
					direction_enemy = DIR_RIGHT;
					enemy->x += (mainPhys->speed - 50) * dt / 1000;
				}
				if (SDL_HasIntersectionF(enemyRect, playerRect))
				{
					lastShotTimeEnemy = SDL_GetTicks();
					if (newtime - lastShotTimeEnemy >= 3000)
						player->hp -= 10;
				}
			}
		}
}

void IsPlayerDie(Player* player, int& respawn_x, int& respawn_y, Weapon* rifle, bool& running, bool&main_menu)
{
	if (player->hp <= 0)
	{
		player->is_die = 1;
		player->score -= 30;
	}

	if (player->is_die == 1)
	{
		player->is_die = 0;
		player->hp = 100;
		player->x = respawn_x;
		player->y = respawn_y;
		player->weapon = rifle;
		player->bonus = NULL;
		player->life--;
	}

	if (player->life <= 0)
	{
		running = 0;
		
	}
}
void BackGround_move(SDL_FRect* CollisArray, Player* player, int& sizeArray, bool& isleft, bool& isright) {

	if (isleft) {
		for (int i = 0; i < sizeArray; i++) {
			CollisArray[i].x++;

		}
	}
	if (isright) {
		for (int i = 0; i < sizeArray; i++) {
			CollisArray[i].x--;

		}
	}
}

void SaveScoreTable(Player* player, const char* fileName)
{
	Score* mass = (Score*)malloc(10 * sizeof(Score));
	if (mass == NULL)
	{
		printf("Ошибка выделения памяти\n");
		exit(1);
	}

	Score temp;
	temp.life = player->life;
	temp.score = player->score;
	temp.killEnemy = player->killEnemy;

	FILE* file;
	fopen_s(&file, fileName, "r+");
	if (file == NULL)
	{
		printf("Ошибка открытия файла\n");
		exit(1);
	}

	for (int i = 0; i < 10; i++)
	{
		fscanf_s(file, "%d %d %d\n", &mass[i].score, &mass[i].killEnemy, &mass[i].life);
	}

	if (player->score > mass[9].score)
	{
		mass[9] = temp;
	}

	// Сортировка массива mass по убыванию score
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9 - i; j++)
		{
			if (mass[j].score < mass[j + 1].score)
			{
				Score temp = mass[j];
				mass[j] = mass[j + 1];
				mass[j + 1] = temp;
			}
		}
	}

	fseek(file, 0, SEEK_SET); // Перемещение указателя файла в начало
	for (int i = 0; i < 10; i++)
	{
		fprintf(file, "%d %d %d\n", mass[i].score, mass[i].killEnemy, mass[i].life);
	}

	fclose(file);
	free(mass);
}


Score* PrintScoreTable(const char* fileName)
{
	FILE* file;
	errno_t err = fopen_s(&file, fileName, "r");
	if (err != 0 || file == NULL)
	{
		printf("Ошибка при открытии файла\n");
		exit(1);
	}
	Score* mass;
	mass = (Score*)malloc(10 * sizeof(Score));
	if (mass == NULL)
	{
		printf("Ошибка при выделении памяти\n");
		fclose(file);
		return NULL;
	}

	for (int i = 0; i < 10; i++)
	{
		fscanf_s(file, "%d %d %d\n", &mass[i].score, &mass[i].killEnemy, &mass[i].life);
	}

	fclose(file);

	for (int i = 0; i < 10; i++)
	{
		printf("%d %d %d\n", mass[i].score, mass[i].killEnemy, mass[i].life);
	}
	

	return mass;
}

void EnemyLoad(Enemy** enemy, const char* fileName, int& ZOMBIE_COUNT, int& SHOOTER_COUNT, int& ROCKET_COUNT)
{
	FILE* file;
	errno_t err = fopen_s(&file, fileName, "r");
	if (err != 0)
	{
		printf("Ошибка открытия файла\n");
		exit(1);
	}

	int x = 0, y = 0;

	fscanf_s(file, "%d\n", &ZOMBIE_COUNT);

	for (int i = 0; i < ZOMBIE_COUNT; i++)
	{
		fscanf_s(file, "%d %d\n", &x, &y);
		enemy[i] = EnemyInit(100, x, y, 0, 0, Zombie);
		x = 0;
		y = 0;
	}

	fscanf_s(file, "%d\n", &SHOOTER_COUNT);

	for (int i = ZOMBIE_COUNT; i < ZOMBIE_COUNT + SHOOTER_COUNT; i++)
	{
		fscanf_s(file, "%d %d\n", &x, &y);
		enemy[i] = EnemyInit(100, x, y, 0, 0, Shooter);
		x = 0;
		y = 0;
	}
	fscanf_s(file, "%d\n", &SHOOTER_COUNT);

	for (int i = ZOMBIE_COUNT + SHOOTER_COUNT; i < ZOMBIE_COUNT + SHOOTER_COUNT + ROCKET_COUNT; i++)
	{
		fscanf_s(file, "%d %d\n", &x, &y);
		enemy[i] = EnemyInit(150, x, y, 0, 0, Rocket_man);
		x = 0;
		y = 0;
	}
	fclose(file);
}

void SaveProgress(Player* player, Weapon* weapon, const char* fileName)
{
	FILE* file;
	fopen_s(&file, fileName, "wb");
	if (file == NULL)
	{
		printf("Ошибка открытия файла\n");
		return;
	}

	fwrite(player, sizeof(Player), 1, file);


	if (player->weapon != nullptr)
	{
		fwrite(player->weapon, sizeof(Weapon), 1, file);
	}

	fclose(file);
}

Player* LoadProgress(const char* fileName)
{

	Player* player = new Player();

	FILE* file;
	fopen_s(&file, fileName, "rb");
	if (file == NULL)
	{
		printf("Ошибка открытия файла\n");
		return nullptr;
	}

	// Читаем данные структуры Player из файла
	fread(player, sizeof(Player), 1, file);

	player->bonus = nullptr;
	player->x = 300;
	player->y = 300;
	player->bossFight = 0;

	// Читаем данные оружия (Weapon), если присутствуют
	if (player->weapon != nullptr)
	{
		player->weapon = new Weapon(); // Создаем новый объект оружия
		fread(player->weapon, sizeof(Weapon), 1, file);
	}

	fclose(file);

	return player;
}





//int hp;
//int score;
//int life;