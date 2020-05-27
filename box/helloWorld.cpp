#include <iostream>
//#include <string>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
using namespace std;

const int Screen_Width = 640;
const int Screen_Height = 480;
int a = 30;
int temp_x = 30;
int temp_y = 30;
int x_temp_mouse = 0;
int y_temp_mouse = 0;
int x_mouse = 0;
int y_mouse = 0;
bool is_running = true;
bool run_game = true;
int dem = 0;
int or_0_1 = 0;
int a1[16][16] = {0};
const string Window_Tille = "Tiny Game";
SDL_Window* window;
SDL_Renderer* renderer_map;
SDL_Surface* h_screen = nullptr;
SDL_Texture* h_texture = nullptr;
SDL_Texture* h_box = nullptr;
SDL_Texture* h_drop_box = nullptr;
SDL_Texture* h_amazing_fire = nullptr;
SDL_Texture* h_bigger_fire = nullptr;
SDL_Texture* h_move_fire = nullptr;
SDL_Texture* h_winner = nullptr;
SDL_Texture* h_loser = nullptr;
SDL_Texture* h_esc = nullptr;
SDL_Texture* h_play = nullptr;
SDL_Texture* h_again = nullptr;
//SDL_Texture* h_help = nullptr;
SDL_Event h_event;



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
    void apply_array(){
        if(w > h){
            for(int i = 0; i<w/30; i++){
                a1[y/30][x/30 + i] = 1;
            }
        }else{
            for(int i=0; i<h/30; i++){
                a1[y/30 + i][x/30] = 1;
            }
        }
    }
};

Box cua_so(480,0,160,480);
Box mini(a,a,480-2*a,480-2*a);
Box column1(240-a,a,a,3*a);
Box column2(a,240-a,3*a,a);
Box column3(240-a,480-4*a,a,3*a);
Box column4(480-4*a,240-a,3*a,a);
Box column5(120, a, a, a);
Box column6(a, 3*a, a, a);
Box column7(3*a, 3*a, 2*a, a);
Box column8(2*a, 5*a, 8*a, a);
Box column9(5*a, 3*a, a, 9*a);
Box column10(2*a, 9*a, 3*a, a);
Box column11(3*a, 10*a, a, 4*a);
Box column12(a,11*a,a,a);
Box column13(a,13*a,a,a);
Box column14(5*a,13*a,a,a);
Box column15(6*a,10*a,a,a);
Box column16(9*a,11*a,a,a);
Box column17(480-2*a,9*a,a,a);
Box column18(480-5*a,4*a,a,a);
Box column19(240-a,240-a,a,a);
Box column20(240,10*a,3*a,a);//
Box column21(240+a,13*a,2*a,a);
Box column22(480-5*a,9*a,a,5*a);
Box column23(480-4*a,9*a,a,a);
Box column24(240-a,240,4*a,a);
Box column25(480-3*a,11*a,a,3*a);
Box column26(480-3*a,2*a,a,4*a);
Box column27(240+a,2*a,4*a,a);
Box column28(240+a,3*a,a,2*a);

SDL_Rect sourceRect;
int x_source_rect = a;
int y_source_rect = a;
SDL_Rect drop_box;
int x_drop_box = 480-a-a;
int y_drop_box = a;
SDL_Rect winner;
int x_winner = 160;
int y_winner = 160;
SDL_Rect fire_one;
int x_fire_1 = 6*a;
int y_fire_1 = a;
SDL_Rect fire_two;
int x_fire_2 = 8*a;
int y_fire_2 = 7*a - 9;
SDL_Rect fire_three;
int x_fire_3 =480-4*a;
int y_fire_3 =3*a;
SDL_Rect loser;
int x_loser = 160;
int y_loser = 160;
SDL_Rect esc;
int x_esc = 480;
int y_esc = 0;
SDL_Rect play;
int x_play = 480;
int y_play = 160;
/*SDL_Rect help;
int x_help = 480;
int y_help = 320;*/
/*SDL_Rect again;
int x_again = 120;
int y_again = 120;*/


SDL_Texture *load_texture(std::string path);

