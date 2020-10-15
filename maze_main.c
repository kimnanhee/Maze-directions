#include <stdio.h>
#define miro_size 6

int stack[2][100] = { 0, };
int stack_point = 0;

void push(int x, int y)
{
	printf("push - %d %d - %d\n", x, y, stack_point);
	stack[0][stack_point] = x;
	stack[1][stack_point] = y;
	stack_point++;
}
void pop()
{
	printf("pop - %d\n", stack_point);
	stack_point--;
}
int top()
{
	int top_value = stack[0][stack_point - 1] * 10 + stack[1][stack_point - 1];
	printf("return value - %d\n", top_value);
	return top_value;
}
int main()
{
	int miro[16][16];
	int s_Row, s_Col; // 시작 위치 저장
	int cur_r, cur_c;

	printf("배열을 입력해주세요\n");
	for (int row = 0; row < miro_size; row++)
	{
		for (int col = 0; col < miro_size; col++)
		{
			int input;
			scanf_s("%d", &input);
			miro[row][col] = input;
			if (input == 2) // 시작 위치 지정
			{
				s_Row = row; 
				s_Col = col;
			}
		}
	}
	// 탐색 시작
	cur_r = s_Row; 
	cur_c = s_Col;
	push(cur_r, cur_c); // 시작 위치를 stack에 삽입
	int cnt = 0;
	while (1) 
	{
		printf("\n\n%d     (%d, %d)\n", cnt++, cur_r, cur_c);
		miro[cur_r][cur_c] = 8;

		// 오른쪽이 뚫려있을 경우
		if (miro[cur_r][cur_c + 1] == 0 && top() != (cur_r * 10 + (cur_c + 1))) {
			push(cur_r, cur_c);
			cur_c = cur_c + 1;
		}
		// 왼쪽이 뚫려있을 경우
		else if (miro[cur_r][cur_c - 1] == 0 && top() != (cur_r * 10 + (cur_c - 1))) {
			push(cur_r, cur_c);
			cur_c = cur_c - 1;
		}
		// 아래쪽이 뚫려있을 경우
		else if (miro[cur_r + 1][cur_c] == 0 && top() != ((cur_r + 1)*10 + cur_c)) {
			push(cur_r, cur_c);
			cur_r = cur_r + 1;
		}
		// 위쪽이 뚫려있을 경우
		else if (miro[cur_r - 1][cur_c] == 0 && top() != ((cur_r - 1) * 10 + cur_c)) {
			push(cur_r, cur_c);
			cur_r = cur_r - 1;
		}

		else if (miro[cur_r][cur_c + 1] == 3 || miro[cur_r][cur_c - 1] == 3 || miro[cur_r + 1][cur_c] == 3 || miro[cur_r - 1][cur_c] == 3) 
		{
			push(cur_r, cur_c);
			printf("finish\n");
			break; 
		}
		else {
			cur_r = top() / 10;
			cur_c = top() % 10;
			pop();
		}

		if (stack_point == 0)
		{
			printf("0\n");
			break;
		}
	}
	int i = 0;
	printf("---------------------\n");
	for (i = 0; i < stack_point; i++) // stack에 들어있는 죄표 출력
	{
		printf("%d - %d %d\n", i, stack[0][i], stack[1][i]);
	}
	return 0;
}