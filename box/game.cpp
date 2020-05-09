#include <iostream>
#include <SDL.h>
using namespace std;

const int Screen_Width = 640;
const int Screen_Height = 480;
const string Window_Tille = "Tiny Game";

void logSDLError(std::ostream& os,
                 const std::string &smg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void waitUntilKeyPressed();

void quitSDL(SDL_Window* &window, SDL_Renderer* &renderer);

struct Box
{
    int x;
    int y;
    int w;
    int h;

    Box(int _x, int _y, int _w, int _h)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;
    }

    void render(SDL_Renderer *renderer,int color1, int color2, int color3, int color4)
    {
        SDL_Rect filled_rect;
        filled_rect.x = x;
        filled_rect.y = y;
        filled_rect.w = w;
        filled_rect.h = h;
        SDL_SetRenderDrawColor(renderer, color1, color2, color3, color4);
        SDL_RenderFillRect(renderer, &filled_rect);
    }
};

int main(int argc,char* agcv[]){
    SDL_Window* window;
    SDL_Renderer* renderer_map;

    initSDL(window, renderer_map);

    SDL_RenderClear(renderer_map);

    Box cua_so(480,0,160,480);
    cua_so.render(renderer_map,255,255,255,255);

    int a = 30;

    Box mini(a,a,480-2*a,480-2*a);
    mini.render(renderer_map,255,255,255,255);

    Box column1(240-a/2,a,a,3*a);
    column1.render(renderer_map,0,0,0,0);

    Box column2(a,240-a/2,3*a,a);
    column2.render(renderer_map,0,0,0,0);

    Box column3(240-a/2,480-4*a,a,3*a);
    column3.render(renderer_map,0,0,0,0);

    Box column4(480-4*a,240-a/2,3*a,a);
    column4.render(renderer_map,0,0,0,0);

    SDL_Rect sourceRect;
    SDL_Rect desRect;

    SDL_Surface* h_screen = SDL_LoadBMP("box/box_1.bmp");
    if(h_screen == NULL){
        cout << "false";
    }
    SDL_Texture* h_texture = NULL;

    h_texture = SDL_CreateTextureFromSurface(renderer_map,h_screen);
    //SDL_FreeSurface(h_screen);
    SDL_QueryTexture(h_texture, NULL, NULL, &sourceRect.w, &sourceRect.h);

    sourceRect.x = desRect.x = 240-a/2;
    sourceRect.y = desRect.y = 240-a/2;
    desRect.w = sourceRect.w;
    desRect.h = sourceRect.h;

    SDL_RenderCopy(renderer_map,h_texture,&sourceRect,&desRect);
    SDL_RenderPresent(renderer_map);


    waitUntilKeyPressed();
    quitSDL(window, renderer_map);
    return 0;
}


void logSDLError(std::ostream& os,
                 const std::string &smg, bool fatal)
{
    os << smg <<"Error: "<<SDL_GetError()<<std::endl;
    if(fatal){
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout,"SDL_Init",true);
    window = SDL_CreateWindow(Window_Tille.c_str(),SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,Screen_Width,Screen_Height,SDL_WINDOW_SHOWN);
    if(window == NULL){
        logSDLError(std::cout,"create Window",true);
    }
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED |
                                            SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL){
        logSDLError(std::cout,"create Renderer",true);
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"linear");
    SDL_RenderSetLogicalSize(renderer,Screen_Width,Screen_Height);
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while(true){
        if(SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return ;
        SDL_Delay(100);
    }
}

void quitSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
