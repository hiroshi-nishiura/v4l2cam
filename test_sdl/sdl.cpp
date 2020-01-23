#include <stdio.h>
#include <iostream>
#include <sstream>

#include <SDL2/SDL.h>
#include "v4l2cam.h"

#if 0
#define WIDTH 800
#define HEIGHT 600
#else
#define WIDTH 320
#define HEIGHT 240
#endif
//#define YUV2RGB

unsigned user_event_trigger(Uint32 interval, void* param)
{
    SDL_Event event;
    event.type = SDL_USEREVENT;
    SDL_PushEvent(&event);
    return interval;
}

int main (int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
        return 1;

    v4l2cam vcam;
    if( vcam.open(WIDTH,HEIGHT) == 0 )
    {
        return 0;
    }

	SDL_Window *win = SDL_CreateWindow("V4L2SDL", 100, 100, vcam.width(), vcam.height(), 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

#ifdef YUV2RGB
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             vcam.width(), vcam.height());
#else
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_YUY2,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             vcam.width(), vcam.height());
#endif
    printf("Resolution=%dx%d\n", vcam.width(), vcam.height());

    SDL_Rect rect = {0,0,vcam.width(), vcam.height()};

    // performance timer
    SDL_TimerID user_event_trigger_id = SDL_AddTimer(1000, user_event_trigger, NULL);

	// main loop
    unsigned fps = 0;
    unsigned cam_fps = 0;
	while (1)
    {
        const void* buffer = vcam.capture(); // async
        if(buffer)
        {
#ifdef YUV2RGB
            buffer = vcam.yuv2rgb(buffer);
            SDL_UpdateTexture(texture, NULL, buffer, vcam.width()*3);
#else
            SDL_UpdateTexture(texture, NULL, buffer, vcam.width()*2);
#endif
            cam_fps++;
        }
        // clear the screen
        SDL_RenderClear(renderer);

        // copy the texture to the rendering context
        SDL_RenderCopy(renderer, texture, NULL, &rect);

        // flip the backbuffer
        SDL_RenderPresent(renderer);

        fps++;
        
		// event handling
        SDL_Event e;
		if ( SDL_PollEvent(&e) )
        {
			if (e.type == SDL_QUIT)
				break;
			else if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
				break;

            else if(e.type == SDL_USEREVENT)
            {
                std::stringstream ss;
                ss << "FPS:" << fps << " CAM_FPS:" << cam_fps;
                SDL_SetWindowTitle(win, ss.str().c_str());
                fps = cam_fps = 0;
            }
		}
	}
	
    vcam.close();

    SDL_RemoveTimer(user_event_trigger_id);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	
	return 0;
}





