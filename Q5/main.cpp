#include <iostream>
using namespace std;

const int SIZE = 252; 
// x, y는 1~250의 범위를 갖는다
// 모든 모서리에 한 줄씩 NULL을 요소로 갖는 boundary 설정

void arrInit(char(*arr)[SIZE]);
void iFunc(int m, int n, char(*arr)[SIZE]);
void cFunc(int m, int n, char(*arr)[SIZE], char c);
void lFunc(int x, int y, char c, char(*arr)[SIZE]);
void vFunc(int x, int y1, int y2, char c, char(*arr)[SIZE]);
void hFunc(int x1, int x2, int y, char c, char(*arr)[SIZE]);
void kFunc(int x1, int x2, int y1, int y2, char c, char(*arr)[SIZE]);
void fFunc(int x, int y, char c, char(*arr)[SIZE]);
void sFunc(char* name, int m, int n, char(*arr)[SIZE]);
void fill(int x, int y, char bc, char c, char(*arr)[SIZE]);
void color(int tempX, int tempY, char bc, char c, char(*arr)[SIZE]);

int main()
{
	char arr[SIZE][SIZE]; // 배열 생성
	arrInit(arr);

	char order = NULL;
	int sizeX = 0, sizeY = 0;

	while (order != 'X')
	{ // 명령 선택기
		cin >> order;

		if (order == 'I')
		{
			cin >> sizeX >> sizeY;
			iFunc(sizeX, sizeY, arr);
		}

		if (order == 'C')
		{
			char c = NULL;
			cin >> c;
			cFunc(sizeX, sizeY, arr, c);
		}

		if (order == 'L')
		{
			int x = 0, y = 0;
			char c = NULL;
			cin >> x >> y >> c;
			lFunc(x, y, c, arr);
		}

		if (order == 'V')
		{
			int x = 0, y1 = 0, y2 = 0;
			char c = NULL;
			cin >> x >> y1 >> y2 >> c;
			vFunc(x, y1, y2, c, arr);
		}

		if (order == 'H')
		{
			int x1 = 0, x2 = 0, y = 0;
			char c = NULL;
			cin >> x1 >> x2 >> y >> c;
			hFunc(x1, x2, y, c, arr);
		}

		if (order == 'K')
		{
			int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
			char c = NULL;
			cin >> x1 >> y1 >> x2 >> y2 >> c;
			kFunc(x1, x2, y1, y2, c, arr);
		}

		if (order == 'F')
		{
			int x = 0, y = 0;
			char c = NULL;
			cin >> x >> y >> c;
			fFunc(x, y, c, arr);
		}

		if (order == 'S')
		{
			char name[10];
			cin >> name;
			sFunc(name, sizeX, sizeY, arr);
		}

		if (order == 'X')
			break;
	}

	return 0;
}

void arrInit(char (*arr)[SIZE]) // 배열 모든요소 NULL로 초기화
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			arr[i][j] = NULL;
}

void iFunc(int m, int n, char(*arr)[SIZE]) // 배열 초기화 후 m, n 인자로 cFunc 호출
{
	arrInit(arr);
	cFunc(m, n, arr, 'O');
}

void cFunc (int m, int n, char(*arr)[SIZE], char c) // m*n 행들을 모두 O(white)으로
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			arr[i][j] = c;
}

void lFunc (int x, int y, char c, char(*arr)[SIZE]) // x, y 픽셀을 c로 칠하기
{
	arr[y][x] = c;
}

void vFunc(int x, int y1, int y2, char c, char(*arr)[SIZE]) // x열의 y1행~y2행까지 c로 칠하기
{
	for (int i = y1; i <= y2; i++)
		arr[i][x] = c;
}

void hFunc(int x1, int x2, int y, char c, char(*arr)[SIZE]) // y행의 x1열~x2열까지 c로 칠하기
{
	for (int i = x1; i <= x2; i++)
		arr[y][i] = c;
}

void kFunc(int x1, int x2, int y1, int y2, char c, char(*arr)[SIZE]) // x1~x2, y1~y2 직사각형 c로 칠하기
{
	for (int i = x1; i <= x2; i++)
		for (int j = y1; j <= y2; j++)
			arr[j][i] = c;
}

void fFunc(int x, int y, char c, char(*arr)[SIZE]) // x, y기준으로 c로 색 채우기
{
	char bc = arr[y][x]; // (x, y)의 색깔 bc에 저장
	arr[y][x] = c;
	fill(x, y, bc, c, arr);
}

void sFunc(char* name, int m, int n, char(*arr)[SIZE]) // 파일명 name과 m*n 사이즈의 전체 배열요소를 출력
{
	cout << name << ".bmp" << endl;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
			cout << arr[i][j];
		cout << endl;
	}
}

void fill(int x, int y, char bc, char c, char(*arr)[SIZE])
// x, y 기준으로 시계방향(위-오른-아래-왼)으로 돌면서 color를 호출시킨다
{
	int tempX = x, tempY = y - 1; // 한 칸 위 픽셀
	color(tempX, tempY, bc, c, arr);

	tempX = x + 1, tempY = y; // 한 칸 오른쪽 픽셀
	color(tempX, tempY, bc, c, arr);

	tempX = x, tempY = y + 1; // 한 칸 아래 픽셀
	color(tempX, tempY, bc, c, arr);

	tempX = x - 1, tempY = y; // 한 칸 왼쪽 픽셀
	color(tempX, tempY, bc, c, arr);
}

void color(int tempX, int tempY, char bc, char c, char(*arr)[SIZE])
// tempX, tempY가 bc와 같은색이면 c로 칠하고, fill을 호출해 tempX, tempY를 기준으로 다시 시계방향으로 돌린다(재귀)
{
	if (arr[tempY][tempX] == bc) // bc와 현재 픽셀이 같은색인지 검사
	{
		arr[tempY][tempX] = c; // 같으면 c로 색 바꾸고
		fill(tempX, tempY, bc, c, arr); // 현재 픽셀을 기준으로 fill 호출해 시계방향으로 다시 돌리기
	}
}