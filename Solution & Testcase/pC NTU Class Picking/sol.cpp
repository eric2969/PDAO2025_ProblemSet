#include <iostream>
#include <map>
#define IOS ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define endl '\n'
using namespace std;

const int MAXN = 1e6 + 5;

bool a[MAXN] = {0};

int main(){
    IOS;
    int n;
    int sum = 0;
    cin >> n;
    for(int i=0; i<n; i++){
        char cmd;
        int tar;
        cin >> cmd >> tar;
        if(cmd == 'I'){
            int i;
            sum++;
            for(i=tar-1;i<MAXN && a[i]!=0;i++){
                sum++;
            } 
            a[i] = 1;
        }
        else if(cmd == 'D'){
            a[tar-1] = 0;
            sum++;
        }
        else return 1;
    }
    cout << sum << endl;
    return 0;
}