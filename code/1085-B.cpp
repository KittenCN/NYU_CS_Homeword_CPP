#include<cstdio>
#include<algorithm>
const int N=50+10;
const int inf=0x3f3f3f3f;
 
int n,a[N][N];
int sum[N][N];
int f[N][N];
bool cal[N][N];
 
void read()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&a[i][j]);
}
 
int walk(int x,int y)
{
    if(x==n)
    {
        int lmax,rmax,res=0;
        lmax=rmax=a[x][y];
        int l=y,r=y;
        while(l>1)
        {
            l--;
            lmax=std::max(lmax,sum[x][y]-sum[x][l-1]);
        }
        while(r<n)
        {
            r++;
            rmax=std::max(rmax,sum[x][r]-sum[x][y-1]);
        }
        res=lmax+rmax-a[x][y];
        //printf("%d %d : %d\n",x,y,res);
        return res;
    }
    if(cal[x][y]) return f[x][y];
    f[x][y]=-inf; cal[x][y]=1;
    for(int m=1;m<=n;m++)
    {
        int tmp=walk(x+1,m);
        int l=y,r=y;
        if(l>m) l=m; else if(r<m) r=m;
        int lmax=sum[x][m]-sum[x][l-1];
        int rmax=sum[x][r]-sum[x][m-1];
        while(l>1)
        {
            l--;
            lmax=std::max(lmax,sum[x][m]-sum[x][l-1]);
        }
        while(r<n)
        {
            r++;
            rmax=std::max(rmax,sum[x][r]-sum[x][m-1]);
        }
        int res=lmax+rmax-a[x][m];
        f[x][y]=std::max(f[x][y],res+tmp);
        //printf("(%d,%d) : lmax=%d   rmax=%d   res=%d   f[x][y]=%d\n",x,y,lmax,rmax,res,f[x][y]);
    }
    return f[x][y];
}
 
void work()
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            sum[i][j]=sum[i][j-1]+a[i][j];
    int res=-inf;
    for(int i=1;i<=n;i++) res=std::max(res,walk(1,i));
    printf("%d",res);
}
 
int main()
{
    //freopen("dog.in","r",stdin);
    //freopen("dog.out","w",stdout);
    read();
    work();
    system("pause");
    return 0;
}