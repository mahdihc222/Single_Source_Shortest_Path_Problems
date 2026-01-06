//https://judge.yosupo.jp/problem/shortest_path
#include <bits/stdc++.h>
using namespace std;
void dijkstra(int s, vector<long long> &d, vector<int> &p, vector<vector<pair<int, long long>>> &adj);

int main()
{
    int n, m;
    int s,t;
    cin >> n >> m;
    cin>>s>>t;
    vector<vector<pair<int, long long>>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    vector<long long> d;
    vector<int> p;
    dijkstra(1, d, p, adj);
    

    vector<int> ans;
    int cur = t;
    while(p[t]!=-1 && p[t]!=s){
        ans.push_back(cur);
        cur = p[t];
    }
    if(p[t]==-1){
        cout<<-1;
    }
    else{
        ans.push_back(s);
        //reverse(ans.begin
    }
}

void dijkstra(int s, vector<long long> &d, vector<int> &p, vector<vector<pair<int, long long>>> &adj)
{
    int n = adj.size();
    d.assign(n, LLONG_MAX);
    p.assign(n, -1);
    d[s] = 0;
    set<pair<long long, int>> q;
    q.insert({0, s});
    while (!q.empty())
    {
        int v = q.begin()->second;
        q.erase(q.begin());

        for (auto edge : adj[v])
        {
            int to = edge.first;
            long long len = edge.second;
            if (d[v] + len < d[to])
            {
                q.erase({d[to], to});
                d[to] = d[v] + len;
                p[to] = v;
                q.insert({d[to], to});
            }
        }
    }
}