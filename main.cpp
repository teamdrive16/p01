//https://www.computerhope.com/jargon/a/ascii.htm

#include <iostream>
#include <string>

#include <thread>
#include <conio.h>
#include <ctime>

//#define _WIN32_WINNT 0x0500
#include <windows.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;
using namespace this_thread;
using namespace chrono;

//#define WIDTH 400
//#define HEIGHT 600
float WIDTH = 500;
float HEIGHT = 800;

char KEY;
int CURRENT_KEY;

void SetUpWindow(float w, float h) {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); // stores the console's current dimensions

	MoveWindow(console, r.left, r.top, w, h, TRUE);
}

void DisableResize(){
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

// Get the horizontal and vertical screen sizes in pixel
void GetDesktopResolution(int& horizontal, int& vertical)
{
   RECT desktop;
   // Get a handle to the desktop window
   const HWND hDesktop = GetDesktopWindow();
   // Get the size of screen to the variable desktop
   GetWindowRect(hDesktop, &desktop);
   // The top left corner will have coordinates (0,0)
   // and the bottom right corner will have coordinates
   // (horizontal, vertical)
   horizontal = desktop.right;
   vertical = desktop.bottom;
}

void CenterWindow() {
	RECT rectClient, rectWindow;
	HWND console = GetConsoleWindow();
	GetClientRect(console, &rectClient);
	GetWindowRect(console, &rectWindow);
	int posX, posY;
	posX = (GetSystemMetrics(SM_CXSCREEN) / 2) - ((rectWindow.right - rectWindow.left) / 2);
	posY = (GetSystemMetrics(SM_CYSCREEN) / 2) - ((rectWindow.bottom - rectWindow.top) / 2);

	MoveWindow(console, posX, posY, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
}

BOOL SetConsoleFontSize(short x, short y){
	COORD dwFontSize;
	dwFontSize.X = x;
	dwFontSize.Y = y;
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX info{sizeof(CONSOLE_FONT_INFOEX)};
    if (!GetCurrentConsoleFontEx(output, false, &info))
        return false;
    info.dwFontSize = dwFontSize;
    return SetCurrentConsoleFontEx(output, false, &info);
}


void RemoveScrollbar(){
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo; 

    // Get console handle and get screen buffer information from that handle.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &screenBufferInfo);

    // Get rid of the scrollbar by setting the screen buffer size the same as 
    // the console window size.
    COORD new_screen_buffer_size;

    // screenBufferInfo.srWindow allows us to obtain the width and height info 
    // of the visible console in character cells.
    // That visible portion is what we want to set the screen buffer to, so that 
    // no scroll bars are needed to view the entire buffer.
    new_screen_buffer_size.X = screenBufferInfo.srWindow.Right - 
    screenBufferInfo.srWindow.Left + 1; // Columns
    new_screen_buffer_size.Y = screenBufferInfo.srWindow.Bottom - 
    screenBufferInfo.srWindow.Top + 1; // Rows

    // Set new buffer size
    SetConsoleScreenBufferSize(hConsole, new_screen_buffer_size);
}

void Test(){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 29; j++){
			cout << "*";
		}
		cout << endl;
	}
	
	while(1){
		KEY = getch();
	}
}

// THIS TEST PROVES STROKE TYPING LIKE MESSAGE
//char stroke = char(221);
//string msg = "";
//void Test2(){
//	while(1){
//		KEY = getch();
//		if((KEY >= ' ' && KEY <= '~')){
//			msg += KEY;
//		}else if (KEY == 13){
//			msg += '\n';
//		}
//	}
//}
//void Stroke(){
//	while(1){
//		if(stroke == char(221)){
//			stroke = ' ';
//		}else{
//			stroke = char(221);
//		}
//		sleep_for(milliseconds(500));
//	}
//}
//void Message(){
//	while(1){
//		system("cls");
//		cout << endl;
//		cout << "Message: " << msg << stroke << endl;
//		
//		sleep_for(milliseconds(100));
//	}
//}

void DebugResolution(){
	HWND console = GetConsoleWindow();
	RECT r;
	while(1){
		GetWindowRect(console, &r); // stores the console's current dimensions
		system("cls");
		cout << "\nbottom: " << r.bottom << "\nright: " << r.right;
	}
}

