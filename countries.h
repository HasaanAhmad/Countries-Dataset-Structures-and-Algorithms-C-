
// Revision History:
// June 3, 2023 Created by Mujtaba SP22-BSE-036
// June 3, 2023 Modified by Mujtaba SP22-BSE-036 : Added operator overloading for Node

#ifndef COUNTRIES_H
#define COUNTRIES_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <queue>
#include <stack>
#include <cmath>
#include <unordered_map>
#include <limits>


using namespace std;

// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

typedef struct Node {
    string code;
    double latitude;
    double longitude;
    string name;

    Node() {
        this->code = "";
        this->latitude = 0.0;
        this->longitude = 0.0;
        this->name = "";
    }

    Node(string code, double latitude, double longitude, string name) {
        this->code = code;
        this->latitude = latitude;
        this->longitude = longitude;
        this->name = name;
    }

    bool operator==(const Node& other) const {
        return (this->code.compare(other.code) == 0 &&
        this->latitude == other.latitude &&
        this->longitude == other.longitude &&
        this->name.compare(other.name) == 0);
    }

    bool operator!=(const Node& other) const {
        return (this->code.compare(other.code) != 0 ||
        this->latitude != other.latitude ||
        this->longitude != other.longitude ||
        this->name.compare(other.name) != 0);
    }

} Node;

// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

// Description: The implementation of the CSVParser class.
// The CSVParser class is used to parse a CSV file and store the data in a
// 2D vector of strings.
// All data is get in the form of string and then converted to the required
// data type by a separate pass (defined later).

class CSVParser {
    private:
        string filename;
        vector<vector<string>> data;
        vector<string> header;
        int rows;
        int cols;

    public:
        CSVParser(string filename);
        void parse();
        vector<vector<string>> get_data();
        vector<string> get_header();
        int get_rows();
        int get_cols();
};


CSVParser::CSVParser(string filename) {
    this->filename = filename;
    this->rows = 0;
    this->cols = 0;
}


void CSVParser::parse() {
    ifstream file(this->filename);
    string line;
    int row = 0;
    while (getline(file, line)) {
        vector<string> row_data;
        stringstream ss(line);
        string cell;
        while (getline(ss, cell, ',')) {
            row_data.push_back(cell);
        }
        if (row == 0) {
            this->header = row_data;
            this->cols = row_data.size();
        } else {
            this->data.push_back(row_data);
        }
        row++;
    }
    this->rows = row - 1;
}


vector<vector<string>> CSVParser::get_data() {
    return this->data;
}


vector<string> CSVParser::get_header() {
    return this->header;
}


int CSVParser::get_rows() {
    return this->rows;
}


int CSVParser::get_cols() {
    return this->cols;
}

// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

// Utility Methods

// This function takes a given string value and converts it to the actual type to which
// it belongs. For example, if the string value is "123", it will be converted to the
// integer 123. And if its 123.123, it will be converted to the float 123.123.
// It will be overloaded for different data types.

double to_double(string value) {
    try {
        return stod(value);
    } catch (const std::invalid_argument& e) {
        // Handle the error here, such as returning a default value or printing an error message
        // std::cerr << "Failed to convert string to double: " << e.what() << " [IGNORE IT]" << std::endl;
        return 0.0; // Default value or appropriate error handling
    }
}

// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

#endif // COUNTRIES_H
