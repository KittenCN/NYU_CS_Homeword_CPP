#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
int T,n; 
struct wood{
    int l,w;
    };
bool cmp(struct wood w1,struct wood w2){
    if(w1.l<w2.l) {return true;}
    if(w1.l==w2.l&&w1.w<=w2.w) {return false;} 
    return false; 
}
int find(struct wood a[]){
	int ans[5001];
	memset(ans,0,sizeof(ans));
    int cnt=0,p;
    ans[1] = 1;
    for (int j = 2; j <= n; j++){
        p = 0;
        for (int k = 1; k < j; k++){
            if(a[j].w < a[k].w && p < ans[k]){
                p = ans[k];
            }
            ans[j] = p + 1;
        }
    }
    for (int l = 1; l <= n; l++){
           if(ans[l] > cnt){
            cnt = ans[l];
        }
    }
	return cnt;
}
int main(){
	wood a[5001];
	scanf("%d",&T);
    for(int m=1;m<=T;m++){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) {
			scanf("%d %d",&a[i].l,&a[i].w);
		}
    	sort(a+1,a+n+1,cmp);
		printf("%d\r\n",find(a));
	}
    system("pause");
    return 0;
}