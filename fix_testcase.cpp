#include<bits/stdc++.h>

using namespace std;
int main(){
    ifstream in;
    ofstream out;
    for(int i=1;i<=90;i++){
    	in.open(to_string(i)+".out");
            int a,b;
    	in >> a >> b;
    	in.close();
    	out.open(to_string(i)+".out");
    	cout << a-1 << " " << b-1 << endl;
    	out.close();
    }
    cout << "Done";

}
