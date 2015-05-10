//
// Created by korshunov on 07.05.15.
//

#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <climits>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;



int main() {
    ifstream in("decomposition.in");
    ofstream of("decomposition.out");

    int n,m;
    in >> n >> m;
    int tmp1, tmp2, tmp3;
    vector< vector<long long int> > f(n, vector<long long int>(n));
    vector<vector<long long int> > c(n, vector<long long int>(n));
    vector<vector<vector<pair<int, int> > > > data;
    vector<string> answ;

    data.resize(n);
    for (int i=0; i<n; i++) {
        data[i].resize(n);
    }

    for (int i=0; i < m ; i++) {
        in >> tmp1 >> tmp2 >> tmp3;
        if (tmp3 >0 ) {
            c[--tmp1][--tmp2] += tmp3;
            data[tmp1][tmp2].push_back(make_pair(tmp3, i));
        }
    }

    long long int flow = 0;
    queue<int> q;
    vector<bool> used;
    vector<int> p;
    vector<int> path;
    long long int cmin=0;

    while(1) {
        //bfs in Gs
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


        cmin=LLONG_MAX;

        for (int i=0; i<path.size()-1; i++)
            cmin = min(cmin, c[path[i]][path[i+1]]-f[path[i]][path[i+1]]);
        flow +=cmin;

        // editing flow

        for (int i=0; i<path.size()-1; i++) {
            f[path[i]][path[i+1]] += cmin;
            f[path[i+1]][path[i]] = -f[path[i]][path[i+1]];
        }



    }

    while(1) {
        //bfs in Gs
        q.push(0);
        used.assign(n,false);
        p.assign(n,-1);
        used[0] = true;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int i = 0; i < f[v].size(); i++) {
                if (used[i]==false && f[v][i]>0) {
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



        cmin=LLONG_MAX;
        string currAnsw = "";
        currAnsw += to_string(path.size()-1)+" ";

        for (int i=0; i<path.size()-1;i++) {
            if (data[path[i]][path[i + 1]][0].first < cmin)
                cmin = data[path[i]][path[i + 1]][0].first;
        }

        for (int i=0; i<path.size()-1;i++) {
            int j=0;
            data[path[i]][path[i + 1]][j].first -= cmin;
            currAnsw+=to_string(data[path[i]][path[i + 1]][j].second+1)+" ";
            if (data[path[i]][path[i + 1]][j].first==0) data[path[i]][path[i + 1]].erase(data[path[i]][path[i + 1]].begin()+j);

        }
        currAnsw = to_string(cmin)+" "+ currAnsw;
        answ.push_back(currAnsw);


        // editing flow

        for (int i=0; i<path.size()-1; i++) {
            f[path[i]][path[i+1]] -= cmin;
        }

    }
    of << answ.size()<<endl;
    for (int i =0; i<answ.size(); i++)
        of << answ[i]<<endl;






    return 0;
}