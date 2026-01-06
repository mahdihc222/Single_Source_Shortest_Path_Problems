#include<bits/stdc++.h>
using namespace std;

int main(){
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
        vector<int> bestBike(n+1,INT_MAX);
        vector<long long> dist(n+1, LLONG_MAX);
        dist[1] = 0;
        bestBike[1] = s[1];
        for(int i=0; i<n-1; i++){
            for(int u=1; u<=n; u++){
                for(auto edge : adj[u]){
                    long long time_u_to_v = bestBike[u]* edge.second;
                    int v = edge.first; 
                    if(dist[v]>dist[u]+time_u_to_v){
                        dist[v]  = dist[u]+time_u_to_v;
                        bestBike[v] = min(bestBike[u],s[v]);
                    }
                }
            }
        }
        cout<<dist[n]<<endl;
}