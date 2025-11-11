#include <SDL.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define CELL_SIZE 30

typedef struct {
    int x, y;
    Uint32 color;
} Block;

typedef struct {
    Block* blocks;
    int count;
    int capacity;
} Tetromino;

// 初始化方块
void initTetromino(Tetromino* t, int capacity) {
    t->blocks = malloc(sizeof(Block) * capacity);
    t->count = 0;
    t->capacity = capacity;
}

// 添加方块
void addBlock(Tetromino* t, int x, int y, Uint32 color) {
    if (t->count < t->capacity) {
        t->blocks[t->count].x = x;
        t->blocks[t->count].y = y;
        t->blocks[t->count].color = color;
        t->count++;
    }
}

// 创建L形方块
void createLTetromino(Tetromino* t, Uint32 color) {
    t->count = 0;
    addBlock(t, 0, 0, color);
    addBlock(t, 0, 1, color);
    addBlock(t, 0, 2, color);
    addBlock(t, 1, 2, color);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("俄罗斯方块",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        BOARD_WIDTH * CELL_SIZE, BOARD_HEIGHT * CELL_SIZE,
        SDL_WINDOW_SHOWN);
    SDL_Surface* screen = SDL_GetWindowSurface(window);

    srand(time(NULL));

    // 游戏板
    Uint32 board[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };

    // 当前方块
    Tetromino current;
    initTetromino(&current, 4);
    createLTetromino(&current, SDL_MapRGB(screen->format, 255, 0, 0));

    int quit = 0;
    SDL_Event e;
    Uint32 lastMove = SDL_GetTicks();

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = 1;
            if (e.type == SDL_KEYDOWN) {
                // 简单的移动控制
            }
        }

        // 自动下落
        if (SDL_GetTicks() - lastMove > 500) {
            // 移动逻辑...
            lastMove = SDL_GetTicks();
        }

        // 绘制
        SDL_FillRect(screen, NULL, 0); // 黑色背景

        // 绘制游戏板
        SDL_Rect cellRect = { 0, 0, CELL_SIZE - 1, CELL_SIZE - 1 };
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            for (int x = 0; x < BOARD_WIDTH; x++) {
                if (board[y][x] != 0) {
                    cellRect.x = x * CELL_SIZE;
                    cellRect.y = y * CELL_SIZE;
                    SDL_FillRect(screen, &cellRect, board[y][x]);
                }
            }
        }

        // 绘制当前方块
        for (int i = 0; i < current.count; i++) {
            cellRect.x = current.blocks[i].x * CELL_SIZE;
            cellRect.y = current.blocks[i].y * CELL_SIZE;
            SDL_FillRect(screen, &cellRect, current.blocks[i].color);
        }

        SDL_UpdateWindowSurface(window);
        SDL_Delay(16);
    }

    free(current.blocks);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}