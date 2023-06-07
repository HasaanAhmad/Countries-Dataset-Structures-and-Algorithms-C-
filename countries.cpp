
// Revision History:
// June 3, 2023 Created by Mujtaba SP22-BSE-036

#include "countries.h" 
#include "list.h" // use applyListOnCountriesData() function
#include "binary_tree.h" // use applyBinaryTreeOnCountriesData() function
#include "graphs.h" // use applyGraphsOnCountriesData() function
#include "hash.h" // use applyHashOnCountriesData() function
#include "heaps.h" // use applyHeapsOnCountriesData() function
#include "array.h" // use applyArrayOnCountriesData() function
#include "AVL.h" // use applyAVLOnCountriesData() function

// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

void datasetTest(CSVParser parser){
    cout << "Calling test functions on dataset... @datasetTest" << endl;
    vector<vector<string>> data = parser.get_data();
    vector<string> header = parser.get_header();
    int rows = parser.get_rows();
    int cols = parser.get_cols();

    vector<Node> nodes;
    for (int i = 0; i < rows; i++) {
        Node node;
        node.code = data[i][0];
        node.latitude = to_double(data[i][1]);
        node.longitude = to_double(data[i][2]);
        node.name = data[i][3];
        nodes.push_back(node);
    }

    cout << "Total countries: " << rows << endl;
    cout << "Total columns: " << cols << endl;

    cout << "First country: " << nodes[0].name << endl;
    cout << "Last country: " << nodes[rows - 1].name << endl;
}

// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

// TODO: Make menu-based to select between furthur operations
void apply(CSVParser& parser){
    // Create a menu-based program to select between furthur operations
    cout << "Choose the opeartion you want to perform" << endl;
    cout << "1. List" << endl;
    cout << "2. Binary Tree" << endl;
    cout << "3. Graphs" << endl;
    cout << "4. Hash" << endl;
    cout << "5. Heaps" << endl;
    cout<< "6. Array" << endl;
    cout << "7. AVL" << endl;
    cout << "8. Exit" << endl;

  
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    cout << endl;
    switch (choice)
    {
    case 1:
        applyListOnCountriesData(parser);
        break;
    case 2:
        applyBinaryTreeOnCountriesData(parser);
        break;
    case 3:
        applyGraphsOnCountriesData(parser);
        break;
    case 4:
        // print stack trace in case of execption to prevent crash
        try {
            applyHashOnCountriesData(parser);
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
        break;
    case 5:
        testHeap(parser);
        break;
    case 6:
        applyArrayOperations(parser);
        break;
    case 7:
        applyAVLOnCountriesData(parser);
        break;
    case 8:
        exit(0);
        break;
    default:
        break;
    }

}

// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

int main() {

    CSVParser parser("countries.csv");
    parser.parse();

    datasetTest(parser);

    cout << endl;
    cout << "- - - - - - - - - - - - - - - -" << endl;
    cout << "- - - - - - - - - - - - - - - -" << endl;
    cout << endl;

    apply(parser);

    return 0;
}

