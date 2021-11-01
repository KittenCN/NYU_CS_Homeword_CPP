#include<iostream>
#include<cstring>
using namespace std;
int r,c,n,nx[105],ny[105],m[55][55];
void pt(){
    cout<<"2:"<<endl;
    for(int i=1;i<=r;++i){
        for(int j=1;j<=c;++j){
            cout<<m[i][j]<<' ';
        }
        cout<<endl;
    }
    cout<<"-------------"<<endl;
    return;
}
bool check(){
    for(int i=1;i<=n;++i){
        //cout<<"|||||"<<nx[i]<<' '<<ny[i]<<' '<<m[nx[i]][ny[i]]<<endl;
        if(m[nx[i]][ny[i]]){
            int f=0,x=nx[i],y=ny[i];
            //cout<<"ck:"<<x<<' '<<y<<endl;
            while(--x&&x>0){
                //cout<<"ck-1:"<<x<<' '<<y<<' '<<m[x][y]<<endl;
                if(m[x][y]>0){
                    ++f;
                    break;
                }
            }
            //cout<<"i:"<<i<<' '<<f<<endl;
            x=nx[i],y=ny[i];
            while(++y&&y<=c){
                //cout<<"ck+1:"<<x<<' '<<y<<' '<<m[x][y]<<endl;
                if(m[x][y]>0){
                    ++f;
                    break;
                }
            }
            //cout<<"ii:"<<i<<' '<<f<<endl;
            if(f>=2) {
                return 0;
            }
        }
    }
    return 1;
}
void dfs(int dep,int s){
    if(dep>n){
        cout<<-1;
        exit(0);
    }
    if(dep!=1&&check()){
        cout<<1<<endl;
        cout<<dep-1;
        exit(0);
    }
    //cout<<"B:"<<dep<<' '<<s<<endl;
    if(s==1) return;
    if(m[nx[dep]][ny[dep]]){
        m[nx[dep]][ny[dep]]=0;
        //cout<<"--------------------"<<endl;
        //cout<<"dfs+:"<<nx[dep]<<' '<<ny[dep]<<' '<<m[nx[dep]][ny[dep]]<<endl;
        dfs(dep+1,s+1);
        //cout<<"dfs-:"<<nx[dep]<<' '<<ny[dep]<<' '<<m[nx[dep]][ny[dep]]<<endl;
        m[nx[dep]][ny[dep]]=1;
        dfs(dep+1,s);
    }
    else dfs(dep+1,s);
    return;
}
int main(){
    //freopen("outfile.out","w",stdout);
    //freopen("infile.in","r",stdin);
    memset(nx,0,sizeof(nx));
    memset(ny,0,sizeof(ny));
    memset(m,0,sizeof(m));
    cin>>r>>c;
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>nx[i]>>ny[i];
        m[nx[i]][ny[i]]=1; 
    }
    if(check()) cout<<0;
    else dfs(1,0);
    return 0;
}