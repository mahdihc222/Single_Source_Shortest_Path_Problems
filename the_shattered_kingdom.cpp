#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m, k, b, e;
    cin >> n >> m >> k >> b >> e;
    vector<int> capitals(k);
    for (int i = 0; i < k; i++)
        cin >> capitals[i];
    vector<int> blocked(b);
    for (int i = 0; i < b; i++)
        cin >> blocked[i];
    vector<int> emgp(e);
    for (int i = 0; i < e; i++)
        cin >> emgp[i];
    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        auto itu = find(blocked.begin(), blocked.end(), u);
        auto itv = find(blocked.begin(), blocked.end(), v);
        if (itu == blocked.end() && itv == blocked.end())
        {
            adj[u].push_back({v,w});
        }
    }

    
}