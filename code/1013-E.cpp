#include<iostream>
#include<cstring>
using namespace std;
int k,l,a[105][105],b[105];
long long maxn,minn,ans=0;
int dfs(int dep, int j){
    if(a[dep][j]>0){
        return a[dep][j];
    }
    int t = 0;
    if(dep==1){
        t = 1;
    }
    else{
        t = 0;
    }
    for (int i = t; i < k; ++i){
        if(b[dep-1])
            ;
    }
}
int main()
{
    memset(a,0,sizeof(a));
    memset(b, 0, sizeof(b));
    cin>>k>>l;
    for (int i = 0; i < k; ++i){
        a[1][i] = 1;
    }
    dfs(1, 0);
    cout<<ans;
    system("pause");
    return 0;
}