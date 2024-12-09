#ifndef TSM_H
#define TSM_H

#include <vector>
#include <string>
#include <climits> // Sử dụng INT_MAX
#include <queue>   // Sử dụng priority_queue
#include <set>
#include<algorithm>
using namespace std;

// Hàm tính đường đi ngắn nhất qua tất cả các đỉnh (Branch and Bound)
string Traveling(int graph[30][30], int numVertices, char startVertex);

#endif // TSM_H
