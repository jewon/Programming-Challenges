#include <iostream>
using namespace std;

void aInit(char(*a)[10]);
bool checkmate(const char(*a)[10], bool iswhite, bool * isempty);
bool checkq(const char(*a)[10], int k_x, int k_y, bool iswhite);
bool checkp(const char(*a)[10], int k_x, int k_y, bool iswhite);
bool checkcross(const char(*a)[10], int k_x, int k_y, bool iswhite, char chkwhat);
bool checkdiag(const char(*a)[10], int k_x, int k_y, bool iswhite, char chkwhat);
bool checkn(const char(*a)[10], int k_x, int k_y, bool iswhite);

int main()
{
	int game = 1;
	char a[10][10];
	aInit(a);
	bool isempty = false;
	
	while (1)
	{
		//2차원 배열로 입력받음
		for (int i = 1; i < 9; i++)
			cin >> a[i];

		if (checkmate(a, false, &isempty))
			cout << endl << "Game #" << game << ": black king is in check.";
		else if (checkmate(a, true, &isempty))
			cout << endl << "Game #" << game << ": white king is in check.";
		else if (isempty)
			break;
		else cout << endl << "Game #" << game << ": no king is  in check";

		game++;

		aInit(a);
		cout << endl;
	}

	system("pause");
	return 0;
}

void aInit (char (*a)[10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			a[i][j] = NULL;
}

//킹의 입장에서 체크가 있나 하나씩 검사하는 함수 만들기
bool checkmate(const char(*a)[10], bool iswhite, bool * isempty) 
{
	int k_x = 0, k_y = 0;
	
	//킹찾기
	for (int i = 1; i < 9; i++)
		for (int j = 1; j < 9; j++)
		{
			if (a[i][j] == (char)('k' - (iswhite * 32)))
			{
				k_x = j;
				k_y = i;
				break;
			}
		}

	if (k_x && k_y)
		return (checkq(a, k_x, k_y, iswhite) || checkp(a, k_x, k_y, iswhite) || checkcross(a, k_x, k_y, iswhite, 'R')
			|| checkdiag(a, k_x, k_y, iswhite, 'B') || checkn(a, k_x, k_y, iswhite));
	//퀸, 폰, 룩, 비숍, 나이트 순서대로 검사
	
	else cout << "Can't find king! : code " << k_x << k_y << endl;
	*isempty = true;
	return false;
}

bool checkq(const char(*a)[10], int k_x, int k_y, bool iswhite)
{
	return (checkcross(a, k_x, k_y, iswhite, 'Q') || checkdiag(a, k_x, k_y, iswhite, 'Q'));
}

bool checkp(const char(*a)[10], int k_x, int k_y, bool iswhite)
{
	return (a[k_y - 1 + iswhite * 2][k_x - 1] == (char)((int)'P' + (iswhite * 32))
		|| a[k_y - 1 + iswhite * 2][k_x + 1] == (char)((int)'P' + (iswhite * 32)));
	//킹의 윈쪽 위(또는 아래)에 폰이 있는 경우 or
	//킹의 오른쪽 위(또는 아래)에 폰이 있는 경우 TRUE 반환
}

bool checkcross(const char(*a)[10], int k_x, int k_y, bool iswhite, char chkwhat)
{//상하좌우에 chkwhat이 있나 검사, 빈 칸은 무시, chkwhat은 체크 할 말의 대문자
	for (int i = 1; k_x + i < 9; i++)
	{// 킹 오른쪽 chkwhat 있는지 검사
		if (a[k_y][k_x + i] == '.')
			continue;
		else if (a[k_y][k_x + i] == (char)((int)chkwhat + (iswhite) * 32))
			return 1;
	}

	for (int i = 1; k_x - i > 0; i++)
	{// 킹 왼쪽에 chkwhat 있는지 검사
		if (a[k_y][k_x - i] == '.')
			continue;
		else if (a[k_y][k_x - i] == (char)((int)chkwhat + (iswhite) * 32))
			return 1;
	}

	for (int i = 1; k_y + i < 9; i++)
	{// 킹 위쪽에 chkwhat 있는지 검사
		if (a[k_y + i][k_x] == '.')
			continue;
		else if (a[k_y + i][k_x] == (char)((int)chkwhat + (iswhite) * 32))
			return 1;
	}

	for (int i = 1; k_y - i > 0; i++)
	{// 킹 왼쪽에 chkwhat 있는지 검사
		if (a[k_y - i][k_x] == '.')
			continue;
		else if (a[k_y - i][k_x] == (char)((int)chkwhat + (iswhite) * 32))
			return 1;
	}

	return 0; // 체크 상태 없음
}

bool checkdiag(const char(*a)[10], int k_x, int k_y, bool iswhite, char chkwhat)
{//대각선 검사
	for (int i = 1; k_x + i < 9 || k_y + i < 9; i++)
	{// 킹 오른쪽 위에 chkwhat 있는지 검사
		if (a[k_y + i][k_x + i] == '.')
			continue;
		else if (a[k_y + i][k_x + i] == (char)((int)chkwhat + (iswhite) * 32))
			return 1;
	}

	for (int i = 1; k_x - i > 0 || k_y + i < 9; i++)
	{// 킹 왼쪽 위에 chkwhat 있는지 검사
		if (a[k_y + i][k_x - i] == '.')
			continue;
		else if (a[k_y + i][k_x - i] == (char)((int)chkwhat + (iswhite) * 32))
			return 1;
	}

	for (int i = 1; k_x + i < 9 || k_y - i > 0; i++)
	{// 킹 오른쪽 아래에 chkwhat 있는지 검사
		if (a[k_y - i][k_x + i] == '.')
			continue;
		else if (a[k_y - i][k_x + i] == (char)((int)chkwhat + (iswhite) * 32))
			return 1;
	}

	for (int i = 1; k_x - i > 0 || k_y - i > 0; i++)
	{// 킹 왼쪽 아래에 chkwhat 있는지 검사
		if (a[k_y - i][k_x - i] == '.')
			continue;
		else if (a[k_y - i][k_x - i] == (char)((int)chkwhat + (iswhite) * 32))
			return 1;
	}

	return 0; // 체크 상태 없음
}

bool checkn(const char(*a)[10], int k_x, int k_y, bool iswhite)
{//나이트의 체크 자리 8자리 검사
	if (k_y < 8 && (a[k_y + 2][k_x + 1] == (char)((int)'N' + (iswhite) * 32)))
		return 1;

	else if (k_y < 8 && (a[k_y + 2][k_x - 1] == (char)((int)'N' + (iswhite) * 32)))
		return 1;

	else if (k_y > 1 && (a[k_y - 2][k_x + 1] == (char)((int)'N' + (iswhite) * 32)))
		return 1;

	else if (k_y > 1 && (a[k_y - 2][k_x - 1] == (char)((int)'N' + (iswhite) * 32)))
		return 1;

	else if (k_x < 8 && (a[k_y + 1][k_x + 2] == (char)((int)'N' + (iswhite) * 32)))
		return 1;

	else if (k_x > 1 && (a[k_y + 1][k_x - 2] == (char)((int)'N' + (iswhite) * 32)))
		return 1;

	else if (k_x < 8 && (a[k_y - 1][k_x + 2] == (char)((int)'N' + (iswhite) * 32)))
		return 1;

	else if (k_x > 1 && (a[k_y - 1][k_x - 2] == (char)((int)'N' + (iswhite) * 32)))
		return 1;

	else return 0;
}

