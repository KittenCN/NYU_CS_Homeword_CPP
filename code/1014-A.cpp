#include<iostream>
#include<cstring>
using namespace std;
int n, m, pn[505], pm[505][505], ansn[505], cntn = 0, anspn[505], sumpn = 0, cntpn = 0, v[505];
int maxn = 0, maxpn = 0, maxan[505], maxapn[505];
void dfs(int dep){
    if(cntn > maxn){
        maxn = cntn;
        memcpy(maxan, ansn, sizeof(ansn));
    }
    if(sumpn > maxpn){
        maxpn = sumpn;
        memcpy(maxapn, anspn, sizeof(anspn));
    }
//    if(!v[dep] && !dep){
//       v[dep] = 1;
//        ansn[++cntn] = dep;
//        anspn[++cntpn] = pn[dep];
//        sumpn += pn[dep];
//    }
    for (int i = dep; i <= n; ++i){
        if(pm[dep][i]&&!v[i]){
            v[i] = 1;
            ansn[++cntn] = i;
            anspn[++cntpn] = pn[i];
            sumpn += pn[i];
            dfs(i);
            --cntn;
            --cntpn;
            v[i] = 0;
            sumpn -= pn[i];
        }
    }
    return;
}
int main(){
    memset(pn, 0, sizeof(pn));
    memset(pm, 0, sizeof(pm));
    memset(ansn, 0, sizeof(ansn));
    memset(anspn, 0, sizeof(anspn));
    memset(v, 0, sizeof(v));
    cin >> n >> m;
    for (int i = 1; i <= n; ++i){
        cin >> pn[i];
        pm[0][i] = 1;
        pm[i][0] = 1;
    }
    for (int i = 1; i <= m; ++i){
        int x, y;
        cin >> x >> y;
    }
    v[0] = 1;
    dfs(0);
    for (int i = 1; i <= maxn; ++i){
        cout << ansn[i] << ' ';
    }
    cout << endl;
    for (int i = 1; i <= maxpn; ++i){
        cout << anspn[i] << ' ';
    }
    system("pause");
    return 1;
}