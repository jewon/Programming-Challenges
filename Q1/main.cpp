#include<iostream>
using namespace std;

int cycleLength(int w);

int main()
{
	cout << "Hello World!" << endl;

	//입력 (i, j)
	//반복연산 결과를 저장할 변수 선언
	//싸이클 길이를 구하는 함수를 i부터 1씩 증가시키며 n까지 반복
		//i의 홀짝 판별
		//홀짝에 따른 연산
		//결과 저장
	//최대 싸이클 길이 출력

	int i = 0, j = 0;
	
	while (i >= 0)
	{
		while (1)
		{
			cin >> i >> j;
			if (i * j)
				break;
			cout << "Input Error!" << endl;
		}	
		int ii = i;
		int jj = j;
		if (ii > jj)//i>j의 경우로 입력되었으면 바꿔주어야 함
		{
			int temp = ii;
			ii = jj;
			jj = temp;
		}
		int maxCycle = 0;
		while (ii < jj)
		{
			if (cycleLength(ii) > maxCycle)
				maxCycle = cycleLength(ii);
			ii++;
		}

		cout << i << " " << j << " " << maxCycle << endl;
	}

	system("pause");
	return 0;
}

int cycleLength(int i)
{
	int w = i;
	int length = 1;
	while (w != 1)
	{
		if (w % 2)
			w = 3 * w + 1;
		else
			w = w / 2;
		length++;
	}
	return length;
}