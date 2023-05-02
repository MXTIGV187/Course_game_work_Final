#ifndef _WEAPON_H_
#define _WEAPON_H_


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



#endif