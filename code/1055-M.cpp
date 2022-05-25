#include<iostream>
#include<cstring>
#include<math.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    for(int i = 1; i <= sqrt(n); ++i){
        if (n % i == 0){
            cout << n << '=' << i << '*' << n / i << endl;
        }
    }
    system("pause");
    return 0;
}
