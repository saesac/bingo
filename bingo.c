#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>

int* bingo_matrix, *copy_bingo_matrix;

int print_result_bingo(int* result_log, int log_cnt, int size);
int check_bingo(int size, int now_num);
int game_start(int size);
int make_bingo();

int set_problem();

int main()
{
	int ch = 0;
	int size ;

	srand((unsigned int)time(NULL));

	while (1)
	{
		printf("참가자시면 a, 문제를 내는사람이면 b를 눌러주세요. 나머지 버튼을 누르시면 종료됩니다. : \n");
		scanf_s(" %c", &ch);

		if (ch == 'a')
		{
			size = make_bingo();

			while (ch != 1)
			{
				ch = game_start(size);

				if (ch == 2)
					size = make_bingo();
				else if (ch == 0)
					printf("잘못 입력하셨습니다. 다시 입력 해 주세요.\n");
			}
		}
		else if (ch == 'b')
		{
			game_start(-1);
		}
		else
		{
			break;
		}
	}

	printf("%%%%%% 끝 %%%%%%\n");
	
	return 1;
}

int make_bingo()
{
	int size, i, temp, matrix_full_on = 0;
	int* num;
	int max_size = 0, rand_n;

	printf("input bingo size : ");
	scanf_s("%d", &size);

	max_size = size * size * 2;
	num = (int*)malloc(sizeof(int) * (max_size));
	bingo_matrix = (int*)malloc(sizeof(int) * size * size);
	copy_bingo_matrix = (int*)malloc(sizeof(int) * size * size);

	for (i = 0; i < max_size; i++)
	{
		num[i] = i;
	}

	while (matrix_full_on < size * size)
	{
		rand_n = rand() % (max_size - matrix_full_on);

		bingo_matrix[matrix_full_on] = num[rand_n];

		temp = num[rand_n];
		num[rand_n] = num[max_size - 1 - matrix_full_on];

		matrix_full_on++;
	}

	for (i = 0; i < max_size / 2; i++)
	{
		if (i % size == 0)
		{
			printf("\n");
		}
		printf("%4d", bingo_matrix[i]);
		copy_bingo_matrix[i] = bingo_matrix[i];
	}

	printf("\n\n");

	return size;
}

int game_start(int size)
{
	char start_check = 0, ch;
	int now_num, bingo_cnt = 0, i;
	int* saving_result_num = (int*)malloc(sizeof(int) * size * size);

	if (size < 0)
	{
		set_problem();
		return 1;
	}

	printf("게임을 시작하실려면 s를 눌러주세요, 빙고를 새로 만드실려면 n을 눌러주세요. \n");
	scanf_s(" %c", &start_check);

	if (start_check == 'n')
	{
		return 2;
	}
	else if (start_check == 's')
	{
		bingo_cnt = 0;

		printf("********** bingo game start  :  *********************\n");

		while (1)
		{
			printf("input num(minus num input-> print result) : ");
			if (scanf_s(" %d", &now_num) == 0)
			{
				// 잘못된 입력
				printf("invalidate value!!\n");
				rewind(stdin);
			}
			else // 제대로 된 값 입력 시 .
			{
				if (now_num < 0)
				{
					print_result_bingo(saving_result_num, bingo_cnt, size);

					printf("종료하시겠습니까? (y/n) \n");
					scanf_s(" %c", &ch);

					if (ch == 'y')
						return 1;
				}

				saving_result_num[bingo_cnt++] = now_num;

				check_bingo(size, now_num);
			}


		}

		return 1;
	}
	else
	{
		return 0;
	}

}

int check_bingo(int size, int now_num)
{
	int i = 0, j, k;

	for (i = 0; i < size * size; i++)
	{
		if (copy_bingo_matrix[i] == now_num)
		{
			copy_bingo_matrix[i] = -1;
		}
	}

	printf("\n");

	for (i = 0; i < size * size; i++)
	{
		if (i % size == 0)
		{
			printf("\n");
		}

		if (copy_bingo_matrix[i] == -1)
		{
			printf("%4c", '#');
		}
		else
		{
			printf("%4d", copy_bingo_matrix[i]);
		}
	}

	printf("\n");


	return  0;
}

int print_result_bingo(int* result_log, int log_cnt, int size)
{
	int i = 0, j = 0;
	printf("result_log : ");
	for (i = 0; i < log_cnt; i++)
	{
		printf(" %4d. ", result_log[i]);
	}

	printf("\n\n original bingo matrix,       result bingo matrix");

	for (i = 0; i < size; i++)
	{
		printf("\n");

		for (j = 0; j < size; j++)
		{
			printf("%4d", bingo_matrix[i * size + j]);
		}

		printf("          ");

		for (j = 0; j < size; j++)
		{
			if (copy_bingo_matrix[i * size + j] == -1)
			{
				printf("%4c", '#');
			}
			else
			{
				printf("%4d", copy_bingo_matrix[i * size + j]);
			}
		}

	}

	printf("\n\n");

	return 1;
}


int set_problem()
{
	int size, i, now_num, * result_log, log_cnt = 0;
	int* num;
	int max_size = 0, rand_n;
	char ch;

	printf("input bingo size : ");
	scanf_s("%d", &size);

	max_size = size * size * 2;
	num = (int*)malloc(sizeof(int) * (max_size));

	for (i = 0; i < max_size; i++)
	{
		num[i] = i;
	}

	result_log = (int*)malloc(sizeof(int) * size * size);

	while (1)
	{
		if (_kbhit())
		{
			ch = _getch();

			if (ch == 'r')
			{
				printf("\n\nresult_log : \n\n");
				for (i = 0; i < log_cnt; i++)
				{
					printf(" %4d,", result_log[i]);
				}
			}
			else if (ch == 'e')
			{
				printf("\n\n프로그램을 종료합니다. (y/n) \n");
				scanf_s(" %c", &ch);
				if (ch == 'y')
					break;
			}
			else // 제대로 된 값 입력 시 .
			{
				rand_n = rand() % (max_size - log_cnt);
				result_log[log_cnt] = num[rand_n];

				num[rand_n] = num[max_size - log_cnt - 1];

				printf("%4d, ", result_log[log_cnt]);

				log_cnt++;
			}
		}
	}

}
