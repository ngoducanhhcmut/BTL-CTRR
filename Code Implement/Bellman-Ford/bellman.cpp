#include "bellman.h"


// Hàm thực hiện một bước của Bellman-Ford
void BF(const int graph[30][30], int numVertices, char startVertex, int valueArray[30], int prevArray[30]){
    int startIdx = startVertex - 'A'; // Chuyển ký tự thành chỉ số

    // Bước 1: Khởi tạo
    // if(valueArray[startIdx]== -1){
            for (int i = 0; i < numVertices; i++) {
                if(graph[startIdx][i] != 0)
                    valueArray[i] = graph[startIdx][i]; // Khoảng cách từ đỉnh bắt đầu đến các đỉnh khác
                else
                    valueArray[i] = INT_MAX;
                    
                // if(graph[startIdx][i] != 0 && graph[startIdx][i] != INT_MAX){
                //     prevArray[i] = startIdx;
                // }
                // else    prevArray[i] = -1;
                if (i == startIdx) {
                    prevArray[i] = -1; // Start vertex has no previous vertex
                } else {
                    prevArray[i] = (graph[startIdx][i] != 0) ? startIdx : -1;
                }
                
            }
                valueArray[startIdx] = 0; // Khoảng cách từ đỉnh bắt đầu đến chính nó là 0
                // prevArray[startIdx] = -1; // Đỉnh bắt đầu không có đỉnh trước đó
    // }

    // Bước 2: Thực hiện cập nhật Bellman-Ford (numVertices - 1 lần)
    for (int i = 0; i < numVertices - 1; i++) {
        for (int u = 0; u < numVertices; ++u) {
            for (int v = 0; v < numVertices; ++v) {
                // Chỉ xét cạnh hợp lệ
                if (graph[u][v] > 0 && valueArray[u] != INT_MAX && (valueArray[u] + graph[u][v]) < valueArray[v]) {
                        valueArray[v] = valueArray[u] + graph[u][v];
                        prevArray[v] = u;
                }
            }
        }
    }
}

// Hàm trả về đường đi ngắn nhất từ startVertex đến goalVertex

string BF_Path(int graph[30][30], int numVertices, char startVertex, char goalVertex) {
    // If start and goal are the same
    if (startVertex == goalVertex) {
        return string(1, startVertex);
    }
    
    int labelValues[30];
    int prevVertices[30];
    
    // Perform Bellman-Ford 
    BF(graph, numVertices, startVertex, labelValues, prevVertices);
    
    // Reconstruct path
    int current = goalVertex - 'A';
    string path;
    
    // Check if path exists
    if (labelValues[current] == INT_MAX) {
        return ""; // No path exists
    }
    
    // Reconstruct path in reverse
    vector<char> reversePath;
    while (current != -1) {
        reversePath.push_back(current + 'A');
        current = prevVertices[current];
    }
    
    // Reverse and create path string
    for (auto it = reversePath.rbegin(); it != reversePath.rend(); ++it) {
        path += string(1, *it);
        if (it + 1 != reversePath.rend()) {
            path += " ";
        }
    }
    
    return path;
}