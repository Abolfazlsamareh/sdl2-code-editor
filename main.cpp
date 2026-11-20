#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <SDL2/SDL_ttf.h>
#include <algorithm>
#include <fstream>
#include <map>
#include <sstream>


using namespace std;

void fillTriangle(SDL_Renderer* renderer, int centerX,int centerY,int size){
    for (int i = -size; i <size; ++i) {
        SDL_RenderDrawLine(renderer,centerX,centerY+i,centerX+2*(size- abs(i)),centerY+i);
    }
}

int main(int arg,char* argv[]) {
    TTF_Init();

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        cerr << "SDL_Init Error: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("clion",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1200,
                                          800,
                                          SDL_WINDOW_SHOWN);

    TTF_Font* font = TTF_OpenFont("C:/Windows/Fonts/consola.ttf", 20);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }



    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Event event;
    SDL_Rect rect;
    SDL_Color colorword;


    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);

// line
    vector<char> character;
    vector <string> lines;
    vector<string> variable;
    char c;
    string Line = " ";
    lines.push_back(Line);

    int currentLine = 0;
    int cursorPos = 0;
// line
    int xlines=30;
    int ylines=10;
// mouse click
    int Xmousclick=0;
    int Ymousclick=0;
// line
    int numberline=0;
    bool shiftperes=false;
// scroll
    int YscrollOffset=0;
    int XscrollOffset=0;
// back grand
bool wightbackgrand=true;
bool blackbackgrand=false;
// save project
bool saveproject=false;
bool newproject=true;

// just render
bool justrender=true;

// run & stop
bool run=false;
bool stop=false;
// iostream & cmath
bool iostream=false;
bool cmath=false;


    bool q=true;

    while(q){

        while(SDL_PollEvent(&event)){
            // quit
            if(event.type==SDL_QUIT){
                q=false;
            }
            // scroll
            else if (event.type == SDL_MOUSEWHEEL) {
                if (event.wheel.y > 0) {
                    YscrollOffset -= 40; // up
                } else if (event.wheel.y < 0) {
                    YscrollOffset += 40; // down
                }

                justrender=true;
            }
            // clids
            else if(event.type== SDL_MOUSEBUTTONDOWN){
                if (event.button.button == SDL_BUTTON_LEFT) {
                    Xmousclick=event.button.x;
                    Ymousclick=event.button.y;

                }
            }
            // shift
            else if(event.type==SDL_KEYUP){
                if(event.key.keysym.sym==SDLK_LSHIFT || event.key.keysym.sym==SDLK_RSHIFT ){
                    shiftperes=false;
                }
            }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////// key down
            else if(event.type==SDL_KEYDOWN) {
                justrender=true;

                // inter
                if (event.key.keysym.sym == SDLK_RETURN) {
                    std::string remainder = lines[currentLine].substr(cursorPos);
                    lines[currentLine] = lines[currentLine].substr(0, cursorPos);
                    lines.insert(lines.begin() + currentLine + 1, remainder);
                    currentLine++;
                    cursorPos = 0;
                    newproject=false;
                }
                    // backspace
                else if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    if (cursorPos > 0) {
                        lines[currentLine].erase(cursorPos - 1, 1);
                        cursorPos--;
                    } else if (currentLine > 0) {

                        cursorPos = lines[currentLine - 1].size();
                        lines[currentLine - 1] += lines[currentLine].substr(0);
                        lines.erase(lines.begin() + currentLine);
                        currentLine--;
                    }
                }
                    // move makan nama
                else if (event.key.keysym.sym == SDLK_LEFT) {
                    if (cursorPos > 0) {
                        cursorPos--;
                    }
                    else if (currentLine > 0) {
                        currentLine--;
                        cursorPos = lines[currentLine].size();
                    }
                }
                else if (event.key.keysym.sym == SDLK_RIGHT) {
                    if (cursorPos < lines[currentLine].size()) {
                        cursorPos++;
                    } else if (currentLine < lines.size() - 1) {
                        currentLine++;
                        cursorPos = 0;
                    }
                }
                else if (event.key.keysym.sym == SDLK_UP) {
                    if (currentLine > 0) {
                        currentLine--;
                        cursorPos = std::min(static_cast<int>(cursorPos), static_cast<int>(lines[currentLine].size()));;
                    }
                }
                else if (event.key.keysym.sym == SDLK_DOWN) {
                    if (currentLine < lines.size() - 1) {
                        currentLine++;
                        cursorPos = std::min(static_cast<int>(cursorPos), static_cast<int>(lines[currentLine].size()));
                    }
                }

                    //character whit shift
                else if (event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT) {
                    shiftperes = true;
                }
                    // another key & space key
                else
                {
                    // sift character
                    if (shiftperes) {
                        switch (event.key.keysym.sym) {
                            case SDLK_1:
                                c= '!';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_2:
                                c = '@';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_3:
                                c= '#';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_4:
                                c= '$';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_5:
                                c= '%';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_6:
                                c= '^';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_7:
                                c= '&';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_8:
                                c= '*';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_9:
                                c= '(';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                c= ')';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                }
                                break;
                            case SDLK_0:
                                c= ')';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_MINUS:
                                c= '_';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_EQUALS:
                                c= '+';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_q:
                                c= 'Q';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_w:
                                c= 'W';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_e:
                                c= 'E';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_r:
                                c= 'R';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_t:
                                c= 'T';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_y:
                                c= 'Y';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_u:
                                c= 'U';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_i:
                                c= 'I';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_o:
                                c= 'O';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_p:
                                c= 'P';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_LEFTBRACKET:
                                c= '{';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                c= '}';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                }
                                break;
                            case SDLK_RIGHTBRACKET:
                                c= '}';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_BACKSLASH:
                                c= '|';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_a:
                                c= 'A';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_s:
                                c= 'S';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_d:
                                c= 'D';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_f:
                                c= 'F';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_g:
                                c= 'G';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_h:
                                c= 'H';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_j:
                                c= 'J';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_k:
                                c= 'K';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_l:
                                c= 'L';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_SEMICOLON:
                                c= ':';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_QUOTE:
                                c= '\"';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                c= '\"';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                }
                                break;
                            case SDLK_z:
                                c= 'Z';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_x:
                                c= 'X';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_c:
                                c= 'C';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_v:
                                c= 'V';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_b:
                                c= 'B';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_n:
                                c= 'N';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_m:
                                c= 'M';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_COMMA:
                                c= '<';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_PERIOD:
                                c= '>';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                            case SDLK_SLASH:
                                c= '?';
                                if (isprint(c)) {
                                    lines[currentLine].insert(cursorPos, 1, c);
                                    cursorPos++;
                                }
                                break;
                        }
                    }
                    // all character
                    else {
                        c = static_cast<char>(event.key.keysym.sym);
                        if (isprint(c)) {
                            lines[currentLine].insert(cursorPos, 1, c);
                            cursorPos++;
                            if(c=='\''){
                                lines[currentLine].insert(cursorPos, 1, c);
                            }
                            if(c=='['){
                                c=']';
                                lines[currentLine].insert(cursorPos, 1, c);
                            }
                        }
                    }
                }



            }
        }
