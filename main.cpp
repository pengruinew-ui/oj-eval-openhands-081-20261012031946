#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 3005;
const int INF = 1e9;

struct Edge {
    int to, cap, rev;
    Edge(int t, int c, int r) : to(t), cap(c), rev(r) {}
};

vector<Edge> graph[MAXN];
bool visited[MAXN];

void addEdge(int from, int to, int cap) {
    graph[from].push_back(Edge(to, cap, graph[to].size()));
    graph[to].push_back(Edge(from, cap, graph[from].size() - 1));
}

int dfs(int v, int t, int f) {
    if (v == t) return f;
    visited[v] = true;
    for (auto& e : graph[v]) {
        if (!visited[e.to] && e.cap > 0) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                graph[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int maxFlow(int s, int t) {
    int flow = 0;
    while (true) {
        memset(visited, 0, sizeof(visited));
        int f = dfs(s, t, INF);
        if (f == 0) return flow;
        flow += f;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    // Initialize graph
    for (int i = 1; i <= n; i++) {
        graph[i].clear();
    }
    
    // Add edges
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        addEdge(a, b, 1);  // Each pipe has capacity 1
    }
    
    // Calculate sum of max flows for all pairs a < b
    long long total = 0;
    for (int a = 1; a <= n; a++) {
        for (int b = a + 1; b <= n; b++) {
            // Recreate original graph for each flow calculation
            for (int i = 1; i <= n; i++) {
                for (auto& e : graph[i]) {
                    e.cap = 1;  // Reset capacity to 1
                    // The reverse edge will be updated in addEdge
                }
            }
            total += maxFlow(a, b);
        }
    }
    
    cout << total << endl;
    
    return 0;
}