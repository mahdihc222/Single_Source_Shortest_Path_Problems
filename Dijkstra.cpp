// https://codeforces.com/problemset/problem/20/C
//  https://judge.yosupo.jp/problem/shortest_path
#include <bits/stdc++.h>
using namespace std;
void dijkstra(int s, vector<long long> &d, vector<int> &p, vector<vector<pair<int, long long>>> &adj);

int main()
{
    int n, m;
    int s = 1, t;
    cin >> n >> m;
    t = n;
    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    vector<long long> d;
    vector<int> p;
    dijkstra(s, d, p, adj);
    if (d[t] == LLONG_MAX)
    {
        cout << -1 << endl;
    }
    else
    {
        vector<int> ans;
        int cur = t;
        ans.push_back(cur);
        while (p[cur] != -1)
        {
            cur = p[cur];
            ans.push_back(cur);
        }
        reverse(ans.begin(), ans.end());
        for (int i = 0; i < ans.size(); i++)
        {
            cout << ans[i] << " ";
        }
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