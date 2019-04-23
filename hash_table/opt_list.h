#ifndef OPT_LIST
#define OPT_LIST

#include <cstdio>
#include <iostream>
#include <list>
#include <string>
#include <algorithm>

template <class T>
class OptBidirectionalList {
private:
    const size_t INIT_BUF_SIZE = 32;
    const size_t EXTENSION_COEFF = 2;

    struct Node {
        T key;
        size_t next;
        size_t prev;
    };

    Node* buf_;
    size_t buf_size_{INIT_BUF_SIZE};
    size_t item_count_{0};

    void makeSentinels() {
        buf_[0].next = buf_size_ - 1;
        buf_[buf_size_ - 1].prev = 0;
    }

    void extend() {
        Node* new_buf = new Node[buf_size_ * EXTENSION_COEFF];

        for (size_t i = 0; i <= item_count_; ++i) {
            new_buf[i] = buf_[i];
        }
        buf_size_ *= EXTENSION_COEFF;
        buf_[item_count_].next = buf_size_ - 1;
        buf_[buf_size_ - 1].prev = item_count_;

        delete[] buf_;
        buf_ = new_buf;
    }

public:
    OptBidirectionalList() {
        buf_ = new Node[INIT_BUF_SIZE];
        makeSentinels();
    }

    size_t size() const {
        return item_count_;
    }

    void insert(const T& item) {
        if (item_count_ + 2 == buf_size_) {
            extend();
        }
        buf_[item_count_].next = item_count_ + 1;
        ++item_count_;
        buf_[item_count_].key = item;
        buf_[item_count_].next = buf_size_ - 1;
        buf_[buf_size_ - 1].prev = item_count_;
    }

    bool find(const T& item) {
       for (size_t i = 1; i <= item_count_; ++i) {
          if (buf_[i].key == item) {
              return true;
          }
       }

       return false;
    }
};


template <class T>
class OptList {
private:
    const size_t INIT_BUF_SIZE = 32;
    const size_t EXTENSION_COEFF = 2;

    T* buf_{nullptr};
    size_t buf_size_{INIT_BUF_SIZE};
    size_t item_count_{0};

    void extend() {
        T* new_buf = new T[buf_size_ * EXTENSION_COEFF];

        for (size_t i = 0; i <= item_count_; ++i) {
            new_buf[i] = buf_[i];
        }
        buf_size_ *= EXTENSION_COEFF;

        delete[] buf_;
        buf_ = new_buf;
    }
public:
    OptList() {
        buf_ = new T[INIT_BUF_SIZE];
    }

    size_t size() const {
        return item_count_;
    }

    void insert(const T& item) {
        if (item_count_ + 2 == buf_size_) {
            extend();
        }
        buf_[++item_count_] = item;
    }

    bool find(const T& item) {
       for (size_t i = 1; i <= item_count_; ++i) {
          if (buf_[i] == item) {
              return true;
          }
       }

       return false;
    }
};
#endif
