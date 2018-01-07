#include<iostream>
using namespace std;

int main()
{
	int s;
	char n[9]; // s는 크기, n은 출력할 숫자
	int line = 0;
	char numcode[10][8] =
	{
		"-|| ||-", "  |  | ", "- |-| -", "- |- |-", " ||- | ",
		"-| - |-", "-| -||-", "- |  | ", "-||-||-", "-||- |-"
	}; // numcode[x]는 x의 7자리 숫자 코드 abcdefg

	while (1)
	{
		s = 0;
		for (int i = 0; i < 9; i++) // 숫자 배열 초기화
			n[i] = NULL;


		cin >> s >> n;
		if (!s & !n) // s=n=0이면 프로그램 종료
			break;

		line = 1;
		for (int loc = 0; n[loc] != NULL; loc++)
		{
			cout << " "; // 1행 첫열 공백
			for (int i = 0; i < s; i++)// a
				cout << numcode[n[loc]-48][0];
			cout << " "; //1행 마지막열 공백
			cout << " "; //한 자리 끝남 공백
		}
		cout << endl;
		line++; // A부분 끝

		for (; line < s + 2; line++) // 가온데 행 전까지 행마다 출력
		{
			for (int loc = 0; n[loc] != NULL; loc++) // 출력할 숫자들 읽기
			{
				cout << numcode[n[loc]-48][1];// b
				for (int i = 0; i < s; i++)
					cout << " ";// 8의 위쪽 동그라미 안부분 고정공백 s개
				cout << numcode[n[loc] - 48][2];// c
				cout << " "; // 한 자리 끝남 공백
			}
			cout << endl; // 줄바꾸고 line에 1 더함
		} // B부분 끝

		for (int loc = 0; n[loc] != NULL; loc++)
		{
			cout << " "; // 중간행 첫열 공백
			for (int i = 0; i < s; i++)// d
				cout << numcode[n[loc] - 48][3];
			cout << " "; //중간행 마지막열 공백
			cout << " "; //한 자리 끝남 공백
		}
		cout << endl;
		line++; // C부분 끝

		for (; line < (2 * s + 3); line++) // 마지막 행 전까지 행마다 출력
		{
			for (int loc = 0; n[loc] != NULL; loc++) // 출력할 숫자들 읽기
			{
				cout << numcode[n[loc] - 48][4];// e
				for (int i = 0; i < s; i++)
					cout << " ";// 8의 아래쪽 동그라미 안부분 고정공백 s개
				cout << numcode[n[loc] - 48][5];// f
				cout << " "; //한 자리 끝남 공백
			}
			cout << endl; // 줄바꿈
		} // D부분 끝
		
		for (int loc = 0; n[loc] != NULL; loc++)
		{
			cout << " "; // 막행 첫열 공백
			for (int i = 0; i < s; i++)
				cout << numcode[n[loc] - 48][6];//g
			cout << " "; //1행 마지막열 공백
			cout << " "; //한 자리 끝남 공백
		}
		cout << endl;
		line++; // E부분 끝
	}

	system("pause");

	return 0;
}