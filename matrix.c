#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

void rowsSwitch(int ROWS, int COLS, double **matrix, int firstrow, int secondrow);
void rowsMultiply(int ROWS, int COLS, double **matrix, int row, double num, char mod);
void rowPLusRowXnumber(int ROWS, int COLS, double **matrix, int secondrow, double num, int firstrow, char mod);
void matrixMultiplyByNumber(int ROWS, int COLS, double **matrix, double num, char mod);
void matrixPlusMatrix(int ROWS, int COLS, double **matrix);
void matrixChangeSigns(int ROWS, int COLS, double **matrix);
void matrixFill(int ROWS, int COLS, double **matrix);
void matrixDelete(int ROWS, double **matrix);
void matrixRedactElem(int ROWS, int COLS, double **matrix, int ROW, int COL, double num);
void matrixPrint(int ROWS, int COLS, double **matrix);
double **matrixMultiply(int ROWS, int *COLS, double **matrix);
double **matrixCreate(int ROWS, int COLS);
double **matrixTranspose(int *ROWS, int *COLS, double **matrix);

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

	double **matrix = matrixCreate(ROWS, COLS);
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
				matrix[row][col] = 0.0;
				printf("%.0lf ", matrix[row][col]);
			}
			printf("|\n");
		}
		printf("\n");
		matrixFill(ROWS, COLS, matrix);
		printf("\n");
		matrixPrint(ROWS, COLS, matrix);

		printf("\n\nДействия:\n");
		printf(" 1 - Поменять строки местами ( поменять первую и вторую строки '1 2' )\n");
		printf(" 2 - Прибавить к строке другую, умноженную или деленную на число ( четвертую строку умножить на -3 и добавить во 2 '4*-3 2' )\n");
		printf(" 3 - Умножить или резделить строку на число ( умножить вторую строку на 6 '2*6' )\n");
		printf(" 4 - Транспонирование матрицы ( столбцы поменются со строками )\n");
		printf(" 5 - Умножить или разделить матрицу на число ( разделить на 5.2 '/5.2' )\n");
		printf(" 6 - Сложение матриц\n");
		printf(" 7 - Умножениить матрицу на другую ( C = A * B )\n");
		printf(" 8 - Получение противоположенной матрицы\n");
		printf(" 9 - Редактировать элемент матрицы ( поменять третье число в первой строке на 27 '1 3 27')\n");
		printf(" 0 - Выйти из программы\n");

		int loop = 1, input;
		int row1, row2, col;
		double num;
		char mod;
		while (loop)
		{
			printf("Действие: ");
			scanf("%d", &input);
			if (!input)
				loop = 0;
			while ((getchar()) != '\n');
			switch (input)
			{
			case 1:
			{
				printf("<строку №> <поменять со строкой №>: ");
				scanf("%d %d", &row1, &row2);
				rowsSwitch(ROWS, COLS, matrix, row1 - 1, row2 - 1);
				break;
			}
			case 2:
			{
				printf("<строку №><* или /><на число> <и добавить в строкe №>: ");
				scanf("%d%c%lf %d", &row1, &mod, &num, &row2);
				rowPLusRowXnumber(ROWS, COLS, matrix, row1 - 1, num, row2 - 1, mod);
				break;
			}
			case 3:
			{
				printf("<строку №><* или /><на число>: ");
				scanf("%d%c%lf", &row1, &mod, &num);
				rowsMultiply(ROWS, COLS, matrix, row1 - 1, num, mod);
				break;
			}
			case 4:
			{
				matrix = matrixTranspose(&ROWS, &COLS, matrix);
				break;
			}
			case 5:
			{
				printf("<* или /><на число>: ");
				scanf("%c%lf", &mod, &num);
				matrixMultiplyByNumber(ROWS, COLS, matrix, num, mod);
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
				printf("<в строке №> <в колонне №> <элемент станет равен чслу>: ");
				scanf("%d %d %lf", &row1, &col, &num);
				matrixRedactElem(COLS, ROWS, matrix, row1 - 1, col - 1, num);
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

double **matrixCreate(int ROWS, int COLS)
{
	double **matrix = (double **)malloc(sizeof(double *) * ROWS);
	for (int i = 0; i < ROWS; i++)
		matrix[i] = (double *)malloc(sizeof(double) * COLS);
	return matrix;
}

void matrixFill(int ROWS, int COLS, double **matrix)
{
	printf("Заполните матрицу\n");
	for (int row = 0; row < ROWS; row++)
	{
		printf("-Строка №%d-\n", row + 1);
		for (int col = 0; col < COLS; col++)
		{
			printf("Элемент №%d = ", col + 1), scanf("%lf", &matrix[row][col]);
		}
	}
	printf("\n");
}

void matrixPrint(int ROWS, int COLS, double **matrix)
{
	double x, i;
	for (int row = 0; row < ROWS; row++)
	{
		printf("| ");
		for (int col = 0; col < COLS; col++)
		{
			x = modfl(matrix[row][col], &i);
			if (x == 0)
				printf("%.0lf\t", matrix[row][col]);
			else
				printf("%.1lf\t", matrix[row][col]);
		}
		printf("|\n");
	}
}

void matrixDelete(int ROWS, double **matrix)
{
	for (int i = 0; i < ROWS; i++)
		free(matrix[i]);
	free(matrix);
}

void rowsSwitch(int ROWS, int COLS, double **matrix, int fromrow, int torow)
{
	if (CheckRowsAndColsInput(ROWS, COLS, fromrow, 0) && CheckRowsAndColsInput(ROWS, COLS, torow, 0))
	{
		int *temp = (double *)malloc(sizeof(double) * COLS);
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

void rowsMultiply(int ROWS, int COLS, double **matrix, int row, double num, char mod)
{
	if (CheckRowsAndColsInput(ROWS, COLS, row, 0))
	{
		if (num != 0)
		{
			for (int i = 0; i < COLS; i++)
				matrix[row][i] = mod == '*' ? (num * matrix[row][i]) : (matrix[row][i] / num);
		}
		else
			printf("ОШИБКА: множитель не может быть равен 0\n");
	}
	else
		printf("ОШИБКА: обращение к несуществующей строке\n");
}

void rowPLusRowXnumber(int ROWS, int COLS, double **matrix, int secondrow, double num, int firstrow, char mod)
{
	if (CheckRowsAndColsInput(ROWS, COLS, firstrow, 0) && CheckRowsAndColsInput(ROWS, COLS, secondrow, 0))
	{
		if (num != 0)
		{
			for (int i = 0; i < COLS; i++)
				matrix[firstrow][i] += mod == '*' ? (matrix[secondrow][i] * num) : (matrix[secondrow][i] / num);
		}
		else
			printf("ОШИБКА: множитель не может быть равен 0\n");
	}
	else
		printf("ОШИБКА: обращение к несуществующей строке\n");
}

double **matrixTranspose(int *ROWS, int *COLS, double **matrix)
{
	double **newmatrix = matrixCreate(*COLS, *ROWS);

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

void matrixMultiplyByNumber(int ROWS, int COLS, double **matrix, double num, char mod)
{
	if (num != 0)
	{
		for (int row = 0; row < ROWS; row++)
			for (int col = 0; col < COLS; col++)
				matrix[row][col] = mod == '*' ? (num * matrix[row][col]) : (matrix[row][col] / num);
	}
	else
		printf("ОШИБКА: множитель не может быть равен 0\n");
}

void matrixPlusMatrix(int ROWS, int COLS, double **matrix)
{
	double x;
	printf("Заполните матрицу с которой выполнится сложение\n");
	for (int row = 0; row < ROWS; row++)
	{
		printf("-Строка №%d-\n", row + 1);
		for (int col = 0; col < COLS; col++)
		{
			printf("Элемент №%d = ", col + 1), scanf("%lf", &x);
			matrix[row][col] += x;
		}
	}
}

void matrixChangeSigns(int ROWS, int COLS, double **matrix)
{
	for (int row = 0; row < ROWS; row++)
		for (int col = 0; col < COLS; col++)
			matrix[row][col] = -matrix[row][col];
}

void matrixRedactElem(int ROWS, int COLS, double **matrix, int ROW, int COL, double num)
{
	if (CheckRowsAndColsInput(ROWS, COLS, ROW, COL))
		matrix[ROW][COL] = num;
	else
		printf("ОШИБКА: обращение к несуществующему элементу\n");
}

double **matrixMultiply(int leftROWS, int *COLS, double **leftmatrix)
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
	double **rightmatrix = matrixCreate(rightROWS, rightCOLS);
	matrixFill(rightROWS, rightCOLS, rightmatrix);

	matrixPrint(leftROWS, *COLS, leftmatrix);
	printf("\t\tX\n");
	matrixPrint(rightROWS, rightCOLS, rightmatrix);
	printf("\t\t=\n");

	double **resultmatrix = matrixCreate(leftROWS, rightCOLS);
	double c = 0;
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
	{
		printf("строка: %d из %d , столбец: %d из %d\n", r, ROWS, c, COLS);
		return 0;
	}
	else
		return 1;
}