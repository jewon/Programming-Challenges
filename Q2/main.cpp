#include <iostream>
using namespace std;

char bomb(char ** s, int nn, int mm);

int main()
{
	//Question num.2
	
	/*
	input :
	4 4
	*...
	....
	.*..
	*/
	int n, m; //n행 m열 지뢰밭
	int field = 1;
	char ** space;
	
	while (1)
	{

		n = 0; m = 0; space = NULL;

		cin >> n >> m;

		space = new char * [n+2]; //n개의 줄 동적할당

		for (int a = 0; a < n+2; a++)
		{
			space[a] = new char[m+2];//a번째 줄에 m개 동적할당
		}

		for (int j = 0; j < m + 2; j++)// 모든 배열요소 '.'으로 리셋
		{
			for (int k = 0; k < m + 2; k++)
				space[j][k] = '.';
		}

		for (int b = 1; b < n+1; b++)//n행까지 b행에 한줄씩 입력받음
		{
			for (int c = 1; c < m+1; c++)
				cin >> space[b][c];
		}

		cout << "Field #" << field << " : " << endl;

		for (int x = 1; x < n+1; x++)
		{
			for (int y = 1; y < m+1; y++)
				cout << bomb(space, x, y) << " ";
			cout << endl;
		}

		for (int c = 0; c < n; c++)
			delete[] space[c];
		delete[] space;

		field++;
	}

}

char bomb(char ** s, int nn, int mm)//s[nn][mm]주변 폭탄 갯수 추출
{
	int counter = 0; //폭탄갯수 저장

	if (s[nn][mm] == '*')//자신이 폭탄이면 -1 리턴함
		return '*';

	if (s[nn - 1][mm - 1] == '*')
		counter++;

	if (s[nn - 1][mm] == '*')
		counter++;

	if (s[nn - 1][mm + 1] == '*')
		counter++;

	if (s[nn + 1][mm - 1] == '*')
		counter++;

	if (s[nn + 1][mm] == '*')
		counter++;

	if (s[nn + 1][mm + 1] == '*')
		counter++;

	if (s[nn][mm - 1] == '*')
		counter++;

	if (s[nn][mm + 1] == '*')
		counter++;

	return counter + '0';
}