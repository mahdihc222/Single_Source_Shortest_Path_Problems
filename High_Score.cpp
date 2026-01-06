// https://cses.fi/problemset/task/1673
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<pair<pair<int, int>, long long>> edges;
    vector<vector<int>> adj(n + 1); // adjacency list to store the reverse graph
    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edges.push_back({{u, v}, w});
        adj[v].push_back(u);
    }
    vector<long long> dist(n + 1, LLONG_MIN);
    dist[1] = 0;
    bool any = false;
    for (int i = 0; i < n - 1; i++)
    {
        any = false;
        for (auto e : edges)
        {
            if (dist[e.first.first] != LLONG_MIN && dist[e.first.first] + e.second > dist[e.first.second])
            {
                dist[e.first.second] = dist[e.first.first] + e.second;
                any = true;
            }
        }
        if (!any)
        {
            break;
        }
    }
    bool is_cycle = false;
    vector<bool> in_cycle(n + 1, false);
    for (auto e : edges)
    {
        if (dist[e.first.first] != LLONG_MIN && dist[e.first.first] + e.second > dist[e.first.second])
        {
            dist[e.first.second] = dist[e.first.first] + e.second;
            is_cycle = true;
            in_cycle[e.first.second] = true;
        }
    }
    if (is_cycle)
    {

        // dfs to check if the cycle can or cannot reach the destination
        queue<int> q;
        q.push(n);
        vector<bool> vis(n + 1, false);
        vis[n] = true;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (auto v : adj[u])
            {
                if (!vis[v])
                {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
        bool larger_possible = false;
        for (int i = 1; i <= n; i++)
        {
            if (vis[i] && in_cycle[i])
            {
                larger_possible = true;
                break;
            }
        }
        if (larger_possible)
            cout << -1 << endl;
        else
            cout << dist[n] << endl;
    }
    else
    {
        cout << dist[n] << endl;
    }
}
