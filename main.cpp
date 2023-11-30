#include <vector>
#include <string>
#include <stdexcept>
#include <numeric>
#include <iostream>
#include <iomanip>

namespace read_manager {

using namespace std::literals;

class ReadManager {
public:
    ReadManager() {
        pages_read_by_id_.resize(max_user_id_);
        count_of_users_on_page_.resize(max_book_page_);
    }

    void Read(unsigned int user_id, unsigned int page_num) {
        if (user_id > max_user_id_ || page_num > max_book_page_) {
            throw std::invalid_argument("User ID or number of page incorrect!"s);
        }
        unsigned int prev_page_num = pages_read_by_id_[user_id];
        if  (prev_page_num == 0) {
            ++num_users_;
        }
        else {
            --count_of_users_on_page_[prev_page_num];
        }
        ++count_of_users_on_page_[page_num];
        pages_read_by_id_[user_id] = page_num;
    }

    double Cheer(unsigned int user_id) {
        if (user_id > max_user_id_) {
            throw std::invalid_argument("User IDincorrect!"s);
        }

        unsigned int page_num = pages_read_by_id_[user_id];
        if (!page_num) {
            return 0.0;
        }
        if (num_users_ == 1) {
            return 1.0;
        }
        auto iterator_of_page = count_of_users_on_page_.begin() + page_num;
        unsigned int num_user_with_less_pages = std::accumulate(count_of_users_on_page_.begin(), iterator_of_page, 0);
        return (num_user_with_less_pages) * 1.0 / (num_users_ - 1);
    }

private:
    const unsigned int max_book_page_ = 1e3;
    const unsigned int max_user_id_ = 1e5;
    unsigned int num_users_ = 0;
    std::vector<unsigned int> pages_read_by_id_;
    std::vector<unsigned int> count_of_users_on_page_;
};

void ReadManagerProcess(std::istream &input, std::ostream &output) {
    ReadManager manager;

    int query_count;
    input >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        std::string query_type;
        input >> query_type;
        unsigned int user_id;
        input >> user_id;

        if (query_type == "READ") {
            unsigned int page_count;
            input >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            output << std::setprecision(6) << manager.Cheer(user_id) << std::endl;
        }
    }
}

} //namespace read_manager

int main() {
    read_manager::ReadManagerProcess(std::cin, std::cout);
    return 0;
}
