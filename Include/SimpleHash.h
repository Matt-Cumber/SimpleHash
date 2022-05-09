//
// Created by Matt on 16/03/2022.
//
#pragma once

#include <iostream>
#include <string>
#include <fstream>

// States of a slot in the table
enum class Status {OCCUPIED, TOMBSTONE, NEVER_USED};

/**
 * Class implements a simple hash table
 */
class SimpleHash {

public:
    static const int Size = 10;
    const char INSERT{'I'}; // Character to define insertion command
    const char DELETE{'D'}; // Character to define deletion command

public:
    SimpleHash() = default;
    bool ReadInDataFile(const std::string &fileName);
    bool Search(const std::string &key, int *outIndex = nullptr);
    void Insert(const std::string &key);
    void Delete(const std::string &key);
    void Print();

private:
    void ProcessData(const std::string &data);
    bool DataIsValid(const std::string &data);
    int Hash(const std::string &key);
    int FindNextIndex(const std::string &key);
    std::string StateToString(Status state);

private:
    struct Entry {
        std::string Data = "";
        Status State = Status::NEVER_USED;
    };

    Entry m_entries[Size];
};