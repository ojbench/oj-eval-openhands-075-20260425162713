
#ifndef STR_HPP
#define STR_HPP

#include <algorithm>
#include <cstring>
#include <vector>

class str
{
private:
    char* data;
    size_t length;

public:
    str() : length(0) {
        data = new char[1];
        data[0] = '\0';
    }

    str(const char &c) : length(1) {
        data = new char[2];
        data[0] = c;
        data[1] = '\0';
    }

    str(const char *&& s_) {
        if (s_) {
            length = std::strlen(s_);
            data = new char[length + 1];
            std::strcpy(data, s_);
        } else {
            length = 0;
            data = new char[1];
            data[0] = '\0';
        }
    }

    str &operator=(const char *&& s_) {
        delete[] data;
        if (s_) {
            length = std::strlen(s_);
            data = new char[length + 1];
            std::strcpy(data, s_);
        } else {
            length = 0;
            data = new char[1];
            data[0] = '\0';
        }
        return *this;
    }

    str(const str &other) : length(other.length) {
        data = new char[length + 1];
        std::strcpy(data, other.data);
    }

    str &operator=(const str &other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            std::strcpy(data, other.data);
        }
        return *this;
    }

    char &operator[](size_t pos) {
        return data[pos];
    }

    size_t len() const {
        return length;
    }

    str join(const std::vector<str> &strs) const {
        if (strs.empty()) {
            return str("");
        }
        size_t total_len = 0;
        for (size_t i = 0; i < strs.size(); ++i) {
            total_len += strs[i].length;
        }
        total_len += (strs.size() - 1) * length;

        char* new_data = new char[total_len + 1];
        char* current = new_data;
        for (size_t i = 0; i < strs.size(); ++i) {
            std::strcpy(current, strs[i].data);
            current += strs[i].length;
            if (i < strs.size() - 1) {
                std::strcpy(current, data);
                current += length;
            }
        }
        *current = '\0';
        
        str result;
        delete[] result.data;
        result.data = new_data;
        result.length = total_len;
        return result;
    }

    str slice(size_t l, size_t r) const {
        if (l >= r || l >= length) {
            return str("");
        }
        if (r > length) r = length;
        size_t new_len = r - l;
        char* new_data = new char[new_len + 1];
        std::strncpy(new_data, data + l, new_len);
        new_data[new_len] = '\0';
        
        str result;
        delete[] result.data;
        result.data = new_data;
        result.length = new_len;
        return result;
    }

    ~str() {
        delete[] data;
    }
};

#endif
