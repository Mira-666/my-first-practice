#include <SDL.h>
#undef main

#define W 1200
#define H 800
int main() {
	//初始化
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		SDL_Log("Init failed: %s", SDL_GetError());
		return -1;
	}
	//创建窗口
	SDL_Window* win = SDL_CreateWindow("Hello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, SDL_WINDOW_RESIZABLE);
	if (NULL == win)
	{
		SDL_Log("SDL_CreateWindow failed: %s ", SDL_GetError());
		return -1;
	}


	//窗口上绘制一个矩形
	//获取与窗口相关的Surface
	SDL_Surface* surf = SDL_GetWindowSurface(win);
	if (NULL == surf)
	{
		SDL_Log("SDL_GetWindosSurface failed: %s ", SDL_GetError());
		return -1;
	}
	//定义一个区域
	SDL_Rect rects[] = { {333,111,50,50},
						{100,100,30,60},
						{500,400,50,20} };

	//在Surface上进行绘制
	SDL_FillRect(surf, &rects[],int 1, 0xff0000);//颜色分量用十六进制
	//SDL_FillRect(surf, &rect, SDL_MapRGB(surf->format, 255, 0, 0)); //颜色分量用十进制分量0-255)
	//将绘制的内容更新到屏幕上
	SDL_UpdateWindowSurface(win);


	//暂停一段时间-->事件监听与响应
	//SDL_Delay(30000);
	//背景黑色因为死循环
	SDL_Event event;
	while (true)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				break;
			}
		}

		SDL_FillRect(surf, &rects, 0x000000);//上一个位置涂黑
		rects.x++;//横坐标往右移动   可以用自增+=
		SDL_FillRect(surf, &rects, 0x0000ff);//重新绘制矩形
		SDL_UpdateWindowSurface(win);//更新
		SDL_Delay(5);//停留时间毫秒  越小速度越快
	}

	//销毁窗口
	SDL_DestroyWindow(win);
	SDL_FreeSurface(surf);


	//退出
	SDL_Quit();
	return 0;
}