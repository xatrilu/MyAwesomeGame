#include "SDL/include/SDL.h"
#include "SDL_Image/include/SDL_image.h"

#pragma comment (lib, "SDL/libx86/SDL2.lib")
#pragma comment (lib, "SDL/libx86/SDL2main.lib")
#pragma comment (lib, "SDL_Image/libx86/SDL2_image.lib")


int main(int argc, char * argv[]) {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	IMG_Init(IMG_INIT_PNG);

	SDL_Window *window;
	SDL_Renderer *renderer = NULL;
	SDL_Event event;
	int running = 1;
	SDL_Rect dstrect, misile;

	int anchventana = 840, altventana = 600;

	window = SDL_CreateWindow(
		"Sprite Prueba",                  
		SDL_WINDOWPOS_CENTERED,           
		SDL_WINDOWPOS_CENTERED,           
		anchventana,
		altventana,
		SDL_WINDOW_OPENGL                  
	);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	SDL_Texture *starship, *bullet, *background;
	background = IMG_LoadTexture(renderer, "assets/SpaceBackground.png");
	starship = IMG_LoadTexture(renderer, "assets/Spaceship.png");
	bullet = IMG_LoadTexture(renderer, "assets/Laser.png");


	dstrect.x = anchventana*0.1;
	dstrect.y = altventana*0.1;
	dstrect.w = 240;
	dstrect.h = 240;

	int left = 0, down = 0, right = 0, up = 0;
	int posx = dstrect.x, posy = dstrect.y;


	struct Vector
	{
		float cx = 0;
		float cy = 0;
	} vector;

	while (running == 1) {
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case (SDL_KEYDOWN):
					switch (event.key.keysym.sym) {
					case SDLK_LEFT: left = 1; break;
					case SDLK_RIGHT: right = 1; break;
					case SDLK_UP: up = 1; break;
					case SDLK_DOWN: down = 1; break;
					case SDLK_ESCAPE: running = 0; break;
					case SDLK_SPACE: 
						misile.x = dstrect.x+ dstrect.w;
						misile.y = dstrect.y+ (dstrect.h/3);
						misile.w = dstrect.w/3;
						misile.h = dstrect.h/4;
						 break;
					}
					break;
				    
				    case SDL_KEYUP:
					switch (event.key.keysym.sym)
					{
					case SDLK_LEFT: left = 0; break;
					case SDLK_DOWN: down = 0; break;
					case SDLK_UP: up  = 0; break;
					case SDLK_RIGHT: right = 0; break;
					}
					break;
				    case (SDL_QUIT): running = 0; break;
					

				}
			}
			if (right == 1 && left == 1)vector.cx = 0;
			else if (left == 1) vector.cx = -1;
			else if (right == 1) vector.cx = 1;
			if (up == 1 && down == 1)vector.cy = 0;
			else if (up == 1) vector.cy = -1;
			else if (down == 1) vector.cy = 1;

			posx += vector.cx;
			posy += vector.cy;
			vector.cx = 0;
			vector.cy = 0;

			dstrect.x = (posx * (2));
			dstrect.y = (posy * (2));


		SDL_RenderClear(renderer);
		misile.x += 10;

		SDL_RenderCopy(renderer, background, NULL, NULL);
		SDL_RenderCopy(renderer, bullet, NULL, &misile);
		SDL_RenderCopy(renderer, starship, NULL, &dstrect);
		SDL_RenderPresent(renderer);

	}
	
	SDL_DestroyTexture(bullet);
	SDL_DestroyTexture(starship);
	SDL_DestroyTexture(background);
	IMG_Quit();
	SDL_Quit();

	return 0;
}
