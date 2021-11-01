#include<iostream>
#include<iomanip>
using namespace std;
int main(){
    int n;
    while(cin>>n){
        if(n==0) {break;}
        if(n<=4) {cout<<10<<endl; continue;}
        double ans=n/8*18; n%=8;
        if(n!=0){
            if(n<=4){
                ans+=n*2.4;
                if((int)ans-ans==0) {printf("%d\n",ans);}
                else{printf("%.1f\n",ans);}
                continue;
            }
            else{
                cout<<ans+10+(n-4)*2<<endl;
                continue;
            }
        }
        if((int)ans-ans==0) {printf("%d\n",ans);}
                else{printf("%.1f\n",ans);}
    }
    system("pause");
    return 0;
}