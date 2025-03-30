#include <string>
#include <iostream>
#include <unordered_map>
#include <map>
#include <stack>
#include <cctype>

using namespace std;

class Solution {
private:
    int ind = 0; // index will point to the character that we are currently parsing

public:
    // Compare two formulas to check if they have the same atomic composition
    bool compare(string f1, string f2) {
        ind = 0;
        unordered_map<string, int> map1 = parseformula(f1);
        ind = 0;
        unordered_map<string, int> map2 = parseformula(f2);

        return map1 == map2; 
    }

private:
    // Recursively parse the formula
    unordered_map<string, int> parseformula(string& f) {
        unordered_map<string, int> currMap;
        string currAtom;
        string currCnt;

        while (ind < f.length()) {
            if (isupper(f[ind])) { // Uppercase letter: New element
                if (!currAtom.empty()) {
                    currMap[currAtom] += (currCnt.empty() ? 1 : stoi(currCnt));
                }
                currAtom = f[ind++];
                currCnt = "";
                if(ind < f.length() && islower(f[ind])) // if lowercases followed by uppercase, then it is a new element with two characters
                    currAtom += f[ind++];
            }
            else if (isdigit(f[ind])) { // Digit: Atomic count
                currCnt += f[ind];
                ind++;
            }
            else if (f[ind] == '(') { // Left parenthesis: Enter recursion
                ind++;
                unordered_map<string, int> nestedMap = parseformula(f);
                for (auto& pair : nestedMap) {
                    currMap[pair.first] += pair.second;
                }
            }
            else if (f[ind] == ')') { // Right parenthesis: Exit recursion
                if (!currAtom.empty()) {
                    currMap[currAtom] += (currCnt.empty() ? 1 : stoi(currCnt));
                }
                ind++;
                string multiplier;
                while (ind < f.length() && isdigit(f[ind])) {
                    multiplier += f[ind++];
                }
                if (!multiplier.empty()) {
                    for (auto& pair : currMap) {
                        currMap[pair.first] *= stoi(multiplier);
                    }
                }
                return currMap;
            }
        }

        if (!currAtom.empty()) { // save the last atom's count
            currMap[currAtom] += (currCnt.empty() ? 1 : stoi(currCnt));
        }
        return currMap;
    }
};

int main() {
    int n1, n2;
    cin >> n1 >> n2; // Read the number of elements in each formula
    string f1, f2;
    cin >> f1 >> f2; 

    Solution sol;
    if (sol.compare(f1, f2))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    return 0;
}
