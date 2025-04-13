#include<graphics.h>
#include <windows.h> // 添加此头文件以使用 MessageBox 和 GetHWnd 函数


char board_data[3][3] = {
	{'-', '-', '-'},
	{'-', '-', '-'},
	{'-', '-', '-'},
};//棋盘初始化

char current_piece = 'O';// 初始化棋子 
//int x_index = 0;
//int y_index = 0;


bool CheckWin(char c) {
	// 检测指定棋子的玩家是否获胜
	if (board_data[0][0] == c && board_data[0][1] == c && board_data[0][2] == c)//第一行
		return true;
	else if (board_data[1][0] == c && board_data[1][1] == c && board_data[1][2] == c)// 第二行
		return true;
	else if (board_data[2][0] == c && board_data[2][1] == c && board_data[2][2] == c) // 第三行
		return true;
	else if (board_data[0][0] == c && board_data[1][1] == c && board_data[2][2] == c) // 左上至右下 对角线
		return true;
	else if (board_data[0][2] == c && board_data[1][1] == c && board_data[2][0] == c) // 左下至右上 对角线
		return true;
	else if (board_data[0][0] == c && board_data[1][0] == c && board_data[2][0] == c) // 第一列
		return true;
	else if (board_data[0][1] == c && board_data[1][1] == c && board_data[2][1] == c) // 第二列
		return true;
	else if (board_data[0][2] == c && board_data[1][2] == c && board_data[2][2] == c) // 第三列
		return true;
	return false;
}
bool CheckDraw() {
	//判断平局
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board_data[i][j] == '-')
				return false;
		}
	}
	return true;
}

void DrawBoard() {
	// 绘制棋盘
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 5); // 设置线条粗细（原代码无此设置）

	line(0, 0, 600, 0);
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
	line(0, 600, 600, 600);

	line(0, 0, 0, 600);
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
	line(600, 0, 600, 600);



}

void DrawChess(int x, int y, char c) {
	switch (c) {
	case 'O':
		setlinecolor(BLUE);
		setlinestyle(PS_SOLID, 5);
		//fillellipse(x, y, 50, 50); 
		circle(200 * x + 100, 200 * y + 100, 80);
		
		break;
	
	case 'X':
		
		setlinecolor(RED);
		setlinestyle(PS_SOLID, 5);
		//fillellipse(x, y, 50, 50); 
		line(x * 200 +20 , y * 200 + 20, (x + 1) * 200 - 20, (y + 1) * 200 - 20);
		line((x+1) * 200 - 20, y * 200 + 20, x * 200 + 20, (y + 1) * 200 - 20);
		//画叉
		break;

	// 绘制棋子
	}
	
}
void DrawTipText() {
	//绘制提示信息
	static TCHAR str[64];
	_stprintf_s(str, _T("当前棋子：%c"), current_piece); // 
	
	settextcolor(RGB(225, 175, 45));
	setbkmode(TRANSPARENT);// ?
	outtextxy(20, 20, str); //??
	
	setbkmode(TRANSPARENT);
}



// 在主循环中声明 x_index 和 y_index 的作用域，使其在整个循环中可用  
int main() {  
   initgraph(600, 600); // initgrapg 绘制界面  

   bool running = true;  

   ExMessage msg; // 创建ExMessage结构体  

   BeginBatchDraw(); // 开始批量绘图  

   while (running) { 
	   DWORD start_time = GetTickCount(); // 获取当前时间
	   cleardevice();
	   // 先清空，再绘制，最后刷新

       DrawBoard();  
       DrawTipText();  
	   for (int i = 0; i < 3; i++) {
		   for (int j = 0; j < 3; j++) {
			   if (board_data[i][j] != '-') {
				   DrawChess(j, i, board_data[i][j]);
			   }
		   }
	   }

       int x_index = -1; // 在循环作用域中声明并初始化 x_index  
       int y_index = -1; // 在循环作用域中声明并初始化 y_index  

       while (peekmessage(&msg)) {  
           // 处理信息，此处只处理鼠标信息  

           if (msg.message == WM_LBUTTONDOWN) {  
               // 计算点击位置  

               int x = msg.x;  
               int y = msg.y;  

               x_index = x / 200;  
               y_index = y / 200;  
           }  

           // 检查位置是否有效，尝试落子  
           if (x_index >= 0 && y_index >= 0 && board_data[y_index][x_index] == '-') {  
               board_data[y_index][x_index] = current_piece;  

               DrawChess(x_index, y_index, current_piece); // 此处应反着传入棋子坐标  

               // 切换棋子  
               if (current_piece == 'X') {  
                   current_piece = 'O';  
               } else {  
                   current_piece = 'X';  
               }  
           }  
       }  

       if (CheckWin('X')) {  
           MessageBox(GetHWnd(), _T("X玩家获胜"), _T("游戏结束"), MB_OK);  
           running = false;  
       } else if (CheckWin('O')) {  
           MessageBox(GetHWnd(), _T("O玩家获胜"), _T("游戏结束"), MB_OK);  
           running = false;  
       } else if (CheckDraw()) {  
           MessageBox(GetHWnd(), _T("平局"), _T("游戏结束"), MB_OK);  
           running = false;  
       }  
	   DWORD end_time = GetTickCount();// 获取当前时间
	   DWORD delta_time = end_time - start_time; // 计算时间差

	   if (delta_time <= 1000 / 60) {
		   Sleep(1000 / 60 - delta_time);
	   }

       FlushBatchDraw(); // 清空画面  
   }  

   EndBatchDraw();  
}