#pragma warning(disable:4996)
#include"Fun.h"

int g_score = 0;//记录分数
int g_xIndex = 3;//记录随机块所在空间的左上角x
int g_yIndex = 0;//记录随机块所在空间的左上角y
int g_highestScore = 0;//记录最高分

int g_blockIndex = 0;//记录当前的俄罗斯方块种类
int g_RussBlocks[2][4] = { 0 };//记录俄罗斯方块的形状
int g_backgroundArray[20][10] = { 0 };//记录背景数组

extern int g_status;//记录游戏状态,0表示游戏未开始,1表示游戏进行中,2表示游戏结束

void OnPaint(HDC hdc, PAINTSTRUCT* ps) {

	//双缓冲区
	HDC hdcMem = CreateCompatibleDC(hdc);
	//创建兼容位图
	HBITMAP hBackmap = CreateCompatibleBitmap(hdc, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(hdcMem, hBackmap);
	//在内存dc上绘制
	DrawBlock(hdcMem);
	//复制到窗口dc
	BitBlt(hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdcMem, 0, 0, SRCCOPY);
	//释放dc
	DeleteObject(hBackmap);
}

void DrawBlock(HDC hdc) {
	//绘制背景
	Rectangle(hdc, 300, 0, 500, 600);
	HBRUSH secondbrush = CreateSolidBrush(RGB(220, 220, 220));
	HBRUSH brush = (HBRUSH)SelectObject(hdc, secondbrush);
	Rectangle(hdc, 0, 0, 300, 600);
	SelectObject(hdc, brush);
	DeleteObject(secondbrush);
	//绘制背景
	HBRUSH hbrush = CreateSolidBrush(RGB(0, 200, 180));
	HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			if (g_backgroundArray[i][j] == 1) {
				Rectangle(hdc, j * 30 + 1, i * 30 + 1, j * 30 + 29, i * 30 + 29);
			}
			if (g_backgroundArray[i][j] == 2) {
				Rectangle(hdc, j * 30 + 1, i * 30 + 1, j * 30 + 29, i * 30 + 29);
			}
		}
	}
	SelectObject(hdc, oldbrush);
	DeleteObject(hbrush);
}

void OnCreate() {
	srand(time(NULL));
	int shape = rand() % 7;
	g_blockIndex = shape;//随机产生六种状况的方块
	switch (shape) {
	case 0:
		//1 1 0 0
		//0 1 1 0
		g_RussBlocks[0][0] = 1; g_RussBlocks[0][1] = 1; g_RussBlocks[0][2] = 0; g_RussBlocks[0][3] = 0;
		g_RussBlocks[1][0] = 0; g_RussBlocks[1][1] = 1; g_RussBlocks[1][2] = 1; g_RussBlocks[1][3] = 0;

		g_xIndex = 3;
		g_yIndex = 0;
		break;
	case 1:
		//0 1 1 0
		//1 1 0 0
		g_RussBlocks[0][0] = 0; g_RussBlocks[0][1] = 1; g_RussBlocks[0][2] = 1; g_RussBlocks[0][3] = 0;
		g_RussBlocks[1][0] = 1; g_RussBlocks[1][1] = 1; g_RussBlocks[1][2] = 0; g_RussBlocks[1][3] = 0;

		g_xIndex = 3;
		g_yIndex = 0;
		break;
	case 2:
		//0 0 1 0
		//1 1 1 0
		g_RussBlocks[0][0] = 0; g_RussBlocks[0][1] = 0; g_RussBlocks[0][2] = 1; g_RussBlocks[0][3] = 0;
		g_RussBlocks[1][0] = 1; g_RussBlocks[1][1] = 1; g_RussBlocks[1][2] = 1; g_RussBlocks[1][3] = 0;

		g_xIndex = 3;
		g_yIndex = 0;
		break;
	case 3:
		//1 0 0 0
		//1 1 1 0
		g_RussBlocks[0][0] = 1; g_RussBlocks[0][1] = 0; g_RussBlocks[0][2] = 0; g_RussBlocks[0][3] = 0;
		g_RussBlocks[1][0] = 1; g_RussBlocks[1][1] = 1; g_RussBlocks[1][2] = 1; g_RussBlocks[1][3] = 0;

		g_xIndex = 3;
		g_yIndex = 0;
		break;
	case 4:
		//0 0 0 0 1 0 0 0 0 0 
		//0 0 0 1 1 1 0 0 0 0 
		g_RussBlocks[0][0] = 0; g_RussBlocks[0][1] = 1; g_RussBlocks[0][2] = 0; g_RussBlocks[0][3] = 0;
		g_RussBlocks[1][0] = 1; g_RussBlocks[1][1] = 1; g_RussBlocks[1][2] = 1; g_RussBlocks[1][3] = 0;

		g_xIndex = 3;
		g_yIndex = 0;
		break;
	case 5:
		//0 0 0 0 1 1 0 0 0 0
		//0 0 0 0 1 1 0 0 0 0
		g_RussBlocks[0][0] = 0; g_RussBlocks[0][1] = 1; g_RussBlocks[0][2] = 1; g_RussBlocks[0][3] = 0;
		g_RussBlocks[1][0] = 0; g_RussBlocks[1][1] = 1; g_RussBlocks[1][2] = 1; g_RussBlocks[1][3] = 0;

		g_xIndex = 4;
		g_yIndex = 0;
		break;
	case 6:
		//0 0 0 1 1 1 1 0 0 0 
		//0 0 0 0 0 0 0 0 0 0
		g_RussBlocks[0][0] = 1; g_RussBlocks[0][1] = 1; g_RussBlocks[0][2] = 1; g_RussBlocks[0][3] = 1;
		g_RussBlocks[1][0] = 0; g_RussBlocks[1][1] = 0; g_RussBlocks[1][2] = 0; g_RussBlocks[1][3] = 0;

		g_xIndex = 4;
		g_yIndex = 0;
		break;
	default:
		break;
	}
	CopyBlock();
}

