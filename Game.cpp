
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "common_parametrs.h"
#include "functions.h"
#include "Player.h"
#include "Weapon.h"
#include "Animation.h"
#include "Level.h"
#include <SDL_mouse.h>
#include <SDL_ttf.h>

//terminator.jpg


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* screen_surface = NULL;
frameAnim* Run;

int main(int argc, char* argv[])
{

    srand(time(NULL));
    SDL_Rect dst_rect = { 0,0,0,0 };

    SDL_Rect dst_rect_score = { 0,0,0,0 };

    SDL_Rect dst_rect_bg = { 0,0,0,0 };

    SDL_Rect dst_rect_bg1 = { 0,0,0,0 };
    SDL_Rect dst_rect_bg11 = { 0,0,0,0 };
    SDL_Rect dst_rect_bg111 = { 0,0,0,0 };

    SDL_Rect dst_rect_bg2 = { 0,0,0,0 };
    SDL_Rect dst_rect_bg22 = { 0,0,0,0 };
    SDL_Rect dst_rect_bg222 = { 0,0,0,0 };


    bool running = 0;
    bool main_menu = 1;
    bool score_window = 0;
    bool load_window = 0;
    bool hero_choice = 0;
    bool hero_one = 1;
    bool hero_two = 0;
    bool hero_three = 0;
   
    Score* mass_score = PrintScoreTable("ScoreTable.txt");

    SDL_Rect dst_enem_rect[100] = { 0,0,0,0 };
    SDL_Rect dst_enem_rocket_rect = { 0,0,0,0 };
    Init(&window, &renderer, &screen_surface);

    int direction = 0;
    int direction_enemy[100];
    for (int i = 0; i < 100; i++)
        direction_enemy[i] = 0;



    TTF_Font* font = TTF_OpenFont("retro-land-mayhem.ttf", 25);

    char score[100] = "score: ";
    SDL_Surface* score_surf = TTF_RenderText_Blended(font, score, { 180,0,0,255 });
    SDL_Texture* score_tex = SDL_CreateTextureFromSurface(renderer, score_surf);

    char score_kd[100] = "Score kill healtf ";
    SDL_Surface* scorekd_surf = TTF_RenderText_Blended(font, score_kd, { 180,0,0,255 });
    SDL_Texture* scorekd_tex = SDL_CreateTextureFromSurface(renderer, scorekd_surf);

    char  new_game[100] = "New game ";
    SDL_Surface* newgame_surf = TTF_RenderText_Blended(font, new_game, { 180,0,0,255 });
    SDL_Texture* newgame_tex = SDL_CreateTextureFromSurface(renderer, newgame_surf);

    char load_game[100] = "Load game ";
    SDL_Surface* load_surf = TTF_RenderText_Blended(font, load_game, { 180,0,0,255 });
    SDL_Texture* load_tex = SDL_CreateTextureFromSurface(renderer, load_surf);

    char score_menu[100] = "Load game ";
    SDL_Surface* scoremenu_surf = TTF_RenderText_Blended(font, score_menu, { 180,0,0,255 });
    SDL_Texture* scoremenu_tex = SDL_CreateTextureFromSurface(renderer, scoremenu_surf);

    char scoremain[100] = "Score ";
    SDL_Surface* scoremain_surf = TTF_RenderText_Blended(font, scoremain, { 180,0,0,255 });
    SDL_Texture* scoremain_tex = SDL_CreateTextureFromSurface(renderer, scoremain_surf);

    char choice_skin[100] = "Choice ";
    SDL_Surface* choice_skin_surf = TTF_RenderText_Blended(font, choice_skin, { 180,0,0,255 });
    SDL_Texture* choice_skin_tex = SDL_CreateTextureFromSurface(renderer, choice_skin_surf);



    char score_one[50] = "FIRST";
   
    SDL_Surface* scoreone_surf = TTF_RenderText_Blended(font, score_one, { 180,0,0,255 });
    SDL_Texture* scoreone_tex = SDL_CreateTextureFromSurface(renderer, scoreone_surf);

    char score_two[50] = "SECOND";

    SDL_Surface* scoretwo_surf = TTF_RenderText_Blended(font, score_two, { 180,0,0,255 });
    SDL_Texture* scoretwo_tex = SDL_CreateTextureFromSurface(renderer, scoretwo_surf);

    char score_three[50] = "THIRD";

    SDL_Surface* scorethree_surf = TTF_RenderText_Blended(font, score_three, { 180,0,0,255 });
    SDL_Texture* scorethree_tex = SDL_CreateTextureFromSurface(renderer, scorethree_surf);

    char score_four[50] = "FOURTH";

    SDL_Surface* scorefour_surf = TTF_RenderText_Blended(font, score_four, { 180,0,0,255 });
    SDL_Texture* scorefour_tex = SDL_CreateTextureFromSurface(renderer, scorefour_surf);

    char score_five[50] = "FIFTH";

    SDL_Surface* scorefive_surf = TTF_RenderText_Blended(font, score_five, { 180,0,0,255 });
    SDL_Texture* scorefive_tex = SDL_CreateTextureFromSurface(renderer, scorefive_surf);

    char score_six[50] = "SIXTH";

    SDL_Surface* scoresix_surf = TTF_RenderText_Blended(font, score_six, { 180,0,0,255 });
    SDL_Texture* scoresix_tex = SDL_CreateTextureFromSurface(renderer, scoresix_surf);

    char score_seven[50] = "Seventh";

    SDL_Surface* scoreseven_surf = TTF_RenderText_Blended(font, score_seven, { 180,0,0,255 });
    SDL_Texture* scoreseven_tex = SDL_CreateTextureFromSurface(renderer, scoreseven_surf);

    char score_eight[50] = "Eighth";

    SDL_Surface* scoreeight_surf = TTF_RenderText_Blended(font, score_eight, { 180,0,0,255 });
    SDL_Texture* scoreeight_tex = SDL_CreateTextureFromSurface(renderer, scoreeight_surf);

    char score_nine[50] = "Ninth";

    SDL_Surface* scorenine_surf = TTF_RenderText_Blended(font, score_nine, { 180,0,0,255 });
    SDL_Texture* scorenine_tex = SDL_CreateTextureFromSurface(renderer, scorenine_surf);

    



    char exit_game[100] = "Exit game ";
    SDL_Surface* exit_surf = TTF_RenderText_Blended(font, exit_game, { 180,0,0,255 });
    SDL_Texture* exit_tex = SDL_CreateTextureFromSurface(renderer, exit_surf);

    SDL_Rect player_rect;
    SDL_Texture* player_tex_run = loadTextureFromFile("Run.png", &player_rect, window, renderer, screen_surface);
    player_rect.w = player_rect.h;

    SDL_Texture* player_tex_idle = loadTextureFromFile("Idle.png", &player_rect, window, renderer, screen_surface);
    player_rect.w = player_rect.h;

    SDL_Texture* hero_two_idle_tex = loadTextureFromFile("hero_two_idle.png", &player_rect, window, renderer, screen_surface);
    player_rect.w = player_rect.h;
    SDL_Rect dst_hero_two_rect = { 0,0,0,0};

    SDL_Texture* hero_two_run_tex = loadTextureFromFile("hero_two_run.png", &player_rect, window, renderer, screen_surface);
    player_rect.w = player_rect.h;
    SDL_Texture* hero_two_shot_tex = loadTextureFromFile("hero_two_shot.png", &player_rect, window, renderer, screen_surface);
    player_rect.w = player_rect.h;

    SDL_Texture* hero_three_idle_tex = loadTextureFromFile("hero_three_idle.png", &player_rect, window, renderer, screen_surface);
    player_rect.w = player_rect.h;
    SDL_Rect dst_hero_three_rect = { 0,0,0,0 };

    SDL_Texture* hero_three_run_tex = loadTextureFromFile("hero_three_run.png", &player_rect, window, renderer, screen_surface);
    player_rect.w = player_rect.h;
    SDL_Texture* hero_three_shot_tex = loadTextureFromFile("hero_three_shot.png", &player_rect, window, renderer, screen_surface);
    player_rect.w = player_rect.h;


    SDL_Rect back_rect;
    SDL_Texture* back_tex = loadTextureFromFile("LEVEL2.png", &back_rect, window, renderer, screen_surface);
   
    

    SDL_Rect back_score;
    SDL_Texture* back_score_tex = loadTextureFromFile("terminator.jpg", &back_score, window, renderer, screen_surface);
    back_score.x = 500; back_score.y = 500; back_score.w = 500; back_score.h = 500;
    dst_rect_score = { back_score.x = 1200, back_score.y = 400, back_score.w = 500, back_score.h = 500 };

    SDL_Rect paralax_bg1_rect;
    SDL_Texture* paralax_bg1_tex = loadTextureFromFile("jungle_paralax_bg1.png", &paralax_bg1_rect, window, renderer, screen_surface);
    paralax_bg1_rect.x = 0; paralax_bg1_rect.y = 0; paralax_bg1_rect.w = 1920; paralax_bg1_rect.h = 1080;

    SDL_Rect paralax_bg11_rect;
    SDL_Texture* paralax_bg11_tex = loadTextureFromFile("jungle_paralax_bg1.png", &paralax_bg11_rect, window, renderer, screen_surface);
    paralax_bg11_rect.x = -1920; paralax_bg11_rect.y = 0; paralax_bg11_rect.w = 1920; paralax_bg11_rect.h = 1080;

    SDL_Rect paralax_bg111_rect;
    SDL_Texture* paralax_bg111_tex = loadTextureFromFile("jungle_paralax_bg1.png", &paralax_bg111_rect, window, renderer, screen_surface);
    paralax_bg111_rect.x = 1920; paralax_bg111_rect.y = 0; paralax_bg111_rect.w = 1920; paralax_bg111_rect.h = 1080;

    SDL_Rect paralax_bg2_rect;
    SDL_Texture* paralax_bg2_tex = loadTextureFromFile("jungle_paralax_bg2.png", &paralax_bg2_rect, window, renderer, screen_surface);
    paralax_bg2_rect.x = 0; paralax_bg2_rect.y = 0; paralax_bg2_rect.w = 1920; paralax_bg2_rect.h = 1080;

    SDL_Rect paralax_bg22_rect;
    SDL_Texture* paralax_bg22_tex = loadTextureFromFile("jungle_paralax_bg2.png", &paralax_bg22_rect, window, renderer, screen_surface);
    paralax_bg22_rect.x = -1920; paralax_bg22_rect.y = 0; paralax_bg22_rect.w = 1920; paralax_bg22_rect.h = 1080;

  
    SDL_Rect paralax_bg222_rect;
    SDL_Texture* paralax_bg222_tex = loadTextureFromFile("jungle_paralax_bg2.png", &paralax_bg222_rect, window, renderer, screen_surface);
    paralax_bg222_rect.x = 1920; paralax_bg222_rect.y = 0; paralax_bg222_rect.w = 1920; paralax_bg222_rect.h = 1080;
    //

    SDL_Rect dst_rect_shotgun = { 0,0,0,0 };
    SDL_Rect shotgun_rect;
    SDL_Texture* shotgun_tex = loadTextureFromFile("shotgun.png", &shotgun_rect, window, renderer, screen_surface);
    shotgun_rect.h = 70; shotgun_rect.w = 70;
    shotgun_rect.x = 150; shotgun_rect.y = 680;
    SDL_FRect* shotgun_frect = InitObject(150, 680, 70, 70);

    SDL_Rect dst_rect_Flame = { 0,0,0,0 };
    SDL_Rect flame_rect;
    SDL_Texture* flame_tex = loadTextureFromFile("Flamegun.png", &flame_rect, window, renderer, screen_surface);
    flame_rect.h = 70; flame_rect.w = 80;
    flame_rect.x = 950; flame_rect.y = 620;
    SDL_FRect* flame_frect = InitObject(950, 620, 70, 80);

    SDL_Rect dst_rect_Boomgun = { 0,0,0,0 };
    SDL_Rect Boom_rect;
    SDL_Texture* Boom_tex = loadTextureFromFile("Boomgun.png", &Boom_rect, window, renderer, screen_surface);
    Boom_rect.h = 70; Boom_rect.w = 70;
    Boom_rect.x = 450; Boom_rect.y = 680;
    SDL_FRect* boom_frect = InitObject(450, 680, 70, 70);

    SDL_Rect dst_rect_lasergun = { 0,0,0,0 };
    SDL_Rect laser_rect;
    SDL_Texture* laser_tex = loadTextureFromFile("lasergun.png", &laser_rect, window, renderer, screen_surface);
    laser_rect.h = 65; laser_rect.w = 85;
    laser_rect.x = 550; laser_rect.y = 680;
    SDL_FRect* laser_frect = InitObject(550, 680, 70, 70);

    SDL_Rect dst_rect_bonus_speed = { 0,0,0,0 };
    SDL_Rect speed_rect;
    SDL_Texture* speedshoot_tex = loadTextureFromFile("bonus_speed.png", &speed_rect, window, renderer, screen_surface);
    speed_rect.h = 65; speed_rect.w = 85;
    speed_rect.x = 1550; speed_rect.y = 680;
    SDL_FRect* speed_frect = InitObject(1550, 680, 70, 70);

    SDL_Rect dst_rect_bonus_damage = { 0,0,0,0 };
    SDL_Rect damage_rect;
    SDL_Texture* damageshoot_tex = loadTextureFromFile("bonus_damage.png", &damage_rect, window, renderer, screen_surface);
    damage_rect.h = 65; damage_rect.w = 85;
    damage_rect.x = 1250; damage_rect.y = 680;
    SDL_FRect* damage_frect = InitObject(1250, 680, 70, 70);






    Weapon* boomgun = spawn_weapon(Boomgun, 1, "Rifle", 10, 100, 100);
    Weapon* rifle = spawn_weapon(Rifle, 1, "Rifle", 50, 100, 100);
    Weapon* shotgun = spawn_weapon(Shotgun, 1, "Rifle", 100, 100, 100);
    Weapon* flame = spawn_weapon(FlameThrower, 1, "Rifle", 30, 100, 100);
    Weapon* laser = spawn_weapon(Laser, 1, "Rifle", 2, 100, 100);
    //
    Bonus* speedShoot = bonusInit(100, 100, SpeedShoot, 0);
    Bonus* upDamage = bonusInit(200, 200, UpDamage, 0);

    //
    int respawn_x = 300;
    int respawn_y = 300;
    Player* player = PlayerInit(100, 100, 3, respawn_x, respawn_y, 0, 1, 0, 0, rifle, NULL);
    mainPhysics* mainPhys = PhysInit(200, 250);

    Uint32 lastShotTime = SDL_GetTicks();
    Uint32 lastShotTimeEnemy[100];

	Enemy* enemy[200];
    int ZOMBIE_COUNT = 0, SHOOTER_COUNT = 0, ROCKET_COUNT = 1;
	// Тут читать
	

	//EnemySave(enemy, "EnemyLevel1.txt", ZOMBIE_COUNT, SHOOTER_COUNT);
	SDL_Rect enemy_rect_zombie;
	SDL_Texture* enemy_tex_idle = loadTextureFromFile("Idle_zombie.png", &enemy_rect_zombie, window, renderer, screen_surface);
	enemy_rect_zombie.w = enemy_rect_zombie.h;

    SDL_Rect enemy_rect_shooter;
    SDL_Texture* enemy_shooter_tex_idle = loadTextureFromFile("Gunner_Blue_Idle.png", &enemy_rect_shooter, window, renderer, screen_surface);
    enemy_rect_shooter.w = enemy_rect_shooter.h;

  

    SDL_Rect enemy_rect_rocket;
    SDL_Texture* enemy_rocket_tex_idle = loadTextureFromFile("Gunner_Green_Idle.png", &enemy_rect_rocket, window, renderer, screen_surface);

    Bullet* bullet[50];
    SDL_FRect* bulletRect[50];

    Rocket* rocket[50];
    SDL_FRect* rocketRect[50];

    Bullet* enemyBullet[100];
    SDL_FRect* enemyBulletRect[100];

    SDL_Rect bullet_rect;
    SDL_Texture* bullet_tex = loadTextureFromFile("bullet1.png", &bullet_rect, window, renderer, screen_surface);
    SDL_Texture* fire_tex = loadTextureFromFile("Shot_1.png", &player_rect, window, renderer, screen_surface);

    SDL_Rect logo_rect;
    SDL_Texture* logo_tex = loadTextureFromFile("contra-logo.png", &logo_rect, window, renderer, screen_surface);

   
    player_rect.w = player_rect.h;
    bool LeftButton = 0;
    int mouseX;
    int mouseY;
    SDL_Rect RectPlay;
    SDL_Rect HeroChoice;
    SDL_Rect RectExit;
    SDL_Rect HeroOne;
    SDL_Rect HeroTwo;
    SDL_Rect HeroThree;
    //PrintScoreTable("ScoreTable.txt");
    SDL_Rect Score_menu;
    SDL_Rect About;
    SDL_Rect LoadGame;
    bool escape = 0;
    while (main_menu || running || score_window || hero_choice || load_window) {

        while (main_menu)
        {
            SDL_RenderCopy(renderer, logo_tex, &logo_rect, NULL);
            RectPlay.x = 30; RectPlay.y = 800; RectPlay.h = 100; RectPlay.w = 400;

            SDL_SetRenderDrawColor(renderer, 100, 200, 5, 2);
            SDL_RenderFillRect(renderer, &RectPlay);
            SDL_RenderDrawRect(renderer, &RectPlay);

            SDL_Rect newgame_rect = { 45 ,800,80,100 };

            sprintf_s(new_game, "New game");

            if ((newgame_tex) != NULL)
                SDL_DestroyTexture(newgame_tex);
            newgame_tex = Load_Texture_Font(new_game, font, &newgame_rect, { 255,0,0,255 }, renderer);
            newgame_rect = { 45 ,800,150,100 };

            SDL_RenderCopy(renderer, newgame_tex, NULL, &newgame_rect);

            HeroChoice.x = 890; HeroChoice.y = 920; HeroChoice.h = 100; HeroChoice.w = 400;

            SDL_SetRenderDrawColor(renderer, 100, 200, 5, 2);
            SDL_RenderFillRect(renderer, &HeroChoice);
            SDL_RenderDrawRect(renderer, &HeroChoice);

            SDL_Rect herochoice_rect = { 890 ,920,80,100 };

            sprintf_s(choice_skin, "     Choice hero");

            if ((choice_skin) != NULL)
                SDL_DestroyTexture(choice_skin_tex);
            choice_skin_tex = Load_Texture_Font(choice_skin, font, &herochoice_rect, { 255,0,0,255 }, renderer);
            herochoice_rect = { 890 ,920,200,100 };

            SDL_RenderCopy(renderer, choice_skin_tex, NULL, &herochoice_rect);

            RectExit.x = 1320; RectExit.y = 800; RectExit.h = 100; RectExit.w = 400;
            SDL_SetRenderDrawColor(renderer, 100, 200, 5, 2);
            SDL_RenderFillRect(renderer, &RectExit);
            SDL_RenderDrawRect(renderer, &RectExit);

            SDL_Rect exitgame_rect = { 45 ,800,80,100 };

            sprintf_s(exit_game, "Exit game");

            if ((exit_tex) != NULL)
                SDL_DestroyTexture(exit_tex);
            exit_tex = Load_Texture_Font(exit_game, font, &exitgame_rect, { 255,0,0,255 }, renderer);
            exitgame_rect = { 1335 ,800,150,100 };

            SDL_RenderCopy(renderer, exit_tex, NULL, &exitgame_rect);

            LoadGame.x = 460; LoadGame.y = 800; LoadGame.h = 100; LoadGame.w = 400;
            SDL_SetRenderDrawColor(renderer, 100, 200, 5, 2);
            SDL_RenderFillRect(renderer, &LoadGame);
            SDL_RenderDrawRect(renderer, &LoadGame);

            Score_menu.x = 890; Score_menu.y = 800; Score_menu.h = 100; Score_menu.w = 400;
            SDL_SetRenderDrawColor(renderer, 100, 200, 5, 2);
            SDL_RenderFillRect(renderer, &Score_menu);
            SDL_RenderDrawRect(renderer, &Score_menu);

            SDL_Rect score_menu_rect = { 45 ,800,80,100 };

            sprintf_s(score_menu, "Score");

            if ((scoremenu_tex) != NULL)
                SDL_DestroyTexture(scoremenu_tex);
            scoremenu_tex = Load_Texture_Font(score_menu, font, &score_menu_rect, { 255,0,0,255 }, renderer);
            score_menu_rect = { 935 ,800,150,100 };
            SDL_RenderCopy(renderer, scoremenu_tex, NULL, &score_menu_rect);




            SDL_Event event_menu;
            while (SDL_PollEvent(&event_menu))
            {
                if (event_menu.type == SDL_QUIT)
                {
                    running = 0;
                }

                switch (event_menu.type)
                {
                case SDL_KEYDOWN:
                    switch (event_menu.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_SPACE: LeftButton = 1; break;
                    case SDL_SCANCODE_L: escape = 1; break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event_menu.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_SPACE: LeftButton = 0; break;
                    case SDL_SCANCODE_L: escape = 0; break;
                    }
                    break;
                }
            }
            SDL_GetMouseState(&mouseX, &mouseY);
            SDL_Point point;
            point.x = mouseX; point.y = mouseY;

            if (SDL_PointInRect(&point, &RectExit))
            {

                SDL_SetRenderDrawColor(renderer, 100, 300, 5, 2);
                SDL_RenderFillRect(renderer, &RectExit);
            }

            if (SDL_PointInRect(&point, &Score_menu))
            {

                SDL_SetRenderDrawColor(renderer, 100, 300, 5, 2);
                SDL_RenderFillRect(renderer, &Score_menu);
            }

            if (SDL_PointInRect(&point, &LoadGame))
            {

                SDL_SetRenderDrawColor(renderer, 100, 300, 5, 2);
                SDL_RenderFillRect(renderer, &LoadGame);
            }



            if (SDL_PointInRect(&point, &RectPlay))
            {

                SDL_SetRenderDrawColor(renderer, 100, 300, 5, 2);
                SDL_RenderFillRect(renderer, &RectPlay);

            }
            if (SDL_PointInRect(&point, &HeroChoice))
            {

                SDL_SetRenderDrawColor(renderer, 100, 300, 5, 2);
                SDL_RenderFillRect(renderer, &HeroChoice);

            }


            if (SDL_PointInRect(&point, &RectPlay) && LeftButton == 1)
            {
                score_window = 0;
                main_menu = 0;
                running = 1;
                LeftButton = 0;
                load_window = 0;
                hero_choice = 0;
                
            }
            if (SDL_PointInRect(&point, &RectExit) && LeftButton == 1)
            {
                main_menu = 0;
                running = 0;
                score_window = 0;
                LeftButton = 0;
                load_window = 0;
                hero_choice = 0;
            }

            if (SDL_PointInRect(&point, &Score_menu) && LeftButton == 1)
            {
                running = 0;
                main_menu = 0;
                score_window = 1;
                LeftButton = 0;
                load_window = 0;
                hero_choice = 0;
            
            }
            if (SDL_PointInRect(&point, &LoadGame) && LeftButton == 1)
            {
                running = 0;
                main_menu = 0;
                score_window = 0;
                LeftButton = 0;
                load_window = 1;
                hero_choice = 0;


            }
            if (SDL_PointInRect(&point, &HeroChoice) && LeftButton == 1)
            {
                running = 0;
                main_menu = 0;
                score_window = 0;
                LeftButton = 0;
                load_window = 0;
                hero_choice = 1;

            }

            SDL_RenderPresent(renderer);


        }
        while (hero_choice) {

            SDL_GetMouseState(&mouseX, &mouseY);
            SDL_Point point;
            point.x = mouseX; point.y = mouseY;

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            

            HeroOne.x = 490; HeroOne.y = 400; HeroOne.h = 300; HeroOne.w = 300;
            SDL_SetRenderDrawColor(renderer, 100, 200, 5, 2);
            SDL_RenderFillRect(renderer, &HeroOne);
            SDL_RenderDrawRect(renderer, &HeroOne);

            dst_rect = { 400,200,500,500 };
            SDL_RenderCopy(renderer, player_tex_idle, &player_rect, &dst_rect);
            
            
            HeroTwo.x = 810; HeroTwo.y = 400; HeroTwo.h = 300; HeroTwo.w = 300;
       
            SDL_RenderFillRect(renderer, &HeroTwo);
            SDL_RenderDrawRect(renderer, &HeroTwo);

            dst_hero_two_rect = { 700,200,500,500 };
            SDL_RenderCopy(renderer, hero_two_idle_tex, &player_rect, &dst_hero_two_rect);

            
            HeroThree.x = 1130; HeroThree.y = 400; HeroThree.h = 300; HeroThree.w = 300;
           
            SDL_RenderFillRect(renderer, &HeroThree);
            SDL_RenderDrawRect(renderer, &HeroThree);
            dst_hero_three_rect = { 1000,200,500,500 };
            SDL_RenderCopy(renderer, hero_three_idle_tex, &player_rect, &dst_hero_three_rect);
            


            SDL_Event event_menu;
            while (SDL_PollEvent(&event_menu))
            {
                if (event_menu.type == SDL_QUIT)
                {
                    running = 0;
                }

                switch (event_menu.type)
                {
                case SDL_KEYDOWN:
                    switch (event_menu.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_SPACE: LeftButton = 1; break;
                    case SDL_SCANCODE_L: escape = 1; break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event_menu.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_SPACE: LeftButton = 0; break;
                    case SDL_SCANCODE_L: escape = 0; break;
                    }
                    break;
                }
            }

            if (SDL_PointInRect(&point, &HeroOne))
            {

                SDL_SetRenderDrawColor(renderer, 100, 300, 5, 2);
                SDL_RenderFillRect(renderer, &HeroOne);

            }
            if (SDL_PointInRect(&point, &HeroTwo))
            {

                SDL_SetRenderDrawColor(renderer, 100, 300, 5, 2);
                SDL_RenderFillRect(renderer, &HeroTwo);

            }
            if (SDL_PointInRect(&point, &HeroThree))
            {

                SDL_SetRenderDrawColor(renderer, 100, 300, 5, 2);
                SDL_RenderFillRect(renderer, &HeroThree);

            }

            if (SDL_PointInRect(&point, &HeroOne) && LeftButton == 1)
            {
                hero_three = 0;
                hero_two = 0;
                hero_one = 1;
                hero_choice = 0;
                main_menu = 1;

            }
            if (SDL_PointInRect(&point, &HeroTwo) && LeftButton == 1)
            {
                hero_three = 0;
                hero_one = 0;
                hero_two = 1;
                hero_choice = 0;
                main_menu = 1;

            }
            if (SDL_PointInRect(&point, &HeroThree) && LeftButton == 1)
            {
                hero_one = 0;
                hero_two = 0;
                hero_three = 1;
                hero_choice = 0;
                main_menu = 1;

            }

            if (escape) {
                hero_choice = 0;
                main_menu = 1;
               
            }






            SDL_RenderPresent(renderer);

        }


        while (score_window) {

            SDL_Event event_menu;
            while (SDL_PollEvent(&event_menu))
            {
                if (event_menu.type == SDL_QUIT)
                {
                    running = 0;
                }

                switch (event_menu.type)
                {
                case SDL_KEYDOWN:
                    switch (event_menu.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_SPACE: LeftButton = 1; break;
                    case SDL_SCANCODE_L: escape = 1; break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event_menu.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_SPACE: LeftButton = 0; break;
                    case SDL_SCANCODE_L: escape = 0; break;
                    }
                    break;
                }
            }

        
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            SDL_Rect score_kd_rect = { 1000 ,800,80,100 };

            sprintf_s(score_kd, "score       kill         health");

            if ((scorekd_tex) != NULL)
                SDL_DestroyTexture(scorekd_tex);
            scorekd_tex = Load_Texture_Font(score_kd, font, &score_kd_rect, { 255,255,0,255 }, renderer);
            score_kd_rect = { 250 ,50,550,90 };
            SDL_RenderCopy(renderer, scorekd_tex, NULL, &score_kd_rect);

            SDL_Rect score_main_one = { 108,108,50,50 };
        
            sprintf_s(score_one, "FIRST:%d         %d             %d", mass_score[0].score, mass_score[0].killEnemy,mass_score[0].life);
            if ((scoreone_tex) != NULL)
                SDL_DestroyTexture(scoreone_tex);
            scoreone_tex = Load_Texture_Font(score_one, font, &score_main_one, { 255,255,255,255 }, renderer);
            score_main_one = { 120 ,120,600,90 };
            SDL_RenderCopy(renderer, scoreone_tex, NULL, &score_main_one);

            SDL_Rect score_main_two = { 108,108,50,50 };

            sprintf_s(score_two, "SECOND:%d         %d             %d", mass_score[1].score, mass_score[1].killEnemy, mass_score[1].life);
            if ((scoretwo_tex) != NULL)
                SDL_DestroyTexture(scoretwo_tex);
            scoretwo_tex = Load_Texture_Font(score_two, font, &score_main_two, { 0,0,255,255 }, renderer);
            score_main_two = { 120 ,240,600,90 };
            SDL_RenderCopy(renderer, scoretwo_tex, NULL, &score_main_two);

            SDL_Rect score_main_three = { 108,108,50,50 };

            sprintf_s(score_three, "THIRD:%d         %d             %d", mass_score[2].score, mass_score[2].killEnemy, mass_score[2].life);
            if ((scorethree_tex) != NULL)
                SDL_DestroyTexture(scorethree_tex);
            scorethree_tex = Load_Texture_Font(score_three, font, &score_main_three, { 255,0,0,255 }, renderer);
            score_main_three = { 120 ,360,600,90 };
            SDL_RenderCopy(renderer, scorethree_tex, NULL, &score_main_three);

            SDL_Rect score_main_four = { 108,108,50,50 };

            sprintf_s(score_four, "FOURTH:%d         %d             %d", mass_score[3].score, mass_score[3].killEnemy, mass_score[3].life);
            if ((scorefour_tex) != NULL)
                SDL_DestroyTexture(scorefour_tex);
            scorefour_tex = Load_Texture_Font(score_four, font, &score_main_four, { 255,255,255,255 }, renderer);
            score_main_four = { 120 ,480,600,90 };
            SDL_RenderCopy(renderer, scorefour_tex, NULL, &score_main_four);

            SDL_Rect score_main_five = { 108,108,50,50 };

            sprintf_s(score_five, "FIFTH:%d         %d             %d", mass_score[4].score, mass_score[4].killEnemy, mass_score[4].life);
            if ((scorefive_tex) != NULL)
                SDL_DestroyTexture(scorefive_tex);
            scorefive_tex = Load_Texture_Font(score_five, font, &score_main_five, { 0,0,255,255 }, renderer);
            score_main_five = { 120 ,600,600,90 };
            SDL_RenderCopy(renderer, scorefive_tex, NULL, &score_main_five);

            SDL_Rect score_main_six = { 108,108,50,50 };

            sprintf_s(score_six, "SIXTH:%d         %d             %d", mass_score[5].score, mass_score[5].killEnemy, mass_score[5].life);
            if ((scoresix_tex) != NULL)
                SDL_DestroyTexture(scoresix_tex);
            scoresix_tex = Load_Texture_Font(score_six, font, &score_main_six, { 255,0,0,255 }, renderer);
            score_main_six = { 120 ,720,600,90 };
            SDL_RenderCopy(renderer, scoresix_tex, NULL, &score_main_six);

            SDL_Rect score_main_seven = { 108,108,50,50 };

            sprintf_s(score_seven, "SEVENTH:%d         %d             %d", mass_score[5].score, mass_score[5].killEnemy, mass_score[5].life);
            if ((scoreseven_tex) != NULL)
                SDL_DestroyTexture(scoreseven_tex);
            scoreseven_tex = Load_Texture_Font(score_seven, font, &score_main_seven, { 255,255,255,255 }, renderer);
            score_main_seven = { 120 ,840,600,90 };
            SDL_RenderCopy(renderer, scoreseven_tex, NULL, &score_main_seven);

            SDL_Rect score_main_eight = { 108,108,50,50 };

            sprintf_s(score_eight, "EIGHTH:%d         %d             %d", mass_score[5].score, mass_score[5].killEnemy, mass_score[5].life);
            if ((scoreeight_tex) != NULL)
                SDL_DestroyTexture(scoreeight_tex);
            scoreeight_tex = Load_Texture_Font(score_eight, font, &score_main_eight, { 0,0,255,255 }, renderer);
            score_main_eight = { 120 ,960,600,90 };
            SDL_RenderCopy(renderer, scoreeight_tex, NULL, &score_main_eight);

            SDL_Rect score_main_nine = { 108,108,50,50 };

            sprintf_s(score_nine, "NINTH:%d         %d             %d", mass_score[5].score, mass_score[5].killEnemy, mass_score[5].life);
            if ((scorenine_tex) != NULL)
                SDL_DestroyTexture(scorenine_tex);
            scorenine_tex = Load_Texture_Font(score_nine, font, &score_main_nine, { 255,0,0,255 }, renderer);
            score_main_nine = { 120 ,1080,600,90 };
            SDL_RenderCopy(renderer, scorenine_tex, NULL, &score_main_nine);

      
            SDL_RenderCopy(renderer, back_score_tex, NULL, &dst_rect_score);

            if (escape) {
                score_window = 0;
                main_menu = 1;
                SDL_DestroyTexture(scorenine_tex);
                SDL_DestroyTexture(scoreeight_tex);
                SDL_DestroyTexture(scoresix_tex);
                SDL_DestroyTexture(scorefive_tex);
                SDL_DestroyTexture(scorekd_tex);
                SDL_DestroyTexture(scoreseven_tex);

            }
     




        
            SDL_RenderPresent(renderer);

       
        }
        while (load_window) 
        {

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);


            

            SDL_Event event_menu;
            while (SDL_PollEvent(&event_menu))
            {
                if (event_menu.type == SDL_QUIT)
                {
                    running = 0;
                }

                switch (event_menu.type)
                {
                case SDL_KEYDOWN:
                    switch (event_menu.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_SPACE: LeftButton = 1; break;
                    case SDL_SCANCODE_L: escape = 1; break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event_menu.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_SPACE: LeftButton = 0; break;
                    case SDL_SCANCODE_L: escape = 0; break;
                    }
                    break;
                }
            }

            if (escape) {
                load_window = 0;
                main_menu = 1;
                escape = 0;

            }
            SDL_RenderPresent(renderer);
        }

        int n = 0;
        int n_enemy = 0;
        bool shootUp = 0;
        bool shootDown = 0;
        bool shootLeft = 0;
        bool shootRight = 0;
        int PowerfulTiming = 1000;
        int PoorTiming = 300;

        for (int i = 0; i < 50; i++)
        {
            bullet[i] = NULL;
            bulletRect[i] = NULL;
        }
        for (int i = 0; i < 100; i++)
        {
            enemyBullet[i] = NULL;
            enemyBulletRect[i] = NULL;
        }
        for (int i = 0; i < 50; i++) {
            rocket[i] = NULL;
            rocketRect[i] = NULL;
        }


        bool isup = 0, isdown = 0, isleft = 0, isright = 0, fire = 0;
       

        float dy = 0, last_y = 0, new_y = 0;
        float last_enemy_y = 0, new_enemy_y = 0, dy_enemy = 0;

   
        bool animate_run = true;
        bool animate_idle = true;

        int lasttime = SDL_GetTicks();
        int newtime;
        int dt = 0;

        int frame = 0;
        int frame_count = 6;
        int frame_count_shoot = 4;
        int frame_count_shooter = 5;
        int cur_frametime = 0;
        int max_frametime = 1000 / 10;

        bool reload = 0;
        int debug = 1;

        SDL_FRect* CollisArray[100];
        SDL_FRect* playerRect = InitObject(player->x, player->y, 10, 130);
        SDL_FRect* enemyRect[100];
        SDL_FRect* enemyRadius[100];

        SDL_FRect* enemyRectRocket;
        SDL_FRect* enemyRadiusRocket;



        EnemyLoad(enemy, "EnemyLevel1.txt", ZOMBIE_COUNT, SHOOTER_COUNT);

	    for (int i = 0; i < ZOMBIE_COUNT; i++)
	    {
		    enemyRect[i] = InitObject(enemy[i]->x, enemy[i]->y, 10, 130);
		    enemyRadius[i] = InitObject(enemy[i]->x, enemy[i]->y, 300, 300);
	    }
	    for (int i = ZOMBIE_COUNT; i < SHOOTER_COUNT + ZOMBIE_COUNT; i++)
	    {
		    enemyRect[i] = InitObject(enemy[i]->x, enemy[i]->y, 10, 130);
		    enemyRadius[i] = InitObject(enemy[i]->x, enemy[i]->y, 300, 300);
	    }
        enemy[150] = EnemyInit(100, 50, 50, 0, 0, Rocket_man);
        enemyRectRocket = InitObject(enemy[150]->x, enemy[150]->y, 10, 130);
        enemyRadiusRocket = InitObject(enemy[150]->x, enemy[150]->y, 300, 300);
        
	    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
	    SDL_RenderClear(renderer);

        int sizeArray = 0;

        MassLoad(*CollisArray, "level1.txt", sizeArray);



	    while (running)
	    {
		    playerRect = InitObject(player->x + 50, player->y + 60, 20, 65);
		    for (int i = 0; i < ZOMBIE_COUNT; i++)
		    {
			    if (enemyRect[i] != NULL)
				    enemyRect[i] = InitObject(enemy[i]->x + 30, enemy[i]->y + 30, 35, 65);
			    if (enemyRadius[i] != NULL)
				    enemyRadius[i] = InitObject(enemy[i]->x - 100, enemy[i]->y - 85, 400, 400);
		    }
		    for (int i = ZOMBIE_COUNT; i < SHOOTER_COUNT + ZOMBIE_COUNT; i++)
		    {
			    if (enemyRect[i] != NULL)
				    enemyRect[i] = InitObject(enemy[i]->x + 30, enemy[i]->y + 30, 35, 55);
			    if (enemyRadius[i] != NULL)
				    enemyRadius[i] = InitObject(enemy[i]->x - 100, enemy[i]->y - 85, 400, 400);
		    }


            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    running = 0;
                }

                switch (event.type)
                {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_SPACE: fire = 1; break;
                    case SDL_SCANCODE_T: debug++; break;
                    case SDL_SCANCODE_R: reload = 1; break;
                    case SDL_SCANCODE_W: isup = 1; break;
                    case SDL_SCANCODE_S: isdown = 1; break;
                    case SDL_SCANCODE_A: isleft = 1; direction = DIR_LEFT; break;
                    case SDL_SCANCODE_D: isright = 1; direction = DIR_RIGHT; break;
                    case SDL_SCANCODE_UP: shootUp = 1; break;
                    case SDL_SCANCODE_DOWN: shootDown = 1; break;
                    case SDL_SCANCODE_LEFT: shootLeft = 1; break;
                    case SDL_SCANCODE_RIGHT: shootRight = 1; break;
                    case SDL_SCANCODE_L: escape = 1; break;
                    
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_SPACE: fire = 0; break;
                    case SDL_SCANCODE_W: isup = 0; break;
                    case SDL_SCANCODE_S: isdown = 0; break;
                    case SDL_SCANCODE_A: isleft = 0; break;
                    case SDL_SCANCODE_D: isright = 0; break;
                    case SDL_SCANCODE_UP: shootUp = 0; break;
                    case SDL_SCANCODE_DOWN: shootDown = 0; break;
                    case SDL_SCANCODE_LEFT: shootLeft = 0; break;
                    case SDL_SCANCODE_RIGHT: shootRight = 0; break;
                    case SDL_SCANCODE_L: escape = 0; break;
                    
                    }
                    break;
                }
            }

        
            animate_run = isleft  || isright || isup||  isdown;
            for (int i = 0; i < ZOMBIE_COUNT; i++)
                if (enemy[i] != NULL)
                    dst_enem_rect[i] = { (int)enemy[i]->x,(int)enemy[i]->y,enemy_rect_zombie.w,enemy_rect_zombie.h };

		    for (int i = ZOMBIE_COUNT; i < SHOOTER_COUNT + ZOMBIE_COUNT; i++)
			    if (enemy[i] != NULL)                                                                                    // Сюда картинку стрелка
				    dst_enem_rect[i] = { (int)enemy[i]->x,(int)enemy[i]->y,enemy_rect_zombie.w,enemy_rect_zombie.h };
		    dst_rect = { (int)player->x,(int)player->y,player_rect.w,player_rect.h };
            dst_enem_rocket_rect = { (int)enemy[150]->x ,(int)enemy[150]->y,enemy_rect_rocket.w,enemy_rect_rocket.h };
		    Tickrate(lasttime, newtime, dt);

    #pragma region DRAWING
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);


            //if (paralax_bg1_rect.x <= 0) {
            //  paralax_bg1_rect.x = 0;
            //  paralax_bg2_rect.x = WINDOW_WIDTH - paralax_bg2_rect.w;
            //}
            //else if (paralax_bg1_rect.x >= WINDOW_WIDTH - paralax_bg1_rect.w) {
            //  paralax_bg1_rect.x = WINDOW_WIDTH - paralax_bg1_rect.w;
            //  paralax_bg2_rect.x = 0;
            //}

		    if (player->x >= WINDOW_WIDTH / 2 && isright) {
			    player->x = WINDOW_WIDTH / 2;
			    back_rect.x-=3;
			    for (int j = 0; j < sizeArray; j++) {
				    (*CollisArray + j)->x-=3;
			    }
			    for (int i = 0; i < ZOMBIE_COUNT; i++) {
				    if(enemy[i] != NULL)
				    {
					    enemy[i]->x-=3;
				    }
			    }
			    for (int i = ZOMBIE_COUNT; i < SHOOTER_COUNT + ZOMBIE_COUNT; i++) {
				    if (enemy[i] != NULL)
				    {
					    enemy[i]->x-=3;
				    }
			    }

                damage_rect.x -= 3;
                speed_rect.x -= 3;
                damage_frect->x -= 3;
                speed_frect->x -= 3;
                speedShoot->x -= 3;
                upDamage->x -= 3;

                boomgun->x -= 3;
                flame->x -= 3;
                laser->x -= 3;
                shotgun->x -= 3;

                Boom_rect.x -= 3;
                boom_frect->x -= 3;

                flame_rect.x -= 3;
                flame_frect->x -= 3;

                laser_rect.x -= 3;
                laser_frect->x -= 3;

                shotgun_rect.x -= 3;
                shotgun_frect->x -= 3;


		    }
		    else if (player->x >= WINDOW_WIDTH / 2 - 10 && isleft) 
		    {
			    player->x = WINDOW_WIDTH / 2;
			    back_rect.x +=3;
			    for (int j = 0; j < sizeArray; j++) {
				    (*CollisArray + j)->x +=3;
			    }
			    for (int i = 0; i < ZOMBIE_COUNT; i++) {
				    if (enemy[i] != NULL)
				    {
					    enemy[i]->x +=3;
				    }
			    }
			    for (int i = ZOMBIE_COUNT; i < SHOOTER_COUNT + ZOMBIE_COUNT; i++) {
				    if (enemy[i] != NULL)
				    {
					    enemy[i]->x +=3;
				    }
			    }

                damage_rect.x += 3;
                speed_rect.x += 3;
                damage_frect->x += 3;
                speed_frect->x += 3;
                speedShoot->x += 3;
                upDamage->x += 3;

                boomgun->x += 3;
                flame->x += 3;
                laser->x += 3;
                shotgun->x += 3;

                Boom_rect.x += 3;
                boom_frect->x += 3;

                flame_rect.x += 3;
                flame_frect->x += 3;

                laser_rect.x += 3;
                laser_frect->x += 3;

                shotgun_rect.x += 3;
                shotgun_frect->x += 3;

            }
            dst_rect_Boomgun = { Boom_rect.x,Boom_rect.y ,Boom_rect.w ,Boom_rect.h };
            dst_rect_Flame = { flame_rect.x,flame_rect.y ,flame_rect.w ,flame_rect.h };
            dst_rect_lasergun = { laser_rect.x, laser_rect.y, laser_rect.w, laser_rect.h };
            dst_rect_shotgun = { shotgun_rect.x,shotgun_rect.y,shotgun_rect.w,shotgun_rect.h };
            dst_rect_bonus_damage = { damage_rect.x,damage_rect.y,damage_rect.w,damage_rect.h };
            dst_rect_bonus_speed = { speed_rect.x,speed_rect.y,speed_rect.w,speed_rect.h };
            dst_rect_bg = { back_rect.x,back_rect.y,back_rect.w,back_rect.h };



            if (isright) {
                paralax_bg1_rect.x -= 3;
                paralax_bg11_rect.x -= 3;
                paralax_bg111_rect.x -= 3;
                paralax_bg2_rect.x -= 4;
                paralax_bg22_rect.x -= 4;
                paralax_bg222_rect.x -= 4;
            }
            if (isleft) {
                paralax_bg1_rect.x += 3;
                paralax_bg11_rect.x += 3;
                paralax_bg111_rect.x += 3;
                paralax_bg2_rect.x += 4;
                paralax_bg22_rect.x += 4;
                paralax_bg222_rect.x += 4;
            }


            dst_rect_bg1 = { paralax_bg1_rect.x, paralax_bg1_rect.y, paralax_bg1_rect.w, paralax_bg1_rect.h };
            SDL_RenderCopy(renderer, paralax_bg1_tex, NULL, &dst_rect_bg1);

            dst_rect_bg11 = { paralax_bg11_rect.x, paralax_bg11_rect.y, paralax_bg11_rect.w, paralax_bg11_rect.h };
            SDL_RenderCopy(renderer, paralax_bg11_tex, NULL, &dst_rect_bg11);

            dst_rect_bg111 = { paralax_bg111_rect.x, paralax_bg111_rect.y, paralax_bg111_rect.w, paralax_bg111_rect.h };
            SDL_RenderCopy(renderer, paralax_bg111_tex, NULL, &dst_rect_bg111);

            dst_rect_bg2 = { paralax_bg2_rect.x, paralax_bg2_rect.y, paralax_bg2_rect.w, paralax_bg2_rect.h };
            SDL_RenderCopy(renderer, paralax_bg2_tex, NULL, &dst_rect_bg2);

            dst_rect_bg22 = { paralax_bg22_rect.x, paralax_bg22_rect.y, paralax_bg22_rect.w, paralax_bg22_rect.h };
            SDL_RenderCopy(renderer, paralax_bg22_tex, NULL, &dst_rect_bg22);

            dst_rect_bg222 = { paralax_bg222_rect.x, paralax_bg222_rect.y, paralax_bg222_rect.w, paralax_bg222_rect.h };
            SDL_RenderCopy(renderer, paralax_bg222_tex, NULL, &dst_rect_bg222);



            if (paralax_bg1_rect.x >= 3840) {
                paralax_bg1_rect.x = -1920;
                dst_rect_bg1 = { paralax_bg1_rect.x, paralax_bg1_rect.y, paralax_bg1_rect.w, paralax_bg1_rect.h };
                SDL_RenderCopy(renderer, paralax_bg1_tex, NULL, &dst_rect_bg1);
            }

            if (paralax_bg11_rect.x >3840) {
                paralax_bg11_rect.x = -1920;
                dst_rect_bg11 = { paralax_bg11_rect.x, paralax_bg11_rect.y, paralax_bg11_rect.w, paralax_bg11_rect.h };
                SDL_RenderCopy(renderer, paralax_bg11_tex, NULL, &dst_rect_bg11);
            }
            if (paralax_bg111_rect.x >= 3840) {
                paralax_bg111_rect.x = -1920;
                dst_rect_bg111 = { paralax_bg111_rect.x, paralax_bg111_rect.y, paralax_bg111_rect.w, paralax_bg111_rect.h };
                SDL_RenderCopy(renderer, paralax_bg111_tex, NULL, &dst_rect_bg111);
            }       

            if (paralax_bg1_rect.x <= -3840) {
                paralax_bg1_rect.x = 1920;
                dst_rect_bg1 = { paralax_bg1_rect.x, paralax_bg1_rect.y, paralax_bg1_rect.w, paralax_bg1_rect.h };
                SDL_RenderCopy(renderer, paralax_bg1_tex, NULL, &dst_rect_bg1);
            }

            if (paralax_bg11_rect.x <= -3840) {
                paralax_bg11_rect.x = 1920;
                dst_rect_bg11 = { paralax_bg11_rect.x, paralax_bg11_rect.y, paralax_bg11_rect.w, paralax_bg11_rect.h };
                SDL_RenderCopy(renderer, paralax_bg11_tex, NULL, &dst_rect_bg11);
            }
            if (paralax_bg111_rect.x < -3840) {
                paralax_bg111_rect.x = 1920;
                dst_rect_bg111 = { paralax_bg111_rect.x, paralax_bg111_rect.y, paralax_bg111_rect.w, paralax_bg111_rect.h };
                SDL_RenderCopy(renderer, paralax_bg111_tex, NULL, &dst_rect_bg111);
            }




            if (paralax_bg2_rect.x >= 3840) {
                paralax_bg2_rect.x = -1920;
                dst_rect_bg2 = { paralax_bg2_rect.x, paralax_bg2_rect.y, paralax_bg2_rect.w, paralax_bg2_rect.h };
                SDL_RenderCopy(renderer, paralax_bg2_tex, NULL, &dst_rect_bg2);
            }

            if (paralax_bg22_rect.x >= 3840) {
                paralax_bg22_rect.x = -1920;
                dst_rect_bg22 = { paralax_bg22_rect.x, paralax_bg22_rect.y, paralax_bg22_rect.w, paralax_bg22_rect.h };
                SDL_RenderCopy(renderer, paralax_bg22_tex, NULL, &dst_rect_bg22);
            }
            if (paralax_bg222_rect.x >= 3840) {
                paralax_bg222_rect.x = -1920;
                dst_rect_bg222 = { paralax_bg222_rect.x, paralax_bg222_rect.y, paralax_bg222_rect.w, paralax_bg222_rect.h };
                SDL_RenderCopy(renderer, paralax_bg222_tex, NULL, &dst_rect_bg222);
            }
            if (paralax_bg2_rect.x <= -3840) {
                paralax_bg2_rect.x = 1920;
                dst_rect_bg2 = { paralax_bg2_rect.x, paralax_bg2_rect.y, paralax_bg2_rect.w, paralax_bg2_rect.h };
                SDL_RenderCopy(renderer, paralax_bg2_tex, NULL, &dst_rect_bg2);
            }
            if (paralax_bg22_rect.x <= -3840) {
                paralax_bg22_rect.x = 1920;
                dst_rect_bg22 = { paralax_bg22_rect.x, paralax_bg22_rect.y, paralax_bg22_rect.w, paralax_bg22_rect.h };
                SDL_RenderCopy(renderer, paralax_bg22_tex, NULL, &dst_rect_bg22);
            }
            if (paralax_bg222_rect.x <= -3840) {
                paralax_bg222_rect.x = 1920;
                dst_rect_bg222 = { paralax_bg222_rect.x, paralax_bg222_rect.y, paralax_bg222_rect.w, paralax_bg222_rect.h };
                SDL_RenderCopy(renderer, paralax_bg222_tex, NULL, &dst_rect_bg222);
            }

        

            SDL_RenderCopy(renderer, back_tex, NULL, &dst_rect_bg);


            dst_rect_Flame = { flame_rect.x,flame_rect.y , flame_rect.w,flame_rect.h };
            SDL_RenderCopy(renderer, flame_tex, NULL, &dst_rect_Flame);

            dst_rect_Boomgun = { Boom_rect.x,Boom_rect.y , Boom_rect.w,Boom_rect.h };
            SDL_RenderCopy(renderer, Boom_tex, NULL, &dst_rect_Boomgun);

            dst_rect_shotgun = { shotgun_rect.x,shotgun_rect.y,shotgun_rect.w,shotgun_rect.h };
            SDL_RenderCopy(renderer, shotgun_tex, NULL, &dst_rect_shotgun);

            dst_rect_lasergun = { laser_rect.x,laser_rect.y,laser_rect.w,laser_rect.h };
            SDL_RenderCopy(renderer, laser_tex, NULL, &dst_rect_lasergun);

       
            dst_rect_bonus_speed = { speed_rect.x,speed_rect.y,speed_rect.w,speed_rect.h };
            SDL_RenderCopy(renderer, speedshoot_tex, NULL, &dst_rect_bonus_speed);

            dst_rect_bonus_damage = { damage_rect.x,damage_rect.y,damage_rect.w,damage_rect.h };
            SDL_RenderCopy(renderer, damageshoot_tex, NULL, &dst_rect_bonus_damage);

            if (animate_run) {

                cur_frametime += dt;
                if (cur_frametime >= max_frametime)
                {
                    cur_frametime -= max_frametime;
                    frame = (frame + 1) % frame_count;
                    player_rect.x = player_rect.w * frame;
                }
                if (hero_one) {

                    if ((direction == DIR_RIGHT))
                        SDL_RenderCopy(renderer, player_tex_run, &player_rect, &dst_rect);
                    else
                        SDL_RenderCopyEx(renderer, player_tex_run, &player_rect, &dst_rect, 0, NULL, SDL_FLIP_HORIZONTAL);
                }
                if (hero_two) {

                    if ((direction == DIR_RIGHT))
                        SDL_RenderCopy(renderer, hero_two_run_tex, &player_rect, &dst_rect);
                    else
                        SDL_RenderCopyEx(renderer, hero_two_run_tex, &player_rect, &dst_rect, 0, NULL, SDL_FLIP_HORIZONTAL);

                }
                if (hero_three) {

                    if ((direction == DIR_RIGHT) )
                        SDL_RenderCopy(renderer, hero_three_run_tex, &player_rect, &dst_rect);
                    else
                        SDL_RenderCopyEx(renderer, hero_three_run_tex, &player_rect, &dst_rect, 0, NULL, SDL_FLIP_HORIZONTAL);

                }
                

            }

            else if (fire || animate_run)
            {
                cur_frametime += dt;
                if (cur_frametime >= max_frametime)
                {
                    cur_frametime -= max_frametime;
                    frame = (frame + 1) % frame_count_shoot;
                    player_rect.x = player_rect.w * frame;
                }
                if (hero_one) {

                    if ((direction == DIR_RIGHT))
                        SDL_RenderCopy(renderer, fire_tex, &player_rect, &dst_rect);
                    else
                        SDL_RenderCopyEx(renderer, fire_tex, &player_rect, &dst_rect, 0, NULL, SDL_FLIP_HORIZONTAL);

                }
                if (hero_two) {

                    if ((direction == DIR_RIGHT))
                        SDL_RenderCopy(renderer, hero_two_shot_tex, &player_rect, &dst_rect);
                    else
                        SDL_RenderCopyEx(renderer, hero_two_shot_tex, &player_rect, &dst_rect, 0, NULL, SDL_FLIP_HORIZONTAL);

                }
                if (hero_three) {

                    if ((direction == DIR_RIGHT))
                        SDL_RenderCopy(renderer, hero_three_shot_tex, &player_rect, &dst_rect);
                    else
                        SDL_RenderCopyEx(renderer, hero_three_shot_tex, &player_rect, &dst_rect, 0, NULL, SDL_FLIP_HORIZONTAL);

                }

            }

            else if ((animate_run && fire) == false)
            {

                cur_frametime += dt;
                if (cur_frametime >= max_frametime)
                {
                    cur_frametime -= max_frametime;
                    frame = (frame + 1) % frame_count;
                    player_rect.x = player_rect.w * frame;
                }
                if (hero_one) {

                    if ((direction == DIR_RIGHT))
                        SDL_RenderCopy(renderer, player_tex_idle, &player_rect, &dst_rect);
                    else
                        SDL_RenderCopyEx(renderer, player_tex_idle, &player_rect, &dst_rect, 0, NULL, SDL_FLIP_HORIZONTAL);

                }
                if (hero_two) {

                    if ((direction == DIR_RIGHT))
                        SDL_RenderCopy(renderer, hero_two_idle_tex, &player_rect, &dst_rect);
                    else
                        SDL_RenderCopyEx(renderer, hero_two_idle_tex, &player_rect, &dst_rect, 0, NULL, SDL_FLIP_HORIZONTAL);

                }
                if (hero_three) {

                    if ((direction == DIR_RIGHT))
                        SDL_RenderCopy(renderer, hero_three_idle_tex, &player_rect, &dst_rect);
                    else
                        SDL_RenderCopyEx(renderer, hero_three_idle_tex, &player_rect, &dst_rect, 0, NULL, SDL_FLIP_HORIZONTAL);

                }

            }
            else if (fire != NULL)
            {

                cur_frametime += dt;
                if (cur_frametime >= max_frametime)
                {
                    cur_frametime -= max_frametime;
                    frame = (frame + 1) % frame_count_shoot;
                    player_rect.x = player_rect.w * frame;
                }
                if (hero_one) {

                    if ((direction == DIR_RIGHT))
                        SDL_RenderCopy(renderer, fire_tex, &player_rect, &dst_rect);
                    else
                        SDL_RenderCopyEx(renderer, fire_tex, &player_rect, &dst_rect, 0, NULL, SDL_FLIP_HORIZONTAL);

                }
                if (hero_two) {

                    if ((direction == DIR_RIGHT))
                        SDL_RenderCopy(renderer, hero_two_shot_tex, &player_rect, &dst_rect);
                    else
                        SDL_RenderCopyEx(renderer, hero_two_shot_tex, &player_rect, &dst_rect, 0, NULL, SDL_FLIP_HORIZONTAL);

                }
                if (hero_three) {

                    if ((direction == DIR_RIGHT))
                        SDL_RenderCopy(renderer, hero_three_shot_tex, &player_rect, &dst_rect);
                    else
                        SDL_RenderCopyEx(renderer, hero_three_shot_tex, &player_rect, &dst_rect, 0, NULL, SDL_FLIP_HORIZONTAL);

                }

            }
            if (running) {
                for (int i = 0; i < ZOMBIE_COUNT; i++)
                    if (enemy[i] != NULL)
                    {
                        if (running) {

						    cur_frametime += dt;
						    if (cur_frametime >= max_frametime)
						    {
							    cur_frametime -= max_frametime;
							    frame = (frame + 1) % frame_count;
							    enemy_rect_zombie.x = enemy_rect_zombie.w * frame;
						    }
						    if (direction_enemy[i] == DIR_RIGHT)
							    SDL_RenderCopy(renderer, enemy_tex_idle, &enemy_rect_zombie, &dst_enem_rect[i]);
						    else
							    SDL_RenderCopyEx(renderer, enemy_tex_idle, &enemy_rect_zombie,& dst_enem_rect[i], 0, NULL, SDL_FLIP_HORIZONTAL);
					    }
				    }
			    for (int i = ZOMBIE_COUNT; i < SHOOTER_COUNT + ZOMBIE_COUNT; i++)       // СЮДА ТОЖЕ КАРТИНКУ СТРЕЛАТ
				    if (enemy[i] != NULL)
				    {
					    if (running) {

                            cur_frametime += dt;
                            if (cur_frametime >= max_frametime)
                            {
                                cur_frametime -= max_frametime;
                                frame = (frame + 1) % frame_count_shooter;
                                enemy_rect_shooter.x = enemy_rect_shooter.w * frame;
                            }
                            if (direction_enemy[i] == DIR_RIGHT)
                                SDL_RenderCopy(renderer, enemy_shooter_tex_idle, &enemy_rect_shooter, &dst_enem_rect[i]);
                            else
                                SDL_RenderCopyEx(renderer, enemy_shooter_tex_idle, &enemy_rect_shooter, &dst_enem_rect[i], 0, NULL, SDL_FLIP_HORIZONTAL);
                        }
                    }
                SDL_Rect score_rect = { 5 ,-20,100,100 };

                sprintf_s(score, "score:%i", player->score);

                if (score_tex != NULL)
                    SDL_DestroyTexture(score_tex);
                score_tex = Load_Texture_Font(score, font, &score_rect, { 255,0,0,255 }, renderer);

                SDL_RenderCopy(renderer, score_tex, NULL, &score_rect);
    #pragma endregion

            
                if (SDL_HasIntersectionF(playerRect, damage_frect))
                 {
                    player->bonus = upDamage;
                    player->bonus->lifeTime = SDL_GetTicks();
                    SDL_DestroyTexture(damageshoot_tex);
                    free(damage_frect);
                 }

                if (SDL_HasIntersectionF(playerRect, speed_frect))
                {
                    player->bonus = speedShoot;
                    player->bonus->lifeTime = SDL_GetTicks();
                    SDL_DestroyTexture(speedshoot_tex);
                    free(speed_frect);
                }

                if (SDL_HasIntersectionF(playerRect, laser_frect))
                {
                    player->weapon = laser;
                    SDL_DestroyTexture(laser_tex);
                    free(laser_frect);
                }

                if (SDL_HasIntersectionF(playerRect, flame_frect))
                {
                    player->weapon = flame;
                    SDL_DestroyTexture(flame_tex);
                    free(flame_frect);
                }

                if (SDL_HasIntersectionF(playerRect, boom_frect))
                {
                    player->weapon = boomgun;
                    SDL_DestroyTexture(Boom_tex);
                    free(boom_frect);
                }

                if (SDL_HasIntersectionF(playerRect, shotgun_frect))
                {
                    player->weapon = shotgun;
                    SDL_DestroyTexture(shotgun_tex);
                    free(shotgun_frect);
                }



			    if (player != NULL)
			    {
				    EnemyShoot(lastShotTimeEnemy, newtime, dt, enemyBullet, enemy, player, enemyRadius, enemyRect, enemyBulletRect, playerRect, n_enemy, renderer, bullet_rect, bullet_tex, direction_enemy, ZOMBIE_COUNT, SHOOTER_COUNT);
				    PlayerMove(player, last_y, new_y, dy, dt, isup, isdown, isleft, isright, mainPhys, playerRect, *CollisArray, sizeArray);
				    for (int i = 0; i < ZOMBIE_COUNT + SHOOTER_COUNT; i++)
					    if (enemy[i] != NULL)
						    EnemyMove(enemy[i], enemyRadius[i], playerRect, enemyRect[i], mainPhys, *CollisArray, sizeArray, dt, last_enemy_y, new_enemy_y, dy_enemy, player, newtime, direction_enemy[i]);
				    Shoot(newtime, lastShotTime, fire, shootRight, shootLeft, shootUp, shootDown, direction, n, bullet, playerRect, dt, bulletRect, enemy, enemyRect, enemyRadius, player, renderer, bullet_rect, bullet_tex, PowerfulTiming, PoorTiming, ZOMBIE_COUNT, SHOOTER_COUNT);
			    IsPlayerDie(player, respawn_x, respawn_y, rifle, running,main_menu);
			    }
			    if (reload == 1)
			    {
				    free(player);
				    player = PlayerInit(100, 100, 3, respawn_x, respawn_y, 0, 1, 0, 0, rifle, speedShoot);
				    reload = 0;
			    }
			    if (debug % 2 == 0)
			    {
				    SDL_SetRenderDrawColor(renderer, 200, 0, 200, 255);
				    for (int i = 0; i < sizeArray; i++)
				    {
					    SDL_RenderFillRectF(renderer, *CollisArray + i);
					    SDL_RenderDrawRectF(renderer, *CollisArray + i);
				    }
				    //SDL_RenderFillRectF(renderer, playerRect);
				    SDL_SetRenderDrawColor(renderer, 200, 150, 200, 255);
				    for (int i = 0; i < ZOMBIE_COUNT + SHOOTER_COUNT; i++)
					    if (enemyRadius[i] != NULL)
					    {
						    SDL_RenderFillRectF(renderer, enemyRadius[i]);
						    SDL_RenderDrawRectF(renderer, enemyRadius[i]);
					    }
				    SDL_SetRenderDrawColor(renderer, 200, 0, 200, 255);
				    for (int i = 0; i < ZOMBIE_COUNT + SHOOTER_COUNT; i++)
					    if (enemyRect[i] != NULL)
					    {
						    SDL_RenderFillRectF(renderer, enemyRect[i]);
						    SDL_RenderDrawRectF(renderer, enemyRect[i]);
					    }
				    for (int i = 1; i < 10; i++)
				    {
					    if (bulletRect[i] != NULL)
					    {
						    SDL_RenderFillRectF(renderer, bulletRect[i]);
						    SDL_RenderDrawRectF(renderer, bulletRect[i]);
					    }
				    }
			    }
                if (player->life <= 0 || escape) {
                    player->life = 3;
                    running = 0;
                    main_menu = 0;
                    score_window = 1;
                    SaveScoreTable(player, "ScoreTable.txt"); 
                    for (int i = 0; i < ZOMBIE_COUNT+SHOOTER_COUNT; i++)
                    {
                        enemyRect[i] = NULL;
                        enemyRadius[i] = NULL;
                    }
                 

     
                   
                }
            
			    SDL_RenderPresent(renderer);
		    }
		

        }
    }

    SaveScoreTable(player, "ScoreTable.txt");
    TTF_CloseFont(font);
    
    
    Quit(&window, &renderer, &screen_surface);
    return 0;
}
/*
ПН: Виды 4 оружия, виды 3 противников
ВТ: 3 уровня, всё в файлы перенести
ЧТ: Сейвы и запись рекордов

ПТ: Босс, точки уязвимрсти.
Подбираемые бонусы оружия
*/


//player->bonus->lifeTime = SDL_GetTicks();