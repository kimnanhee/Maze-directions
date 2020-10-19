#include <stdio.h>
#define miro_size 11

int stack[2][100] = { 0, };
int stack_point = 0;

void push(int x, int y)
{
	// printf("push - %d %d - %d\n", x, y, stack_point);
	stack[0][stack_point] = x;
	stack[1][stack_point] = y;
	stack_point++;
}
void pop()
{
	// printf("pop - %d\n", stack_point);
	stack_point--;
}
int top()
{
	int top_value = stack[0][stack_point - 1] * 100 + stack[1][stack_point - 1];
	// printf("return value - %d\n", top_value);
	return top_value;
}
int main()
{
	int miro[16][16];
	int s_Row, s_Col; // 시작 위치 저장
	int cur_r, cur_c;

	printf("배열을 입력해주세요\n");
	int row, col;
	for (row = 0; row < miro_size; row++)
	{
		for (col = 0; col < miro_size; col++)
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
	// 시작위치로 커서 옮기기
	cur_r = s_Row; 
	cur_c = s_Col;
	push(cur_r, cur_c); // 시작 위치를 stack에 삽입

	while (1) 
	{
		miro[cur_r][cur_c] = 8; // 방문 했을때 

		if (miro[cur_r][cur_c + 1] == 0 && top() != (cur_r * 100 + (cur_c + 1))) // 오른쪽이 뚫려있을 경우
		{
			push(cur_r, cur_c);
			cur_c = cur_c + 1;
		}
		
		else if (miro[cur_r][cur_c - 1] == 0 && top() != (cur_r * 100 + (cur_c - 1))) // 왼쪽이 뚫려있을 경우
		{
			push(cur_r, cur_c);
			cur_c = cur_c - 1;
		}
		
		else if (miro[cur_r + 1][cur_c] == 0 && top() != ((cur_r + 1)*100 + cur_c)) // 아래쪽이 뚫려있을 경우
		{
			push(cur_r, cur_c);
			cur_r = cur_r + 1;
		}
		
		else if (miro[cur_r - 1][cur_c] == 0 && top() != ((cur_r - 1) * 100 + cur_c)) // 위쪽이 뚫려있을 경우
		{
			push(cur_r, cur_c);
			cur_r = cur_r - 1;
		}

		else if (miro[cur_r][cur_c + 1] == 3) // right
		{
			push(cur_r, cur_c);
			push(cur_r, cur_c + 1);
			break; 
		}
		else if (miro[cur_r][cur_c - 1] == 3) // left
		{
			push(cur_r, cur_c);
			push(cur_r, cur_c - 1);
			break; 
		}
		else if(miro[cur_r + 1][cur_c] == 3) // down
		{
			push(cur_r, cur_c);
			push(cur_r + 1, cur_c);
			break; 
		}
		else if (miro[cur_r - 1][cur_c] == 3) // up
		{
			push(cur_r, cur_c);
			push(cur_r - 1, cur_c);
			break; 
		}
		else 
		{
			cur_r = top() / 100; // 길이 없으면 전의 위치로 back
			cur_c = top() % 100;
			pop();
		}

		if (stack_point == 0) { // 스택에 든 값이 없을 때
			printf("0\n");
			break;
		}
	}
	int i = 0;
	printf("---------------------\nDirections\n\n");
	for (i = 0; i < stack_point; i++) // stack에 들어있는 경로 출력
	{
		printf("%d - %d %d\n", i, stack[0][i], stack[1][i]);
	}
	return 0;
}
