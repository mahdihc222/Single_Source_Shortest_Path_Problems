#include <bits/stdc++.h>
using namespace std;

int main()
{
    int k, n, x;
    cin >> k >> n >> x;

    vector<vector<pair<pair<int, int>, int>>> adj(n + 1);
    for (int i = 0; i < x; i++)
    {
        int u, v;
        cin >> u >> v;
        int t, c;
        cin >> t >> c;
        adj[u].push_back({{v, t}, c});
        adj[v].push_back({{u, t}, c});
    }
    int s, t;
    cin >> s >> t;

    vector<int> p(n + 1, -1);
    vector<int> d(n + 1, INT_MAX);
    vector<int> times(n + 1, INT_MAX);
    d[s] = 0;
    times[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});
    while (!pq.empty())
    {
        int u = pq.top().second;
        int cos = pq.top().first;
        pq.pop();
        if (d[u] != cos)
            continue;

        for (auto it : adj[u])
        {
            int v = it.first.first;
            int t = it.first.second;
            int c = it.second;
            int newD;
            if (u == s)
                newD = t * k + c + cos;
            else
                newD = (t + 1) * k + c + cos; // Relaxing edges
            if (newD < d[v])
            {
                d[v] = newD;
                p[v] = u;
                times[v] = times[u] + t + (u != s);
                pq.push({newD, v});
            }
        }
    }
    if (d[t] == INT_MAX)
        cout << -1 << endl;
    else
    {
        vector<int> ans;
        int cur = t;
        while (cur != -1)
        {
            ans.push_back(cur);
            cur = p[cur];
        }
        reverse(ans.begin(), ans.end());
        for (int i : ans)
            cout << i << (i != t ? "->" : " ");
        cout << times[t] << " " << d[t] << endl;
    }
}