void CopyBlock() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			if (g_RussBlocks[i][j] == 1) {
				g_backgroundArray[i][j + 3] = g_RussBlocks[i][j];
			}
		}
	}
}

void OnTimer(HWND hWnd) {
	if (!Check_Buttom())
	{
		//停止下落
		StopDown();
		//检查是否有行消除
		Check_If_Delete_Row(hWnd);
		//产生新的方块
		if (IsGameOver()) {
			WriteHighestScore();
			KillTimer(hWnd, ID_DOWN_TIMER);
			MessageBox(hWnd, "Game Over!", "Game Over", MB_OK);
			SendMessage(hWnd, WM_DESTROY, NULL, NULL);
			return;
		}
		OnCreate();
	}
	else
	{
		BlockDown(hWnd);
	}
	InvalidateRect(hWnd, NULL, FALSE);//重绘窗口,此时产生WM_PAINT消息,调用OnPaint函数
}

void BlockDown(HWND hwnd) {
	if (!Check_Buttom())
	{
		//停止下落
		StopDown();
		//检查是否有行消除
		Check_If_Delete_Row(hwnd);
		//产生新的方块
		OnCreate();
		InvalidateRect(hwnd, NULL, FALSE);
	}
	else {
		g_yIndex++;
		for (int i = 19; i >= 0; i--) {
			for (int j = 0; j < 10; j++) {
				if (g_backgroundArray[i][j] == 1) {
					g_backgroundArray[i + 1][j] = 1;
					g_backgroundArray[i][j] = 0;
				}
			}
		}
		InvalidateRect(hwnd, NULL, FALSE);
	}
}

BOOL Check_Buttom() {
	int flag = 1;
	for (int i = 19; i >= 0; i--) {
		for (int j = 0; j < 10; j++) {
			if (g_backgroundArray[i][j] == 1) {
				if (i == 19) {
					flag = 0;
					return flag;
				}
				else if (g_backgroundArray[i + 1][j] == 2) {
					flag = 0;
					return flag;
				}
				else {
					flag = 1;
					continue;
				}
			}
		}
	}
	return flag;
}

void StopDown() {
	for (int i = 19; i >= 0; i--) {
		for (int j = 0; j < 10; j++) {
			if (g_backgroundArray[i][j] == 1) {
				g_backgroundArray[i][j] = 2;
			}
		}
	}
}