int* UpdateWindow(int ret[]);

int main() {
//	system("color a");
	SetUpWindow(WIDTH, HEIGHT);
//	SetConsoleFontSize(20,40);
	DisableResize();
	CenterWindow();
	RemoveScrollbar();
//	int horizontal = 0;
//    int vertical = 0;
//    GetDesktopResolution(horizontal, vertical);
//    cout << '\n' << horizontal << '\n' << vertical << '\n';
	
	int index = 0;
	char key = '?';
	int arr[2] = {index, int(key)};
	int *ret = arr;
	while(true){
		ret = UpdateWindow(ret);
	}
	
//	for(int i = 0; i < 25; i++){
//		for(int j = 0; j < 15; j++){
//			if(i == 0 || i == 24 || j == 0 || j == 14){
//				cout << "* ";
//			}else{
//				cout << "  ";
//			}
//		}
//		cout << endl;
//	}
	
//	thread debugresolution(DebugResolution);
//	debugresolution.join();
	
//	thread test2(Test2);
//	thread stroke(Stroke);
//	thread message(Message);
//	test2.join();
//	stroke.join();
//	message.join();
	
	return 0;
}

void CreateButton(string name, bool selected = false){
	if(selected){
		////////////////////////////////////////
		cout << char(186)<< "       ";
		cout << char(201);
		for(int i = 0; i < 20; i++){
			cout << char(205);
		}
		cout << char(187);
		cout << "        " << char(186) << endl;
		
		cout << char(186) << "       ";
		
		cout << char(186) << "      "<<name<<"      " << char(186);
		
		cout << "        " << char(186) << endl;
		
		cout << char(186)<< "       ";
		cout << char(200);
		for(int i = 0; i < 20; i++){
			cout << char(205);
		}
		cout << char(188);
		cout << "        " << char(186) << endl;
		////////////////////////////////////////
	}else{
		cout << char(186) << "                                     " << char(186) << endl;
		cout << char(186) << "              Contacts               " << char(186) << endl;
		cout << char(186) << "                                     " << char(186) << endl;
	}
}

