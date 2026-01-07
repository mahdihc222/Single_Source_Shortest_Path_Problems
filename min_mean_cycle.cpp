#include <bits/stdc++.h>
using namespace std;
struct Edge
{
    int u, v;
    double w;
};
vector<Edge> edges;
int n, m;

// Returns true if a negative cycle exists with current adjustment
bool hasNegativeCycle(double x)
{
    vector<double> dist(n + 1, 0); // Initialize to 0 to find cycle anywhere
    int relax_count;

    // Bellman-Ford core
    for (int i = 0; i < n; i++)
    {
        relax_count = 0;
        for (auto &e : edges)
        {
            // Virtual weight is w - x
            if (dist[e.u] + (e.w - x) < dist[e.v])
            {
                dist[e.v] = dist[e.u] + (e.w - x);
                relax_count++;
            }
        }
    }
    // If we can still relax in Nth step, negative cycle exists
    return relax_count > 0;
}

void solve()
{
    // ... input edges ...
    double low = -1e9, high = 1e9;
    for (int i = 0; i < 100; ++i)
    { // 100 iterations for precision
        double mid = (low + high) / 2;
        if (hasNegativeCycle(mid))
            high = mid;
        else
            low = mid;
    }
    printf("%.2f\n", low); // Minimum mean
}