//////////////////////////////////////////////////////////////////////////////////////////////////////////// mouse click
        // exit
        if(1177<Xmousclick && Xmousclick < 1200  && 2<Ymousclick && Ymousclick<25 ){
            break;
        }
        // wight back grand
        else if(200<Xmousclick && Xmousclick < 219  && 3<Ymousclick && Ymousclick<22 ){
            wightbackgrand=true;
            blackbackgrand=false;
            justrender=true;
            Xmousclick=0;
            Ymousclick=0;
        }
        // black back grand
        else if(174<Xmousclick && Xmousclick < 174+19  && 3<Ymousclick && Ymousclick<22 ){
            wightbackgrand=false;
            blackbackgrand=true;
            justrender=true;
            Xmousclick=0;
            Ymousclick=0;
        }
        // save project
        else if(897 < Xmousclick && Xmousclick < 897+135  && 0 < Ymousclick && Ymousclick < 25 ){
            saveproject=true;
            Xmousclick=0;
            Ymousclick=0;
        }
        // new project
        else if(1050 < Xmousclick && Xmousclick < 1050+125  && 0 < Ymousclick && Ymousclick < 25 ){
            newproject=true;
            justrender=true;
            currentLine = 0;
            cursorPos = 0;
            xlines=30;
            ylines=10;
            Xmousclick=0;
            Ymousclick=0;
            numberline=0;
            shiftperes=false;
            YscrollOffset=0;
            XscrollOffset=0;

            lines.clear();

            string Line = " ";
            lines.push_back(Line);


            Xmousclick=0;
            Ymousclick=0;
        }
        // run & stop
        else if(500 < Xmousclick && Xmousclick < 525  && 0 < Ymousclick && Ymousclick < 25){
            run=true;
        }
        else if(500 < Xmousclick && Xmousclick < 525  && 0 < Ymousclick && Ymousclick < 25){
            run=false;
        }


        if(justrender){
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// wight back grand
            if(wightbackgrand) {
                //    (clear)
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderClear(renderer);

                // makan nama
                int xcurpos = 0;
                if (currentLine==0){
                    if (cursorPos > 0) {
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        surface = TTF_RenderText_Solid(font, lines[currentLine].substr(0, cursorPos).c_str(),{0, 0, 0, 255});
                        SDL_RenderDrawLine(renderer, surface->w + 350 - XscrollOffset, currentLine * 30 + 380,surface->w + 350 - XscrollOffset, currentLine * 30 + 400);
                        xcurpos = surface->w;
                        SDL_FreeSurface(surface);

                        // x scroll
                        if (xcurpos > 500 ) {
                            XscrollOffset = xcurpos - 500;
                        }
                    }
                }
                else {
                    if (cursorPos > 0) {
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                        surface = TTF_RenderText_Solid(font, lines[currentLine].substr(0, cursorPos).c_str(),{0, 0, 0, 255});
                        SDL_RenderDrawLine(renderer, surface->w + 30 - XscrollOffset, currentLine * 30 - 5 -YscrollOffset ,surface->w + 30 - XscrollOffset, currentLine * 30 + 15 - YscrollOffset);
                        xcurpos = surface->w;
                        SDL_FreeSurface(surface);

                        // x scroll
                        if (xcurpos > 1170) {
                            XscrollOffset = xcurpos - 1170;
                        }
                    }
                }

                // manage scroll
                if (YscrollOffset < 0)YscrollOffset = 0;


                for (int k = 1; k < lines.size(); ++k) {

                    ylines = k * 30 - 5;
                    string line = lines[k];

////////////////////////////////////////////////////////////////////////////////////////////////////////// namayesh line

                    // word number
                    int wordnumber = 0;
                    // commend
                    bool commend = false;
                    int firstCommend = 0;
                    // Function or variable
                    bool maybeFunction = false;
                    bool yesFunction = false;
                    int firstNumberOfVariable = 0;
                    int lastNumberOfVariable = 0;

                    // string mark
                    int numberofmarkstring = 0;
                    int numberofmarkchar = 0;
                    // numbers
                    bool itsnumber = true;
                    int alamatbefornumber = 0;
                    int harfbefornumbe = 0;

                    string characterLine;
                    string word;

                    // parsing to character
                    for (const char &ch: line) {
                        character.push_back(ch);
                    }



/////////////////////////////////////////////////////////////////////////////////////////////////////////// graphic line
                    for (int i = 0; i < character.size(); ++i) {

                        word += character[i];


                        // number of mark string ( " )
                        if (character[i] == '\"') {
                            numberofmarkstring++;
                        }
                        // number of mark char ( ' )
                        if (character[i] == '\'') {
                            numberofmarkchar++;
                        }



                        // commend
                        if (character[i] == '/' && character[i - 1] == '/') {

                            characterLine = character[i - 1];
                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            xlines -= surface->w;
                            SDL_FreeSurface(surface);

                            colorword = {128, 128, 128, 255};
                            characterLine = character[i - 1];

                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);

                            firstCommend = i;
                            commend = true;
                            break;

                        }
                            // mark string ( " )
                        else if (numberofmarkstring % 2 == 1) {
                            colorword = {0, 100, 0, 255};
                            characterLine = character[i];

                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);
                        }
                            // mark char ( ' )
                        else if (numberofmarkchar % 2 == 1) {
                            colorword = {0, 100, 0, 255};
                            characterLine = character[i];

                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);
                        }
                            // class
                        else if (word == "class") {
                            colorword = {0, 51, 102, 255};

                            for (int j = 1; j <= 4; ++j) {
                                characterLine = character[i - j];
                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                xlines -= surface->w;
                                SDL_FreeSurface(surface);
                            }


                            surface = TTF_RenderText_Solid(font, word.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);

                        }
                            // if
                        else if (word == "if") {
                            colorword = {0, 51, 102, 255};

                            for (int j = 1; j <= 1; ++j) {
                                characterLine = character[i - j];
                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                xlines -= surface->w;
                                SDL_FreeSurface(surface);
                            }


                            surface = TTF_RenderText_Solid(font, word.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);

                        }
                            // while
                        else if (word == "while") {
                            colorword = {0, 51, 102, 255};

                            for (int j = 1; j <= 4; ++j) {
                                characterLine = character[i - j];
                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                xlines -= surface->w;
                                SDL_FreeSurface(surface);
                            }


                            surface = TTF_RenderText_Solid(font, word.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);

                        }
                            // #include
                        else if (word == "#include") {
                            colorword = {0, 139, 139, 255};

                            for (int j = 1; j <= 7; ++j) {
                                characterLine = character[i - j];
                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                xlines -= surface->w;
                                SDL_FreeSurface(surface);
                            }


                            surface = TTF_RenderText_Solid(font, word.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);

                        }
                            // int
                        else if (word == "int ") {
                            colorword = {0, 128, 128, 255};

                            for (int j = 1; j <= 3; ++j) {
                                characterLine = character[i - j];
                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                xlines -= surface->w;
                                SDL_FreeSurface(surface);
                            }


                            surface = TTF_RenderText_Solid(font, word.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;
                            maybeFunction = true;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);


                            firstNumberOfVariable = i;

                        }
                            // float
                        else if (word == "float ") {
                            colorword = {0, 128, 128, 255};

                            for (int j = 0; j <= 4; ++j) {
                                characterLine = character[i - j];
                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                xlines -= surface->w;
                                SDL_FreeSurface(surface);
                            }


                            surface = TTF_RenderText_Solid(font, word.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;
                            maybeFunction = true;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);


                            firstNumberOfVariable = i;
                        }
                            // double
                        else if (word == "double ") {
                            colorword = {0, 128, 128, 255};

                            for (int j = 1; j <= 6; ++j) {
                                characterLine = character[i - j];
                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                xlines -= surface->w;
                                SDL_FreeSurface(surface);
                            }


                            surface = TTF_RenderText_Solid(font, word.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;
                            maybeFunction = true;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);


                            firstNumberOfVariable = i;

                        }
                            // anotherWords
                        else {
                            colorword = {0, 0, 0, 255};
                            characterLine = character[i];

                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);
                        }


                        //// function & variable
                        if (character[i] == ';' || character[i] == '=' || character[i] == ')' || character[i] == '[' ||
                            character[i] == ']' || character[i] == '{' || character[i] == '}') {
                            maybeFunction = false;
                        }
                        // variable
                        if (maybeFunction) {

                            if (character[i] == '(') {
                                lastNumberOfVariable = i;
                                yesFunction = true;
                            }


                            characterLine = character[i];
                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            xlines -= surface->w;
                            SDL_FreeSurface(surface);

                            colorword = {139, 0, 0, 255};
                            characterLine = character[i];


                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);

                        }
                        // function
                        if (yesFunction) {
                            for (int j = firstNumberOfVariable; j <= lastNumberOfVariable; ++j) {
                                characterLine = character[j];
                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                xlines -= surface->w;
                                SDL_FreeSurface(surface);
                            }

                            for (int j = firstNumberOfVariable; j <= lastNumberOfVariable; ++j) {

                                colorword = {255, 140, 0, 255};
                                characterLine = character[j];

                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                texture = SDL_CreateTextureFromSurface(renderer, surface);
                                rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                                SDL_RenderCopy(renderer, texture, nullptr, &rect);

                                xlines += surface->w;

                                SDL_DestroyTexture(texture);
                                SDL_FreeSurface(surface);
                            }
                            yesFunction = false;
                            maybeFunction = false;
                        }


                        // numbers
                        if (character[i] == '0' || character[i] == '1' || character[i] == '2' || character[i] == '3' ||
                            character[i] == '4' || character[i] == '5' || character[i] == '6' || character[i] == '7' ||
                            character[i] == '8' || character[i] == '9') {

                            if (i == 0) {
                                characterLine = character[i];
                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                xlines -= surface->w;
                                SDL_FreeSurface(surface);


                                colorword = {128, 0, 128, 255};
                                characterLine = character[i];

                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                texture = SDL_CreateTextureFromSurface(renderer, surface);
                                rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                                SDL_RenderCopy(renderer, texture, nullptr, &rect);

                                xlines += surface->w;

                                SDL_DestroyTexture(texture);
                                SDL_FreeSurface(surface);
                            } else if (character[i - 1] == ' ' || character[i - 1] == '-' || character[i - 1] == '+' ||
                                       character[i - 1] == '=' || character[i - 1] == '*' || character[i - 1] == '/' ||
                                       character[i - 1] == '!' || character[i - 1] == '@' || character[i - 1] == '#' ||
                                       character[i - 1] == '%' || character[i - 1] == '^' || character[i - 1] == '&' ||
                                       character[i - 1] == '{' || character[i - 1] == '}' || character[i - 1] == '[' ||
                                       character[i - 1] == ']' || character[i - 1] == '\\' || character[i - 1] == '|' ||
                                       character[i - 1] == ':' || character[i - 1] == '?' || character[i - 1] == '<' ||
                                       character[i - 1] == '>' || character[i - 1] == '(' || character[i - 1] == ')') {
                                characterLine = character[i];
                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                xlines -= surface->w;
                                SDL_FreeSurface(surface);


                                colorword = {128, 0, 128, 255};
                                characterLine = character[i];

                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                texture = SDL_CreateTextureFromSurface(renderer, surface);
                                rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                                SDL_RenderCopy(renderer, texture, nullptr, &rect);

                                xlines += surface->w;

                                SDL_DestroyTexture(texture);
                                SDL_FreeSurface(surface);

                                alamatbefornumber = i - 1;
                            } else {
                                for (const char &ch: word) {
                                    if (ch != '0' && ch != '1' && ch != '2' && ch != '3' && ch != '4' && ch != '5' &&
                                        ch != '6' && ch != '7' && ch != '8' && ch != '9') {
                                        itsnumber = false;
                                        break;
                                    }
                                }

                                if (itsnumber) {
                                    characterLine = character[i];
                                    surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                    xlines -= surface->w;
                                    SDL_FreeSurface(surface);


                                    colorword = {128, 0, 128, 255};
                                    characterLine = character[i];

                                    surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                    texture = SDL_CreateTextureFromSurface(renderer, surface);
                                    rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                                    SDL_RenderCopy(renderer, texture, nullptr, &rect);

                                    xlines += surface->w;

                                    SDL_DestroyTexture(texture);
                                    SDL_FreeSurface(surface);
                                } else if (character[i - 1] != '0' && character[i - 1] != '1' &&
                                           character[i - 1] != '2' && character[i - 1] != '3' &&
                                           character[i - 1] != '4' &&
                                           character[i - 1] != '5' && character[i - 1] != '6' &&
                                           character[i - 1] != '7' && character[i - 1] != '8' &&
                                           character[i - 1] != '9') {
                                    harfbefornumbe = i - 1;
                                }

                                if (alamatbefornumber > harfbefornumbe) {
                                    characterLine = character[i];
                                    surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                    xlines -= surface->w;
                                    SDL_FreeSurface(surface);


                                    colorword = {128, 0, 128, 255};
                                    characterLine = character[i];

                                    surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                    texture = SDL_CreateTextureFromSurface(renderer, surface);
                                    rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                                    SDL_RenderCopy(renderer, texture, nullptr, &rect);

                                    xlines += surface->w;

                                    SDL_DestroyTexture(texture);
                                    SDL_FreeSurface(surface);
                                }
                                itsnumber = true;
                            }
                        }

                        // (") or (')
                        if (character[i] == '\'' || character[i] == '\"') {
                            characterLine = character[i];
                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            xlines -= surface->w;
                            SDL_FreeSurface(surface);


                            colorword = {0, 100, 0, 255};
                            characterLine = character[i];

                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);
                        }

                        // + or - or / or *
                        if (character[i] == '+' || character[i] == '-' || character[i] == '*' || character[i] == '/') {
                            characterLine = character[i];
                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            xlines -= surface->w;
                            SDL_FreeSurface(surface);

                            colorword = {128, 0, 0, 255};
                            characterLine = character[i];

                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);
                        }

                        // {} or [] or ()
                        if (character[i] == '{' || character[i] == '}' || character[i] == '(' || character[i] == ')' ||
                            character[i] == '[' || character[i] == ']') {
                            characterLine = character[i];
                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            xlines -= surface->w;
                            SDL_FreeSurface(surface);

                            colorword = {184, 134, 11, 255};
                            characterLine = character[i];

                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);
                        }


                        if (character[i] == ' ') {
                            wordnumber++;
                            word = "";
                        }

                    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////// command
                    if (commend) {

                        for (int i = firstCommend; i < character.size(); ++i) {
                            colorword = {128, 128, 128, 255};
                            characterLine = character[i];

                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);
                        }

                    }

