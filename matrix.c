#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void rowsSwitch(int ROWS, int COLS, int **matrix, int firstrow, int secondrow);
void rowsMultiply(int ROWS, int COLS, int **matrix, int row, int num);
void rowPLusRowXnumber(int ROWS, int COLS, int **matrix, int firstrow, int secondrow, int num);
void matrixMultiplyByNumber(int ROWS, int COLS, int **matrix, int x);
void matrixPlusMatrix(int ROWS, int COLS, int **matrix);
void matrixChangeSigns(int ROWS, int COLS, int **matrix);
void matrixFill(int ROWS, int COLS, int **matrix);
void matrixDelete(int ROWS, int **matrix);
void matrixRedactElem(int ROWS, int COLS, int **matrix, int ROW, int COL, int num);
void matrixPrint(int ROWS, int COLS, int **matrix);
int **matrixMultiply(int ROWS, int *COLS, int **matrix);
int **matrixCreate(int ROWS, int COLS);
int **matrixTranspose(int *ROWS, int *COLS, int **matrix);

int main()
{
	setlocale(LC_ALL, "ru_RU.UTF-8");
	printf("------------------\n");

	int ROWS = 0, COLS = 0;
	while (ROWS <= 0 || COLS <= 0)
	{
		printf("Количество строк: ");
		scanf("%d", &ROWS);
		printf("Количество столбцов: ");
		scanf("%d", &COLS);
		if (ROWS <= 0 || COLS <= 0)
			printf("Повторите попытку\n");
	}

	int **matrix = matrixCreate(ROWS, COLS);
	if (matrix != NULL)
	{
		for (int i = 0; i < ROWS; i++)
			if (matrix[i] == NULL)
				goto errorend;
		printf(" A %dx%d\n", ROWS, COLS);
		for (int row = 0; row < ROWS; row++)
		{
			printf("| ");
			for (int col = 0; col < COLS; col++)
			{
				matrix[row][col] = 0;
				printf("%d ", matrix[row][col]);
			}
			printf("|\n");
		}
		printf("\n");
		matrixFill(ROWS, COLS, matrix);
		printf("\n");
		matrixPrint(ROWS, COLS, matrix);

		printf("\n\nДействия:\n");
		printf(" 1 - Поменять строки местами ( поменять первую и вторую строки '1 2' )\n");
		printf(" 2 - Прибавить к строке другую, умноженную на число ( прибавить к первой строке третью, умноженную на -2 '1 3 -2' )\n");
		printf(" 3 - Умножить строку на число ( умножить вторую строку на 6 '2 6' )\n");
		printf(" 4 - Транспонирование матрицы ( столбцы поменются со строками )\n");
		printf(" 5 - Умножить матрицу на число\n");
		printf(" 6 - Сложение матриц\n");
		printf(" 7 - Умножениить матрицу на другую ( C = A * B )\n");
		printf(" 8 - Получение противоположенной матрицы\n");
		printf(" 9 - Редактировать элемент матрицы ( поменять третье число в первой строке на 27 '1 3 27')\n");
		printf(" 0 - Выйти из программы\n");

		int loop = 1, input;
		int x, y, z;
		while (loop)
		{
			printf("Действие: ");
			scanf("%d", &input);
			if (!input)
				loop = 0;
			switch (input)
			{
			case 1:
			{
				printf("Введите номера строк: ");
				scanf("%d %d", &x, &y);
				rowsSwitch(ROWS, COLS, matrix, x - 1, y - 1);
				break;
			}
			case 2:
			{
				printf("Введите номера строк и множитель: ");
				scanf("%d %d %d", &x, &y, &z);
				rowPLusRowXnumber(ROWS, COLS, matrix, x - 1, y - 1, z);
				break;
			}
			case 3:
			{
				printf("Введите номер строки и множитель: ");
				scanf("%d %d", &x, &z);
				rowsMultiply(ROWS, COLS, matrix, x - 1, z);
				break;
			}
			case 4:
			{
				matrix = matrixTranspose(&ROWS, &COLS, matrix);
				break;
			}
			case 5:
			{
				printf("Введите множитель: ");
				scanf("%d", &z);
				matrixMultiplyByNumber(ROWS, COLS, matrix, z);
				break;
			}
			case 6:
			{
				matrixPlusMatrix(ROWS, COLS, matrix);
				break;
			}
			case 7:
			{
				matrix = matrixMultiply(ROWS, &COLS, matrix);
				break;
			}
			case 8:
			{
				matrixChangeSigns(ROWS, COLS, matrix);
				break;
			}
			case 9:
			{
				printf("Введите номер строки, колонны и новое значение: ");
				scanf("%d %d %d", &x, &y, &z);
				matrixRedactElem(COLS, ROWS, x - 1, y - 1, matrix, z);
				break;
			}
			default:
			{
				printf("Введите существующее действие\n");
			}
			}
			matrixPrint(ROWS, COLS, matrix);
		}
		matrixDelete(ROWS, matrix);
	}
	else
	{
	errorend:
		printf("Недостаточно памяти для работы программы\n");
	}
	return 0;
}

int **matrixCreate(int ROWS, int COLS)
{
	int **matrix = (int **)malloc(sizeof(int *) * ROWS);
	for (int i = 0; i < ROWS; i++)
		matrix[i] = (int *)malloc(sizeof(int) * COLS);
	return matrix;
}

void matrixFill(int ROWS, int COLS, int **matrix)
{
	printf("Заполните матрицу\n");
	for (int row = 0; row < ROWS; row++)
	{
		printf("-Строка №%d-\n", row + 1);
		for (int col = 0; col < COLS; col++)
		{
			printf("Элемент №%d = ", col + 1), scanf("%d", &matrix[row][col]);
		}
	}
	printf("\n");
}

