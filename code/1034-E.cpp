#include <iostream>
using namespace std;
int n, cnt = 0;
string cr;
bool judge(){
    for (int i = 0; i < n - 3; ++i){
        string s1 = "";
        string s2 = "";
        s1 += cr[i];
        s1 += cr[i + 1];
        s2 += cr[i + 2];
        s2 += cr[i + 3];
        if(s1 == s2)
            return 0;
    }
        return 1;
}
void dfs(int dep){
    if(dep == n){
        if(judge()){       
            ++cnt;
        }
        return;
    }
    cr[dep] = 'A';
    dfs(dep + 1);
    cr[dep] = 'B';
    dfs(dep + 1);
    cr[dep] = 'C';
    dfs(dep + 1);
    return;
}
int main(){
    cin >> n;
    dfs(0);
    cout << cnt;
    system("pause");
    return 0;
}