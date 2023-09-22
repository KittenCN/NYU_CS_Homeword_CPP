#include<iostream>
#include<cstring>
using namespace std;
int main(){
	int sumdays = 0;
	int Y, M, D;
	cin >> Y >> M >> D;
	for(int i = 1; i <= M - 1; ++i){
		if(i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12){
			sumdays = sumdays + 31;
		}
		else if(i == 4 || i == 6 || i == 9 || i == 11){
			sumdays = sumdays + 30;
		}
		else{
			if((Y % 100 != 0 && Y % 4 == 0) || (Y % 100 == 0 && Y % 4 == 0 && Y % 400 == 0)){
				sumdays = sumdays + 29;
			}
			else{
				sumdays = sumdays + 28;
			}
		}
	}
	sumdays = sumdays + D;
	cout << sumdays;
    system("pause");
    return 0;
}