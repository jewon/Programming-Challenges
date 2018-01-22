#include<iostream>
using namespace std;

int overfifty(int * result, int cand, int vote_s);
int openvote(int ** vote, int cand, int vote_s);
int * countvote(int cand, int vote_s, int ** vote, bool * fail);
void whofail(int cand, int * result, bool * fail);

int main()
{
	int numCase;
	cin >> numCase;
	

	for (int i = 0; i < numCase; i++)
	{
		//***투표
		char temp[40];
		for (int i = 0; i < 40; i++)
			temp[i] = NULL;
		int cand = 0;

		cin >> cand;

		char(*candName)[80] = new char[cand][80];
		//후보 수만큼 80자씩 후보이름 메모리 동적할당

		for (int i = 0; i < cand; i++)
			cin >> candName[i];
		//후보 수만큼 후보이름 입력받음

		int * vote[1000];//vote는 투표결과를 저장할 포인터
		for (int i = 0; i < 1000; i++)
			vote[i] = NULL;

		int vote_s = 0; //총 투표지 수를 저장할 변수

		cin.ignore();
		while (1)
		{
			cin.getline(temp, 40);

			if (temp[0] == 0)
				break;

			else
			{
				//투표지 만들고 입력받음
				vote[vote_s] = new int[cand];
				for (int i = 0; i < cand; i++)
					vote[vote_s][i] = temp[2 * i] - 48;
				vote_s++;
			}

			//투표수가 1000개넘어가면 중단
			if (vote_s >= 1000)
				break;
		}

		//개표
		int elec = openvote(vote, cand, vote_s);
		if (elec + 1)
			cout << candName[elec] << endl;
		else cout << elec << "multiple cand got same votes" << endl;
	}

	system("pause");
	return 0;
}

int openvote(int ** vote, int cand, int vote_s)
{//vote 투표지들을 개표해서 result에 집계하는 함수로 경선결과를 elec을 반환함

	//탈락했으면 true를 저장하는 후보 갯수만큼의 bool배열
	bool * fail = new bool[cand];
	for (int i = 0; i < cand; i++)
		fail[i] = false;

	while(1)
	{
		//집계
		int * result = countvote(cand, vote_s, vote, fail);

		//모두탈락하는 경우 = 후보들이 동률인 경우 : 개표종료
		for (int i = 0; i < cand; i++)
			if (!(fail[i]))
				break;
			else if (i == cand - 1)
				return -1;

		//50퍼 이상 후보 있는지 검사해서 있으면 선출끝
		int elec = overfifty(result, cand, vote_s);
		if (elec + 1)
			return elec;

		//50퍼 이상 후보 없으면 탈락시킬 후보 추가함
		whofail(cand, result, fail);
	}
}

int overfifty(int * result, int cand, int vote_s)
{//50퍼 넘는 후보 있으면 해당후보 배열번호를, 없으면 -1 반환
	for (int i = 0; i < cand; i++)
		if (result[i] > vote_s * 0.5)
			return i;
	return -1;
}

int * countvote(int cand, int vote_s, int ** vote, bool * fail)
{
	//반환할 결과 저장할 변수
	int * result = new int [cand];
	for (int i = 0; i < cand; i++)
		result[i] = 0;

	//한 표씩 개표
	for (int i = 0; i < vote_s; i++)
	{
		for (int r = 0; r < cand; r++)
			if (fail[vote[i][r]]) //r순위 후보가 탈락자면 다음 순위로
				continue;
			else
			{//탈락자 아니면 result에 반영하고 break
				result[vote[i][r] - 1]++; 
				break;
			}
	}
	return result;
}

void whofail(int cand, int * result, bool * fail)
{
	//가장 낮은 득표수를 저장할 fff변수
	int fff;
	for (int i = 0; i < cand; i++)
		if (!fail[i])
		{
			fff = result[i];
			break;
		}

	//가장 낮은 득표수를 찾는다
	for (int i = 0; i < cand; i++)
		if (!fail[i] && fff < result[i])
			fff = result[i];

	//가장 낮은 득표수를 가진 후보들을 반복문으로 찾아 탈락시킴
	for (int i = 0; i < cand; i++)
		if (result[i] == fff)
			fail[i] = true;
}


