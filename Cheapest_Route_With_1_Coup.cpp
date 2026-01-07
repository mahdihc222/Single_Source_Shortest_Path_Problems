#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, long long>>> adj(n + 1);
    //vector<vector<pair<int, long long>>> rev_adj(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        //rev_adj[v].push_back({u, w});
    }

    priority_queue<pair<long long, pair<int, int>>, vector<pair<long long, pair<int, int>>>, greater<pair<long long, pair<int, int>>>> pq;
    vector<vector<long long>> dist(2, vector<long long>(n + 1, LONG_LONG_MAX));
    dist[0][1] = 0;
    pq.push({0, {1, 0}});
    while (!pq.empty())
    {
        pair<long long, pair<int, int>> p = pq.top();
        pq.pop();

        int node = p.second.first;
        int state = p.second.second;
        long long dis = p.first;

        if (dis > dist[state][node])
            continue;

        for (auto it : adj[node])
        {
            int v = it.first;
            long long w = it.second;
            if (dis + w < dist[state][v])
            {
                dist[state][v] = dis + w;
                pq.push({dist[state][v], {v, state}});
            }
            if (state == 0 && dis + w / 2 < dist[1][v])
            {
                dist[1][v] = dis + w / 2;
                pq.push({dist[1][v], {v, 1}});
            }
        }
    }

    cout << dist[1][n]<< endl;

    // pq.push({0, n});
    // dist2[n] = 0;
    // while (!pq.empty())
    // {
    //     pair<long long, int> p = pq.top();
    //     pq.pop();

    //     int node = p.second;
    //     long long dis = p.first;

    //     if (dis > dist2[node])
    //         continue;

    //     for (auto it : rev_adj[node])
    //     {
    //         int v = it.first;
    //         long long w = it.second;
    //         if (dis + w < dist2[v])
    //         {
    //             dist2[v] = dis + w;
    //             pq.push({dist2[v], v});
    //         }
    //     }
    // }

    // long long min_path = LONG_LONG_MAX;

    // for (int u = 1; u <= n; u++)
    // {
    //     for (auto it : adj[u])
    //     {
    //         int v = it.first;
    //         long long w = it.second;
    //         if (dist1[u] != LONG_LONG_MAX && dist2[v] != LONG_LONG_MAX)
    //             min_path = min(min_path, dist1[u] + w / 2 + dist2[v]);
    //     }
    // }
    // cout << min_path << endl;
}