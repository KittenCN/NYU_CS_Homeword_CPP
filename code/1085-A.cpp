#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
#include<iomanip>
#include<climits>
using namespace std;
long long m,n,r,a,bi[100005];
double ans = -1.0, ti;
int main(){
	cin>>m>>n>>r;
	cin>>a;
	a*=1024;
	m*=60;
	for(int i=1;i<=n;++i) {
		cin>>bi[i];
		bi[i]+=r;
		ti=(a*1.0)/(bi[i]*1.0);
		if(ti>ans) ans=ti;
	}
	if(ans>m) cout<<"xi wen le jian";
	else cout<<fixed<<setprecision(2)<<ans;
    system("pause");
    return 0;
}