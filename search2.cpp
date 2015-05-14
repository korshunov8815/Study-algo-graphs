//
// Created by korshunov on 14.05.15.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


int main() {
    ifstream in("search2.in");
    ofstream of("search2.out");
    vector<int> answ;
    string p,t;
    in >> p >> t;
    int pl = p.length();

    const int val = 31;
    vector<long long> val_pow (max (p.length(), t.length()));
    val_pow[0] = 1;
    for (int i=1; i<val_pow.size(); i++)
        val_pow[i] = val_pow[i-1] * val;

    // hash of p
    long long hash_p = 0;
    for (int i=0; i<p.length(); i++)
        hash_p += (p[i] - 'a' + 1) * val_pow[i];

    //hash of t prefixes
    vector<long long> hash (t.length());
    for (int i=0; i<t.length(); i++)
    {
        hash[i] = (t[i] - 'a' + 1) * val_pow[i];
        if (i)  hash[i] += hash[i-1];
    }

    // find
    for (int i = 0; i + p.length() - 1 < t.length(); i++) {
        long long cur_hash = hash[i + p.length() - 1];
        if (i) cur_hash -= hash[i - 1];
        if (cur_hash == hash_p * val_pow[i]) {
            if (p[0]==t[i] && p[pl/2]==t[i+pl/2] && p[pl-1]==t[i+pl-1])
                answ.push_back(i+1);
        }
    }


    of << answ.size() << endl;
    for (int i=0; i<answ.size();i++)
        of << answ[i] << " ";

    return 0;
}