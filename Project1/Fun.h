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

int canSquareChange();//�ж��Ƿ���Ըı䷽��
int canLongSquareChange();//�ж��Ƿ���Ըı䳤���η���

void OnPaintText(HDC hdc, PAINTSTRUCT* ps);
void OnPaint(HDC hdc, PAINTSTRUCT* ps);//���Ʊ���
void DrawBlock(HDC hdc);//���ƶ���˹����
void OnCreate();//������ɶ���˹����
void CopyBlock();//���ƶ���˹���鵽����
void OnTimer(HWND hWnd);//��ʱ��
void LeftMove(HWND hwnd);//���ƶ���˹����
void RightMove(HWND hwnd);//���ƶ���˹����
void DownMove(HWND hwnd);//���ƶ���˹����
void ReadHighestScore();//��ȡ��߷�
void WriteHighestScore();//д����߷�

void change0To4SquareShape(HWND hWnd);//�ı�0����Ϊ4����
void changeLongSquareShape(HWND hWnd);//�ı䳤���η���

int IsGameOver();//�ж���Ϸ�Ƿ����
void Check_If_Delete_Row(HWND hWnd);
BOOL Check_Buttom();//�ж��Ƿ񵽴�ײ�

#endif