#include<iostream>
#include<cstring>
#include<climits>
using namespace std;
int n,c[21][21],mint=INT_MAX,v[21];
void dfs(int dep,int sumt){
    if(dep>n&&sumt<mint){
        mint=sumt;
        return;
    }
    if(sumt>sumt) return;
    for(int i=1;i<=n;i++){
        if(!v[i]&&c[i][dep]+sumt<mint){
            v[i]=1;
            dfs(dep+1,c[i][dep]+sumt);
            v[i]=0;
        }
    }
    return;
}
int main(){
    memset(v,0,sizeof(v));
    memset(c,0,sizeof(c));
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>c[i][j];
        }
    }
    dfs(1,0);
    cout<<mint;
    return 0;
}