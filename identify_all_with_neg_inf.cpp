#include <bits/stdc++.h>
using namespace std;

const long long INF = LLONG_MAX;

int main() {
    int n, m, start_node;
    cin >> n >> m >> start_node; // Assume 1-based indexing

    vector<tuple<int, int, long long>> edges;
    vector<vector<int>> adj(n + 1); // For propagation BFS
    for (int i = 0; i < m; i++) {
        int u, v; long long w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
        adj[u].push_back(v);
    }

    vector<long long> dist(n + 1, INF);
    dist[start_node] = 0;

    // Phase 1: Standard Bellman-Ford
    for (int i = 0; i < n - 1; i++) {
        for (auto [u, v, w] : edges) {
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Phase 2: Find nodes directly affected by negative cycles
    queue<int> q;
    vector<bool> is_inf(n + 1, false);

    for (int i = 0; i < n; i++) { // Run a few more times or just check
        for (auto [u, v, w] : edges) {
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                // We force update to avoid logic traps, but mainly we queue it
                dist[v] = -INF; 
                if (!is_inf[v]) {
                    is_inf[v] = true;
                    q.push(v);
                }
            }
        }
    }

    // Phase 3: Propagate -INF to all descendants
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : adj[u]){
            if(!is_inf[v]){
                is_inf[v] = true;
                q.push(v);
            }
        }
    }

    // Output
    for(int i=1; i<=n; ++i) {
        if(is_inf[i]) cout << "-INF" << endl;
        else if(dist[i] == INF) cout << "Unreachable" << endl;
        else cout << dist[i] << endl;
    }
}