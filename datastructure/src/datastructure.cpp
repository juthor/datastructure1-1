//============================================================================
// Name        : datastructure.cpp
// Author      : Hyunju Kim
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>//1번 전기세 확인
using namespace std;

int electricCharge(int month, int khw);//함수 원형 정의

int main()
{
	int month, kwh;
	cout<<"해당하는 month와 전기 사용량을 입력하세요 : ";
	cin>>month>>kwh;

	cout<<endl<<"전기요금 : "<<electricCharge(month, kwh);//월과 kwh 입력, 함수에 입력

	return 0;
}

int electricCharge(int month, int khw)
{
	int ele_total, temp, use_el, sum=0, gi, gi_na, sum_na;
	//기본요금, 사용량요금, 합, 기반기금, 기반기금 나머지, 합계 나머지
	float bu;//부가가치세

	//기본요금측정
	if(khw<401)//두 번째 범위가 첫번째까지 포함하므로
	{
		if(khw<401 && khw>200)//만약 두 번째 구간에 해당한다면
		{
			ele_total=1600;//기본요금 201~400khw 사용했으므로 1600 부과
		}
		else//아니면 첫 번째 구간
		{
			ele_total=910;//기본요금 200khw보다 작거나 같이 사용했으므로 910 부과
		}
	}
	else//그게 아니면 세 번째 범위에 해당
	{
		ele_total=7300;//기본요금 401khw초과 사용했으므로 7300 부과
	}



	//사용량요금
	if((month>6 && month<9) || (month<3 && month>0) || month==12)
	{//슈퍼유저요금 동하계, 7~8월, 12월~2월
		if(khw<201)//만약 첫 번째 구간에 해당한다면
		{
			use_el=khw*93.3;//200보다 작게 쓴 거니까 입력값과 범위값 계산
		}
		else if(khw>200 && khw<401)//만약 두 번째 구간에 해당한다면
		{
			use_el=200*93.3;//사용량요금=첫 번째 구간의 최대제한범위 값 계산
			khw=khw-200;//첫 번째 구간에 해당하므로 khw에 구간의 최대제한범위 값 200 빼줌
			use_el+=khw*187.9;//빼준 나머지 khw와 두 번째 구간에 해당하는 범위 값을 더해줌
		}
		else if(khw>400 && khw<1001)//만약 세 번째 구간에 해당한다면
		{
			use_el=200*93.3;//사용량요금=첫 번째 구간의 최대제한범위 값 계산
			khw=khw-200;//첫 번째 구간에 해당하므로 khw에 구간의 최대제한범위 값 200 빼줌
			use_el+=200*187.9;//사용량요금=두 번째 구간의 최대제한범위 값 계산후 더해줌
			khw=khw-200;//두 번째 구간에 해당하므로 khw에 구간의 최대제한범위 값 200 빼줌
			use_el+=khw*280.6;//빼준 나머지 khw와 세 번째 구간에 해당하는 범위 값을 더해줌
		}
		else//그게 아니면 슈퍼유저요금으로 네 번째 범위에 해당
		{
			use_el=200*93.3;//사용량요금=첫 번째 구간의 최대제한범위 값 계산
			khw=khw-200;//첫 번째 구간에 해당하므로 khw에 구간의 최대제한범위 값 200 빼줌
			use_el+=200*187.9;
			khw=khw-200;//두 번째 구간에 해당하므로 khw에 구간의 최대제한범위 값 200 빼줌
			use_el+=600*280.6;
			khw=khw-600;//세 번째 구간에 해당하므로 khw에 구간의 최대제한범위 값 600 빼줌
			use_el+=khw*709.5;
		}
	}
	else//그냥 달
	{
		if(khw<201)
		{
			use_el=khw*93.3;//200보다 작게 쓴 거니까 입력값과 범위값 계산
		}
		else if(khw<401)
		{
			use_el=200*93.3;
			khw=khw-200;//첫 번째 구간에 해당하므로 khw에 구간의 최대제한범위 값 200 빼줌
			use_el+=khw*187.9;
		}
		else
		{
			use_el=200*93.3;
			khw=khw-200;//첫 번째 구간에 해당하므로 khw에 구간의 최대제한범위 값 200 빼줌
			use_el+=200*187.9;
			khw=khw-200;//두 번째 구간에 해당하므로 khw에 구간의 최대제한범위 값 200 빼줌
			use_el+=khw*280.6;
		}
	}


	sum=(int)ele_total+(int)use_el;//전기요금=기본요금+사용량요금, 원단위 미만 절사
	//세금
	bu=sum*0.1;//부가가치세=전기요금계의 10%, 원 단위 미만 반올림
	gi=sum*0.037;//전력산업기반기금=전기요금계의 3.7%, 10원 미만 절사


	//기반요금은 10원미만 절사
	gi_na=gi%10;//1의 자리를 알기 위해 gi%10계산
	gi=gi-gi_na;//gi는 gi-gi_na로, 1의자리수를 뺀 값


	temp=bu;//부가가치세 정수부분
	float temp_fra=bu;//부가가치세 소수부분

	int bu_real;//정수 부가가치세 구한것
	temp_fra=temp_fra-temp;//실수-정수, 소수부분 나옴

	if(temp_fra>0 && temp_fra<0.5)//부가가치 나머지가 10보다 작으면
	{
		bu_real=bu-temp_fra;//소수부분 제거, 반올림 안함
	}
	else
	{
		bu_real=bu+1-temp_fra;//반올림 함
	}

	sum=sum+gi+bu_real;//청구요금계는 기본요금+전력량요금+부가세+기반요금, 위에서 전기요금을 계산했음
	sum_na=sum%10;//청구요금계는 10원미만 절사, 1의 자리 수를 알기 위해 %10을함

	sum=sum-sum_na;//청구요금계는 sum-1의 자리수를 한 값

	return sum;
}
