#include <iostream>
#include <cstring>
using namespace std;
int li[5][15],ans[5];
bool check(){
    for (int i = 1; i <= 3; ++i){
        ans[i] = 0;
        for (int j = 1; j <= 10; ++j){
            if(li[i][j] == li[0][j]){
                ans[i] += 10;
            }
        }
        if(ans[i] != li[i][11]){
            return 0;
        }
    }
        return 1;
}
void dfs(int dep){
    if(dep > 10 && check()){
        int sa = 0;
        for (int i = 1; i <= 10; ++i){
            if(li[4][i] == li[0][i]){
                sa += 10;
            }
        }
        cout << sa;
        system("pause");
        exit(0);
    }
    else if(dep > 10 && !check())
        return;
    else{
        li[0][dep] = 0;
        dfs(dep + 1);
        li[0][dep] = 1;
        dfs(dep + 1);
    }
    return;
}
int main(){
    memset(li, 0, sizeof(li));
    memset(ans, 0, sizeof(ans));
    for (int i = 1; i <= 4; ++i){
        for (int j = 1; j <= 11; ++j){
            if(i == 4 && j == 11)
                break;
            cin >> li[i][j];
        }
    }
    dfs(1);
    return 0;
}