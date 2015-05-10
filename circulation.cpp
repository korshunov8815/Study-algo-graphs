//
// Created by korshunov on 09.05.15.
//


#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <climits>
#include <algorithm>
#include <queue>

using namespace std;


int main() {
    ifstream in("circulation.in");
    ofstream of("circulation.out");

    int n,m;
    in >> n >> m;
    int from, to, mincap, cap;
    vector< vector<long long int> > f(n+2, vector<long long int>(n+2));
    vector< vector<long long int> > c(n+2, vector<long long int>(n+2));
    vector <pair<int,pair<int,int> > > edges;

    for (int i=0; i < m ; i++) {
        in >> from >> to >> mincap >> cap;
        c[0][to] +=mincap;
        c[from][to] += cap-mincap;
        c[from][n+1] += mincap;
        edges.push_back(make_pair(mincap,make_pair(from,to)));
    }
    n=n+2;
    long long int flow = 0;
    queue<int> q;
    vector<bool> used;
    vector<int> p;
    vector<int> path;

    while(1) {
        //bfs is Gs
        q.push(0);
        used.assign(n,false);
        p.assign(n,-1);
        used[0] = true;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int i = 0; i < c[v].size(); i++) {
                if (used[i]==false && c[v][i]-f[v][i]>0) {
                    q.push(i);
                    used[i] = true;
                    p[i] = v;
                }
            }
        }

        if (p[n-1]==-1) break;
        path.clear();
        for (int v=n-1; v!=-1; v=p[v])
            path.push_back (v);
        reverse (path.begin(), path.end());

        long long int cmin=LLONG_MAX;
        for (int i=0; i<path.size()-1; i++)
            cmin = min(cmin, c[path[i]][path[i+1]]-f[path[i]][path[i+1]]);
        flow +=cmin;

        // editing flow

        for (int i=0; i<path.size()-1; i++) {
            f[path[i]][path[i+1]] += cmin;
            f[path[i+1]][path[i]] = -f[path[i]][path[i+1]];
        }



    }

    for (int i=1; i<c[0].size()-1; i++) {
        if (f[0][i]<c[0][i]) {
            of << "NO"<< endl;  exit(0);
        }
    }


        of << "YES" << endl;
        for (int i = 0; i < edges.size(); i++) {
            of << f[edges[i].second.first][edges[i].second.second] + edges[i].first << endl;
        }



    return 0;
}