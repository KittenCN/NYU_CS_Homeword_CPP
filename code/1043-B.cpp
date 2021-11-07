#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
double anv(string st){
    double sum = 0;
    double cnt = 0;
    for (unsigned int i = 0; i < st.size(); i++){
        if(st[i] != ' '){
            switch (st[i]){
                case 'A':
                    sum += 4;
                    cnt++;
                    break;
                case 'B':
                    sum += 3;
                    cnt++;
                    break;
                case 'C':
                    sum += 2;
                    cnt++;
                    break;
                case 'D':
                    sum += 1;
                    cnt++;
                    break;
                case 'F':
                    sum += 0;
                    cnt++;
                    break;
                default:
                    return -1;
            }
        }
    }
    return sum / cnt;
}
int main(){
    string st;
    while(getline(cin, st)){
        if(anv(st) == -1){
            cout << "Unknown" << endl;
        }
        else cout << fixed << setprecision(2) << anv(st) << endl;
    }
    return 0;
}