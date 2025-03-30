#include <vector>
#include <algorithm>
#include <set>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cctype>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream studentInput, solution;
    
    studentInput.open(argv[2]);
    solution.open(argv[3]);

    for (int i = 0; i < 2; i++) {
        string studentLine, solutionLine;
        getline(studentInput, studentLine);
        getline(solution, solutionLine);

        if (solutionLine == "no channels" && studentLine == "no channels") {
            continue;
        } else if (solutionLine == "no channels" || studentLine == "no channels") {
            return 0;
        }

        stringstream studentStream(studentLine), solutionStream(solutionLine);
        set<int> studentEdges, solutionEdges;

        int studentEdge, solutionEdge;
        while (studentStream >> studentEdge) {
            studentEdges.insert(studentEdge);
        }
        while (solutionStream >> solutionEdge) {
            solutionEdges.insert(solutionEdge);
        }

        if (studentEdges != solutionEdges) {
            return 0;
        }
    }

    return 1;
}