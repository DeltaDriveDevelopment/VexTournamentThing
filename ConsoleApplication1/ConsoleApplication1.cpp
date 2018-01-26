// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#define _CRT_SECURE_NO_WARNINGS

void LeftClick(POINT point);
void Display();
void printControls();
int fieldVal = 0;
HWND OBS;
HWND terminalWindow;
HWND controlwindow;
HWND managerwindow;

POINT scene1, scene2, scene3, start, inmatch, results, getInput;

BOOL CALLBACK enumChildWindows(HWND window, LPARAM lParam)
{
  WCHAR title[100];
  GetWindowText(window, title, 100);
  printf("%S\n", title);
  return TRUE;
}

int main()
{
  Sleep(2000);
  int desktopWidth;
  int desktopHeight;
  RECT desktopRect;
  HWND desktop = GetDesktopWindow();
  GetWindowRect(desktop, &desktopRect);
  desktopWidth = desktopRect.right;
  desktopHeight = desktopRect.bottom;
  
  terminalWindow = GetConsoleWindow();
  SetWindowPos(terminalWindow, nullptr, desktopWidth / 2, 0, desktopWidth / 2, desktopHeight / 2, NULL);
  SetForegroundWindow(terminalWindow);

  managerwindow = FindWindow(NULL, L"VEX Tournament Manager");
  SetWindowPos(managerwindow, nullptr, desktopWidth / 2, desktopHeight / 2, desktopWidth / 2, desktopHeight / 2, NULL);
  SetForegroundWindow(terminalWindow);

  std::string obsWindowTitle;
  printf("Enter the name of OBS Window\n");
  getline(std::cin, obsWindowTitle);
  
  //OBS = FindWindow(NULL, L"OBS 0.16.5 (windows) - Profile: Untitled - Scenes: Untitled");
  int bufferlen = ::MultiByteToWideChar(CP_ACP, 0, obsWindowTitle.c_str(), obsWindowTitle.size(), NULL, 0);
  LPWSTR widestr = new WCHAR[bufferlen + 1];
  ::MultiByteToWideChar(CP_ACP, 0, obsWindowTitle.c_str(), obsWindowTitle.size(), widestr, bufferlen);
  widestr[bufferlen] = 0;
  LPCWSTR constWideString = widestr;


  OBS = FindWindow(NULL, constWideString);
  SetWindowPos(OBS, nullptr, 0, 0, (desktopWidth / 2), (desktopHeight / 2), NULL);
  SetForegroundWindow(terminalWindow);

  std::string fieldSetControlTitle;
  printf("Enter the name of the field set control window\n");
  getline(std::cin, fieldSetControlTitle);
  
  int bufferlen2 = ::MultiByteToWideChar(CP_ACP, 0, fieldSetControlTitle.c_str(), fieldSetControlTitle.size(), NULL, 0);
  LPWSTR widestr2 = new WCHAR[bufferlen2 + 1];
  ::MultiByteToWideChar(CP_ACP, 0, fieldSetControlTitle.c_str(), fieldSetControlTitle.size(), widestr2, bufferlen2);
  widestr2[bufferlen2] = 0;
  LPCWSTR constWideString2 = widestr2;

  controlwindow = FindWindow(NULL, constWideString2);
  SetWindowPos(controlwindow, nullptr, 0, desktopHeight / 2, desktopWidth / 2, desktopHeight / 2, NULL);
  SetForegroundWindow(terminalWindow);

  printf("Hover your mouse over the Scene1 button and press a control key\nA sound will play once you've pressed control\n\n");

  while (!GetAsyncKeyState(VK_CONTROL));
  GetCursorPos(&scene1);
  MessageBeep(MB_OK);
  Sleep(500);

  printf("Now Scene2\n");
  while (!GetAsyncKeyState(VK_CONTROL));
  GetCursorPos(&scene2);
  MessageBeep(MB_OK);
  Sleep(500);

  printf("Scene3\n");
  while (!GetAsyncKeyState(VK_CONTROL));
  GetCursorPos(&scene3);
  MessageBeep(MB_OK);
  Sleep(500);

  printf("start\n");
  while (!GetAsyncKeyState(VK_CONTROL));
  GetCursorPos(&start);
  MessageBeep(MB_OK);
  Sleep(500);

  printf("inmatch\n");
  while (!GetAsyncKeyState(VK_CONTROL));
  GetCursorPos(&inmatch);
  MessageBeep(MB_OK);
  Sleep(500);

  printf("results\n");
  while (!GetAsyncKeyState(VK_CONTROL));
  GetCursorPos(&results);
  MessageBeep(MB_OK);
  Sleep(500);
  MessageBeep(MB_ICONWARNING);
  Sleep(300);
  MessageBeep(MB_ICONWARNING);
  Sleep(300);
  MessageBeep(MB_ICONWARNING);
  Sleep(300);



  bool running = true;

  int stage = 0;

  int incrementKey;
  int switchDisplayKey;
  int useSafety;
  int safetyKey;
  std::fstream infile;
  infile.open("keyConfig.txt", std::fstream::in);

  infile >> std::hex >> incrementKey;
  infile >> std::hex >> switchDisplayKey;
  infile >> useSafety;
  if(useSafety) infile >> std::hex >> safetyKey;

  printControls();
  while (running)
  {
    //Reset Windows
    if (GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(0x38))
    {
      WCHAR title[900];
      printf("Resetting Windows\n");
      SetWindowPos(OBS, nullptr, 0, 0, desktopWidth / 2, desktopHeight / 2, NULL);
      GetWindowText(OBS, title, 900);
      printf("\nOBS: %S\n", title);
      SetWindowPos(terminalWindow, nullptr, desktopWidth / 2, 0, desktopWidth / 2, desktopHeight / 2, NULL);
      GetWindowText(terminalWindow, title, 900);
      printf("\nTerminal: %S\n", title);
      SetWindowPos(controlwindow, nullptr, 0, desktopHeight / 2, desktopWidth / 2, desktopHeight / 2, NULL);

      HWND temp = GetParent(controlwindow);
      if (temp == NULL)
        printf("First parent NULL\n");
      int i = 0;
      while (temp != NULL)
      {
        GetWindowText(temp, title, 900);
        printf("\nControlParent %d: %S\n", i, title);
        temp = GetParent(temp);
      }
      GetWindowText(controlwindow, title, 900);
      printf("\nControl: %S\n", title);
      SetWindowPos(managerwindow, nullptr, desktopWidth / 2, desktopHeight / 2, desktopWidth / 2, desktopHeight / 2, NULL);
      GetWindowText(managerwindow, title, 900);
      printf("\nManager: %S\n", title);
      printControls();
    }

    //Increment
    else if ((useSafety) ? GetAsyncKeyState(safetyKey) && GetAsyncKeyState(incrementKey) : GetAsyncKeyState(incrementKey))
    {
      //TODO Increment stage
      stage++;
      switch (stage)
      {
      case 1:
        printf("Stage1: Clicking inmatch\n");
        LeftClick(inmatch);
        Display();
        break;
      case 2:
        printf("Stage2: Clicking Start\n");
        LeftClick(start);
        break;
      case 3:
        printf("Stage3: Clicking start and delaying for 115000ms\n");
        LeftClick(start);
        int timer = 0;

        while (timer < 115000)
        {
          timer += 1000;
          int seconds = timer / 1000;
          printf("%d seconds have elapsed.\n\n", seconds);
          Sleep(1000);
        }


        printf("****************\n");
        printf("Clicking results\n");
        printf("****************\n");
        LeftClick(results);
        printf("Clicking scene3\n");
        LeftClick(scene3);
        stage = 0;
        break;
      }
      printControls();
    }

    else if (GetAsyncKeyState(switchDisplayKey)) // 0 key
    {
      // todo Switch displayed field
      printf("Swapping display to ");
      Display();
      printControls();
    }

    else if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(0x51)) // Q key
      running = false;

    else if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(0x58)) // X key
    {
      /*CloseWindow(OBS);
      CloseWindow(terminalWindow);
      CloseWindow(controlwindow);
      CloseWindow(managerwindow);*/
      running = false;
    }

    Sleep(500);
  }
  
  SetForegroundWindow(terminalWindow);
  printf("Goodbye!\n");
  system("pause");
  return 0;
}


void LeftClick(POINT point)
{
  SetCursorPos(point.x, point.y);
  mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
  mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
  SetFocus(terminalWindow);
}

void Display()
{
  if (!fieldVal)
  {
    printf("scene1\n");
    LeftClick(scene1);
  }
  else if (fieldVal)
  {
    printf("scene2\n");
    LeftClick(scene2);
  }
  fieldVal = (fieldVal) ? 0 : 1;
}

void printControls()
{
  printf("\nPress Shift + 8 ('*') to reset all windows\n");
  printf("Press shift + = ('+') to increment the program\n");
  printf("Press 0 to switch the display\n");
  printf("Press ctrl + q or ctrl + x to exit the program\n");

}

