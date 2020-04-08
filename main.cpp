#include <iostream>
#include <SDL.h>

using namespace std;

const int SCREEN_WIDTH=800;
const int SCREEN_HEIGHT=670;
//const string SCREEN_WINDOW="DEMO_GAME";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);


bool loadMedia();

void close();

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

SDL_Surface *gXout = NULL;

SDL_Window *gWindow = NULL;

SDL_Surface *gScreenSurface = NULL;

void underGround(SDL_Renderer* &renderer);

struct Box {
    int x;
    int y;
    int size1;
    int size2;

    void render(SDL_Renderer* renderer,int color1,int color2,int color3,int color4){
        SDL_Rect filled_rect;
        filled_rect.x = x;
        filled_rect.y = y;
        filled_rect.w = size1;
        filled_rect.h = size2;
        SDL_SetRenderDrawColor(renderer,color1 ,color2 ,color3 ,color4);
        SDL_RenderFillRect(renderer, &filled_rect);
    }

    bool inside(int minX, int minY, int maxX, int maxY){
        return (minX <= x && minY <= y && maxX >= x + size1 && maxY >= y + size2);
    }

    void moveleft()
    {
        x-=10;
    }
    void moveright()
    {
        x+=10;
    }
};

void jumping(Box box_X,SDL_Renderer* &renderer);

void impediment(SDL_Renderer* &renderer);

int main(int argc, char* argv[])
{
    SDL_Renderer *renderer;

    initSDL(gWindow, renderer);

    SDL_RenderClear(renderer);

    Box box;
    box.x = 400;
    box.y = 500;
    box.size1 = 50;
    box.size2 = 70;
    SDL_Event e;

    while(box.inside(0,0,SCREEN_WIDTH, SCREEN_HEIGHT)){
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderClear(renderer);
        underGround(renderer);
        box.render(renderer, 255, 0, 0, 255);
        //impediment(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(10);
        if ( SDL_WaitEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN) {
        	switch (e.key.keysym.sym) {
        		case SDLK_ESCAPE: break;
        			break;
                case SDLK_LEFT : box.moveleft();
                    break;
            	case SDLK_RIGHT : box.moveright();
            		break;
            	case SDLK_UP : jumping(box,renderer);
            		break;
        		default: break;
			}
        }

    }

    SDL_RenderPresent(renderer);

    close();

    quitSDL(gWindow, renderer);

    return 0;
}


void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow("DEMO_GAME", SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}


bool loadMedia()
{
    bool success = true;
    gXout = SDL_LoadBMP("...");

    if(gXout = NULL){
        cout <<"false: "<<SDL_GetError();
        success = false;
    }

    return success;
}

void underGround(SDL_Renderer* &renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    SDL_Rect ground;
    ground.x = 0;
    ground.y = 570;
    ground.w = SCREEN_WIDTH;
    ground.h = SCREEN_HEIGHT-570;

    SDL_RenderFillRect(renderer,& ground);

}

void jumping(Box box_X, SDL_Renderer* &renderer)
{
    int jump = box_X.y;
    for(int i=jump; i>=jump-80; i-=10){
        box_X.y -= 10;
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderClear(renderer);
        underGround(renderer);
        box_X.render(renderer, 255, 0, 0, 255);
        SDL_RenderPresent(renderer);
        SDL_Delay(50);
    }
    for(int i=jump; i<=jump+80; i+=10){
        box_X.y += 10;
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderClear(renderer);
        underGround(renderer);
        box_X.render(renderer, 255, 0, 0, 255);
        SDL_RenderPresent(renderer);
        SDL_Delay(50);
    }

}

void impediment(SDL_Renderer* &renderer)
{
    int X = rand() % 800 + 0;
    int Y = 0;
    Box box1;
    box1.x = X;
    box1.y = Y;
    box1.size1 = 30;
    box1.size2 = 30;
    box1.render(renderer,0,0,0,0);
}

void waitUntilKeyPressed()
{
	SDL_Event e;
	while (true) {
		if (SDL_WaitEvent(&e) != 0 &&
			(e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
			return;
	}
}

void close()
{
    SDL_FreeSurface(gXout);
    gXout = NULL;
    SDL_DestroyWindow(gWindow);

    gWindow = NULL;

    SDL_Quit();
}

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

