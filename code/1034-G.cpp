#include<iostream>
#include<cstring>
using namespace std;
int n, q[11][11], ans[11][11], st[105][3], cnt = 0;
int mx[9] = {0,1,1,0,-1,-1,-1,0,1};
int my[9] = {0,0,1,1,1,0,-1,-1,-1};
void pt(int step){
    for (int i = 1; i <= step; ++i){
        cout << '(' << st[i][1] << ',' << st[i][2] << ')';
        if(i!=step)
            cout << "-->";
    }
    cout << endl;
    return;
}
void dfs(int x, int y, int step){
    if(x == 1 && y == n){
        ++cnt;
        //pt(step);
        return;
    }
    if (x < 1 || y < 1 || x > n || y > n || q[x][y]){
        return;
    }
    for (int i = 1; i <= 8; ++i){
        //cout << x << ' ' << y << ' ' << i << ' ' << (x + mx[i] > 0 && x + mx[i] <= n && y + my[i] > 0 && y + my[i] <= n && !q[x + mx[i]][y + my[i]] && !ans[x + mx[i]][y + my[i]]) << endl;
        if(x + mx[i] > 0 && x + mx[i] <= n && y + my[i] > 0 && y + my[i] <= n && !q[x + mx[i]][y + my[i]] && !ans[x + mx[i]][y + my[i]]){
            //cout << x << ' ' << y << ' ' << i << endl;
            //cout << x + mx[i] << ' ' << y + my[i] << endl;
            ans[x + mx[i]][y + my[i]] = 1;
            st[step + 1][1] = x + mx[i];
            st[step + 1][2] = y + my[i];
            dfs(x + mx[i], y + my[i], step + 1);
            ans[x + mx[i]][y + my[i]] = 0;
        }
    }
    return;
}
int main(){
    memset(q, 0, sizeof(q));
    memset(ans, 0, sizeof(ans));
    memset(st, 0, sizeof(st));
    cin >> n;
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= n; ++j){
            cin >> q[i][j];
        }
    }
    st[1][1] = 1;
    st[1][2] = 1;
    ans[1][1] = 1;
    dfs(1, 1, 1);
    cout << cnt;
    system("pause");
    return 0;
}