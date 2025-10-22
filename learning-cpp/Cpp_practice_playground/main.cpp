#include <iostream>
#include <print>
#include <stack>
#include <unordered_map>
#include <vector>

// Graph Algorithms

using std::vector, std::unordered_map, std::println;

std::string line(100, '-');

void printGraph(std::unordered_map<int, std::vector<int>> &g) {

  for (auto itr : g) {
    for (auto neigh : itr.second) {
      println("{} => {} ", itr.first, neigh);
    }
  }
}
void DFS(std::unordered_map<int, std::vector<int>> &g, int node,
         std::vector<bool> &visited) {

  if (!visited[node]) {
    // std::print(" {} ", node);
  }
  visited[node] = true;
  for (auto neigh : g[node]) {
    if (!visited[neigh]) {
      std::print("{} ,", neigh);
      DFS(g, neigh, visited);
    }
  }
  std::println("");
}

bool detectCycleRecursive(std::unordered_map<int, std::vector<int>> &g,
                          int node, std::vector<bool> &visited,
                          std::vector<bool> &currNodes) {
  // DFS
  if (currNodes[node])
    return true;
  if (visited[node])
    return false;

  visited[node] = true;
  currNodes[node] = true;
  for (auto neigh : g[node]) {
    if (detectCycleRecursive(g, neigh, visited, currNodes))
      return true;
  }

  currNodes[node] = false;
  return false;
}

void detectCycle(std::unordered_map<int, std::vector<int>> &g, int vertices,
                 int source) {

  std::vector<bool> visited(vertices, false);
  std::vector<bool> currNodes(vertices, false);
  bool hasCycle = false;
  for (int i = 1; i <= vertices; i++) {
    hasCycle = detectCycleRecursive(g, source, visited, currNodes);
  }
  std::println("Has graph cycle: {}", hasCycle);
}

void cycleDetectionExample() {
  std::println("Cycle Detection Example:");

  std::unordered_map<int, std::vector<int>> graphEdges = {
      // {0, {1, 2, 3}},
      // {1, {3, 4}},
      // {3, {5}},
      {1, {2}},
      {2, {3}},
      {3, {4}},
      // {4, {2}}, // This makes a cycle
      {3, {5}},
      {5, {6}},

  };
  int vertices = 6;
  std::vector<bool> visited(vertices, false);
  std::println("Write you code here : ");
  std::println("{}", line);
  printGraph(graphEdges);
  DFS(graphEdges, 1, visited);
  detectCycle(graphEdges, vertices, 1);
  std::println("\n{}", line);
}

// 2. Find mother  vertex

void motherVertexDFS(std::unordered_map<int, std::vector<int>> &graph, int node,
                     vector<bool> &visited, int &visitedCount) {

  visited[node] = true;
  visitedCount++;
  std::println("{}", node);
  for (auto neigh : graph[node]) {
    if (!visited[neigh]) {
      motherVertexDFS(graph, neigh, visited, visitedCount);
    }
  }
}

int findMotherVertex(unordered_map<int, vector<int>> &g, int vertices) {
  vector<bool> visited(vertices, false);
  int visitedCount = 0;
  for (int i = 0; i < vertices; i++) {
    visitedCount = 0;
    std::println("Printing DFS for node: {} ", i);
    std::println("{}", line);
    motherVertexDFS(g, i, visited, visitedCount);
    std::println("{}", line);
    if (visitedCount == vertices) {
      return i;
    }
  }
  return -1;
}

void runFindMotherVertexExample() {
  int v1 = 3;
  int v2 = 4;
  unordered_map<int, vector<int>> g1 = {{0, {1, 2}}, {1, {2}}, {2, {}}};
  unordered_map<int, vector<int>> g2 = {
      {0, {}}, {1, {}}, {2, {3, 1}}, {3, {2, 0}}};
  auto result = findMotherVertex(g2, v2);

  std::cout << "Mother vertex: " << result << std::endl;
}

int countNumberOfEdges(unordered_map<int, vector<int>> &g, int vertices) {
  int count = 0;
  for (int i = 0; i < vertices; i++) {
    for (auto neigh : g[i]) {
      count++;
    }
  }

  return count;
}

void runCountNumberOfEdgesExample() {
  int vertices = 6;
  unordered_map<int, vector<int>> g = {{0, {1, 2, 3}}, {1, {5, 6}}};
  auto noOfEdges = countNumberOfEdges(g, vertices);
  std::println("Number of edges: {}", noOfEdges);
}
// BST - Start
template <typename T> class BSTNode {
public:
  BSTNode<T> *left;
  BSTNode<T> *right;
  T value;
  BSTNode(T val) : left(nullptr), value(val), right(nullptr) {};
};

template <typename T> class BST {
private:
  BSTNode<T> *root;

public:
  BST() : root(nullptr) {};
  BST(T val) { root = new BSTNode<T>(val); }
  void addNode(T newVal) {
    if (root == nullptr) {
      root = new BSTNode<T>(newVal);
      return;
    }
    BSTNode<T> *curr = root;
    BSTNode<T> *newNode = new BSTNode<T>(newVal);
    while (curr != nullptr) {
      if (newVal < curr->value) {
        // move left
        if (curr->left == nullptr) {
          curr->left = newNode;
          std::println("Left of {} Inserted: {} ", curr->value, newNode->value);
          break;
        }
        curr = curr->left;

      } else {
        // move right
        if (curr->right == nullptr) {
          curr->right = newNode;
          std::println("Right of {} Inserted: {} ", curr->value,
                       newNode->value);
          break;
        }

        curr = curr->right;
      }
    }
  };
  void printBST() {
    std::stack<BSTNode<T> *> stk;
    stk.push(root);
    std::println("Root: {}", root->value);
    while (!stk.empty()) {
      BSTNode<T> *node = stk.top();
      stk.pop();
      std::print("{} | ", node->value);
      if (node->left) {
        stk.push(node->left);
      }
      if (node->right) {
        stk.push(node->right);
      }
    }
    std::println("");
  }
};

void runBSTExample() {
  BST bst = BST<int>(10);
  bst.addNode(12);
  bst.addNode(8);
  bst.addNode(20);
  bst.addNode(40);
  bst.printBST();
}
// BST - End
// Main function start - entry point

int main(int argvs, char **args) {
  // std::println("Hello Cpp ");
  // for (int i = 0; i < argvs; i++) {
  //   std::println("Arg {}: {}", i, args[i]);
  //   std::println("Hello Cpp23");
  // }

  // cycleDetectionExample();
  // runFindMotherVertexExample();
  // runCountNumberOfEdgesExample();

  runBSTExample();
  return 0;
}