void LeftMove(HWND hwnd) {
	if (g_status != 1) {
		return;
	}
	int flag = 0;
	for (int i = 19; i >= 0; i--) {
		for (int j = 0; j < 10; j++) {
			if (g_backgroundArray[i][j] == 1) {
				if (j == 0) {
					flag = 1;
					return;
				}
				else if (g_backgroundArray[i][j - 1] == 2) {
					flag = 1;
					return;
				}
				else if (g_backgroundArray[i][j - 1] == 1) {
					continue;
				}
			}
		}
	}
	if (flag == 0) {
		g_xIndex--;
		for (int i = 19; i >= 0; i--) {
			for (int j = 0; j < 10; j++) {
				if (g_backgroundArray[i][j] == 1) {
					g_backgroundArray[i][j] = 0;
					g_backgroundArray[i][j - 1] = 1;
				}
			}
		}
	}
	InvalidateRect(hwnd, NULL, FALSE);
}

void RightMove(HWND hWnd) {
	if (g_status != 1) {
		return;
	}
	int flag = 0;
	for (int i = 19; i >= 0; i--) {
		for (int j = 9; j >= 0; j--) {
			if (g_backgroundArray[i][j] == 1) {
				if (j == 9) {
					flag = 1;
					return;
				}
				else if (g_backgroundArray[i][j + 1] == 2) {
					flag = 1;
					return;
				}
				else if (g_backgroundArray[i][j + 1] == 1) {
					continue;
				}
			}
		}
	}
	if (flag == 0) {
		g_xIndex++;
		for (int i = 19; i >= 0; i--) {
			for (int j = 9; j >= 0; j--) {
				if (g_backgroundArray[i][j] == 1) {
					g_backgroundArray[i][j] = 0;
					g_backgroundArray[i][j + 1] = 1;
				}
			}
		}
	}
	InvalidateRect(hWnd, NULL, FALSE);
}

void DownMove(HWND hwnd) {
	if (g_status != 1) {
		return;
	}
	if (!Check_Buttom())
	{
		//停止下落
		StopDown();
		//检查是否有行消除
		Check_If_Delete_Row(hwnd);
		//产生新的方块
		OnCreate();
		InvalidateRect(hwnd, NULL, FALSE);
	}
	else {
		g_yIndex++;
		int flag = 0;
		for (int i = 19; i >= 0; i--) {
			for (int j = 0; j < 10; j++) {
				if (g_backgroundArray[i][j] == 1) {
					if (i == 19) {
						flag = 1;
						return;
					}
					else if (g_backgroundArray[i + 1][j] == 1) {
						continue;
					}
				}
			}
		}
		if (flag == 0) {
			for (int i = 19; i >= 0; i--) {
				for (int j = 0; j < 10; j++) {
					if (g_backgroundArray[i][j] == 1) {
						g_backgroundArray[i][j] = 0;
						g_backgroundArray[i + 1][j] = 1;
					}
				}
			}
		}
		InvalidateRect(hwnd, NULL, FALSE);
	}
}

void Check_If_Delete_Row(HWND hWnd) {
	int count = 0;
	for (int i = 19; i >= 0; i--) {
		int flag = 1;
		for (int j = 0; j < 10; j++) {
			if (g_backgroundArray[i][j] == 0) {
				flag = 0;
				break;
			}
		}
		if (flag == 1) {
			count++;
			int iTempI = i - 1;
			for (int j = 0; j < 10; j++) {
				g_backgroundArray[i][j] = 0;
			}
			for (int k = i; k > 0; k--) {
				for (int j = 0; j < 10; j++) {
					g_backgroundArray[k][j] = g_backgroundArray[k - 1][j];
				}
			}
			g_score++;
			i++;
		}
	}
	if (count > 0) {
		InvalidateRect(hWnd, NULL, FALSE);
	}
}

void OnPaint(HWND hWnd) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	RECT rcClient;
	GetClientRect(hWnd, &rcClient);
	HDC hdcMem = CreateCompatibleDC(hdc);
}

void onChangeProc(HWND hWnd)
{
	if (g_status != 1) {
		return;
	}
	HDC hdc = GetDC(hWnd);
	switch (g_blockIndex)
	{
		//0-4为一类
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		if (canSquareChange())
		{
			change0To4SquareShape(hWnd);
		}
		else
		{
			return;
		}
		break;
	case 5://5为正方形，不需要变形
		break;
	case 6://6为长条
		if (canLongSquareChange())
			changeLongSquareShape(hWnd);
		break;
	}
	ReleaseDC(hWnd, hdc);
}

