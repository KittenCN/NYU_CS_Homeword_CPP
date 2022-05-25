#include<iostream>
#include<cstring>
using namespace std;
int main(){
    int n, m, p = 0;
    cin >> n;
    while (cin >> m && m != -1)
    {
        p++;
        if (m == n){
            cout << p;
            return 0;
        }
        /* code */
    }
    cout << -1;
    system("pause");
    return 0;
}