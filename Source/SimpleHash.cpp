//
// Created by Matt on 16/03/2022.
//

#include "SimpleHash.h"

/**
 * Adds/Removes data into the table using data from a file
 * @param fileName : name of the file to load data from
 * @return : true if loaded successfully, false otherwise
 */
bool SimpleHash::ReadInDataFile(const std::string &fileName) {
    std::ifstream inFile(fileName);

    if (!inFile.is_open())    {
        std::cerr << "Could not open file \'" << fileName << "\'" << std::endl;
        return false;
    }

    std::string data;

    while (inFile >> data) {
        ProcessData(data);
    }

    inFile.close();
    return true;
}

/**
 * Searches the table to determine if a key exists
 * @param key : Key to search for
 * @param outIndex : The index the key is in the table if found
 * @return : True if found, false otherwise
 */
bool SimpleHash::Search(const std::string &key, int *outIndex) {
    int hash = Hash(key);

    // Attempt to find key in table checking each slot one-by-one
    for (int count = 0; count < Size; ++count) {
        if (m_entries[hash].Data == key && m_entries[hash].State == Status::OCCUPIED) {
            // Hit
            *outIndex = hash;
            return true;
        }

        if (m_entries[hash].State == Status::NEVER_USED)
            return false;

        hash = (hash + 1) % Size;
    }
    return false;
}

/**
 * Inserts a key into the table and sets slot to OCCUPIED
 * Does not insert if there is no free slot
 * @param key : Key to add
 */
void SimpleHash::Insert(const std::string &key) {
    if (!Search(key)) {
        // Find next available slot
        int index = FindNextIndex(key);
        if (index < 0) {
            std::cerr << "Table is full, cannot insert any more information" << std::endl;
        } else {
            m_entries[index].Data = key;
            m_entries[index].State = Status::OCCUPIED;
        }
    }
}

/**
 * Removes a key from the table and sets slot Status to TOMBSTONE
 * @param key
 */
void SimpleHash::Delete(const std::string &key) {
    int index;
    if (Search(key, &index)) {
        m_entries[index].Data = "";
        m_entries[index].State = Status::TOMBSTONE;
    }
}

/**
 * Prints the table in the format:
 *  Slot[i]: Status (state): Data (data)
 */
void SimpleHash::Print() {
    for (unsigned int i = 0; i < Size; ++i) {
        std::cout << "Slot [" << i << "]: Status (" <<
            StateToString(m_entries[i].State) << "): Data (" <<
            m_entries[i].Data << ")" << std::endl;
    }
}

/**
 * Processes a token by determining it's command
 * @param data : data token from file
 */
void SimpleHash::ProcessData(const std::string &data) {
    if (DataIsValid(data)) {
        if (data[0] == INSERT)
            Insert(&data[1]);
        else if (data[0] == DELETE)
            Delete(&data[1]);
    }
}

/**
 * Determines if a given data token is valid
 * Valid data is no more than 10 chars long and only lower case letters
 * @param data : Data token to validate
 * @return True if valid, false otherwise
 */
bool SimpleHash::DataIsValid(const std::string &data) {
    // Expect Insertion or Deletion command as first char
    // Only allow keys of size 10
    if (data.size() > 11 || data.size() < 2)
        return false;

    // Only allow lowercase english letters
    for (unsigned int i = 1; i < data.size(); ++i) {
        if (!std::islower(data[i]))
            return false;
    }
    return true;
}

/**
 * Hashes a key into it's hash value
 * @param key : Key to hash
 * @return Hash value
 */
int SimpleHash::Hash(const std::string &key) {
    return (key.back() - 'a') % Size;
}

/**
 * Finds the next free index of a key to determine where to add into the table
 * @param key : Key to add
 * @return -1 if no space available, otherwise next free index into the table
 */
int SimpleHash::FindNextIndex(const std::string &key) {
    int hash = Hash(key);

    for (int count = 0; count < Size; ++count) {
        if (m_entries[hash].State == Status::TOMBSTONE ||
            m_entries[hash].State == Status::NEVER_USED) {
            return hash;
        }

        hash = (hash + 1) % Size;
    }

    return -1;
}

/**
 * Converts a state into a printable string
 * @param state : State
 * @return State as a string
 */
std::string SimpleHash::StateToString(Status state) {
    switch (state) {
        case Status::OCCUPIED:
            return "occupied";
        case Status::TOMBSTONE:
            return "tombstone";
        case Status::NEVER_USED:
            return "never used";
        default:
            return "never used";
    }
}