//////////////////////////////////////////////////////////////////////////////////////////////// namayesh number of line
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    rect = {25, 25, 3, 775};
                    SDL_RenderFillRect(renderer, &rect);
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    rect = {0, 25, 25, 775};
                    SDL_RenderFillRect(renderer, &rect);
                    // number
                    for (int i = 0; i < lines.size(); ++i) {
                        string number = to_string(i + 1);
                        surface = TTF_RenderText_Solid(font, number.c_str(), {0, 0, 0, 255});
                        texture = SDL_CreateTextureFromSurface(renderer, surface);
                        rect = {0, i * 30 + 25 - YscrollOffset, 25, 30};
                        SDL_RenderCopy(renderer, texture, nullptr, &rect);

                        SDL_DestroyTexture(texture);
                        SDL_FreeSurface(surface);
                    }


                    character.clear();
                    xlines = 30;

                }


/////////////////////////////////////////////////////////////////////////////////////////////////////////////// graphics
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
                rect = {0, 0, 1200, 25};
                SDL_RenderFillRect(renderer, &rect);
                // exit
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                rect = {1175 + 2, 2, 23, 23};
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                for (int i = 1175 + 4; i < 1175 + 6; ++i) {
                    SDL_RenderDrawLine(renderer, i, 4, i + 19, 23);
                    SDL_RenderDrawLine(renderer, i + 19, 4, i, 23);
                }
                // new project
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                rect = {1047, 0, 125, 25};
                SDL_RenderDrawRect(renderer, &rect);

                surface = TTF_RenderText_Solid(font, "new project", {255, 255, 255, 255});
                texture = SDL_CreateTextureFromSurface(renderer, surface);
                rect = {1050, 2, surface->w, surface->h};
                SDL_RenderCopy(renderer, texture, nullptr, &rect);

                SDL_DestroyTexture(texture);
                SDL_FreeSurface(surface);

                // save project
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                rect = {897, 0, 135, 25};
                SDL_RenderDrawRect(renderer, &rect);

                surface = TTF_RenderText_Solid(font, "save project", {255, 255, 255, 255});
                texture = SDL_CreateTextureFromSurface(renderer, surface);
                rect = {900, 2, surface->w, surface->h};
                SDL_RenderCopy(renderer, texture, nullptr, &rect);

                SDL_DestroyTexture(texture);
                SDL_FreeSurface(surface);

                // run
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                rect = {500 + 2, 2, 23, 23};
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                fillTriangle(renderer, 500 + 4, 12, 8);

                // stop
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                rect = {530 + 2, 2, 23, 23};
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                rect = {530 + 6, 6, 15, 15};
                SDL_RenderFillRect(renderer, &rect);

                // back grand

                surface = TTF_RenderText_Solid(font, "back grand :", {255, 255, 255, 255});
                texture = SDL_CreateTextureFromSurface(renderer, surface);
                rect = {40, 2, surface->w, surface->h};
                SDL_RenderCopy(renderer, texture, nullptr, &rect);

                SDL_DestroyTexture(texture);
                SDL_FreeSurface(surface);
                // wight
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                rect = {200, 3, 19, 19};
                SDL_RenderFillRect(renderer, &rect);
                // black
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                rect = {174, 3, 19, 19};
                SDL_RenderFillRect(renderer, &rect);

