#include <cstdio>
#include <iostream>
#include <list>
#include <string>
#include <algorithm>

class OptHashTable {
private:
    static const long long MODULO = 100007;
    static const long long P = 127;

    struct Bucket {
        std::list<std::string> values;

        void add(const std::string& s) {
            values.push_back(s);
        }

        bool find(const std::string& s) {
            return std::find(values.begin(), values.end(), s) != values.end();
        }
    }; 


    Bucket buckets[MODULO];

public:
    OptHashTable() {
        std::cout << "Я родился!\n";
    }

    long long getHash(const std::string& s) {
        long long result = 0;

        for (size_t i = 0; i < s.size(); ++i) {
            result = (result * P) % MODULO;
        }
        return result;
    }

    bool insert(const std::string& s) {
        long long bucket_num = getHash(s);

        if (buckets[bucket_num].find(s)) {
            return false;
        }

        buckets[bucket_num].add(s);
        return true;
    }

    bool find(const std::string& s) {
        return buckets[getHash(s)].find(s);
    }
};
