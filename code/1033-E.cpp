#include<iostream>
#include<cstring>
using namespace std;
int n, m, f[100005], a[100005];
int main(){
    cin >> n >> m;
    memset(f, 0, sizeof(f));
    memset(a, 0, sizeof(a));
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        f[a[i]] = 1;
    }
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){
            if(i >= a[j] && f[i - a[j]] > 0 && (f[i - a[j]] + 1 < f[i] || f[i] == 0)){
                f[i] = f[i - a[j]] + 1;
            }
        }
    }
    if(f[m] > 0) cout << f[m] << endl;
    else {
        for (int i = m - 1; i >= 1; i--){
            if(f[i] > 0) {
                cout << m - i << endl;
                break;
            }
        }
    }
    system("pause");
    return 0;
}