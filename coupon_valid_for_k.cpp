#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k; // n = nodes, m = edges, k = max flights coupon is valid

    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        // adj[v].push_back({u, w}); // Uncomment if undirected
    }

    // dist[usedCoupon][flights][node] = min distance
    vector<vector<vector<long long>>> dist(2, vector<vector<long long>>(k + 1, vector<long long>(n + 1, LONG_LONG_MAX)));

    // priority queue: {distance, {node, {flights, usedCoupon}}}
    using T = pair<long long, pair<int, pair<int,int>>>;
    priority_queue<T, vector<T>, greater<T>> pq;

    dist[0][0][1] = 0;
    pq.push({0, {1, {0, 0}}}); // start at node 1, 0 flights, coupon unused

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        long long d = top.first;
        int u = top.second.first;
        int flights = top.second.second.first;
        int usedCoupon = top.second.second.second;

        if (d > dist[usedCoupon][flights][u]) continue;

        for (auto &it : adj[u]) {
            int v = it.first;
            long long w = it.second;

            // 1️⃣ Move without using coupon
            if (d + w < dist[usedCoupon][flights + 1][v]) {
                dist[usedCoupon][flights + 1][v] = d + w;
                pq.push({dist[usedCoupon][flights + 1][v], {v, {flights + 1, usedCoupon}}});
            }

            // 2️⃣ Move using coupon (only if not used yet and flights + 1 <= k)
            if (usedCoupon == 0 && flights + 1 <= k) {
                long long newDist = d + w / 2;
                if (newDist < dist[1][flights + 1][v]) {
                    dist[1][flights + 1][v] = newDist;
                    pq.push({newDist, {v, {flights + 1, 1}}});
                }
            }
        }
    }

    // Answer: minimum distance to reach node n with any flights count and coupon state
    long long ans = LONG_LONG_MAX;
    for (int f = 0; f <= k; f++) {
        for (int c = 0; c <= 1; c++) {
            ans = min(ans, dist[c][f][n]);
        }
    }

    cout << ans << endl;
}
