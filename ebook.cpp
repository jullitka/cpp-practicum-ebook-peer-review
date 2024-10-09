#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <unordered_map>
using namespace std;
class ReadingSystem {
public:
    
    // сохраняет прогресс page пользователя user
    void SaveProgress(int user, int page) {
        
        if (user_progress_.find(user) != user_progress_.end()) {
            int old_page = user_progress_.at(user);
            if (page_user_count_.at(old_page) > 0) {
                page_user_count_[old_page] --;
            }
        }
        user_progress_[user] = page;
        page_user_count_[page] ++;
    }
    
    // выводит долю пользователей, не дочитавших до странице пользователя user
    double GetCheer(int user) {
        // если пользователь не добавлял прогресс
        if (user_progress_.find(user) == user_progress_.end()) {
            return 0;
        }
        // если пользователь единственный начал читать книгу
        if (user_progress_.size() == 1) {
            return 1;
        }
        
        int cur_user_page = user_progress_.at(user);
        int count_users = 0;
        
        for (auto [page, count] : page_user_count_) {
            if (page >= cur_user_page) {
                break;
            }
            count_users += count;
        }
        double result = static_cast<double> (count_users) / (user_progress_.size() - 1);
        return result;
    }

private:
    unordered_map<int, int> user_progress_; // прогресс пользователей
    map<int, int> page_user_count_; // количество пользовательей на каждой странице книги
};
// выводит значение функции
template <typename T>
void PrintValue(const T& value) {
    cout << value << endl;
}
// парсит команды и выполняет их
void ParseAndPrint(ReadingSystem& system, string request) {
    istringstream iss(request);
    string command;
    iss >> command;
    if (command == "CHEER") {
        int cur_user;
        iss >> cur_user;
        double cheer = system.GetCheer(cur_user);
        PrintValue(cheer);
        
    } else if (command == "READ") {
        int user, page;
        iss >> user >> page;
        system.SaveProgress(user, page);
    } else {
        cout << "Unknown command" << endl;
    }
}
// читает строки из потока и выполняет команды
void ReadAndProcessRequests(ReadingSystem& system, istream& input) {
    int request_count;
    input >> request_count >> ws;
    
    for (int i = 0; i < request_count; ++i) {
        string line;
        getline(input, line);
        ParseAndPrint(system, line);
    }
 }


int main() {
    ReadingSystem system;
    ReadAndProcessRequests(system, cin);
}