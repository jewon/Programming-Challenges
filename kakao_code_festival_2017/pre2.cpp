#include<iostream>
#include<vector>
using namespace std;

int solution(int m, int n, vector<vector<int> > city_map);

const int MOD = 20170805;

int main()
{
	vector<vector<int> > city_map;

	vector<int> element(6, 0);
	for (int i = 0; i < 3; i++)
		city_map.push_back(element);

	int arr[3][6] = { {0, 2, 0, 0, 0, 2},{0, 0, 2, 0, 1, 0},{1, 0, 0, 2, 2, 0} };
	
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 6; j++)
		{
			city_map[i][j] = arr[i][j];
			cout << city_map[i][j];
		}

	cout << endl;
	int answer = solution(3, 6, city_map);

	cout << answer;
	system("pause");
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int m, int n, vector<vector<int> > city_map) {
	vector<vector<int> > routesV;
	vector<int> elementV(n + 1, 0);
	for (int i = 0; i < m + 1; i++)
		routesV.push_back(elementV);

	vector<vector<int> > routesH;
	vector<int> elementH(n + 1, 0);
	for (int i = 0; i < m + 1; i++)
		routesH.push_back(elementH);

	routesH[1][0] = 1;
	for (int i = 1; i < m + 1; i++)
	{
		for (int j = 1; j < n + 1; j++)
		{
			if (city_map[i-1][j-1] == 1)
				continue;

			else if (city_map[i-1][j-1] == 0)
			{
				routesV[i][j] = routesV[i - 1][j] + routesH[i][j - 1];
				routesH[i][j] = routesV[i][j];
			}

			else if (city_map[i-1][j-1] == 2)
			{
				routesV[i][j] = routesV[i - 1][j];
				routesH[i][j] = routesH[i][j - 1];
			}
		}
	}

	return routesH[m][n];
}

/*
도시 중심가의 지도는 m × n 크기의 격자 모양 배열 city_map으로 주어진다. 자동차는 오른쪽 또는 아래 방향으로 한 칸씩 이동 가능하다.

city_map[i][j]에는 도로의 상황을 나타내는 값이 저장되어 있다.

0인 경우에는 자동차가 자유롭게 지나갈 수 있다.
1인 경우에는 자동차 통행이 금지되어 지나갈 수 없다.
2인 경우는 보행자 안전을 위해 좌회전이나 우회전이 금지된다. (왼쪽에서 오던 차는 오른쪽으로만, 위에서 오던 차는 아래쪽으로만 진행 가능하다)
*/