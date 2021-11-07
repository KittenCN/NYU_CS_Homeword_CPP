#include<iostream>
#include<iomanip>
#include<algorithm>
struct node
{
    int l;
    int m;
};
node tt[105];
using namespace std;
bool cmp(node a,node b)
{
    return a.l < b.l && a.m < b.m;
}
int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> tt[i].l >> tt[i].m;
    }
    sort(tt, tt + n, cmp);
    for(int i = 0; i < n; i++){
        cout << tt[i].l << " " << tt[i].m << endl;
    }
    system("pause");
    return 0;
}