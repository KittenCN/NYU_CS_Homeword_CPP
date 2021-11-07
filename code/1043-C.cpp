#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
string check()
{

    int a[3], b[3];
    for (int i = 0; i < 3; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < 3; i++)
    {
        cin >> b[i];
    }
    for (int i = 0; i < 3; i++)
    {
        if (a[i] > b[i])
        {
            return "First";
        }
        else if (a[i] < b[i])
        {
            return "Second";
        }
    }
    return "Same";
}
int main(){
    int n;
    cin >> n;
    getchar();
    for (int i = 0; i < n; i++){
        cout << check() << endl;
    }
    system("pause");
    return 0;
}