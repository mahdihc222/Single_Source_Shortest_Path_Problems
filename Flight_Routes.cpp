// https://cses.fi/problemset/task/1196/
//  https://judge.yosupo.jp/problem/shortest_path
#include <bits/stdc++.h>
using namespace std;
void dijkstra(int s, vector<long long> &d, vector<int> &p, vector<vector<pair<int, long long>>> &adj);

int main()
{
    int n, m;
    int k;
    cin >> n >> m;
    cin >> k;
    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<int> count(n + 1, 0);
    vector<long long> res;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;
    q.push({0, 1});
    while (!q.empty())
    {
        auto a = q.top();
        q.pop();
        int v = a.second;
        long long cost = a.first;
        count[v]++;
        if (count[v] > k)
            continue;
        if (v == n)
        {
            res.push_back(cost);
        }
        for (auto edge : adj[v])
        {
            int to = edge.first;
            long long len = edge.second;
            q.push({len + cost, to});
        }
    }
    for (auto l : res)
    {
        cout << l << " ";
    }
    return 0;
}