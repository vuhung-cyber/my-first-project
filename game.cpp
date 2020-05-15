#include <iostream>
//#include <string>
#include <SDL.h>
using namespace std;

const int Screen_Width = 640;
const int Screen_Height = 480;
int a = 30;
const string Window_Tille = "Tiny Game";
SDL_Window* window;
SDL_Renderer* renderer_map;
SDL_Surface* h_screen = nullptr;
SDL_Texture* h_texture = nullptr;
SDL_Texture* h_box = nullptr;
SDL_Texture* h_drop_box = nullptr;
SDL_Event h_event;
bool is_running = true;

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

Box cua_so(480,0,160,480);
Box mini(a,a,480-2*a,480-2*a);
Box column1(240-a/2,a,a,3*a);
Box column2(a,240-a/2,3*a,a);
Box column3(240-a/2,480-4*a,a,3*a);
Box column4(480-4*a,240-a/2,3*a,a);
SDL_Rect sourceRect;
int x_source_rect = a;
int y_source_rect = a;
SDL_Rect drop_box;
int x_drop_box = 480-a-a;
int y_drop_box = a;

SDL_Texture *load_texture(std::string path);

void load_picture();

void box_drop();
void Move();

void paint_screen();


int main(int argc,char* agcv[]){


    initSDL(window, renderer_map);

    SDL_RenderClear(renderer_map);
    paint_screen();
    while(is_running){
        SDL_RenderClear(renderer_map);
        if(y_drop_box <= 240 - a/2 - a){
            box_drop();
        }
        SDL_PollEvent(&h_event);
        if(h_event.type == SDL_QUIT){
            is_running = false;
            break;
        }
        if(h_event.type == SDL_KEYDOWN){
            Move();

        }
        paint_screen();
    }

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

SDL_Texture *load_texture(std::string path)
{
    SDL_Surface* load_surface = SDL_LoadBMP(path.c_str());
    if(load_surface == nullptr){
        cout << "false";
        return nullptr;
    }else{
        h_texture = SDL_CreateTextureFromSurface(renderer_map,load_surface);
        if(h_texture == nullptr){
            cout << "fail to load texture" << endl;
        }
        SDL_FreeSurface(load_surface);
    }
    return h_texture;
}

void load_picture()
{
    h_box = load_texture("box/box_main.bmp");
    if(h_box == nullptr){
        cout << "fail load picture" << endl;
    }else{
        SDL_QueryTexture(h_box, NULL, NULL, &sourceRect.w, &sourceRect.h);
        sourceRect.x = x_source_rect;
        sourceRect.y = y_source_rect;
        SDL_RenderCopy(renderer_map,h_box,NULL,&sourceRect);
    }

    h_drop_box = load_texture("box/box_drop_2.bmp");
    if(h_drop_box == nullptr){
        cout << "fail load picture" << endl;
    }else{
        SDL_QueryTexture(h_drop_box, NULL, NULL, &drop_box.w, &drop_box.h);
        drop_box.x = x_drop_box;
        drop_box.y = y_drop_box;
        SDL_RenderCopy(renderer_map,h_drop_box,NULL,&drop_box);
    }
}

void box_drop()
{
    y_drop_box += 10;
    if(y_drop_box > 240 - a/2 - a){
        y_drop_box = 240 - a/2 - a;
    }
    SDL_Delay(100);
}

void Move()
{
    switch(h_event.key.keysym.sym){
        case SDLK_ESCAPE : {
            is_running = false;
            break;
        }
        case SDLK_DOWN : {
            y_source_rect += 10;
            SDL_Delay(100);
            break;
        }
        case SDLK_UP : {
            y_source_rect -= 10;
            SDL_Delay(100);
            break;
        }
        case SDLK_LEFT : {
            x_source_rect -= 10;
            SDL_Delay(100);
            break;
        }
        case SDLK_RIGHT : {
            x_source_rect += 10;
            SDL_Delay(100);
            break;
        }
    }
}

void paint_screen()
{
    cua_so.render(renderer_map,255,255,255,255);
    mini.render(renderer_map,255,255,255,255);
    column1.render(renderer_map,0,0,0,0);
    column2.render(renderer_map,0,0,0,0);
    column3.render(renderer_map,0,0,0,0);
    column4.render(renderer_map,0,0,0,0);

    load_picture();

    SDL_RenderPresent(renderer_map);

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
