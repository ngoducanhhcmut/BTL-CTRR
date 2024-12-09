#ifndef BELLMAN_H
#define BELLMAN_H

#include <vector>
#include <string>
#include <iostream>
#include <climits> // Sử dụng INT_MAX
#include <algorithm> // Sử dụng reverse
using namespace std;

// Khai báo các hàm cần triển khai
void BF(const int graph[30][30], int numVertices, char startVertex, int valueArray[30], int prevArray[30]);

string BF_Path(int graph[30][30], int numVertices, char startVertex, char goalVertex);

#endif // BELLMAN_H
