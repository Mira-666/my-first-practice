//显示窗口
//1.引入头文件
#include <SDL.h>//mingw SDL2/SDL.h

#define W 1200
#define H 800

#undef main //防止SDL重定义main函数

int main() {
	//2.初始化
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) //初始化成功返回0  失败返回负值
	{
		SDL_Log("Init failed: %s",SDL_GetError());//用法和printf类似  //获取错误信息
		return -1;
	}

	//3.创建窗口
	SDL_Window* win = SDL_CreateWindow("Hey", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,1200,800,SDL_WINDOW_RESIZABLE);
	if (NULL == win) {
		SDL_Log("SDL_CreateWindow failedd: %s", SDL_GetError());
		return -1;
	}

	//在窗口上绘制矩形
	//1.获取窗口关联的Surface
	SDL_Surface* surf = SDL_GetWindowSurface(win);
	if (NULL == surf) 
	{
		SDL_Log("SDL_GetWindowSurface failedd: %s", SDL_GetError());//创建要销毁 获取要释放
		return -1;
	}

	//2.定义一个区域
	SDL_Rect rect = {100,300,50,50 };//x y w h

	//3.在surface进行绘制
	SDL_FillRect(surf, &rect, 0x0000ff);//16进制表示颜色  RGB
	//SDL_FillRect(surf, &rect, SDL_MapRGB(surf->format,100,200,10));

	//4.将绘制内容更新到屏幕上
	SDL_UpdateWindowSurface(win);


	//4.暂停一段时间--->事件监听与响应
	//SDL_Delay(3000);
	SDL_Event event;//有死循环背景黑色  
	while (true)//事件监听响应关闭事件
	{
		if (SDL_PollEvent(&event))//从事件队列中取出一个事件  //接受指针类型 有事件返回1 没有返回0
		{
			if(event.type==SDL_QUIT)//判断事件类型是否为关闭事件
			{
				break;//跳出循环
			}
		}

		SDL_FillRect(surf, &rect, 0x000000);//rect 区域涂黑
		rect.x+= 2;
		SDL_FillRect(surf, &rect, 0x0000ff);
		SDL_UpdateWindowSurface(win);
		SDL_Delay(10);
	}//死循环  判断能否取出事件  判断事件类型 是  结束循环


	//5.销毁窗口//释放surface

	SDL_FreeSurface(surf);
	SDL_DestroyWindow(win);
	SDL_Quit();//初始化对应退出
	return 0;
}