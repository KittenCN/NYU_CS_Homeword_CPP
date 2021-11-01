#include <cstdio>
#include <cstring>
#include <iostream>
#define N 100001
char s[N];
using namespace std;
int main(){
    while ( ~scanf("%s",s)){
        int len=strlen(s);
        int flag=0,i;
        for(i=len/2-1;i>=0;--i){
            if(s[i]>s[len-1-i]){flag=1;break;}
            else if(s[i]<s[len-1-i]){ flag=-1;break;}
        }
        if(flag!=1){//前半串要加1
            //s[(len-1)/2]++;
            for(i=(len-1)/2;i>=0;--i){//199 191 999
                s[i]++;
                if(s[i]>'9'){
                    s[i]='0';
                }else break;
            }
            if(s[0]=='0'){//999 9999
                s[0]='1';
                len++;
                s[len/2]='0';
            }
        }
        for(i=0;i<len/2;++i)
            printf("%c",s[i]);
        for(i=(len+1)/2-1;i>=0;--i)
            printf("%c",s[i]);
        printf("\n");
    }
    system("pause");
    return 0;
}