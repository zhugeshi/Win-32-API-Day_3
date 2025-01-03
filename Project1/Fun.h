#ifndef __FUN_H__
#define __FUN_H__

#include <windows.h>
#include <stdio.h>
#include<time.h>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 640
#define ID_DOWN_TIMER 1

void StopDown();
void BlockDown(HWND hwnd);
void onChangeProc(HWND hWnd);

int canSquareChange();//判断是否可以改变方块
int canLongSquareChange();//判断是否可以改变长方形方块

void OnPaintText(HDC hdc, PAINTSTRUCT* ps);
void OnPaint(HDC hdc, PAINTSTRUCT* ps);//绘制背景
void DrawBlock(HDC hdc);//绘制俄罗斯方块
void OnCreate();//随机生成俄罗斯方块
void CopyBlock();//复制俄罗斯方块到背景
void OnTimer(HWND hWnd);//定时器
void LeftMove(HWND hwnd);//左移俄罗斯方块
void RightMove(HWND hwnd);//右移俄罗斯方块
void DownMove(HWND hwnd);//下移俄罗斯方块
void ReadHighestScore();//读取最高分
void WriteHighestScore();//写入最高分

void change0To4SquareShape(HWND hWnd);//改变0方块为4方块
void changeLongSquareShape(HWND hWnd);//改变长方形方块

int IsGameOver();//判断游戏是否结束
void Check_If_Delete_Row(HWND hWnd);
BOOL Check_Buttom();//判断是否到达底部

#endif