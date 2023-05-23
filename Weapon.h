#ifndef _WEAPON_H_
#define _WEAPON_H_

#include <SDL.h>
#include "Player.h"

enum WeaponType {
   None,
   Rifle,
   Pistol,
   Shotgun,
   Sniper
};

struct Weapon {
    int id;
    WeaponType type;
    const char* name; // название
    int damage; // урон
    float x;
    float y;
};

struct Inventory {
    Weapon items[3];
};
struct Bullet;
struct Enemy;
struct Player;
Weapon* spawn_weapon(WeaponType type, int id, const char* name, int damage, float x, float y);
void Shoot(int& newtime, Uint32& lastShotTime, bool& fire, bool& shootRight, bool& shootLeft, bool& shootUp, bool& shootDown, int& direction, int& n, Bullet** bullet, SDL_FRect* playerRect,
    int& dt, SDL_FRect** bulletRect, Enemy** enemy, SDL_FRect** enemyRect, SDL_FRect** enemyRadius, Player* player, SDL_Renderer* renderer, SDL_Rect bullet_rect, SDL_Texture* bullet_tex);



#endif