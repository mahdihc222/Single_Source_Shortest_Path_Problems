// https://cses.fi/problemset/task/1671
#include <bits/stdc++.h>
using namespace std;
void dijkstra(int s, vector<long long> &d, vector<int> &p, vector<vector<pair<int, long long>>> &adj);
int main()
{
    int n, m;

    cin >> n >> m;
    vector<vector<pair<int, long long>>> adj(n + 1);
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
    for (int i = 1; i <= n; i++)
    {
        cout << d[i] << " ";
    }
    return 0;
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