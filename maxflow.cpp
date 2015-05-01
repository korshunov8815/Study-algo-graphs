#include <iostream>
#include <list>                                                         
#include <vector>
#include <fstream>
#include <climits>
#include <algorithm> 
#include <queue>

using namespace std;

  
int main() {
    ifstream in("maxflow.in");
    ofstream of("maxflow.out");

    int n,m;
    in >> n >> m;
    int tmp1, tmp2, tmp3;
    vector< vector<int> > f(n, vector<int>(n));
    vector< vector<int> > c(n, vector<int>(n));

    for (int i=0; i < m ; i++) {
        in >> tmp1 >> tmp2 >> tmp3;
        c[--tmp1][--tmp2]=tmp3;
    }

    int flow = 0;
    queue<int> q;
    vector<bool> used;
    vector<int> p;
    vector<int> path;

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

		int cmin=INT_MAX;
		for (int i=0; i<path.size()-1; i++)
			cmin = min(cmin, c[path[i]][path[i+1]]-f[path[i]][path[i+1]]);
         flow +=cmin;

		// editing flow

		for (int i=0; i<path.size()-1; i++) {
			f[path[i]][path[i+1]] += cmin;
            f[path[i+1]][path[i]] = -f[path[i]][path[i+1]];
		}



 	}
    of << flow;


    return 0;
}
