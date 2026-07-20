#include "tiledmap.h"
#include "global.h"

TiledMap::TiledMap(): Entity(EntityRole::CANVAS) {
    for(int r = 0; r < WINDOW_ROWS; r++) {
        for(int c = 0; c < WINDOW_COLS; c++) {
            grid[r][c] = None;
        }
    }
    sprite.add_render_handler("render_tiled_map", [this] (Viewport* vp, SDL_Renderer* gRenderer) {
        this->load_media(gRenderer);
        SDL_Rect src, dest;
        double x, y;
        for(int r=0; r<WINDOW_ROWS; r++) {
            for(int c=0; c<WINDOW_COLS; c++) {
                x = 64*c;
                y = 64*r;
                auto coord = vp->translate({x,y});
                switch(grid[r][c]) {
                    case None:
                        break;
                    case CobbledBlock:
                        src = {0,0,UNIT,UNIT};
                        dest = {0,0,UNIT, UNIT};
                        dest.x = coord.x;
                        dest.y = coord.y;
                        SDL_RenderCopy(gRenderer, this->cblock, &src, &dest);
                        break;
                    case Ladder:
                        dest = {0,0,UNIT, UNIT};
                        dest.x = coord.x;
                        dest.y = coord.y;
                        src = {0,0,107,107};
                        SDL_RenderCopy(gRenderer, this->ladder, &src, &dest);
                        break;
                    case Building:
                        src = {0,0,579,447};
                        dest = {0,0,2*UNIT,2*UNIT};
                        dest.x = coord.x;
                        dest.y = coord.y;
                        SDL_RenderCopy(gRenderer, this->building, nullptr, &dest);
                        break;
                }
                
            }
            
        }
        return true;
    });
}

void TiledMap::load_media(SDL_Renderer* gRenderer) {
    if(loaded) return;
    if(cblock == nullptr) {
        std::string path = "/Users/donaldsontan/Projects/mtd215/mtd215/assets/cobbled_block.png";
        SDL_Surface* s = IMG_Load(path.c_str());
        if(s == nullptr) throw SDL_Cannot_Load_Media(path, SDL_GetError());
        cblock = SDL_CreateTextureFromSurface(gRenderer, s);
        SDL_FreeSurface(s);
    }
    if(ladder == nullptr) {
        std::string path = "/Users/donaldsontan/Projects/mtd215/mtd215/assets/ladder.png";
        SDL_Surface* s = IMG_Load(path.c_str());
        if(s == nullptr) throw SDL_Cannot_Load_Media(path, SDL_GetError());
        ladder = SDL_CreateTextureFromSurface(gRenderer, s);
        SDL_FreeSurface(s);
    }
    if(building == nullptr) {
        std::string path = "/Users/donaldsontan/Projects/mtd215/mtd215/assets/building.png";
        SDL_Surface* s = IMG_Load(path.c_str());
        if(s == nullptr) throw SDL_Cannot_Load_Media(path, SDL_GetError());
        building = SDL_CreateTextureFromSurface(gRenderer, s);
        SDL_FreeSurface(s);
    }
    loaded = true;
    std::cout << "loaded";
}

TiledMap::~TiledMap() {}

DemoMap::DemoMap(): TiledMap() {
    int mygrid[12][24] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,1,1,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},
        {0,2,1,1,1,1,1,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},
        {0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},
        {0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,1,1,1,0},
        {0,2,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
        {0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };
    for(int r=0; r<12;r++) {
        for(int c=0; c<24; c++) {
            switch(mygrid[r][c]) {
            case 0:
                grid[r][c] = Block::None;
                break;
            case 1:
                grid[r][c] = Block::CobbledBlock;
                break;
            case 2:
                grid[r][c] = Block::Ladder;
                break;
            case 3:
                grid[r][c] = Block::Building;
                break;
            }
        }
    }
}

DemoMap::~DemoMap() {};
