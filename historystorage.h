#ifndef HISTORYSTORAGE_H
#define HISTORYSTORAGE_H

#include <vector>
#include <string>

class HistoryStorage {
public:
    static HistoryStorage& instance();
    void add(const std::string& password);
    std::vector<std::string> getAll() const;
    void clear();
    void loadFromFile();
    void saveToFile() const;

private:
    HistoryStorage() = default;
    std::vector<std::string> history;
};

#endif