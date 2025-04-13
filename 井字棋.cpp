#include<graphics.h>
#include <windows.h> // ��Ӵ�ͷ�ļ���ʹ�� MessageBox �� GetHWnd ����


char board_data[3][3] = {
	{'-', '-', '-'},
	{'-', '-', '-'},
	{'-', '-', '-'},
};//���̳�ʼ��

char current_piece = 'O';// ��ʼ������ 
//int x_index = 0;
//int y_index = 0;


bool CheckWin(char c) {
	// ���ָ�����ӵ�����Ƿ��ʤ
	if (board_data[0][0] == c && board_data[0][1] == c && board_data[0][2] == c)//��һ��
		return true;
	else if (board_data[1][0] == c && board_data[1][1] == c && board_data[1][2] == c)// �ڶ���
		return true;
	else if (board_data[2][0] == c && board_data[2][1] == c && board_data[2][2] == c) // ������
		return true;
	else if (board_data[0][0] == c && board_data[1][1] == c && board_data[2][2] == c) // ���������� �Խ���
		return true;
	else if (board_data[0][2] == c && board_data[1][1] == c && board_data[2][0] == c) // ���������� �Խ���
		return true;
	else if (board_data[0][0] == c && board_data[1][0] == c && board_data[2][0] == c) // ��һ��
		return true;
	else if (board_data[0][1] == c && board_data[1][1] == c && board_data[2][1] == c) // �ڶ���
		return true;
	else if (board_data[0][2] == c && board_data[1][2] == c && board_data[2][2] == c) // ������
		return true;
	return false;
}
bool CheckDraw() {
	//�ж�ƽ��
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board_data[i][j] == '-')
				return false;
		}
	}
	return true;
}

void DrawBoard() {
	// ��������
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 5); // ����������ϸ��ԭ�����޴����ã�

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
		//����
		break;

	// ��������
	}
	
}
void DrawTipText() {
	//������ʾ��Ϣ
	static TCHAR str[64];
	_stprintf_s(str, _T("��ǰ���ӣ�%c"), current_piece); // 
	
	settextcolor(RGB(225, 175, 45));
	setbkmode(TRANSPARENT);// ?
	outtextxy(20, 20, str); //??
	
	setbkmode(TRANSPARENT);
}



// ����ѭ�������� x_index �� y_index ��������ʹ��������ѭ���п���  
int main() {  
   initgraph(600, 600); // initgrapg ���ƽ���  

   bool running = true;  

   ExMessage msg; // ����ExMessage�ṹ��  

   BeginBatchDraw(); // ��ʼ������ͼ  

   while (running) { 
	   DWORD start_time = GetTickCount(); // ��ȡ��ǰʱ��
	   cleardevice();
	   // ����գ��ٻ��ƣ����ˢ��

       DrawBoard();  
       DrawTipText();  
	   for (int i = 0; i < 3; i++) {
		   for (int j = 0; j < 3; j++) {
			   if (board_data[i][j] != '-') {
				   DrawChess(j, i, board_data[i][j]);
			   }
		   }
	   }

       int x_index = -1; // ��ѭ������������������ʼ�� x_index  
       int y_index = -1; // ��ѭ������������������ʼ�� y_index  

       while (peekmessage(&msg)) {  
           // ������Ϣ���˴�ֻ���������Ϣ  

           if (msg.message == WM_LBUTTONDOWN) {  
               // ������λ��  

               int x = msg.x;  
               int y = msg.y;  

               x_index = x / 200;  
               y_index = y / 200;  
           }  

           // ���λ���Ƿ���Ч����������  
           if (x_index >= 0 && y_index >= 0 && board_data[y_index][x_index] == '-') {  
               board_data[y_index][x_index] = current_piece;  

               DrawChess(x_index, y_index, current_piece); // �˴�Ӧ���Ŵ�����������  

               // �л�����  
               if (current_piece == 'X') {  
                   current_piece = 'O';  
               } else {  
                   current_piece = 'X';  
               }  
           }  
       }  

       if (CheckWin('X')) {  
           MessageBox(GetHWnd(), _T("X��һ�ʤ"), _T("��Ϸ����"), MB_OK);  
           running = false;  
       } else if (CheckWin('O')) {  
           MessageBox(GetHWnd(), _T("O��һ�ʤ"), _T("��Ϸ����"), MB_OK);  
           running = false;  
       } else if (CheckDraw()) {  
           MessageBox(GetHWnd(), _T("ƽ��"), _T("��Ϸ����"), MB_OK);  
           running = false;  
       }  
	   DWORD end_time = GetTickCount();// ��ȡ��ǰʱ��
	   DWORD delta_time = end_time - start_time; // ����ʱ���

	   if (delta_time <= 1000 / 60) {
		   Sleep(1000 / 60 - delta_time);
	   }

       FlushBatchDraw(); // ��ջ���  
   }  

   EndBatchDraw();  
}