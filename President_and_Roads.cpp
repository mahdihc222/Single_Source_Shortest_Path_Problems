// https://codeforces.com/problemset/problem/567/E
#include <bits/stdc++.h>
using namespace std;
void dijkstra(int s, vector<long long> &d, vector<int> &p, vector<vector<pair<int, long long>>> &adj);
// pari na U_U
int main()
{
    int n, m;
    cin >> n >> m;
    int s, t;
    cin >> s >> t;
    vector<vector<pair<int, long long>>> adj(n + 1);
    vector<vector<pair<int, long long>>> rev_adj(n + 1);
    vector<pair<pair<int, int>, long long>> edges;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        rev_adj[v].push_back({u, w});
        edges.push_back({{u, v}, w});
    }

    vector<int> ps, pt;
    vector<long long> dist_s, dist_t;
    dijkstra(s, dist_s, ps, adj);
    dijkstra(t, dist_t, pt, rev_adj);

    for (auto e : edges)
    {
        if (dist_s[e.first.first] + e.second + dist_t[e.first.second] == dist_s[t])
        {
            cout << "YES" << endl;
        }
        else if (0)
        {
        }
        else
        {
            cout << "NO" << endl;
        }
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