void matrixPrint(int ROWS, int COLS, int **matrix)
{
	for (int row = 0; row < ROWS; row++)
	{
		printf("| ");
		for (int col = 0; col < COLS; col++)
		{
			printf("%3d ", matrix[row][col]);
		}
		printf("|\n");
	}
}

void matrixDelete(int ROWS, int **matrix)
{
	for (int i = 0; i < ROWS; i++)
		free(matrix[i]);
	free(matrix);
}

void rowsSwitch(int ROWS, int COLS, int **matrix, int fromrow, int torow)
{
	if (CheckRowsAndColsInput(ROWS, COLS, fromrow, 0) && CheckRowsAndColsInput(ROWS, COLS, torow, 0))
	{
		int *temp = (int *)malloc(sizeof(int) * COLS);
		int i;
		for (i = 0; i < COLS; i++)
			temp[i] = matrix[torow][i];
		for (i = 0; i < COLS; i++)
			matrix[torow][i] = matrix[fromrow][i];
		for (i = 0; i < COLS; i++)
			matrix[fromrow][i] = temp[i];
		free(temp);
	}
	else
		printf("ОШИБКА: обращение к несуществующей строке\n");
}

void rowsMultiply(int ROWS, int COLS, int **matrix, int row, int num)
{
	if (CheckRowsAndColsInput(ROWS, COLS, row, 0))
	{
		if (num != 0)
		{
			for (int i = 0; i < COLS; i++)
				matrix[row][i] = matrix[row][i] * num;
		}
		else
			printf("ОШИБКА: множитель не может быть равен 0\n");
	}
	else
		printf("ОШИБКА: обращение к несуществующей строке\n");
}

void rowPLusRowXnumber(int ROWS, int COLS, int **matrix, int firstrow, int secondrow, int num)
{
	if (CheckRowsAndColsInput(ROWS, COLS, firstrow, 0) && CheckRowsAndColsInput(ROWS, COLS, secondrow, 0))
	{
		if (num != 0)
		{
			for (int i = 0; i < COLS; i++)
				matrix[firstrow][i] = matrix[firstrow][i] + matrix[secondrow][i] * num;
		}
		else
			printf("ОШИБКА: множитель не может быть равен 0\n");
	}
	else
		printf("ОШИБКА: обращение к несуществующей строке\n");
}

int **matrixTranspose(int *ROWS, int *COLS, int **matrix)
{
	int **newmatrix = matrixCreate(*COLS, *ROWS);

	for (int row = 0; row < *ROWS; row++)
	{
		for (int col = 0; col < *COLS; col++)
		{
			newmatrix[col][row] = matrix[row][col];
		}
	}
	matrixDelete(*ROWS, matrix);
	int temp = *COLS;
	*COLS = *ROWS;
	*ROWS = temp;
	return newmatrix;
}

void matrixMultiplyByNumber(int ROWS, int COLS, int **matrix, int x)
{
	if (x != 0)
	{
		for (int row = 0; row < ROWS; row++)
			for (int col = 0; col < COLS; col++)
				matrix[row][col] *= x;
	}
	else
		printf("ОШИБКА: множитель не может быть равен 0\n");
}

void matrixPlusMatrix(int ROWS, int COLS, int **matrix)
{
	int x;
	printf("Заполните матрицу с которой выполнится сложение\n");
	for (int row = 0; row < ROWS; row++)
	{
		printf("-Строка №%d-\n", row + 1);
		for (int col = 0; col < COLS; col++)
		{
			printf("Элемент №%d = ", col + 1), scanf("%d", &x);
			matrix[row][col] += x;
		}
	}
}

void matrixChangeSigns(int ROWS, int COLS, int **matrix)
{
	for (int row = 0; row < ROWS; row++)
		for (int col = 0; col < COLS; col++)
			matrix[row][col] = -matrix[row][col];
}

void matrixRedactElem(int ROWS, int COLS, int **matrix, int ROW, int COL, int num)
{
	if (CheckRowsAndColsInput(ROWS, COLS, ROW, COL))
		matrix[ROW][COL] = num;
	else
		printf("ОШИБКА: обращение к несуществующему элементу\n");
}

int **matrixMultiply(int leftROWS, int *COLS, int **leftmatrix)
{
	int rightROWS = *COLS;
	int rightCOLS = 0;
	printf("Количество строк в правой матрице будет равно количеству столбцов левой: %d\n", rightROWS);
	printf("Введите количество столбцов: ");
	while (rightCOLS <= 0)
	{
		scanf("%d", &rightCOLS);
		if (rightCOLS <= 0)
			printf("Неверный ввод\n");
	}
	int **rightmatrix = matrixCreate(rightROWS, rightCOLS);
	matrixFill(rightROWS, rightCOLS, rightmatrix);

	matrixPrint(leftROWS, *COLS, leftmatrix);
	printf("\t\tX\n");
	matrixPrint(rightROWS, rightCOLS, rightmatrix);
	printf("\t\t=\n");

	int **resultmatrix = matrixCreate(leftROWS, rightCOLS);
	int c = 0;
	for (int row = 0; row < leftROWS; row++)
	{
		for (int col = 0; col < rightCOLS; col++)
		{
			for (int i = 0; i < rightROWS; i++)
				c += leftmatrix[row][i] * rightmatrix[i][col];
			resultmatrix[row][col] = c;
			c = 0;
		}
	}
	*COLS = rightCOLS;
	matrixDelete(leftROWS, leftmatrix);
	matrixDelete(rightROWS, rightmatrix);
	return resultmatrix;
}

int CheckRowsAndColsInput(int ROWS, int COLS, int r, int c)
{
	if (r < 0 || r >= ROWS || c < 0 || c >= ROWS)
		return 0;
	else
		return 1;
}