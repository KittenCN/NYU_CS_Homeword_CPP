#include<iostream>
#include<string.h>
using namespace std;
int n, num[505][505], val[505][505], vis[505], ans[505];
void dfs(int dep){
    if(dep > n){
        for(int i = 1; i <= n; i++) {
            cout << ans[i] << endl;
        }
        system("pause");
        exit(0);
    }
    for(int i = 1; i <= n; i++){
        if(!vis[num[dep][i]] && val[dep][i]){
            vis[num[dep][i]] = 1;
            ans[dep] = num[dep][i];
            dfs(dep + 1);
            vis[num[dep][i]] = 0;
        }
    }
    return;
}
int main(){
    memset(num, 0, sizeof(num));
    memset(vis, 0, sizeof(vis));
    memset(ans, 0, sizeof(ans));
    memset(val, 0, sizeof(val));
    cin >> n;
    for (int i = 1; i <= n; i++){        
        for (int j = 1; j <= n; j++)
            cin >> num[i][j];
        for (int j = 1; j <= n; ++j){
            if(num[i][j] == i){
                val[i][j] = 1;
                break;
            }
            else{
                val[i][j] = 1;
            }
        }
    }
    dfs(1);
    system("pause");
    return 0;
}