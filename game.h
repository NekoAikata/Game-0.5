#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const int TILE_SIZE = 40;
const int MAP_WIDTH = SCREEN_WIDTH / TILE_SIZE;
const int MAP_HEIGHT = SCREEN_HEIGHT / TILE_SIZE;

class Game{
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;

    //function
    Game(){
        running = true;
        if (SDL_Init(SDL_INIT_VIDEO) < 0){
            cerr << "Couldnt init:" << SDL_GetError() << endl;
            running = false;
        }
        window = SDL_CreateWindow("Save the King", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (!window){
            cerr << "Couldnt window:" << SDL_GetError() << endl;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer){
            cerr << "Couldnt renderer:" << SDL_GetError() << endl;
        }
    }
    void render() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for (int i = 1; i < MAP_HEIGHT - 1;++i){
            for (int j = 1; j < MAP_WIDTH - 1;++j){
                SDL_Rect tile = {j*TILE_SIZE, i*TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_RenderFillRect(renderer, &tile);
            }
        }
        SDL_RenderPresent(renderer);
    }

    void run () {
        while (running){
            render();
            SDL_Delay(16);
        }
    }

    ~Game() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};
