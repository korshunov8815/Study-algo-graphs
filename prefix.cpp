//
// Created by korshunov on 14.05.15.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


int main() {
    ifstream in("prefix.in");
    ofstream of("prefix.out");
    string input;
    in >> input;

    int n = input.length();
    vector<int> pi (n);
    for (int i=1; i<n; i++) {
        int j = pi[i-1];
        while (j > 0 && input[i] != input[j])
            j = pi[j-1];
        if (input[i] == input[j])  j++;
        pi[i] = j;
    }

    for (int i=0; i<pi.size(); i++)
        of << pi[i] <<" ";


}
