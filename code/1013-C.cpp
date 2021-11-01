#include<iostream>
#include<climits>
#include<cstring>
#include<algorithm>
using namespace std;
int n,k,t[21],v[21],mint=INT_MAX,tp[21];
bool cmp(int a,int b){
    return a>b;
}
void dfs(int dep,int sumt){
    if(dep>n&&sumt<mint){
        mint=sumt;
        return;
    }
    if(sumt>=mint) return;
    for(int i=1;i<=k;i++){
        if(!v[dep]&&tp[i]+t[dep]<mint){
            v[dep]=1;
            tp[i]+=t[dep];
            //cout<<sumt<<' '<<tp[i]<<endl;
            dfs(dep+1,max(sumt,tp[i]));
            tp[i]-=t[dep];
            v[dep]=0;
        }
    }
    return;
}
int main(){
    memset(v,0,sizeof(v));
    memset(tp,0,sizeof(tp));
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>t[i];
    }
    sort(t+1,t+n+1,cmp);
    dfs(1,0);
    cout<<mint;
    system("pause");
    return 0;
}