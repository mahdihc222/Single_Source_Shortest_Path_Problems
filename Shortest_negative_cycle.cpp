#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    long long w;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, long long>>> adj(n + 1);
    vector<Edge> edges;

    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        edges.push_back({u, v, w});
    }

    // Super-source trick
    for (int i = 1; i <= n; i++) {
        adj[0].push_back({i, 0});
        edges.push_back({0, i, 0});
    }

    vector<long long> dist(n + 1, LLONG_MAX);
    vector<int> parent(n + 1, -1);
    vector<int> lastUpdated(n + 1, -1); // iteration of last update
    dist[0] = 0;

    int x = -1;
    // Standard Bellman-Ford
    for (int i = 0; i < n; i++) {
        x = -1;
        for (auto e : edges) {
            int u = e.u, v = e.v;
            long long w = e.w;
            if (dist[u] != LLONG_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                x = v;
                lastUpdated[v] = i; // track iteration
            }
        }
    }

    // Check for negative cycle
    int cycleStart = -1;
    int earliestIter = n + 1; // to find shortest cycle
    for (auto e : edges) {
        int u = e.u, v = e.v;
        long long w = e.w;
        if (dist[u] != LLONG_MAX && dist[u] + w < dist[v]) {
            // Candidate negative cycle
            if (lastUpdated[v] < earliestIter) {
                earliestIter = lastUpdated[v];
                cycleStart = v;
            }
        }
    }

    if (cycleStart == -1) {
        cout << "NO\n";
    } else {
        // Recover the cycle
        int y = cycleStart;
        for (int i = 0; i <= n; i++) y = parent[y]; // move to cycle node

        vector<int> neg_cycle;
        int cur = y;
        do {
            neg_cycle.push_back(cur);
            cur = parent[cur];
        } while (cur != y);
        neg_cycle.push_back(y); // close the cycle

        reverse(neg_cycle.begin(), neg_cycle.end());

        cout << "YES\n";
        for (int u : neg_cycle) cout << u << " ";
        cout << "\n";
    }

    return 0;
}
