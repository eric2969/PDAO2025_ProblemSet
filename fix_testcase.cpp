#include<bits/stdc++.h>

using namespace std;
int main(){
    int a, b;
    ifstream in;
    ofstream out;
    for(int i=1;i<=100;i++){
    	in.open(to_string(i)+".out");
    	in >> a;
    	in.close();
    	out.open(to_string(i)+".out");
    	out << a-1 << endl;
    	out.close();
    }
    cout << "Done";
    system("pause");
    return 0;
}
