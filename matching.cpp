#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>


using namespace std;

int n, k,m;
vector < vector<int> > g;
vector<int> mt;
vector<char> used;

bool try_kuhn (int v) {
    if (used[v]) return false;
    used[v] = true;
    for (int i=0; i<g[v].size(); i++) {
        int to = g[v][i];
        if (mt[to] == -1 || try_kuhn (mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

int main() {
    ifstream in("matching.in");
    ofstream of("matching.out");

    in >> n >> k >> m;
    int tmp1, tmp2, res;
    res=0;
    g.resize(n);

    for (int i=0; i < m ; i++) {
        in >> tmp1 >> tmp2;
        g[--tmp1].push_back(--tmp2);
    }

    mt.assign(k,-1);
    for (int v=0; v<n; v++) {
        used.assign (n, false);
        if (try_kuhn (v)) res++;
    }

    of << res;



    return 0;
}

