#ifndef _WEAPON_H_
#define _WEAPON_H_

#include <SDL.h>
#include "Player.h"

enum WeaponType {
   None,
   Rifle,
   Shotgun,
   FlameThrower,
   Boomgun,
   Laser
};

enum BonusType
{
    NoneB,
    SpeedShoot,
    UpDamage
};

struct Weapon {
    int id;
    WeaponType type;
    const char* name; // название
    int damage; // урон
    float x;
    float y;
};

struct Bonus {
    float x;
    float y;
    BonusType type;
    Uint32 lifeTime;
};
struct Bullet;
struct Enemy;
struct Player;
struct Rocket;
Weapon* spawn_weapon(WeaponType type, int id, const char* name, int damage, float x, float y);
Bonus* bonusInit(float x, float y, BonusType type, Uint32 lifeTime);
void Shoot(int& newtime, Uint32& lastShotTime, bool& fire, bool& shootRight, bool& shootLeft, bool& shootUp, bool& shootDown, int& direction, int& n, Bullet** bullet, SDL_FRect* playerRect,
    int& dt, SDL_FRect** bulletRect, Enemy** enemy, SDL_FRect** enemyRect, SDL_FRect** enemyRadius, Player* player, SDL_Renderer* renderer, SDL_Rect bullet_rect, SDL_Texture* bullet_tex, int& PowerfulTiming, int& PoorTiming, int ZOMBIE_COUNT, int SHOOTER_COUNT, int ROCKET_COUNT);
void EnemyShoot(Uint32* lastShotTimeEnemy, Uint32* lastShotRocket, int& newtime, int& dt, Bullet** enemyBullet, Rocket** rocket, SDL_FRect** rocketRect, Enemy** enemy, Player* player, SDL_FRect** enemyRadius, SDL_FRect** enemyRect, SDL_FRect** enemyBulletRect, SDL_FRect* playerRect, int& n_enemy, int& n_rocket, SDL_Renderer* renderer, SDL_Rect bullet_rect, SDL_Texture* bullet_tex, int* direction_enemy, int ZOMBIE_COUNT, int SHOOTER_COUNT, int ROCKET_COUNT);



#endif