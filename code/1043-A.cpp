#include<iostream>
#include<cstring>
using namespace std;
char tochar(int asc){
    return char(asc);
}
int main(){
    int n;
    int cr[1005];
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> cr[i];
    }
    for(int i = 0; i < n; i++){
        if(cr[i] == ' '){
            cout << " ";
        }
        else{
            cout << tochar(cr[i]);
        }
    }
    system("pause");
    return 0;
}