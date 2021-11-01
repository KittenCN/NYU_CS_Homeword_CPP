#include<iostream>
#include<cstring>
using namespace std;
int n,cnt=0,fp[1001]={6,2,5,5,4,5,6,3,7,6},ans[4];
void dfs(int dep,int cp){
    for(int i=0;i<=999;++i){
        if(dep+fp[i]<=n){
            ans[cp]=i;
            dep+=fp[i];
            if(cp==3){
                if(ans[1]+ans[2]==ans[3]&&dep==n){
                    //cout<<ans[1]<<' '<<ans[2]<<' '<<ans[3]<<' '<<dep<<endl;
                    ++cnt;
                }
            }
            else dfs(dep,cp+1);
            dep-=fp[i];
        }
    }
}
int main(){
    //freopen("outfile.out","w",stdout);
    //freopen("infile.in","r",stdin);
    memset(ans,0,sizeof(ans));
    cin>>n;
    n-=4;
    for(int i=10;i<=999;++i){
        fp[i]=fp[i/10]+fp[i%10];
    }
    dfs(0,1);
    cout<<cnt;
    return 0;
}