#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
long long n,c,wi[1005],v[1005],cnt=0,sumw[1005];
void pt(){
    for(int i=1;i<=n;++i){
        if(v[i]==1) cout<<wi[i]<<' ';
    }
    cout<<endl;
}
bool cmp(int a,int b){
    return a>b;
}
void dfs(int dep,int sw){
    if(sw>cnt&&sw<=c){
        cnt=sw;
    }
    if(sw>c||dep>n||sw+(sumw[n]-sumw[dep-1])<=cnt){
        return;
    }
    if(!v[dep]||sw+wi[dep]<=c){
        v[dep]=1;
        dfs(dep+1,sw+wi[dep]);
        v[dep]=0;
        dfs(dep+1,sw);
    }
    else dfs(dep+1,sw);
    return;
}
int main(){
    //freopen("outfile.out","w",stdout);
    //freopen("infile.in","r",stdin);
    memset(wi,0,sizeof(wi));
    memset(v,0,sizeof(v));
    memset(sumw,0,sizeof(sumw));
    cin>>n>>c;
    for(int i=1;i<=n;++i){
        cin>>wi[i];
        sumw[i]=sumw[i-1]+wi[i];
    }
    sort(wi+1,wi+n+1,cmp);
    if(sumw[n]>c) dfs(1,0);
    else cnt=sumw[n];
    cout<<cnt;
    return 0;
}
 