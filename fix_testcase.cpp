#include<bits/stdc++.h>

using namespace std;
int main(){
    string D[1005];
    int p[1005], n;
    ifstream in;
    ofstream out;
    for(int i=1;i<=101;i++){
    	in.open(to_string(i)+".in");
    	in >> n;
        for(int j=0;j<n;j++)
            in >> D[j] >> p[j];
    	in.close();
    	out.open(to_string(i)+".in");
        out << n << endl;
        for(int j=0;j<n;j++)
            out << D[j] << " " << p[j]-1 << endl;
    	out.close();
    }
    cout << "Done";
    system("pause");
    return 0;
}