int canSquareChange()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (g_backgroundArray[g_yIndex + i][g_xIndex + j] == 2)
				return 0;
		}
	}

	//第一种方案，到达边界不让其变形
	if (g_xIndex < 0 || g_xIndex + 2 >9)
	{
		return 0;
	}

	////第二种方案，到达边界仍让其变形，但g_xIndex移动一位，使其在边界上
	//if (g_xIndex < 0)
	//{
	//	g_xIndex = 0;
	//}
	//else if (g_xIndex + 2 > 9)
	//{
	//	g_xIndex = 7;
	//}
	return 1;
}

int canLongSquareChange()
{
	int i = 1, j = 1;

	for (; i < 4;)//判断中心右边距离边界或者值为2的方块有多远
	{
		if (g_backgroundArray[g_yIndex][g_xIndex + i] == 2 ||
			g_xIndex + i > 9)
		{
			i--;
			break;
		}
		i++;
	}

	for (; j < 4;)//判断中心左边距离边界或者值为2的方块有多远
	{
		if (g_backgroundArray[g_yIndex][g_xIndex - j] == 2 ||
			g_xIndex - j < 0)
		{
			j--;//因为上一轮先加了1，这轮再做判断的，所以不符合条件要减去1
			break;
		}
		j++;
	}

	if (i + j < 3)
	{
		return 0;
	}

	return 1;
}

void change0To4SquareShape(HWND hWnd)
{
	char tempArray[3][3] = { 0 };
	//将3*3数组从背景中提出来
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tempArray[i][j] = g_backgroundArray[g_yIndex + i][g_xIndex + j];
		}
	}

	//将变换后的再赋值回去
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			g_backgroundArray[g_yIndex + i][g_xIndex + j] = tempArray[2 - j][i];
		}
	}
	InvalidateRect(hWnd, NULL, FALSE);
}

void changeLongSquareShape(HWND hWnd)
{
	//横着的情况
	if (g_backgroundArray[g_yIndex][g_xIndex - 1] == 1)//中心的左边为1，说明横着
	{
		//先将原背景里的清除
		g_backgroundArray[g_yIndex][g_xIndex - 1] = 0;
		g_backgroundArray[g_yIndex][g_xIndex + 0] = 0;//中心
		g_backgroundArray[g_yIndex][g_xIndex + 1] = 0;
		g_backgroundArray[g_yIndex][g_xIndex + 2] = 0;

		// 1 1 1 1 
		// 2 2 2 2 
		if (g_backgroundArray[g_yIndex + 1][g_xIndex] == 2)
		{
			//防止
			// 2 2 2 2		2 2 2 2
			// 1 1 1 1	或	0 0 0 0
			// 2 2 2 2		1 1 1 1
			//				2 2 2 2
			if (g_backgroundArray[g_yIndex - 3][g_xIndex] != 2 &&
				g_backgroundArray[g_yIndex - 2][g_xIndex] != 2 &&
				g_backgroundArray[g_yIndex - 1][g_xIndex] != 2)
			{
				//然后填上变形后的
				g_backgroundArray[g_yIndex - 3][g_xIndex] = 1;
				g_backgroundArray[g_yIndex - 2][g_xIndex] = 1;
				g_backgroundArray[g_yIndex - 1][g_xIndex] = 1;
				g_backgroundArray[g_yIndex + 0][g_xIndex] = 1;//中心
			}


		}
		else if (g_backgroundArray[g_yIndex + 2][g_xIndex] == 2)
		{
			// 2 2 2 2
			// 1 1 1 1
			// 0 0 0 0
			// 2 2 2 2	
			if (g_backgroundArray[g_yIndex - 1][g_xIndex] != 2 &&
				g_backgroundArray[g_yIndex - 2][g_xIndex] != 2)
			{
				//然后填上变形后的
				g_backgroundArray[g_yIndex - 2][g_xIndex] = 1;
				g_backgroundArray[g_yIndex - 1][g_xIndex] = 1;
				g_backgroundArray[g_yIndex + 0][g_xIndex] = 1;//中心
				g_backgroundArray[g_yIndex + 1][g_xIndex] = 1;
			}

		}
		else
		{
			//防止
			//2 2 2 2
			//1 1 1 1
			//0 0 0 0
			//0 0 0 0
			if (g_backgroundArray[g_yIndex - 1][g_xIndex] != 2)
			{
				//然后填上变形后的
				g_backgroundArray[g_yIndex - 1][g_xIndex] = 1;
				g_backgroundArray[g_yIndex + 0][g_xIndex] = 1;//中心
				g_backgroundArray[g_yIndex + 1][g_xIndex] = 1;
				g_backgroundArray[g_yIndex + 2][g_xIndex] = 1;
			}

		}

	}
	else//竖着的
	{
		//先将原背景里的清除
		g_backgroundArray[g_yIndex - 1][g_xIndex] = 0;
		g_backgroundArray[g_yIndex + 0][g_xIndex] = 0;//中心
		g_backgroundArray[g_yIndex + 1][g_xIndex] = 0;
		g_backgroundArray[g_yIndex + 2][g_xIndex] = 0;

		if (g_backgroundArray[g_yIndex][g_xIndex + 1] == 2 || g_xIndex == 9)
		{	//整体向左平移2位
			g_backgroundArray[g_yIndex][g_xIndex + 0] = 1;
			g_backgroundArray[g_yIndex][g_xIndex - 1] = 1;
			g_backgroundArray[g_yIndex][g_xIndex - 2] = 1;
			g_backgroundArray[g_yIndex][g_xIndex - 3] = 1;

			//标记中心改变
			g_xIndex -= 2;
		}
		else if (g_backgroundArray[g_yIndex][g_xIndex + 2] == 2 || g_xIndex == 8)
		{	//整体向左平移1位
			g_backgroundArray[g_yIndex][g_xIndex + 1] = 1;
			g_backgroundArray[g_yIndex][g_xIndex + 0] = 1;
			g_backgroundArray[g_yIndex][g_xIndex - 1] = 1;
			g_backgroundArray[g_yIndex][g_xIndex - 2] = 1;

			//标记中心改变
			g_xIndex -= 1;
		}
		else if (g_backgroundArray[g_yIndex][g_xIndex - 1] == 2 || g_xIndex == 0)
		{	//整体向右平移1位
			g_backgroundArray[g_yIndex][g_xIndex + 3] = 1;
			g_backgroundArray[g_yIndex][g_xIndex + 2] = 1;
			g_backgroundArray[g_yIndex][g_xIndex + 1] = 1;
			g_backgroundArray[g_yIndex][g_xIndex + 0] = 1;

			//标记中心改变
			g_xIndex += 1;
		}
		else
		{
			//然后填上变形后的
			g_backgroundArray[g_yIndex][g_xIndex - 1] = 1;
			g_backgroundArray[g_yIndex][g_xIndex + 0] = 1;//中心
			g_backgroundArray[g_yIndex][g_xIndex + 1] = 1;
			g_backgroundArray[g_yIndex][g_xIndex + 2] = 1;
		}
	}
	InvalidateRect(hWnd, NULL, FALSE);
}

