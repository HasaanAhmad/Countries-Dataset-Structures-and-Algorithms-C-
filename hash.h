
// Revision History:
// June 6, 2023 Created by Haider SP22-BSE-033
#ifndef HASH_H
#define HASH_H




#include "countries.h"


const int TABLE_SIZE = 300; // Size of the hash table array

class HashTable {
private:
    Node table[TABLE_SIZE]; // Array to store country information

    // Hash function to convert a country code to an index
    int hashFunction(const std::string& countryCode) {
        int hash = 0;
        for (char c : countryCode) {
            hash += static_cast<int>(c);
        }
        return hash % TABLE_SIZE;
    }

public:
    // Insert a new country info into the hash table
    void insert(const Node& countryInfo) {
        int index = hashFunction(countryInfo.code);
        if (table[index].code.empty()) {
            table[index] = countryInfo;
        } else {
            // Handle collision by linear probing
            int i = (index + 1) % TABLE_SIZE;
            while (i != index && !table[i].code.empty()) {
                i = (i + 1) % TABLE_SIZE;
            }
            if (i == index) {
                std::cerr << "Hash table is full. Cannot insert country: "
                          << countryInfo.code << std::endl;
            } else {
                table[i] = countryInfo;
            }
        }
    }

    // Retrieve the country info for a given country code
    Node* get(const std::string& countryCode) {
        int index = hashFunction(countryCode);
        if (table[index].code == countryCode) {
            return &table[index];
        } else {
            // Handle collision by linear probing
            int i = (index + 1) % TABLE_SIZE;
            while (i != index && table[i].code != countryCode) {
                i = (i + 1) % TABLE_SIZE;
            }
            if (i == index) {
                return nullptr; // Country code not found
            } else {
                return &table[i];
            }
        }
    }
};

void applyHashOnCountriesData(CSVParser& parser) {
    HashTable hashTable;

    vector<vector<string>> data = parser.get_data();
    for (const vector<string>& row : data) {
        Node countryInfo = {row[0], to_double(row[1]), to_double(row[2]), row[3]};
        hashTable.insert(countryInfo);
    }
    // Create a menu for searching
    cout << "Choose the opeartion you want to perform" << endl;
    cout << "1. Search by country code" << endl;
    cout << "2. Exit" << endl;

    int choice;
    do {
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                string countryCode;
                cout << "Enter country code: ";
                cin >> countryCode;
                Node* countryInfo = hashTable.get(countryCode);
                if (countryInfo == nullptr) {
                    cout << "Country code not found" << endl;
                } else {
                    cout << "Country name: " << countryInfo->name << endl;
                    cout << "Latitude: " << countryInfo->latitude << endl;
                    cout << "Longitude: " << countryInfo->longitude << endl;
                    cout << "Country code: " << countryInfo->code << endl;
                }
                break;
            }
            case 2: {
                cout << "Exiting..." << endl;
                break;
            }
            default: {
                cout << "Invalid choice" << endl;
                break;
            }
        }
    } while (choice != 2);
}
#endif //HASH_H