int* UpdateWindow(int ret[]){
	int index = ret[0];
	char key = ret[1];
	system("cls");
//	cout << key << endl;

	cout << char(201);
	for(int i = 0; i < 37; i++){
		cout<<char(205);
	}
	cout<<char(187)<<endl;
	
	cout <<char(186)<<" 11:59         4G "<<char(219)<< "" <<char(220)<<"       "<<char(254)<< "" <<char(254)<< "" <<char(254)<< "" <<char(254)<<" 100% "<<char(186) << endl;
	
//	cout << char(200);
//	for(int i = 0; i < 37; i++){
//		cout<<char(205);
//	}
//	cout<<char(188)<<endl;
	
	//
	cout << char(204);
	for(int i = 0; i < 37; i++){
		cout<<char(205);
	}
	cout<<char(185)<<endl;
	
	switch(index){
		case 0:
			//-------------------------------------------------------------------------------------//
			cout << char(186) << "                                     " << char(186) << endl;
			CreateButton("Contacts", 1);
			
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			//-------------------------------------------------------------------------------------//
			break;
		case 1:
			//-------------------------------------------------------------------------------------//
			cout << char(186) << "                                     " << char(186) << endl;
			CreateButton("Contacts", 0);
			////////////////////////////////////////
			cout << char(186)<< "       ";
			cout << char(201);
			for(int i = 0; i < 20; i++){
				cout << char(205);
			}
			cout << char(187);
			cout << "        " << char(186) << endl;
			
			cout << char(186) << "       ";
			
			cout << char(186) << "      Contacts      " << char(186);
			
			cout << "        " << char(186) << endl;
			
			cout << char(186)<< "       ";
			cout << char(200);
			for(int i = 0; i < 20; i++){
				cout << char(205);
			}
			cout << char(188);
			cout << "        " << char(186) << endl;
			////////////////////////////////////////
			
			cout << char(186) << "                                     " << char(186) << endl;
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			//-------------------------------------------------------------------------------------//
			break;
		case 2:
			//-------------------------------------------------------------------------------------//
			cout << char(186) << "                                     " << char(186) << endl;
			CreateButton("Contacts", 0);
			
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
				////////////////////////////////////////
			cout << char(186)<< "       ";
			cout << char(201);
			for(int i = 0; i < 20; i++){
				cout << char(205);
			}
			cout << char(187);
			cout << "        " << char(186) << endl;
			
			cout << char(186) << "       ";
			
			cout << char(186) << "      Contacts      " << char(186);
			
			cout << "        " << char(186) << endl;
			
			cout << char(186)<< "       ";
			cout << char(200);
			for(int i = 0; i < 20; i++){
				cout << char(205);
			}
			cout << char(188);
			cout << "        " << char(186) << endl;
			////////////////////////////////////////
			
			cout << char(186) << "                                     " << char(186) << endl;
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			//-------------------------------------------------------------------------------------//
			break;
		case 3:
			//-------------------------------------------------------------------------------------//
			cout << char(186) << "                                     " << char(186) << endl;
			CreateButton("Contacts", 0);
			
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			////////////////////////////////////////
			cout << char(186)<< "       ";
			cout << char(201);
			for(int i = 0; i < 20; i++){
				cout << char(205);
			}
			cout << char(187);
			cout << "        " << char(186) << endl;
			
			cout << char(186) << "       ";
			
			cout << char(186) << "      Contacts      " << char(186);
			
			cout << "        " << char(186) << endl;
			
			cout << char(186)<< "       ";
			cout << char(200);
			for(int i = 0; i < 20; i++){
				cout << char(205);
			}
			cout << char(188);
			cout << "        " << char(186) << endl;
			////////////////////////////////////////
			
			cout << char(186) << "                                     " << char(186) << endl;
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			//-------------------------------------------------------------------------------------//
			break;
		case 4:
			//-------------------------------------------------------------------------------------//
			cout << char(186) << "                                     " << char(186) << endl;
			CreateButton("Contacts", 0);
			
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			////////////////////////////////////////
			cout << char(186)<< "       ";
			cout << char(201);
			for(int i = 0; i < 20; i++){
				cout << char(205);
			}
			cout << char(187);
			cout << "        " << char(186) << endl;
			
			cout << char(186) << "       ";
			
			cout << char(186) << "      Contacts      " << char(186);
			
			cout << "        " << char(186) << endl;
			
			cout << char(186)<< "       ";
			cout << char(200);
			for(int i = 0; i < 20; i++){
				cout << char(205);
			}
			cout << char(188);
			cout << "        " << char(186) << endl;
			////////////////////////////////////////
			
			cout << char(186) << "                                     " << char(186) << endl;
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			//-------------------------------------------------------------------------------------//
			break;
		case 5:
			//-------------------------------------------------------------------------------------//
			cout << char(186) << "                                     " << char(186) << endl;
			CreateButton("Contacts", 0);
			
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			
			CreateButton("Contacts", 0);
			cout << char(186) << "                                     " << char(186) << endl;
			////////////////////////////////////////
			cout << char(186)<< "       ";
			cout << char(201);
			for(int i = 0; i < 20; i++){
				cout << char(205);
			}
			cout << char(187);
			cout << "        " << char(186) << endl;
			
			cout << char(186) << "       ";
			
			cout << char(186) << "      Contacts      " << char(186);
			
			cout << "        " << char(186) << endl;
			
			cout << char(186)<< "       ";
			cout << char(200);
			for(int i = 0; i < 20; i++){
				cout << char(205);
			}
			cout << char(188);
			cout << "        " << char(186) << endl;
			////////////////////////////////////////
			
			cout << char(186) << "                                     " << char(186) << endl;
			//-------------------------------------------------------------------------------------//
			break;
	}
	cout << "Test";
	cout << char(200);
	for(int i = 0; i < 37; i++){
		cout<<char(205);
	}
	cout<<char(188)<<endl;
	//
	cout << (key = char(getch()));
	switch(key){
		case 'w': case 'H':
			index-=1;
			break;
		case 's': case 'P':
			index+=1;
			break;
	}
	if(index < 0){
		index = 5;
	}else if(index > 5){
		index = 0;
	}
	
	ret[0] = index;
	ret[1] = int(key);
	
	return ret;
}
