// https://onlinejudge.org/external/100/10099.pdf
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int i = 0;
    while (true)
    {
        i++;
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;
        vector<vector<pair<int, long long>>> adj(n + 1);
        for (int i = 0; i < m; i++)
        {
            int u, v;
            long long w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        int s, t;
        cin >> s >> t;
        long long passengers;
        cin >> passengers;
        vector<long long> cap(n + 1, 0);
        cap[s] = LLONG_MAX;
        priority_queue<pair<long long, int>> pq;
        pq.push({LLONG_MAX, s});
        while (!pq.empty())
        {
            pair<long long, int> elem = pq.top();
            pq.pop();
            int u = elem.second;
            long long capa = elem.first;

            for (auto e : adj[u])
            {
                long long weight = e.second;
                int v = e.first;
                if (min(capa, weight) > cap[v])
                {
                    cap[v] = min(capa, weight);
                    pq.push({cap[v], v});
                }
            }
        }
        cout << "Scenario #" << i << endl;
        if (cap[t] <= 1)
        {
            cout << "Minimum Number of Trips = IMPOSSIBLE" << endl
                 << endl;
        }
        else
        {
            cout << "Minimum Number of Trips = " << ceil(passengers / (cap[t] - 1.0)) << endl
                 << endl;
        }
    }
}