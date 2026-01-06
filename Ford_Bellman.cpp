#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<pair<pair<int, int>, long long>> edges;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edges.push_back({{u, v}, w});
    }

    vector<long long> dist(n + 1, LLONG_MAX);
    dist[1] = 0;
    bool any = false;
    for (int i = 0; i < n - 1; i++)
    {
        any = false;
        for (auto e : edges)
        {
            if (dist[e.first.first] != LLONG_MAX && dist[e.first.second] > dist[e.first.first] + e.second)
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

    for (int i = 1; i <= n; i++)
    {
        if(dist[i]==LLONG_MAX) cout<<30000<<" ";
        else cout << dist[i] << " ";
    }
    return 0;
}