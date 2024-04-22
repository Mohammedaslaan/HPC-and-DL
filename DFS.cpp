#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

class Graph {
    int V;    // No. of vertices
    vector<vector<int>> adj;    // Adjacency List

public:
    Graph(int V) : V(V) {
        adj.resize(V);
    }

    // Function to add an edge to the graph
    void addEdge(int v, int w) {
        adj[v].push_back(w); // Add w to v’s list.
    }

    // A utility function to do DFS traversal
    // from a given vertex u using OpenMP
    void DFSUtil(int u, vector<bool>& visited) {
        stack<int> stack;

        stack.push(u);

        while (!stack.empty()) {
            u = stack.top();
            stack.pop();

            if (!visited[u]) {
                cout << u << " ";
                visited[u] = true;

                // Parallelize the loop over adjacent vertices
                #pragma omp parallel for
                for (int i = 0; i < adj[u].size(); i++) {
                    int v = adj[u][i];
                    if (!visited[v]) {
                        stack.push(v);
                    }
                }
            }
        }
    }

    // The function to do DFS traversal. It uses recursive DFSUtil()
    void DFS() {
        // Mark all the vertices as not visited
        vector<bool> visited(V, false);

        // Call the recursive helper function to print DFS traversal
        // starting from all vertices one by one
        for (int u = 0; u < V; u++) {
            if (!visited[u]) {
                DFSUtil(u, visited);
            }
        }
    }
};

int main() {
    // Create a graph
    Graph g(5); // 5 vertices numbered from 0 to 4

    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);

    cout << "Depth First Traversal (starting from vertex 0): ";
    g.DFS();
    cout << endl;

    return 0;
}