void logSDLError(std::ostream& os,
                 const std::string &smg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void waitUntilKeyPressed();

void quitSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void load_picture();

void blow_fire();

void run_fire();

void Move();

void mouse();

void paint_screen();

void map_arr_0_1();

void scan_arr();

bool va_cham(int _x, int _y);

void destroy_all();

void play_again();

int main(int argc,char* agcv[]){


    initSDL(window, renderer_map);
    SDL_RenderClear(renderer_map);
    paint_screen();

    map_arr_0_1();

    while(is_running){
        if(run_game == true){
            SDL_RenderClear(renderer_map);
            blow_fire();
            run_fire();

            SDL_PollEvent(&h_event);
            if(h_event.type == SDL_QUIT){
                is_running = false;
                break;
            }
            if(h_event.type == SDL_KEYDOWN){
                dem = 0;
                Move();
                scan_arr();
                if(dem == 0){
                    x_source_rect = temp_x;
                    y_source_rect = temp_y;
                }
            }
            mouse();
            paint_screen();
            SDL_Delay(100);
        }else if(run_game == false){
            mouse();

        }
    }

    destroy_all();
    //waitUntilKeyPressed();
    //quitSDL(window, renderer_map);
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
        cout << "false!!";
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
    h_esc = load_texture("box/thoat.bmp");
    if(h_esc != nullptr){
        SDL_QueryTexture(h_esc,NULL,NULL,&esc.w,&esc.h);
        esc.x = x_esc;
        esc.y = y_esc;
        SDL_RenderCopy(renderer_map,h_esc,NULL,&esc);
    }

    h_play = load_texture("box/play.bmp");
    if(h_play != nullptr){
        SDL_QueryTexture(h_play,NULL,NULL,&play.w,&play.h);
        play.x = x_play;
        play.y = y_play;
        SDL_RenderCopy(renderer_map,h_play,NULL,&play);
    }

    /*h_help = load_texture("box/help.bmp");
    if(h_help != nullptr){
        SDL_QueryTexture(h_help,NULL,NULL,&help.w,&help.h);
        help.x = x_help;
        help.y = y_help;
        SDL_RenderCopy(renderer_map,h_help,NULL,&help);
    }*/

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

    h_amazing_fire = load_texture("box/fire_1.bmp");
    if(h_amazing_fire != nullptr){
        SDL_QueryTexture(h_amazing_fire, NULL, NULL, &fire_one.w, &fire_one.h);
        fire_one.x = x_fire_1;
        fire_one.y = y_fire_1;
        SDL_RenderCopy(renderer_map,h_amazing_fire,NULL,&fire_one);
    }else{
        cout << "fail load picture fire";
    }

    h_bigger_fire = load_texture("box/fire_3.bmp");
    if(h_bigger_fire != nullptr){
        SDL_QueryTexture(h_bigger_fire, NULL, NULL, &fire_two.w, &fire_two.h);
        fire_two.x = x_fire_2;
        fire_two.y = y_fire_2;
        SDL_RenderCopy(renderer_map,h_bigger_fire,NULL,&fire_two);
    }

    h_move_fire = load_texture("box/fire_1.bmp");
    if(h_move_fire != nullptr){
        SDL_QueryTexture(h_move_fire, NULL, NULL, &fire_three.w, &fire_three.h);
        fire_three.x = x_fire_3;
        fire_three.y = y_fire_3;
        SDL_RenderCopy(renderer_map,h_move_fire,NULL,&fire_three);
    }
    if((x_source_rect == x_drop_box - a && y_source_rect == y_drop_box) || (x_source_rect == x_drop_box && y_source_rect == y_drop_box + a)){
        h_winner = load_texture("box/winner.bmp");
        if(h_winner == nullptr){
            cout << "fucking... "<<endl;
        }
        SDL_QueryTexture(h_winner, NULL, NULL, &winner.w, &winner.h);
        winner.x = x_winner;
        winner.y = y_winner;
        SDL_RenderCopy(renderer_map,h_winner,NULL,&winner);
        run_game = false;
    }
    if(va_cham(x_fire_3,y_fire_3) == false ||va_cham(x_fire_1,y_fire_1) == false ||(x_source_rect == 9*a && y_source_rect == 6*a)){
        h_loser = load_texture("box/loser.bmp");
        if(h_loser != nullptr){
            SDL_QueryTexture(h_loser, NULL, NULL, &loser.w, &loser.h);
            loser.x = x_loser;
            loser.y = y_loser;
            SDL_RenderCopy(renderer_map,h_loser,NULL,&loser);
            run_game = false;
        }
    }
    /*if((x_mouse >= help.x && x_mouse <= help.x + help.w)
        && (y_mouse >= help.y && y_mouse <= help.y + help.h)){
        h_again = load_texture("box/again.bmp");
        SDL_QueryTexture(h_again,NULL,NULL,&again.w,&again.h);
        again.x = x_again;
        again.y = y_again;
        SDL_RenderCopy(renderer_map,h_again,NULL,&again);
        run_game = false;
    }*/
}

void blow_fire()
{
    if(x_source_rect >= 6*a && x_source_rect <= 8*a && y_source_rect >= 3*a && y_source_rect <= 5*a ){
        if(y_fire_1 != 4*a){
            y_fire_1 += 10;
        }
    }
}

void run_fire()
{
    if(or_0_1 == 0){
        y_fire_3 += 10;
        if(y_fire_3 == 6*a)or_0_1 = 1;
        //cout << y_fire_3 <<endl;
    }
    else if(or_0_1 == 1){
        y_fire_3 -= 10;
        if(y_fire_3 == 3*a)or_0_1 = 0;
        //cout << y_fire_3 <<endl;
    }
}

void Move()
{
    temp_x = x_source_rect;
    temp_y = y_source_rect;
    switch(h_event.key.keysym.sym){
        case SDLK_ESCAPE : {
            is_running = false;
            break;
        }
        case SDLK_DOWN : {
            temp_y = y_source_rect + 10;

            break;
        }
        case SDLK_UP : {
            temp_y = y_source_rect - 10;

            break;
        }
        case SDLK_LEFT : {
            temp_x = x_source_rect - 10;

            break;
        }
        case SDLK_RIGHT : {
            temp_x = x_source_rect + 10;

            break;
        }
    }
}

void mouse()
{
    switch(h_event.type)
    {
        case SDL_QUIT :
        {
            is_running = false;
            break;
        }
        case SDL_MOUSEMOTION:
        {
            x_temp_mouse = h_event.motion.x;
            y_temp_mouse = h_event.motion.y;
            break;
        }
        case SDL_MOUSEBUTTONDOWN:{
            x_mouse = x_temp_mouse;
            y_mouse = y_temp_mouse;
            if((x_mouse >= play.x && x_mouse <= play.x + play.w)
                && (y_mouse >= play.y && y_mouse <= play.y + play.h)){

                    play_again();
                }
        }
    }
}

bool va_cham(int _x, int _y)
{
    if(((temp_x < _x) && (temp_x + 30 > _x)) || ((_x <= temp_x) && (_x + 30 > temp_x)))
    {
        if(((temp_y < _y) && (30 + temp_y > _y)) || ((_y <= temp_y) && (_y + 30 > temp_y)))
        {
            //cout << "false !";
            return false;
        }
    }
    return true;
}

void paint_screen()
{
    cua_so.render(renderer_map,255,255,255,255);
    mini.render(renderer_map,255,255,255,255);
    column1.render(renderer_map,0,0,0,0);
    column2.render(renderer_map,0,0,0,0);
    column3.render(renderer_map,0,0,0,0);
    column4.render(renderer_map,0,0,0,0);
    column5.render(renderer_map,0,0,0,0);
    column6.render(renderer_map,0,0,0,0);
    column7.render(renderer_map,0,0,0,0);
    column8.render(renderer_map,0,0,0,0);
    column9.render(renderer_map,0,0,0,0);
    column10.render(renderer_map,0,0,0,0);
    column11.render(renderer_map,0,0,0,0);
    column12.render(renderer_map,0,0,0,0);
    column13.render(renderer_map,0,0,0,0);
    column14.render(renderer_map,0,0,0,0);
    column15.render(renderer_map,0,0,0,0);
    column16.render(renderer_map,0,0,0,0);
    column17.render(renderer_map,0,0,0,0);
    column18.render(renderer_map,0,0,0,0);
    column19.render(renderer_map,0,0,0,0);
    column20.render(renderer_map,0,0,0,0);
    column21.render(renderer_map,0,0,0,0);
    column22.render(renderer_map,0,0,0,0);
    column23.render(renderer_map,0,0,0,0);
    column24.render(renderer_map,0,0,0,0);
    column25.render(renderer_map,0,0,0,0);
    column26.render(renderer_map,0,0,0,0);
    column27.render(renderer_map,0,0,0,0);
    column28.render(renderer_map,0,0,0,0);

    load_picture();

    SDL_RenderPresent(renderer_map);

}

void map_arr_0_1(){
    column1.apply_array();
    column2.apply_array();
    column3.apply_array();
    column4.apply_array();
    column5.apply_array();
    column6.apply_array();
    column7.apply_array();
    column8.apply_array();
    column9.apply_array();
    column10.apply_array();
    column11.apply_array();
    column12.apply_array();
    column13.apply_array();
    column14.apply_array();
    column15.apply_array();
    column16.apply_array();
    column17.apply_array();
    column18.apply_array();
    column19.apply_array();
    column20.apply_array();
    column21.apply_array();
    column22.apply_array();
    column23.apply_array();
    column24.apply_array();
    column25.apply_array();
    column26.apply_array();
    column27.apply_array();
    column28.apply_array();

    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            if(i == 0 || i == 15){
                a1[i][j] = 1;
            }else if(j == 0 || j == 15){
                a1[i][j] = 1;
            }
        }
    }
}

