
// TODO:
// 1. This list implementation is tested: NO (PENDING TEST)
// 2. This list is applied on countries data: NO (PENDING IMPLEMENTATION)

//  START -

// Linked List Implementation

// Revision History:
// 1. June 3, 2023 - Initial commit - Hasaan SP22-BSE-017
// 2. June 3, 2023 - Modification - Mujtaba SP22-BSE-036

#ifndef LIST_H
#define LIST_H

#include "countries.h"

class List {
    private:
        struct ListNode {
            Node data; // Node is the global Node defined in countries.h
            ListNode* next; // Pointer to the next "list" node (not global node)
        };
        ListNode* head = NULL;
        ListNode* tail = NULL;
        int size = 0;
    public:
        List();
        ~List();
        void insert(Node data);
        void remove(Node data);
        void print();
        int getSize();
        Node* getHead();
        Node* getTail();
        Node* linearSearch(string name);
        Node* binarySearch(string name);
        void sort();
        void swap(Node* a, Node* b);
        void reverse();
        void clear();

        // Additionals
        void bubbleSort();
        void selectionSort();
        void mergeSort();
};

List::List() {
    head = NULL;
    tail = NULL;
    size = 0;
}

List::~List() {
    clear();
}

void List::insert(Node data) {
    ListNode* newNode = new ListNode;
    newNode->data = data;
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

void List::remove(Node data) {
    ListNode* curr = head;
    ListNode* prev = NULL;
    while (curr != NULL) {
        if (curr->data == data) {
            if (prev == NULL) {
                head = curr->next;
            } else {
                prev->next = curr->next;
            }
            delete curr;
            size--;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void List::print() {
    ListNode* curr = head;
    while (curr != NULL) {
        cout << curr->data.name << endl;
        curr = curr->next;
    }
}

int List::getSize() {
    return size;
}

Node* List::getHead() {
    return &head->data;
}

Node* List::getTail() {
    return &tail->data;
}

Node* List::linearSearch(string name) {
    ListNode* curr = head;
    while (curr != NULL) {
        if (curr->data.name == name) {
            return &curr->data;
        }
        curr = curr->next;
    }
    return NULL;
}

// Binary method to search through the list. It should convert Letters of Countries to ASCII and then compare them.
Node* List::binarySearch(string name) {
    ListNode* curr = head;
    ListNode* prev = NULL;
    while (curr != NULL) {
        if (curr->data.name == name) {
            if (prev == NULL) {
                return &head->data;
            } else {
                return &prev->data;
            }
        }
        prev = curr;
        curr = curr->next;
    }
    return NULL;
}


// General purpose sort
void List::sort() {
    ListNode* curr = head;
    ListNode* index = NULL;
    if (head == NULL) {
        return;
    } else {
        while (curr != NULL) {
            index = curr->next;
            while (index != NULL) {
                if (curr->data.name.compare(index->data.name) > 0) {
                    swap(&curr->data, &index->data);
                }
                index = index->next;
            }
            curr = curr->next;
        }
    }
}

void List::swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void List::reverse() {
    ListNode* curr = head;
    ListNode* prev = NULL;
    ListNode* next = NULL;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

void List::clear() {
    ListNode* curr = head;
    ListNode* next = NULL;
    while (curr != NULL) {
        next = curr->next;
        delete curr;
        curr = next;
    }
    head = NULL;
    tail = NULL;
    size = 0;
}

// Additional Functions

void List::bubbleSort() {
    ListNode* curr = head;
    ListNode* index = NULL;
    if (head == NULL) {
        return;
    } else {
        while (curr != NULL) {
            index = curr->next;
            while (index != NULL) {
                if (curr->data.name.compare(index->data.name) > 0) {
                    swap(&curr->data, &index->data);
                }
                index = index->next;
            }
            curr = curr->next;
        }
    }
    // Print the list
    print();
}

void List::selectionSort() {
    ListNode* curr = head;
    ListNode* index = NULL;
    ListNode* min = NULL;
    if (head == NULL) {
        return;
    } else {
        while (curr != NULL) {
            min = curr;
            index = curr->next;
            while (index != NULL) {
                if (min->data.name.compare(index->data.name) > 0) {
                    min = index;
                }
                index = index->next;
            }
            swap(&curr->data, &min->data);
            curr = curr->next;
        }
    }
    // Print the list
    print();
}

void List::mergeSort() {
    ListNode* curr = head;
    ListNode* index = NULL;
    ListNode* min = NULL;
    if (head == NULL) {
        return;
    } else {
        while (curr != NULL) {
            min = curr;
            index = curr->next;
            while (index != NULL) {
                if (min->data.name.compare(index->data.name) > 0) {
                    min = index;
                }
                index = index->next;
            }
            swap(&curr->data, &min->data);
            curr = curr->next;
        }
    }
    // Print the list
    print();

}

// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

void applyListOnCountriesData(CSVParser& parser){
    cout << "Applying List on Countries Data" << endl;

    vector<vector<string>> data = parser.get_data();

    List list = List();

    for (const vector<string>& row : data) {
        string code = row[0];
        double lat = to_double(row[1]);
        double lon = to_double(row[2]);
        string name = row[3];

        Node node = Node(code, lat, lon, name);
        list.insert(node);
    }

    cout << "List Size: " << list.getSize() << endl;

    // Ask for list operations (including all searches and sorts)
    // and make it menu-based but except insert, delete.
    int option = 0;

    while (option != 9) {
        cout << "1. Linear Search" << endl;
        cout << "2. Binary Search" << endl;
        cout << "3. Bubble Sort" << endl;
        cout << "4. Selection Sort" << endl;
        cout << "5. Merge Sort" << endl;
        cout << "6. Reverse" << endl;
        cout << "7. Print" << endl;
        cout << "8. Clear" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter Option: ";
        cin >> option;

        if (option == 1) {
            string name;
            cout << "Enter Name: ";
            cin >> name;
            Node* node = list.linearSearch(name);
            if (node != NULL) {
                cout << "Found: " << node->name << endl;
            } else {
                cout << "Not Found" << endl;
            }
        } else if (option == 2) {
            string name;
            cout << "Enter Name: ";
            cin >> name;
            Node* node = list.binarySearch(name);
            if (node != NULL) {
                cout << "Found: " << node->name << endl;
            } else {
                cout << "Not Found" << endl;
            }
        } else if (option == 3) {
            list.bubbleSort();
        } else if (option == 4) {
            list.selectionSort();
        } else if (option == 5) {
            list.mergeSort();
        } else if (option == 6) {
            list.reverse();
        } else if (option == 7) {
            list.print();
        } else if (option == 8) {
            list.clear();
        } else if (option == 9) {
            break;
        } else {
            cout << "Invalid Option" << endl;
        }
    }


}


#endif

// - END
