#include <windows.h>
#include <cstring>
#include <cstdlib>
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	static HWND h, h2, r;
	switch(Message) {
		case WM_CREATE: {
			CreateWindow("STATIC", "请输入Hexo博客根目录地址", WS_CHILD | WS_VISIBLE, 20, 20, 190, 20, hwnd, (HMENU)9, 0, 0);
			CreateWindow("STATIC", "请输入文章名称", WS_CHILD | WS_VISIBLE, 20, 150, 110, 20, hwnd, (HMENU)8, 0, 0);
			CreateWindow("STATIC", "请输页面名称", WS_CHILD | WS_VISIBLE, 20, 110, 110, 20, hwnd, (HMENU)8, 0, 0);
			CreateWindow("BUTTON", "新建文章", WS_CHILD | WS_VISIBLE, 500, 143, 70, 32, hwnd, (HMENU)10, 0, 0);
			CreateWindow("BUTTON", "新建页面", WS_CHILD | WS_VISIBLE, 500, 103, 70, 32, hwnd, (HMENU)6, 0, 0);
			CreateWindow("BUTTON", "在本机预览", WS_CHILD | WS_VISIBLE, 20, 200, 110, 20, hwnd, (HMENU)5, 0, 0);
			CreateWindow("BUTTON", "上传至GitHub", WS_CHILD | WS_VISIBLE, 150, 200, 110, 20, hwnd, (HMENU)11, 0, 0);
			h = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 110, 320, 20, hwnd, (HMENU)3, 0, 0);
			h2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 150, 320, 20, hwnd, (HMENU)2, 0, 0);
			r = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 45, 320, 20, hwnd, (HMENU)2, 0, 0);
//			h2 = CreateWindow("BUTTON",)
			break;
		}
		case WM_COMMAND: {
			switch(LOWORD(wParam)) {
				case 10: {
					char *p = new char[1024];
					char *str = new char[1024];
					char *Adress = new char[512];
					str[0] = 0;
					GetWindowText(r, Adress, 512);
					if (strlen(Adress) == 0) {
						MessageBox(hwnd, "请输入Hexo根目录地址！", "提示", MB_ICONWARNING | MB_OK);
						break;
					} 
					GetWindowText(h2, p, 1024);
					strcat(str, "cd ");
					strcat(str, Adress);
					strcat(str, " & hexo new ");
					strcat(str, p);
//					Exec(Cd);
//					ShellExecute(0,0,"cmd.exe","");
					system(str);
					MessageBox(hwnd, "创建成功！", "提示", MB_ICONINFORMATION | MB_OK);
					delete[] p;
					delete[] str;
					delete[] Adress;
					break;
				}
				case 6: {
					char *p = new char[1024];
					char *str = new char[1024];
					char *Adress = new char[512];
					str[0] = 0;
					GetWindowText(r, Adress, 512);
					if (strlen(Adress) == 0) {
						MessageBox(hwnd, "请输入Hexo根目录地址！", "提示", MB_ICONWARNING | MB_OK);
						break;
					}
					GetWindowText(h, p, 1024);
					strcat(str, "cd ");
					strcat(str, Adress);
					strcat(str, " & hexo new page ");
					strcat(str, p);
//					Exec(Cd);
//					ShellExecute(0,0,"cmd.exe","");
					system(str);
					MessageBox(hwnd, "创建成功！", "提示", MB_ICONINFORMATION | MB_OK);
					delete[] p;
					delete[] str;
					delete[] Adress;
					break;
				}
				case 5: {
					char *p = new char[1024];
					char *str = new char[1024];
					char *Adress = new char[512];
					str[0] = 0;
					GetWindowText(r, Adress, 512);
					if (strlen(Adress) == 0) {
						MessageBox(hwnd, "请输入Hexo根目录地址！", "提示", MB_ICONWARNING | MB_OK);
						break; 
					}
					strcat(str, "cd ");
					strcat(str, Adress);
					strcat(str, " & hexo clean & hexo s ");
//					Exec(Cd);
//					ShellExecute(0,0,"cmd.exe","");
					system(str);
//					MessageBox(hwnd, "已经可以在localhost上查看", "提示", MB_ICONINFORMATION | MB_OK);
					delete[] p;
					delete[] str;
					delete[] Adress;
					break;
				}
				case 11: {
					char *p = new char[1024];
					char *str = new char[1024];
					char *Adress = new char[512];
					str[0] = 0;
					GetWindowText(r, Adress, 512);
					strcat(str, "cd ");
					strcat(str, Adress);
					strcat(str, " & hexo clean & hexo d ");
//					Exec(Cd);
//					ShellExecute(0,0,"cmd.exe","");
					system(str);
//					MessageBox(hwnd, "已经上传完成！", "提示", MB_ICONINFORMATION | MB_OK);
					delete[] p;
					delete[] str;
					delete[] Adress;
					break;
				}
			}
			break;
		}
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}

		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);

	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Caption",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
	                      CW_USEDEFAULT, /* x */
	                      CW_USEDEFAULT, /* y */
	                      640, /* width */
	                      480, /* height */
	                      NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}

