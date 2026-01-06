//https://cses.fi/problemset/task/1202
#include<bits/stdc++.h>
using namespace std;

void dijkstra(int s, vector<long long> &d, vector<int> &p, vector<vector<pair<int, long long>>> &adj, int t)
{

    
    int n = adj.size(); //ekhane n age thekei n+1 kintu 
    //tmi barbar gadhar mto abr n+1 use kro
    vector<long long> ways(n);
    vector<int> minFlights(n), maxFlights(n);

    d.assign(n, LLONG_MAX);
    p.assign(n, -1);
    d[s] = 0;
    maxFlights[s] = 0;
    minFlights[s] = 0;
    ways[s] =1;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;
    q.push({0, s});
    while (!q.empty())
    {
        auto it = q.top();
        int u = it.second;
        long long dis = it.first;
        q.pop();

        if(dis>d[u]) continue;

        for (auto edge : adj[u])
        {
            int v = edge.first;
            long long len = edge.second;
            if (d[u] + len < d[v])
            {
                d[v] = d[u] + len;
                ways[v] = ways[u];
                minFlights[v] = minFlights[u]+1;
                maxFlights[v] = maxFlights[u]+1;
                p[v] = u;
                q.push({d[v],v});
            }
            else if(d[u]+len == d[v]){
                ways[v] = (ways[u]+ways[v])%1000000007;
                minFlights[v] = min(minFlights[v], minFlights[u]+1);
                maxFlights[v] = max(maxFlights[v],maxFlights[u]+1);
            }
        }
    }
    cout<<d[n-1]<<" "<<ways[n-1]<<" "<<minFlights[n-1]<<" "<<maxFlights[n-1]<<endl;
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<pair<int,long long>>> adj(n+1);
    for(int i=0; i<m; i++){
        int u,v;
        long long w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
    }

    vector<long long> d(n+1);
    vector<int> p(n+1);
    dijkstra(1,d,p,adj,n);
}