#include "tsm.h"


// Cấu trúc để lưu trữ trạng thái
struct State {
    vector<char> path;  // Current path
    vector<bool> visited;  // Visited vertices
    int cost;  // Current total cost
    int remainingVertices;  // Number of unvisited vertices

    // Custom comparator for priority queue (min-heap)
    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

string Traveling(int graph[30][30], int numVertices, char startVertex) {
    // Priority queue for Branch and Bound
    priority_queue<State, vector<State>, greater<State>> pq;

    // Initial state
    State initial;
    initial.path = {startVertex};
    initial.visited.resize(numVertices, false);
    initial.visited[startVertex - 'A'] = true;
    initial.cost = 0;
    initial.remainingVertices = numVertices - 1;

    pq.push(initial);
    
    int bestCost = INT_MAX;
    string bestPath;

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        // If all vertices have been visited, complete the tour
        if (current.remainingVertices == 0) {
            // Check if there's a path back to start vertex
            int returnCost = graph[current.path.back() - 'A'][startVertex - 'A'];
            
            if (returnCost > 0) {
                int totalCost = current.cost + returnCost;
                
                // Update best path if this is cheaper
                if (totalCost < bestCost) {
                    bestCost = totalCost;
                    
                    // Create path string, including return to start
                    bestPath = "";
                    for (char v : current.path) {
                        bestPath += v;
                        bestPath += " ";
                    }
                    bestPath += startVertex;
                }
            }
            continue;
        }

        // Try adding unvisited vertices
        for (int i = 0; i < numVertices; i++) {
            char nextVertex = 'A' + i;
            
            // Skip if already visited or no edge exists
            if (current.visited[i] || 
                graph[current.path.back() - 'A'][i] == 0) {
                continue;
            }

            // Create new state
            State next = current;
            next.path.push_back(nextVertex);
            next.visited[i] = true;
            next.cost += graph[current.path.back() - 'A'][i];
            next.remainingVertices--;

            // Prune branches that exceed current best cost
            if (next.cost < bestCost) {
                pq.push(next);
            }
        }
    }

    return bestPath;
}