// https://codeforces.com/contest/1915/problem/G
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
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
            adj[v].push_back({u, w});
        }
        vector<int> s(n + 1);
        for (int i = 1; i <= n; i++)
            cin >> s[i];

        vector<vector<long long>> d(n + 1, vector<long long>(1001, LLONG_MAX));
        d[1][s[1]] = 0;

        priority_queue<pair<pair<long long, int>, int>, vector<pair<pair<long long, int>, int>>, greater<pair<pair<long long, int>, int>>> q;
        q.push({{0, 1}, s[1]});
        while (!q.empty())
        {
            auto it = q.top();
            int u = it.first.second;
            long long dis = it.first.first;
            int curS = it.second;
            q.pop();

            if (dis != d[u][curS])
                continue;
            int newS = min(curS, s[u]);
            for (auto edge : adj[u])
            {
                int v = edge.first;
                long long len = edge.second;
                if (dis + len * newS < d[v][newS])
                {
                    d[v][newS] = dis + len * newS;
                    q.push({{d[v][newS], v}, newS});
                }
            }
        }
        long long ans = LLONG_MAX;
        for (int k = 1; k <= 1000; k++)
        {
            ans = min(ans, d[n][k]);
        }
        cout << ans << endl;
    }
}