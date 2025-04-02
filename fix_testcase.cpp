#include<bits/stdc++.h>

using namespace std;
int main(){
    int a, b;
    ifstream in;
    ofstream out;
    for(int i=1;i<=102;i++){
    	in.open(to_string(i)+".out");
    	in >> a >> b;
    	in.close();
    	out.open(to_string(i)+".out");
    	out << a-1 << " " << b-1 << endl;
    	out.close();
    }
    cout << "Done";
    system("pause");
    return 0;
}
