#include<iostream>
#include<iomanip>
#include<algorithm>
using namespace std;
int n, l[105], ans[105], v[105];
void dfs(int dep){
    if(dep == n){
        for(int i = 0; i < n; i++)
            cout << ans[i] << " ";
        cout << endl;
        return;
    }
    for (int i = 0; i < n; i++){
        if(v[i]) continue;
        ans[dep] = l[i];
        v[i] = 1;
        dfs(dep + 1);
        v[i] = 0;
    }
        return;
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> l[i];
    }
    sort(l, l + n);
    memset(ans, 0, sizeof(ans));
    memset(v, 0, sizeof(v));
    dfs(0);
    system("pause");
    return 0;
}