#include <iostream>

template <typename T>
class DataNode {
public:
    T data;
    DataNode* next;

    DataNode(const T& data) : data(data), next(nullptr) {}
};

template <typename T>
class vector {
private:
    DataNode<T>* head;
    size_t size;

public:
    vector() : head(nullptr), size(0) {}

    ~vector() {
        clear();
    }

    void push_back(const T& value) {
        DataNode<T>* newNode = new DataNode<T>(value);

        if (head == nullptr) {
            head = newNode;
        }
        else {
            DataNode<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }

        size++;
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }

        DataNode<T>* current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }

        return current->data;
    }

    size_t getSize() const {
        return size;
    }

    void clear() {
        while (head != nullptr) {
            DataNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }
};
