


class Heap {
    private:
        struct HeapNode {
            Node data;
            HeapNode* left;
            HeapNode* right;
        };
        HeapNode* root = NULL;
        int size = 0;
    public:
        Heap();
        ~Heap();
        void insert(Node data);
        void remove(Node data);
        void print();
        int getSize();
        Node* getRoot();
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

Heap::Heap() {
    root = NULL;
    size = 0;
}

Heap::~Heap() {
    clear();
}

void Heap::insert(Node data) {
    HeapNode* newNode = new HeapNode;
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    if (root == NULL) {
        root = newNode;
    } else {
        HeapNode* curr = root;
        while (curr != NULL) {
            if (curr->left == NULL) {
                curr->left = newNode;
                break;
            } else if (curr->right == NULL) {
                curr->right = newNode;
                break;
            } else {
                curr = curr->left;
            }
        }
    }
    size++;
}

void Heap::remove(Node data) {
    HeapNode* curr = root;
    HeapNode* prev = NULL;
    while (curr != NULL) {
        if (curr->data.name == data.name) {
            if (curr->left == NULL && curr->right == NULL) {
                if (prev == NULL) {
                    root = NULL;
                } else if (prev->left == curr) {
                    prev->left = NULL;
                } else {
                    prev->right = NULL;
                }
            } else if (curr->left == NULL) {
                if (prev == NULL) {
                    root = curr->right;
                } else if (prev->left == curr) {
                    prev->left = curr->right;
                } else {
                    prev->right = curr->right;
                }
            } else if (curr->right == NULL) {
                if (prev == NULL) {
                    root = curr->left;
                } else if (prev->left == curr) {
                    prev->left = curr->left;
                } else {
                    prev->right = curr->left;
                }
            } else {
                HeapNode* temp = curr->right;
                while (temp->left != NULL) {
                    temp = temp->left;
                }
                curr->data = temp->data;
                temp->data = data;
                curr = temp;
                prev = NULL;
                continue;
            }
            delete curr;
            size--;
            break;
        } else if (curr->data.name < data.name) {
            prev = curr;
            curr = curr->left;
        } else {
            prev = curr;
            curr = curr->right;
        }
    }
}

void Heap::print() {
    if (root == NULL) {
        cout << "Empty" << endl;
    } else {
        queue<HeapNode*> q;
        q.push(root);
        while (!q.empty()) {
            HeapNode* curr = q.front();
            q.pop();
            cout << curr->data.name << " ";
            if (curr->left != NULL) {
                q.push(curr->left);
            }
            if (curr->right != NULL) {
                q.push(curr->right);
            }
        }
        cout << endl;
    }
}

int Heap::getSize() {
    return size;
}

Node* Heap::getRoot() {
    return &root->data;
}

Node* Heap::linearSearch(string name) {
    HeapNode* curr = root;
    while (curr != NULL) {
        if (curr->data.name == name) {
            return &curr->data;
        } else if (curr->data.name < name) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return NULL;
}

Node* Heap::binarySearch(string name) {
    HeapNode* curr = root;
    while (curr != NULL) {
        if (curr->data.name == name) {
            return &curr->data;
        } else if (curr->data.name < name) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return NULL;
}

void Heap::sort() {
    bubbleSort();
}

void Heap::swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void Heap::reverse() {
    HeapNode* curr = root;
    while (curr != NULL) {
        swap(&curr->data, &curr->left->data);
        curr = curr->left;
    }
}

void Heap::clear() {
    queue<HeapNode*> q;
    q.push(root);
    while (!q.empty()) {
        HeapNode* curr = q.front();
        q.pop();
        if (curr->left != NULL) {
            q.push(curr->left);
        }
        if (curr->right != NULL) {
            q.push(curr->right);
        }
        delete curr;
    }
    root = NULL;
    size = 0;
}

void Heap::bubbleSort() {
    for (int i = 0; i < size; i++) {
        HeapNode* curr = root;
        while (curr != NULL) {
            if (curr->left != NULL && curr->data.name > curr->left->data.name) {
                swap(&curr->data, &curr->left->data);
            }
            if (curr->right != NULL && curr->data.name > curr->right->data.name) {
                swap(&curr->data, &curr->right->data);
            }
            curr = curr->left;
        }
    }
}

void Heap::selectionSort() {
    HeapNode* curr = root;
    while (curr != NULL) {
        HeapNode* min = curr;
        HeapNode* temp = curr;
        while (temp != NULL) {
            if (temp->data.name < min->data.name) {
                min = temp;
            }
            temp = temp->left;
        }
        swap(&curr->data, &min->data);
        curr = curr->left;
    }
}

void Heap::mergeSort() {
        // todo
}


// =======================================================

void testHeap(CSVParser &parser){

    vector<vector<string>> data = parser.get_data();

    Heap heap = Heap();

     for (const vector<string>& row : data) {
        string code = row[0];
        double lat = to_double(row[1]);
        double lon = to_double(row[2]);
        string name = row[3];

        Node node = Node(code, lat, lon, name);
        heap.insert(node);
     }

    cout << "Heap size: " << heap.getSize() << endl;

    // make a menu based program to test all functions
    int choice = 0;
    cout << "1. Print" << endl;
    cout << "2. Insert" << endl;
    cout << "3. Remove" << endl;
    cout << "4. Linear Search" << endl;
    cout << "5. Binary Search" << endl;
    cout << "6. Sort" << endl;
    cout << "7. Reverse" << endl;
    cout << "8. Clear" << endl;
    cout << "9. Exit" << endl;

    cout << "Enter choice: ";
    cin >> choice;

    if(choice == 1){
        heap.print();
    }
    else if(choice == 2){
        string code;
        double lat;
        double lon;
        string name;

        cout << "Enter code: ";
        cin >> code;
        cout << "Enter lat: ";
        cin >> lat;
        cout << "Enter lon: ";
        cin >> lon;
        cout << "Enter name: ";
        cin >> name;

        Node node = Node(code, lat, lon, name);
        heap.insert(node);
    }
    else if(choice == 3){
        string name;
        cout << "Enter name: ";
        cin >> name;

    // get node through name
        Node* node = heap.linearSearch(name);
        if(node != NULL){
            heap.remove(*node);
            cout<<"Deleted Successfully" <<endl;
        }
        else{
            cout << "Not found" << endl;
        }
    }
    else if(choice == 4){
        string name;
        cout << "Enter name: ";
        cin >> name;
        Node* node = heap.linearSearch(name);
        if(node != NULL){
            cout << node->name << endl;
        }
        else{
            cout << "Not found" << endl;
        }
    }
    else if(choice == 5){
        string name;
        cout << "Enter name: ";
        cin >> name;
        Node* node = heap.binarySearch(name);
        if(node != NULL){
            cout << node->name << endl;
        }
        else{
            cout << "Not found" << endl;
        }
    }
    else if(choice == 6){
        heap.sort();
    }
    else if(choice == 7){
        heap.reverse();
    }
    else if(choice == 8){
        heap.clear();
    }
    else if(choice == 9){
        exit(0);
    }
    else{
        cout << "Invalid choice" << endl;
    }

}