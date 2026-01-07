#include <bits/stdc++.h>

using namespace std;

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

    for (int i = 1; i <= n; i++)
    {
        adj[0].push_back({i, 0});
    }
    vector<long long> dist(n + 1, LLONG_MAX);
    vector<int> parent(n + 1, -1);
    dist[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < n; i++)
    {
        // for (long long d : dist)
        //     cout << d << " ";
        for (int u = 0; u <= n; u++)
        {
            if (dist[u] == LLONG_MAX)
                continue;
            for (auto it : adj[u])
            {
                int v = it.first;
                long long w = it.second;
                if (dist[v] > w + dist[u])
                {
                    parent[v] = u;
                    dist[v] = w + dist[u];
                }
            }
        }
    }
    int x = -1;
    for (int u = 0; u <= n; u++)
    {
        for (auto it : adj[u])
        {
            int v = it.first;
            long long w = it.second;
            if (dist[u] != LLONG_MAX && dist[v] > w + dist[u])
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                x = v;
            }
        }
    }
    if (x != -1)
    {
        for (int i = 0; i <= n; i++)
            x = parent[x];
        int s = x;
        vector<int> neg_circle;
        do
        {
            neg_circle.push_back(s);
            s = parent[s];
        } while (s != x);
        reverse(neg_circle.begin(), neg_circle.end());

        for (int u : neg_circle)
            cout << u << " ";
    }
    else
        cout << x << endl;
    return 0;
}