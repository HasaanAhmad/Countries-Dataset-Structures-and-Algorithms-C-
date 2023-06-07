
// Description: Implementation of Graphs, BFS, DFS, Dijkstra and Prim algorithms.

// Revision History:
// Hasaan Ahmad (SP22-BSE-017) - Initial commit. - Dated June 4, 2023

// Hasaan Signing off! Cheers!

#include "countries.h"

using namespace std;

class Graph {
private:
    unordered_map<string, vector<Node>> adjacencyList;

public:
    void addNode(const Node& node);
    void addEdge(const string& code1, const string& code2);
    vector<string> bfs(const string& startCode);
    vector<string> dfs(const string& startCode);
    vector<string> dijkstra(const string& startCode, const string& endCode);
    vector<string> prim(const string& startCode);
};

void Graph::addNode(const Node& node) {
    adjacencyList[node.code].push_back(node);
}

void Graph::addEdge(const string& code1, const string& code2) {
    // Assuming both codes exist in the adjacency list
    adjacencyList[code1].push_back(adjacencyList[code2][0]);
    adjacencyList[code2].push_back(adjacencyList[code1][0]);
}

vector<string> Graph::bfs(const string& startCode) {
    vector<string> visited;
    queue<string> q;

    visited.push_back(startCode);
    q.push(startCode);

    while (!q.empty()) {
        string currentCode = q.front();
        q.pop();

        for (const Node& neighbor : adjacencyList[currentCode]) {
            if (find(visited.begin(), visited.end(), neighbor.code) == visited.end()) {
                visited.push_back(neighbor.code);
                q.push(neighbor.code);
            }
        }
    }

    return visited;
}

vector<string> Graph::dfs(const string& startCode) {
    vector<string> visited;
    stack<string> s;

    visited.push_back(startCode);
    s.push(startCode);

    while (!s.empty()) {
        string currentCode = s.top();
        s.pop();

        for (const Node& neighbor : adjacencyList[currentCode]) {
            if (find(visited.begin(), visited.end(), neighbor.code) == visited.end()) {
                visited.push_back(neighbor.code);
                s.push(neighbor.code);
            }
        }
    }

    return visited;
}

vector<string> Graph::dijkstra(const string& startCode, const string& endCode) {
    unordered_map<string, double> distance;
    unordered_map<string, string> previous;
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;

    // Initialize distances and previous nodes
    for (const auto& entry : adjacencyList) {
        const string& code = entry.first;
        distance[code] = numeric_limits<double>::infinity();
        previous[code] = "";
    }

    distance[startCode] = 0.0;
    pq.push(make_pair(0.0, startCode));

    while (!pq.empty()) {
        string currentCode = pq.top().second;
        pq.pop();

        if (currentCode == endCode) {
            break;
        }

        for (const Node& neighbor : adjacencyList[currentCode]) {
            double edgeWeight = sqrt(pow(neighbor.latitude - adjacencyList[currentCode][0].latitude, 2) +
                                     pow(neighbor.longitude - adjacencyList[currentCode][0].longitude, 2));
            double newDistance = distance[currentCode] + edgeWeight;

            if (newDistance < distance[neighbor.code]) {
                distance[neighbor.code] = newDistance;
                previous[neighbor.code] = currentCode;
                pq.push(make_pair(newDistance, neighbor.code));
            }
        }
    }

    vector<string> shortestPath;
    string currentCode = endCode;

    while (currentCode != startCode) {
        shortestPath.insert(shortestPath.begin(), currentCode);
        currentCode = previous[currentCode];
    }

    shortestPath.insert(shortestPath.begin(), startCode);

    return shortestPath;
}

vector<string> Graph::prim(const string& startCode) {
    unordered_map<string, bool> visited;
    unordered_map<string, pair<string, double>> mst;
    priority_queue<pair<double, pair<string, string>>, vector<pair<double, pair<string, string>>>, greater<pair<double, pair<string, string>>>> pq;

    // Initialize visited and MST
    for (const auto& entry : adjacencyList) {
        const string& code = entry.first;
        visited[code] = false;
        mst[code] = make_pair("", numeric_limits<double>::infinity());
    }

    pq.push(make_pair(0.0, make_pair(startCode, startCode)));

    while (!pq.empty()) {
        double weight = pq.top().first;
        string u = pq.top().second.first;
        string v = pq.top().second.second;
        pq.pop();

        if (visited[v]) {
            continue;
        }

        visited[v] = true;
        mst[v] = make_pair(u, weight);

        for (const Node& neighbor : adjacencyList[v]) {
            if (!visited[neighbor.code]) {
                double edgeWeight = sqrt(pow(neighbor.latitude - adjacencyList[v][0].latitude, 2) +
                                         pow(neighbor.longitude - adjacencyList[v][0].longitude, 2));
                pq.push(make_pair(edgeWeight, make_pair(v, neighbor.code)));
            }
        }
    }

    vector<string> mstEdges;
    for (const auto& entry : mst) {
        const string& u = entry.second.first;
        const string& v = entry.first;

        if (u != "" && v != "") {
            mstEdges.push_back(u + "->" + v);
        }
    }

    return mstEdges;
}

// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

void applyGraphsOnCountriesData(CSVParser& parser) {

    vector<vector<string>> data = parser.get_data();
    vector<string> header = parser.get_header();
    int rows = parser.get_rows();
    int cols = parser.get_cols();

    Graph graph;

    // Creating nodes and adding them to the graph
    for (const vector<string>& row : data) {
        Node node;
        node.code = row[0];
        node.latitude = to_double(row[1]);
        node.longitude = to_double(row[2]);
        node.name = row[3];

        graph.addNode(node);
    }

    // Adding edges between neighboring countries
    for (const vector<string>& row : data) {
        string code1 = row[0];
        double lat1 = to_double(row[1]);
        double lon1 = to_double(row[2]);

        for (const vector<string>& otherRow : data) {
            string code2 = otherRow[0];
            double lat2 = to_double(otherRow[1]);
            double lon2 = to_double(otherRow[2]);

            double distance = sqrt(pow(lat2 - lat1, 2) + pow(lon2 - lon1, 2));
            if (distance < 10.0) {
                graph.addEdge(code1, code2);
            }
        }
    }

    // Create menu for user
    int choice = 0;
    while (choice != 5) {
        cout << "1. Print BFS" << endl;
        cout << "2. Print DFS" << endl;
        cout << "3. Print Dijkstra" << endl;
        cout << "4. Print Prim" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string startCode;
            cout << "Enter start code: ";
            cin >> startCode;

            vector<string> bfs = graph.bfs(startCode);
            for (const string& code : bfs) {
                cout << code << "->";
            }
            cout << endl;
        } 
        else if (choice == 2)
        {
            string startCode;
            cout << "Enter start code: ";
            cin >> startCode;

            vector<string> dfs = graph.dfs(startCode);
            for (const string& code : dfs) {
                cout << code << "->";
            }
            cout << endl;
        }
        else if (choice == 3) {
            string startCode;
            string endCode;
            cout << "Enter start code: ";
            cin >> startCode;
            cout << "Enter end code: ";
            cin >> endCode;

            vector<string> dijkstra = graph.dijkstra(startCode, endCode);
            for (const string& code : dijkstra) {
                cout << code << endl;
            }
        } else if (choice == 4) {
            string startCode;
            cout << "Enter start code: ";
            cin >> startCode;

            vector<string> prim = graph.prim(startCode);
            for (const string& edge : prim) {
                cout << edge << endl;
            }
        }
        else if (choice == 5){
            cout << "Goodbye!" << endl;
            break;
        }
    }
}
