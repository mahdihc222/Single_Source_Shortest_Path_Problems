#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m, f;
    cin >> n >> m >> f;
    vector<int> capacity(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> capacity[i];
    }
    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    int k;
    cin >> k;
    vector<int> p(n + 1, -1);
    vector<long long> d(n + 1, LLONG_MAX);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, 1});
    d[1] = 0;
    while (!pq.empty())
    {
        int v = pq.top().second;
        long long dist = pq.top().first;
        pq.pop();
        if (dist != d[v])
            continue;
        for (auto edge : adj[v])
        {
            int to = edge.first;
            long long len = edge.second;
            if (d[v] + len < d[to])
            {
                d[to] = d[v] + len;
                p[to] = v;
                pq.push({d[to], to});
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        cout << d[i] << " ";
    }
    cout << endl;
    vector<long long> cost(k + 1);
    int totalStud = k;
    for (int i = 1; i <= n; i++)
        pq.push({d[i], i});
    while (k != 0 && !pq.empty())
    {
        long long path_cost = pq.top().first;
        int v = pq.top().second;
        capacity[v]--;
        if (capacity[v] == 0)
            pq.pop();
        cost[totalStud - k + 1] = path_cost + f;
        k--;
    }
    while (k != 0)
    {
        cost[totalStud - k + 1] = -1;
        k--;
    }
    for (int i = 1; i <= totalStud; i++)
        cout << cost[i] << " ";
    cout << endl;
    return 0;
}