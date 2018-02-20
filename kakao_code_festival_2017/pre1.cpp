#include <iostream>
#include <vector>

using namespace std;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector< vector <int> > picture)
{
	int number_of_area = 0;
	int max_size_of_one_area = 0;

	//area와 area 크기 저장할 벡터 선언, area[0]는 색칠되지 않은 곳이다.
	vector <int> areas;
	areas.push_back(0);
	//area의 번호를 저장해 둘 m*n 사이즈 판(?) 선언
	//vector< vector <int> > picture_a(m, vector<int>(n, NULL));
	vector<vector<int> > picture_a;
	for (int i = 0; i < m; i++)
	{
		vector<int> element;
		element.resize(n);
		for (int j = 0; j < n; j++)
			element[j] = 0;
		picture_a.push_back(element);
	}


	//area의 매기는 번호 저장해 둘 변수
	int area_n = 0;

	 for (int tm = 0; tm < m; tm++)
		 for (int tn = 0; tn < n; tn++)
		 {
			 int color = picture[tm][tn];

			 if (color == 0)
				 continue;

			 //위, 왼쪽 picture 검사해서 같은 색깔이면 해당하는 area 번호를 똑같이 매겨준다. 
			 //상
			 else if (tm > 0 && picture[tm - 1][tn] == color)
				 picture_a[tm][tn] = picture_a[tm - 1][tn];

			 //좌
			 else if (tn > 0 && picture[tm][tn - 1] == color)
				 picture_a[tm][tn] = picture_a[tm][tn - 1];
			 
			 //위, 왼쪽에 모두 같은 색이 없었으면 새로운 색을 할당한다. 1행 1열도 이 경우에 포함된다.
			 else
			 {
				 area_n++;
				 picture_a[tm][tn] = area_n;
				 areas.push_back(0);
			 }

			 //해당 영역 번호의 영역 크기를 1 증가시킴
			 areas[picture_a[tm][tn]]++;
		 }

	 //area 수 구하기
	 number_of_area = area_n;

	 //max_area 면적 구하기
	 for (int i = 1; i <= area_n; i++)
		 if (areas[i] > max_size_of_one_area)
			 max_size_of_one_area = areas[i];
		 
	vector<int> answer(2);
	answer[0] = number_of_area;
	answer[1] = max_size_of_one_area;
	return answer;
}

int main()
{
	vector<vector<int> > picture;
	{
		vector<int> element;
		element.resize(4);
		picture.push_back(element);
	}

	picture = { { 1, 1, 1, 0 },{ 1, 2, 2, 0 },{ 1, 0, 0, 1 },{ 0, 0, 0, 1 },{ 0, 0, 0, 3 },{ 0, 0, 0, 3 } };

	vector<int> answer = solution(6, 4, picture);
	cout << answer[0] << endl;
	cout << answer[1] << endl;

	system("pause");
	return 0;
}