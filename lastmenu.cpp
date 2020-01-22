Obj playagain_lm,highscore_lm,firstmenu_lm, saveinfo ;
SDL_Renderer* ren_lm;
SDL_Surface* surf_lm ;
SDL_Texture* text;
SDL_Rect dest;
SDL_Color foreground = { 0, 0, 0 };
bool running_lm = true ;
void input_lm() {
	static const unsigned char* keys = SDL_GetKeyboardState( NULL );
  while (SDL_PollEvent(&e) != 0) {
    SDL_GetMouseState(&mousex,&mousey) ;
    switch(e.type){
      case SDL_QUIT:
      running_lm = false;
      windowloop = false;
      SDL_Quit();
      return;
      break;
      case SDL_KEYDOWN:
      if(e.key.keysym.sym == SDLK_ESCAPE) {
        running_lm = false;
        windowloop = false;
        SDL_Quit();
        return;
      }
			if (e.key.keysym.sym == SDLK_BACKSPACE && playername.size()) {
				playername.pop_back();
			}
      break;
    case SDL_MOUSEBUTTONDOWN:
      if ((mousex>=playagain_lm.dest.x)&&(mousex<=playagain_lm.dest.x+playagain_lm.dest.w)&&(mousey>=playagain_lm.dest.y)&&(mousey<=playagain_lm.dest.y+playagain_lm.dest.h)) {
        status = 2;
        SDL_DestroyRenderer(ren_lm);
        running_lm = false;
        SDL_StopTextInput();
        return;
      }
      if ((mousex>=highscore_lm.dest.x)&&(mousex<=highscore_lm.dest.x+highscore_lm.dest.w)&&(mousey>=highscore_lm.dest.y)&&(mousey<=highscore_lm.dest.y+highscore_lm.dest.h)) {
      status = 5;
			SDL_DestroyRenderer(ren_lm);
			running_lm = false;
			SDL_StopTextInput();
			return;
      }
			if ((mousex>=saveinfo.dest.x)&&(mousex<=saveinfo.dest.x+saveinfo.dest.w)&&(mousey>=saveinfo.dest.y)&&(mousey<=saveinfo.dest.y+saveinfo.dest.h)) {
				if(playername.size() == 0){
					if(savescore(playerscore,"NONAME")){
						cout<<"Score Saved";
					}else{
						cout<<"SCORE SAVING ERROR";
					}
				}else{
					if(savescore(playerscore,playername)){
						cout<<"SCORE AND NAME SAVED";
					}else{
						cout<<"ERROR SAVING NAME AND SCORE OF PLAYER";
					}
				}
      }
      if ((mousex>=firstmenu_lm.dest.x)&&(mousex<=firstmenu_lm.dest.x+firstmenu_lm.dest.w)&&(mousey>=firstmenu_lm.dest.y)&&(mousey<=firstmenu_lm.dest.y+firstmenu_lm.dest.h)) {
        status = 0;
        SDL_DestroyRenderer(ren_lm);
        running_lm = false;
        SDL_StopTextInput();
        return;
}
  break;
  case SDL_TEXTINPUT:
  playername+=e.text.text;
	cout<<"x1";
  break;
}
}
if ( playername.size() ) {
	SDL_Surface* text_surf = TTF_RenderText_Solid(font, playername.c_str(), foreground);
	text = SDL_CreateTextureFromSurface(ren_lm, text_surf);

	dest.x = 200 - (text_surf->w / 2.0f);
	dest.y = 100;
	dest.w = text_surf->w;
	dest.h = text_surf->h;
	SDL_RenderCopy(ren_lm, text, NULL, &dest);

	SDL_DestroyTexture(text);
	SDL_FreeSurface(text_surf);
}

// Update window
SDL_RenderPresent( ren_lm );
}
void lastmenu(){
	font = TTF_OpenFont("data/GTA.ttf", 72);
	if ( !font ) {
		cout << "Error loading font: " << TTF_GetError() << endl;
		return;
	}
	SDL_StartTextInput();
  running_lm = true ;
  ren_lm = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
  SDL_Rect rect_fm ;
  rect_fm.x = 0 ;
  rect_fm.y = 0 ;
  rect_fm.w = 350 ;
  rect_fm.h = 600 ;
  // playagain_lm
  playagain_lm.setDest(250,380,70,70);
  playagain_lm.setSource(0,0,1500,1500);
  playagain_lm.setImage("data/play.png",ren_lm) ;
	//savaeinfo
	saveinfo.setDest(250,250,70,70);
  saveinfo.setSource(0,0,1500,1500);
  saveinfo.setImage("data/play.png",ren_lm) ;
  // firstmenu_lm
  highscore_lm.setDest(180,490,70,70);
  highscore_lm.setSource(0,0,1500,1500);
  highscore_lm.setImage("data/play.png",ren_lm) ;
  // highscore_lms
  firstmenu_lm.setDest(20,415,70,70);
  firstmenu_lm.setSource(0,0,1500,1500);
  firstmenu_lm.setImage("data/play.png",ren_lm) ;

  float hei = 0 ;
  bool down = true ;
  float sh = 2.2 ;
  float pos = 0 ;
  float rot = 0 ;
  while (running_lm) {
    int framecount = 0 ;
    int lastframe = SDL_GetTicks();
    static int lasttime = 0 ;
    if (lastframe >= lasttime+1000) {
      lasttime = lastframe ;
      framecount = 0 ;
    }
    SDL_SetRenderDrawColor(ren_lm,255-(hei/2.7),148-(hei/2.7),194-(hei/2.7),255);
    SDL_RenderFillRect(ren_lm,&rect_fm);

    SDL_RenderCopyEx(ren_lm,playagain_lm.tex,&playagain_lm.src,&playagain_lm.dest,0,NULL,SDL_FLIP_NONE);
    SDL_RenderCopyEx(ren_lm,highscore_lm.tex,&highscore_lm.src,&highscore_lm.dest,0+rot,NULL,SDL_FLIP_NONE);
    SDL_RenderCopyEx(ren_lm,firstmenu_lm.tex,&firstmenu_lm.src,&firstmenu_lm.dest,0+rot,NULL,SDL_FLIP_NONE);
		SDL_RenderCopyEx(ren_lm,saveinfo.tex,&saveinfo.src,&saveinfo.dest,0+rot,NULL,SDL_FLIP_NONE);

    rot += 2 ;

    framecount++ ;
    int timerFPS = SDL_GetTicks() - lastframe ;
    if (timerFPS < (1000/10)) {
      SDL_Delay((1000/10)-timerFPS);
    }

    SDL_RenderPresent(ren_lm);
    input_lm();
  }
}
