#include "historystorage.h"
#include <fstream>

void HistoryStorage::add(const std::string& password) {
    history.push_back(password);
    saveToFile();
}
std::vector<std::string> HistoryStorage::getAll() const { return history; }
void HistoryStorage::clear() { history.clear(); saveToFile(); }
void HistoryStorage::loadFromFile() {
    std::ifstream file("history.txt");
    std::string line;
    while (std::getline(file, line)) if (!line.empty()) history.push_back(line);
}
void HistoryStorage::saveToFile() const {
    std::ofstream file("history.txt");
    for (const auto& p : history) file << p << "\n";
}
HistoryStorage& HistoryStorage::instance() { static HistoryStorage inst; return inst; }