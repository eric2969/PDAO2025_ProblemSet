#include <iostream>

using namespace std;

int cntry[10000+5][2] = {};

signed main() {
    int n, max_people = 0, min_day = 0, min_ctry = -1;
    int days;
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> cntry[i][0] >> cntry[i][1];

    
    for (int i = 0; i < n; i++) {
        days = cntry[i][1] + (cntry[i][0] != cntry[i][1]);
        if(min_ctry == -1 || days < min_day || (days == min_day && cntry[i][0] > max_people)) {
            max_people = cntry[i][0];
            min_day = days;
            min_ctry = i;
        }
    }

    cout << min_ctry << endl;

    return 0;
}