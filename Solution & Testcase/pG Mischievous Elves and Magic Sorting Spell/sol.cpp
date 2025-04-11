#include<iostream>
#include<vector>
#define IOS ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define endl '\n'
using namespace std ;

int main(){
    IOS;
    int maxId=0, minId=0 ;
    int element=0 ;
    cin >> element;
    vector<int> nums ;
    while(cin>>element){
        nums.push_back(element) ;
    }
    
    if(!nums.empty()){
        maxId=0, minId=0 ;
    }

    for(int i=0; i<nums.size(); i++){
        if(nums[maxId] <= nums[i]) maxId = i ;
        if(nums[minId] > nums[i]) minId = i ; 
    }

    if(minId > maxId) cout << minId-maxId+nums.size()-2 ;
    else cout << minId-maxId+nums.size()-1 ;

    return 0 ;
}
