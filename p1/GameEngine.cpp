#include "headers/Game.h"
#include "headers/Object.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "firstmenu.cpp"
#include "settingsmenu.cpp"
int status = 0;

using namespace std;


int main(int argc, char const *argv[]) {
  bool windowloop = true;
  //while(windowloop){
  Loop:switch(status){
    case 0: firstmenu(); status = 1; goto Loop; break;
    case 1: settingsmenu(); break;
//  }
}
//SDL_CreateWindowAndRenderer(350,600,0,&win,&ren_fm);
  return 0;
}