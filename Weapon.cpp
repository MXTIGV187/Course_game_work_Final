#include <stdlib.h>
#include "Weapon.h"


Weapon* spawn_weapon(WeaponType type, int id, const char* name, int damage, float x, float y)
{
    Weapon* weapon = (Weapon*)malloc(sizeof(Weapon));
    weapon->id = id;
    weapon->type = type;
    weapon->name = name;
    weapon->damage = damage;
    weapon->x = x;
    weapon->y = y;
    return weapon;
}