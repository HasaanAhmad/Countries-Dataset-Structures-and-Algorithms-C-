#ifndef ARRAY_H
#define ARRAY_H
#include "countries.h"

// Making array of Nodes

void bubbleSort(Node arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].name > arr[j + 1].name) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}
// Quick Sort for string


void insertionSort(Node arr[], int size) {
    for (int i = 1; i < size; i++) {
        Node key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].name > key.name) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void mergeSort(Node arr[], int l, int r) {
    if (l >= r) {
        return;
    }
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    Node* left = new Node[m - l + 1];
    Node* right = new Node[r - m];

    for (int i = 0; i < m - l + 1; i++) {
        left[i] = arr[l + i];
    }
    for (int i = 0; i < r - m; i++) {
        right[i] = arr[m + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i < m - l + 1 && j < r - m) {
        if (left[i].name <= right[j].name) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < m - l + 1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < r - m) {
        arr[k] = right[j];
        j++;
        k++;
    }
}


void LinearSearch(Node arr[], int size, string name) {
    for (int i = 0; i < size; i++) {
        if (arr[i].name == name) {
            cout << "Found at index: " << i << endl;
            return;
        }
    }
    cout << "Not found" << endl;
}

void printArray(Node arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i].name << endl;
    }
}


void BinarySearch(Node arr[], int size, string name) {
    int l = 0;
    int r = size - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m].name == name) {
            cout << "Found at index: " << m << endl;
            return;
        }
        if (arr[m].name < name) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    cout << "Not found" << endl;
}


void applyArrayOperations(CSVParser& parser) {

    vector<vector<string>> data = parser.get_data();

    Node* arr = new Node[data.size()];

    int i = 0;
    for (const vector<string>& row : data) {
        string code = row[0];
        double lat = to_double(row[1]);
        double lon = to_double(row[2]);
        string name = row[3];

        Node node = Node(code, lat, lon, name);
        arr[i] = node;
        i++;
    }
        int choice;
    
    while (true) {
        cout << "1. Bubble Sort" << endl;
        cout << "2. Insertion Sort" << endl;
        cout << "3. Merge Sort" << endl;
        cout << "4. Linear Search" << endl;
        cout << "5. Binary Search" << endl;
        cout << "6. Print Array" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1) {
            bubbleSort(arr, data.size());
        } else if (choice == 2) {
            insertionSort(arr, data.size());
        } else if (choice == 3) {
            mergeSort(arr, 0, data.size() - 1);
        } else if (choice == 4) {
            string name;
            cout << "Enter name to search: ";
            cin >> name;
            LinearSearch(arr, data.size(), name);
        } else if (choice == 5) {
            string name;
            cout << "Enter name to search: ";
            cin >> name;
            BinarySearch(arr, data.size(), name);
        } else if (choice == 6) {
            printArray(arr, data.size());
        } else if (choice == 7) {
            break;
        } else {
            cout << "Invalid choice" << endl;
        }
}
}
    // Menu based program

// Making array of Nodes

#endif