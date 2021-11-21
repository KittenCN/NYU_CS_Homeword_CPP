#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
#include<iomanip>
#include<climits>
using namespace std;
int a[1005],t,n,ans=0;
int main()
{
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>n;
        memset(a,1,sizeof(a));
        for(int j=1;j<=n;j++){
            cin>>a[j];
        }
        for(int j=1;j<=n-1;j++)
            for(int k=n;k>=j+1;k--)
                if(a[k]<a[k-1]){
                    swap(a[k],a[k-1]);
                }
        while(n>=4){
            if(a[2]+a[2]<a[n-1]+a[1]){
                ans+=a[2]+a[1]+a[n]+a[2];
                n-=2;
            } 
            else{
                ans+=a[1]+a[n];
                n--;
            } 
        } 
        if(n==1) ans+=a[1];
        if(n==2) ans+=a[2];
        if(n==3) ans+=a[2]+a[1]+a[3];
        cout<<ans<<endl;
        ans=0;
    }
    system("pause");
    return 0;
}