void scan_arr(){
    for(int i = 0 ; i<16; i++){
        for(int j = 0; j<16; j++){

            if(((temp_x < j*30) && (temp_x + 30 > j*30)) || ((j*30 <= temp_x) && (j*30 + 30 > temp_x)))
            {
                if(((temp_y < i*30) && (30 + temp_y > i*30)) || ((i*30 <= temp_y) && (i*30 + 30 > temp_y)))
                {
                    if(a1[i][j] == 1){
                        dem++;
                    }
                }
            }

        }
    }

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

void destroy_all()
{
    SDL_DestroyRenderer(renderer_map);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(h_texture);
    SDL_DestroyTexture(h_box);
    SDL_DestroyTexture(h_drop_box);
    SDL_DestroyTexture(h_amazing_fire);
    SDL_DestroyTexture(h_bigger_fire);
    SDL_DestroyTexture(h_move_fire);
    SDL_DestroyTexture(h_winner);
    SDL_DestroyTexture(h_loser);
    SDL_Quit();
}

void play_again()
{
    temp_x = 30;
    temp_y = 30;
    x_temp_mouse = 0;
    y_temp_mouse = 0;
    x_mouse = 0;
    y_mouse = 0;
    is_running = true;
    run_game = true;
    dem = 0;
    or_0_1 = 0;
    a1[16][16] = {0};


    h_texture = nullptr;
    h_box = nullptr;
    h_drop_box = nullptr;
    h_amazing_fire = nullptr;
    h_bigger_fire = nullptr;
    h_move_fire = nullptr;
    h_winner = nullptr;
    h_loser = nullptr;
    h_esc = nullptr;
    h_play = nullptr;
    h_again = nullptr;
    //h_help = nullptr;



    x_source_rect = a;
    y_source_rect = a;

    x_drop_box = 480-a-a;
    y_drop_box = a;

    x_winner = 80;
    y_winner = 80;

    x_fire_1 = 6*a;
    y_fire_1 = a;

    x_fire_2 = 8*a;
    y_fire_2 = 7*a - 9;

    x_fire_3 =480-4*a;
    y_fire_3 =3*a;

    x_loser = 80;
    y_loser = 80;

    x_esc = 480;
    y_esc = 0;

    x_play = 480;
    y_play = 160;

    //x_help = 480;
    //y_help = 320;

    //x_again = 120;
    //y_again = 120;


}
