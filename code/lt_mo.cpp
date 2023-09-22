#include<iostream>
#include<cstring>
using namespace std;

int e[1005], ne[1005], head = 0, idx = 1;

void insert_head(int x) {
    e[idx] = x;
    ne[idx] = head;	
    head = idx;		
    idx++;
}

void insert(int k, int x) {
    e[idx] = x;
    ne[idx] = ne[k];
    ne[k] = idx++;
}

void remove(int k) {
    ne[k] = ne[ne[k]];	
}

int main(){
    int num;
    while(cin >> num && num != -1){
        insert_head(num);
    }
    for(int i = head; i != 0; i = ne[i]){
        cout << e[i] << " ";
    }
    system("pause");
    return 0;
}