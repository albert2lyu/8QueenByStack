// 8QueenByStack.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"

#define MAXQUEEN 8

struct stack_node {
	int x;
	int y;
	struct stack_node *next;
};
typedef struct stack_node stack_list;
typedef stack_list *link;

link solution = NULL;

int pad [MAXQUEEN][MAXQUEEN] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

/*
 * ���ʺ��Ƿ����໥����
 */
int place(int x, int y)
{
	int x1, y1;

	if (x < 0 || y < 0 || x >= MAXQUEEN || y >= MAXQUEEN) {
		return 0;
	}

	if (pad[x][y] != 0) {
		return 0;
	}

	// ������Ϸ�
	x1 = x-1;
	y1 = y-1;
	while (x1 >= 0 && y1 >= 0) {
		if (pad[x1--][y1--] != 0) {
			return 0;
		}
	}

	// ����Ϸ�
	x1 = x-1;
	y1 = y;
	while (x1 >= 0) {
		if (pad[x1--][y1] != 0) {
			return 0;
		}
	}

	// ������Ϸ�
	x1 = x-1;
	y1 = y+1;
	while (x1 >= 0 && y1 < MAXQUEEN) {
		if (pad[x1--][y1++] != 0) {
			return 0;
		}
	}

	// ����ҷ�
	x1 = x;
	y1 = y+1;
	while (y1 < MAXQUEEN) {
		if (pad[x1][y1++] != 0) {
			return 0;
		}
	}

	// ������·�
	x1 = x+1;
	y1 = y+1;
	while (x1 < MAXQUEEN && y1 < MAXQUEEN) {
		if (pad[x1++][y1++] != 0) {
			return 0;
		}
	}

	// ����·�
	x1 = x+1;
	y1 = y;
	while (x1 < MAXQUEEN) {
		if (pad[x1++][y1] != 0) {
			return 0;
		}
	}

	// ������·�
	x1 = x+1;
	y1 = y-1;
	while (x1 < MAXQUEEN && y1 >= 0) {
		if (pad[x1++][y1--] != 0) {
			return 0;
		}
	}

	// �����
	x1 = x;
	y1 = y-1;
	while (y1 >= 0) {
		if (pad[x1][y1--] != 0) {
			return 0;
		}
	}

	return 1;
}

link push(link stack, int x, int y)
{
	link new_node;

	new_node = (link)malloc(sizeof(stack_list) );
	if (!new_node) {
		_tprintf(_T("�ڴ����ʧ��!\n"));
		return NULL;
	}

	new_node->x = x;
	new_node->y = y;
	new_node->next = stack;

	stack = new_node;

	return stack;
}

link pop(link stack, int *x, int *y)
{
	link top;

	if (stack != NULL) {
		top = stack;
		stack = stack->next;
		*x = top->x;
		*y = top->y;
		free(top);
		return stack;
	}
	else {
		*x = -1;
		return NULL;
	}
}

void print_pad(int *pad)
{
	for (int i = 0; i < MAXQUEEN; i++) {
		for (int j = 0; j < MAXQUEEN; j++) {
			printf("%d ", pad[i*MAXQUEEN+j]);
		}
		printf("\n");
	}

	printf("\n");
}

/*
 * ����Ϊ��λ���������ҷ���
 * ���Է��ã�����ջ
 *   ��i ��ʱ��ջ���Ϊi+1����Ϊj
 *   �����ΪMAXQUEEN �����ҵ�һ���
 * �����Է��ã�������j ��������
 * ��j >= MAXQUEEN ʱ����һ�г�ջ������j ����
 * ��j >= MAXQUEEN ��ջ�ѿ�ʱ�������з������Ѽ���
 */
int _tmain(int argc, _TCHAR* argv[])
{
	int solutionCount = 0;
	int stackDepth = 0;
	int stackCol = 0;

	do {
		if (place(stackDepth, stackCol) ) {
			solution = push(solution, stackDepth, stackCol);
			pad[stackDepth][stackCol] = 1;
			stackDepth++;
			stackCol = 0; // ��һ�д�0 ��ʼ
			// print_pad(&pad[0][0]);
		}
		else {
			if (stackDepth>=MAXQUEEN || stackCol >= MAXQUEEN) {
				solution = pop(solution, &stackDepth, &stackCol);
				pad[stackDepth][stackCol] = 0;
				if (stackDepth < 0) {
					break;
				}
				stackCol++; // ����һ�п�ʼ����
			}
			else {
				stackCol++;
			}
		}
		if (stackDepth == MAXQUEEN) {
			printf("No.%d\n", ++solutionCount);
			print_pad(&pad[0][0]);
		}
	} while (stackDepth < MAXQUEEN || stackCol < MAXQUEEN);

	// print_pad(&pad[0][0]);

	return 0;
}