//////////////////////////////////////////////////////////////////////////////////////////////////////////// new project
                if(newproject){
                    SDL_SetRenderDrawColor(renderer,0,0,0,255);
                    rect={300,250,600,300};
                    SDL_RenderDrawRect(renderer,&rect);

                    surface = TTF_RenderText_Solid(font, "project name :", {0, 0, 0, 0});
                    texture = SDL_CreateTextureFromSurface(renderer, surface);
                    rect = {450, 280, surface->w*2, surface->h*2};
                    SDL_RenderCopy(renderer, texture, nullptr, &rect);


                    surface = TTF_RenderText_Solid(font, lines[0].c_str(), {0, 0, 0, 0});
                    texture = SDL_CreateTextureFromSurface(renderer, surface);
                    rect = {350-XscrollOffset, 380, surface->w, surface->h};
                    SDL_RenderCopy(renderer, texture, nullptr, &rect);


                    SDL_DestroyTexture(texture);
                    SDL_FreeSurface(surface);


                }

            }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// black back grand
            if(blackbackgrand){

                //    (clear)
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                SDL_RenderClear(renderer);

                // makan nama
                int xcurpos = 0;
                if (cursorPos > 0) {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    surface = TTF_RenderText_Solid(font, lines[currentLine].substr(0, cursorPos).c_str(), {0, 0, 0, 255});
                    SDL_RenderDrawLine(renderer, surface->w + 30 - XscrollOffset, currentLine * 30 - 5,surface->w + 30 - XscrollOffset, currentLine * 30 + 15);
                    xcurpos = surface->w;
                    SDL_FreeSurface(surface);

                    // x scroll
                    if (xcurpos > 1170) {
                        XscrollOffset = xcurpos - 1170;
                    }
                }
                // manage scroll
                if (YscrollOffset < 0)YscrollOffset = 0;


                for (int k = 1; k < lines.size(); ++k) {

                    ylines = k * 30 - 5;
                    string line = lines[k];

////////////////////////////////////////////////////////////////////////////////////////////////////////////// variables

                    // word number
                    int wordnumber = 0;
                    // commend
                    bool commend = false;
                    int firstCommend = 0;
                    // Function or variable
                    bool maybeFunction = false;
                    bool yesFunction = false;
                    int firstNumberOfVariable = 0;
                    int lastNumberOfVariable = 0;

                    // string mark
                    int numberofmarkstring = 0;
                    int numberofmarkchar = 0;
                    // numbers
                    bool itsnumber = true;
                    int alamatbefornumber = 0;
                    int harfbefornumbe = 0;

                    string characterLine;
                    string word;

                    // parsing to character
                    for (const char &ch: line) {
                        character.push_back(ch);
                    }



/////////////////////////////////////////////////////////////////////////////////////////////////////////// graphic line
                    for (int i = 0; i < character.size(); ++i) {

                        word += character[i];


                        // number of mark string ( " )
                        if (character[i] == '\"') {
                            numberofmarkstring++;
                        }
                        // number of mark char ( ' )
                        if (character[i] == '\'') {
                            numberofmarkchar++;
                        }



                        // commend
                        if (character[i] == '/' && character[i - 1] == '/') {

                            characterLine = character[i - 1];
                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            xlines -= surface->w;
                            SDL_FreeSurface(surface);

                            colorword = {92, 99, 112, 255};
                            characterLine = character[i - 1];

                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);

                            firstCommend = i;
                            commend = true;
                            break;

                        }
                            // mark string ( " )
                        else if (numberofmarkstring % 2 == 1) {
                            colorword = {152, 195, 121, 255};
                            characterLine = character[i];

                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);
                        }
                            // mark char ( ' )
                        else if (numberofmarkchar % 2 == 1) {
                            colorword = {152, 195, 121, 255};
                            characterLine = character[i];

                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);
                        }
                            // class
                        else if (word == "class") {
                            colorword = {198, 120, 221, 255};

                            for (int j = 1; j <= 4; ++j) {
                                characterLine = character[i - j];
                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                xlines -= surface->w;
                                SDL_FreeSurface(surface);
                            }


                            surface = TTF_RenderText_Solid(font, word.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);

                        }
                            // if
                        else if (word == "if") {
                            colorword = {198, 120, 221, 255};

                            for (int j = 1; j <= 1; ++j) {
                                characterLine = character[i - j];
                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                xlines -= surface->w;
                                SDL_FreeSurface(surface);
                            }


                            surface = TTF_RenderText_Solid(font, word.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);

                        }
                            // while
                        else if (word == "while") {
                            colorword = {198, 120, 221, 255};

                            for (int j = 1; j <= 4; ++j) {
                                characterLine = character[i - j];
                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                xlines -= surface->w;
                                SDL_FreeSurface(surface);
                            }


                            surface = TTF_RenderText_Solid(font, word.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);

                        }
                            // #include
                        else if (word == "#include") {
                            colorword = {86, 182, 194, 255};

                            for (int j = 1; j <= 7; ++j) {
                                characterLine = character[i - j];
                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                xlines -= surface->w;
                                SDL_FreeSurface(surface);
                            }


                            surface = TTF_RenderText_Solid(font, word.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);

                        }
                            // int
                        else if (word == "int ") {
                            colorword = {224, 108, 117, 255};

                            for (int j = 1; j <= 3; ++j) {
                                characterLine = character[i - j];
                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                xlines -= surface->w;
                                SDL_FreeSurface(surface);
                            }


                            surface = TTF_RenderText_Solid(font, word.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;
                            maybeFunction = true;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);


                            firstNumberOfVariable = i;

                        }
                            // float
                        else if (word == "float ") {
                            colorword = {224, 108, 117, 255};

                            for (int j = 0; j <= 4; ++j) {
                                characterLine = character[i - j];
                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                xlines -= surface->w;
                                SDL_FreeSurface(surface);
                            }


                            surface = TTF_RenderText_Solid(font, word.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;
                            maybeFunction = true;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);


                            firstNumberOfVariable = i;
                        }
                            // double
                        else if (word == "double ") {
                            colorword = {224, 108, 117, 255};

                            for (int j = 1; j <= 6; ++j) {
                                characterLine = character[i - j];
                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                xlines -= surface->w;
                                SDL_FreeSurface(surface);
                            }


                            surface = TTF_RenderText_Solid(font, word.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;
                            maybeFunction = true;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);


                            firstNumberOfVariable = i;

                        }
                            // anotherWords
                        else {
                            colorword = {255, 255, 255, 255};
                            characterLine = character[i];

                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);
                        }


                        //// function & variable
                        if (character[i] == ';' || character[i] == '=' || character[i] == ')' || character[i] == '[' ||
                            character[i] == ']' || character[i] == '{' || character[i] == '}') {
                            maybeFunction = false;
                        }
                        // variable
                        if (maybeFunction) {

                            if (character[i] == '(') {
                                lastNumberOfVariable = i;
                                yesFunction = true;
                            }


                            characterLine = character[i];
                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            xlines -= surface->w;
                            SDL_FreeSurface(surface);

                            colorword = {229, 192, 123, 255};
                            characterLine = character[i];


                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);

                        }
                        // function
                        if (yesFunction) {
                            for (int j = firstNumberOfVariable; j <= lastNumberOfVariable; ++j) {
                                characterLine = character[j];
                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                xlines -= surface->w;
                                SDL_FreeSurface(surface);
                            }

                            for (int j = firstNumberOfVariable; j <= lastNumberOfVariable; ++j) {

                                colorword = {97, 175, 254, 255};
                                characterLine = character[j];

                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                texture = SDL_CreateTextureFromSurface(renderer, surface);
                                rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                                SDL_RenderCopy(renderer, texture, nullptr, &rect);

                                xlines += surface->w;

                                SDL_DestroyTexture(texture);
                                SDL_FreeSurface(surface);
                            }
                            yesFunction = false;
                            maybeFunction = false;
                        }


                        // numbers
                        if (character[i] == '0' || character[i] == '1' || character[i] == '2' || character[i] == '3' ||
                            character[i] == '4' || character[i] == '5' || character[i] == '6' || character[i] == '7' ||
                            character[i] == '8' || character[i] == '9') {

                            if (i == 0) {
                                characterLine = character[i];
                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                xlines -= surface->w;
                                SDL_FreeSurface(surface);


                                colorword = {209, 154, 102, 255};
                                characterLine = character[i];

                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                texture = SDL_CreateTextureFromSurface(renderer, surface);
                                rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                                SDL_RenderCopy(renderer, texture, nullptr, &rect);

                                xlines += surface->w;

                                SDL_DestroyTexture(texture);
                                SDL_FreeSurface(surface);
                            } else if (character[i - 1] == ' ' || character[i - 1] == '-' || character[i - 1] == '+' ||
                                       character[i - 1] == '=' || character[i - 1] == '*' || character[i - 1] == '/' ||
                                       character[i - 1] == '!' || character[i - 1] == '@' || character[i - 1] == '#' ||
                                       character[i - 1] == '%' || character[i - 1] == '^' || character[i - 1] == '&' ||
                                       character[i - 1] == '{' || character[i - 1] == '}' || character[i - 1] == '[' ||
                                       character[i - 1] == ']' || character[i - 1] == '\\' || character[i - 1] == '|' ||
                                       character[i - 1] == ':' || character[i - 1] == '?' || character[i - 1] == '<' ||
                                       character[i - 1] == '>' || character[i - 1] == '(' || character[i - 1] == ')') {
                                characterLine = character[i];
                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                xlines -= surface->w;
                                SDL_FreeSurface(surface);


                                colorword = {209, 154, 102, 255};
                                characterLine = character[i];

                                surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                texture = SDL_CreateTextureFromSurface(renderer, surface);
                                rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                                SDL_RenderCopy(renderer, texture, nullptr, &rect);

                                xlines += surface->w;

                                SDL_DestroyTexture(texture);
                                SDL_FreeSurface(surface);

                                alamatbefornumber = i - 1;
                            } else {
                                for (const char &ch: word) {
                                    if (ch != '0' && ch != '1' && ch != '2' && ch != '3' && ch != '4' && ch != '5' &&
                                        ch != '6' && ch != '7' && ch != '8' && ch != '9') {
                                        itsnumber = false;
                                        break;
                                    }
                                }

                                if (itsnumber) {
                                    characterLine = character[i];
                                    surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                    xlines -= surface->w;
                                    SDL_FreeSurface(surface);


                                    colorword = {209, 154, 102, 255};
                                    characterLine = character[i];

                                    surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                    texture = SDL_CreateTextureFromSurface(renderer, surface);
                                    rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                                    SDL_RenderCopy(renderer, texture, nullptr, &rect);

                                    xlines += surface->w;

                                    SDL_DestroyTexture(texture);
                                    SDL_FreeSurface(surface);
                                }
                                else if (character[i - 1] != '0' && character[i - 1] != '1' &&
                                         character[i - 1] != '2' && character[i - 1] != '3' &&
                                         character[i - 1] != '4' &&
                                         character[i - 1] != '5' && character[i - 1] != '6' &&
                                         character[i - 1] != '7' && character[i - 1] != '8' &&
                                         character[i - 1] != '9') {
                                    harfbefornumbe = i - 1;
                                }

                                if (alamatbefornumber > harfbefornumbe) {
                                    characterLine = character[i];
                                    surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                    xlines -= surface->w;
                                    SDL_FreeSurface(surface);


                                    colorword = {209, 154, 102, 255};
                                    characterLine = character[i];

                                    surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                                    texture = SDL_CreateTextureFromSurface(renderer, surface);
                                    rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                                    SDL_RenderCopy(renderer, texture, nullptr, &rect);

                                    xlines += surface->w;

                                    SDL_DestroyTexture(texture);
                                    SDL_FreeSurface(surface);
                                }
                                itsnumber = true;
                            }
                        }

                        // (") or (')
                        if (character[i] == '\'' || character[i] == '\"') {
                            characterLine = character[i];
                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            xlines -= surface->w;
                            SDL_FreeSurface(surface);


                            colorword = {152, 195, 121, 255};
                            characterLine = character[i];

                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);
                        }

                        // + or - or / or *
                        if (character[i] == '+' || character[i] == '-' || character[i] == '*' || character[i] == '/') {
                            characterLine = character[i];
                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            xlines -= surface->w;
                            SDL_FreeSurface(surface);

                            colorword = {213, 94, 0, 255};
                            characterLine = character[i];

                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);
                        }

                        // {} or [] or ()
                        if (character[i] == '{' || character[i] == '}' || character[i] == '(' || character[i] == ')' ||
                            character[i] == '[' || character[i] == ']') {
                            characterLine = character[i];
                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            xlines -= surface->w;
                            SDL_FreeSurface(surface);

                            colorword = {171, 178, 191, 255};
                            characterLine = character[i];

                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);
                        }


                        if (character[i] == ' ') {
                            wordnumber++;
                            word = "";
                        }

                    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////// command
                    if (commend) {

                        for (int i = firstCommend; i < character.size(); ++i) {
                            colorword = {92, 99, 112, 255};
                            characterLine = character[i];

                            surface = TTF_RenderText_Solid(font, characterLine.c_str(), colorword);
                            texture = SDL_CreateTextureFromSurface(renderer, surface);
                            rect = {xlines - XscrollOffset, ylines - YscrollOffset, surface->w, surface->h};
                            SDL_RenderCopy(renderer, texture, nullptr, &rect);

                            xlines += surface->w;

                            SDL_DestroyTexture(texture);
                            SDL_FreeSurface(surface);
                        }

                    }

                    ////////// namayesh number of line
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    rect = {25, 25, 3, 775};
                    SDL_RenderFillRect(renderer, &rect);
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    rect = {0, 25, 25, 775};
                    SDL_RenderFillRect(renderer, &rect);
                    // number
                    for (int i = 0; i <= currentLine; ++i) {
                        string number = to_string(i + 1);
                        surface = TTF_RenderText_Solid(font, number.c_str(), {255, 255, 255, 255});
                        texture = SDL_CreateTextureFromSurface(renderer, surface);
                        rect = {0, i * 30 + 25 - YscrollOffset, 25, 30};
                        SDL_RenderCopy(renderer, texture, nullptr, &rect);

                        SDL_DestroyTexture(texture);
                        SDL_FreeSurface(surface);
                    }

                    character.clear();
                    xlines = 30;

                }


