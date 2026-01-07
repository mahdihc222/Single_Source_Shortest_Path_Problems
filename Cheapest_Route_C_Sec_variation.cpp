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

    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    const long long INF = LLONG_MAX;
    vector<vector<vector<long long>>> dist(
        n + 1,
        vector<vector<long long>>(2, vector<long long>(3, INF)));

    // (cost, node, usedCoupon, stage)
    priority_queue<
        tuple<long long, int, int, int>,
        vector<tuple<long long, int, int, int>>,
        greater<tuple<long long, int, int, int>>
    > pq;

    dist[1][0][0] = 0;
    pq.push({0, 1, 0, 0});

    while (!pq.empty())
    {
        auto [cost, u, used, stage] = pq.top();
        pq.pop();

        if (cost > dist[u][used][stage])
            continue;

        for (auto [v, w] : adj[u])
        {
            int newStage = stage;

            // Mandatory edge progression
            if (u == x1 && v == y1 && stage == 0)
                newStage = 1;
            else if (u == x2 && v == y2 && stage == 1)
                newStage = 2;

            // Normal transition
            if (cost + w < dist[v][used][newStage])
            {
                dist[v][used][newStage] = cost + w;
                pq.push({cost + w, v, used, newStage});
            }

            // Coupon transition (not allowed on mandatory edges)
            bool isMandatory =
                (u == x1 && v == y1) ||
                (u == x2 && v == y2);

            if (!used && !isMandatory)
            {
                if (cost + w / 2 < dist[v][1][newStage])
                {
                    dist[v][1][newStage] = cost + w / 2;
                    pq.push({cost + w / 2, v, 1, newStage});
                }
            }
        }
    }

    long long ans = min(dist[n][0][2], dist[n][1][2]);
    if (ans == INF)
        cout << -1 << endl;
    else
        cout << ans << endl;

    return 0;
}

/*✔ Allow coupon on mandatory edges

→ remove isMandatory check

✔ Add more mandatory segments

→ replace stage ∈ {0..k}

✔ Force exactly one coupon

→ only take dist[n][1][2]

✔ Allow multiple coupons

→ change usedCoupon to 0..k
*/