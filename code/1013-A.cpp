#include<iostream>
#include<cstring>
using namespace std;
int n,c,s[7001],v[7001],ans[7001],sums[7001];
bool pflag=false;
void dfs(int dep,int sump){
    if(dep>n||sump>c||(c-sump)>(sums[n]-sump)) return;
    if(dep<=n&&sump==c){
        pflag=true;
        for(int i=1;i<dep;i++) cout<<ans[i]<<' ';
        exit(0);
    }
    for(int i=1;i<=n;i++){
        if(!v[i]&&(s[i]+sump<=c)){
            v[i]=1;
            ans[dep]=s[i];
            dfs(dep+1,s[i]+sump);
            v[i]=0;
        }
    }
    return;
}
int main(){
    //freopen("outfile.out","w",stdout);
    //freopen("infile.in","r",stdin);
    cin>>n>>c;
    memset(s,0,sizeof(s));
    memset(v,0,sizeof(v));
    memset(ans,0,sizeof(ans));
    memset(sums,0,sizeof(sums));
    for(int i=1;i<=n;i++){
        cin>>s[i];
        sums[i]=sums[i-1]+s[i];
    }
    dfs(1,0);
    if(!pflag) cout<<"No Solution!";
    return 0;
}