int IsGameOver()
{
	for (int i = 0; i < 10; i++)
	{
		if (g_backgroundArray[0][i] == 2)
		{
			g_status = 2;
			return 1;
		}
	}
	return 0;
}

void OnPaintText(HDC hdc, PAINTSTRUCT* ps) {
	char g_scoreText[100];
	char g_highestScoreText[100];
	ps->rcPaint.left = 302;
	ps->rcPaint.top = 50;
	ps->rcPaint.right = 500;
	ps->rcPaint.bottom = 220;
	DrawText(hdc, "Welcom to Tetris\nPress enter to start\n\n\nPress space to change\nPress down to move down\nPress left and right to move sideways\n"
		, -1, &ps->rcPaint,
		DT_LEFT);
	sprintf_s(g_scoreText, 100, "Present Score:%d", g_score );
	DrawText(hdc, g_scoreText, -1, &ps->rcPaint,  DT_LEFT | DT_BOTTOM | DT_SINGLELINE);
	sprintf_s(g_highestScoreText, 100, "Highest Score:%d", g_highestScore);
	TextOut(hdc, 302, 250, g_highestScoreText, strlen(g_highestScoreText));
}

void ReadHighestScore() {
	FILE* pFile;
	if (fopen_s(&pFile, "highestScore.txt", "r") == 0) {
		fscanf_s(pFile, "%d", &g_highestScore);
		fclose(pFile);
	}	
}

void WriteHighestScore() {
	if (g_score > g_highestScore) {
		g_highestScore = g_score;
		FILE* pFile;
		if (fopen_s(&pFile, "highestScore.txt", "w") == 0) {
			fprintf_s(pFile, "%d", g_highestScore);
			fclose(pFile);
		}
	}
}
