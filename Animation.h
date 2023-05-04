#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <stdio.h>
#include <SDL.h>

struct frameAnim {
	SDL_Texture* player_action_run;
	SDL_Texture* player_action_idle;
	SDL_Texture* player_action_die;
	int frame;
	int frame_count_run;
	int frame_count_idle;
	int frame_count_die;
	int cur_frametime;
	int max_frametime;

};

#endif