/////////////////////////////////////////////////////////////////////////////////////////////////////////////// graphics
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
                rect = {0, 0, 1200, 25};
                SDL_RenderFillRect(renderer, &rect);
                // exit
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                rect = {1175 + 2, 2, 23, 23};
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                for (int i = 1175 + 4; i < 1175 + 6; ++i) {
                    SDL_RenderDrawLine(renderer, i, 4, i + 19, 23);
                    SDL_RenderDrawLine(renderer, i + 19, 4, i, 23);
                }
                // new project
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                rect = {1047, 0, 125, 25};
                SDL_RenderDrawRect(renderer, &rect);

                surface = TTF_RenderText_Solid(font, "new project", {0, 0, 0, 255});
                texture = SDL_CreateTextureFromSurface(renderer, surface);
                rect = {1050, 2, surface->w, surface->h};
                SDL_RenderCopy(renderer, texture, nullptr, &rect);

                SDL_DestroyTexture(texture);
                SDL_FreeSurface(surface);

                // save project
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                rect = {897, 0, 135, 25};
                SDL_RenderDrawRect(renderer, &rect);

                surface = TTF_RenderText_Solid(font, "save project", {0, 0, 0, 0});
                texture = SDL_CreateTextureFromSurface(renderer, surface);
                rect = {900, 2, surface->w, surface->h};
                SDL_RenderCopy(renderer, texture, nullptr, &rect);

                SDL_DestroyTexture(texture);
                SDL_FreeSurface(surface);

                // run
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                rect = {500 + 2, 2, 23, 23};
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                fillTriangle(renderer, 500 + 4, 12, 8);

                // stop
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                rect = {530 + 2, 2, 23, 23};
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                rect = {530 + 6, 6, 15, 15};
                SDL_RenderFillRect(renderer, &rect);

                // back grand

                surface = TTF_RenderText_Solid(font, "back grand :", {0, 0, 0, 0});
                texture = SDL_CreateTextureFromSurface(renderer, surface);
                rect = {40, 2, surface->w, surface->h};
                SDL_RenderCopy(renderer, texture, nullptr, &rect);

                SDL_DestroyTexture(texture);
                SDL_FreeSurface(surface);
                // wight
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                rect = {200, 3, 19, 19};
                SDL_RenderFillRect(renderer, &rect);
                // black
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                rect = {174, 3, 19, 19};
                SDL_RenderFillRect(renderer, &rect);

                if(newproject){
                    SDL_SetRenderDrawColor(renderer,255,255,255,255);
                    rect={300,250,600,300};
                    SDL_RenderDrawRect(renderer,&rect);

                    surface = TTF_RenderText_Solid(font, "project name :", {255, 255, 255, 255});
                    texture = SDL_CreateTextureFromSurface(renderer, surface);
                    rect = {450, 280, surface->w*2, surface->h*2};
                    SDL_RenderCopy(renderer, texture, nullptr, &rect);


                    surface = TTF_RenderText_Solid(font, lines[0].c_str(), {255, 255, 255, 255});
                    texture = SDL_CreateTextureFromSurface(renderer, surface);
                    rect = {350-XscrollOffset, 380, surface->w, surface->h};
                    SDL_RenderCopy(renderer, texture, nullptr, &rect);


                    SDL_DestroyTexture(texture);
                    SDL_FreeSurface(surface);


                }

            }

            justrender=false;
        }

/////////////////////////////////////////////////////////////////////////////////////////////////////////// save project
        if(saveproject){


            string filepath="C:/Users/F/CLionProjects/progect/projects/";
            filepath+=lines[0];
            ofstream file(filepath);
            if (!file) {
                std::cerr << "error open file" << std::endl;
                return 1;
            }

            {
                for (int i = 1; i <lines.size() ; ++i) {
                    file<<lines[i]<<endl;
                }
            }
            file.close();



            SDL_SetRenderDrawColor(renderer,128,128,128,255);
            rect={300,250,600,300};
            SDL_RenderFillRect(renderer,&rect);

            surface = TTF_RenderText_Solid(font, "save successfully", {0, 255, 0, 0});
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            rect = {410, 380, surface->w*2, surface->h*2};
            SDL_RenderCopy(renderer, texture, nullptr, &rect);

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface);

            saveproject=false;
        }

        if (run){





        }





        SDL_RenderPresent(renderer);
    }

    for (int i = 0; i < lines.size(); ++i) {
        cout<<lines[i]<<endl;
    }

    for (int i = 0; i < variable.size(); ++i) {
        cout<<variable[i]<<endl;
    }




    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
