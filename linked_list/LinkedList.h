#ifndef LinkedList_h
#define LinkedList_h

#include <vector>
#include <iostream>
#include <stdexcept>

template <typename T>
class LinkedList {

public:

    class Node {

    public:

        T data;
        Node* next;
        Node* prev;

        Node() { data = 0; next = nullptr; prev = nullptr; }
        explicit Node(const T &_data) { data = _data; next = nullptr; prev = nullptr; }

        Node* duplicate(Node* node) {

            auto copy = new Node (node->data);

            copy->next = node->next;

            copy->prev = node->prev;

            return copy;

        }



    };

    void Set(const LinkedList<T>&);
    void removeNode(Node* node);
    const T* getData();

    void PrintForward();
    void PrintReverse();
    void PrintForwardRecursive(const Node*) const;
    void PrintReverseRecursive(const Node*) const;

    unsigned int NodeCount() const { return count; }
    void FindAll(std::vector<Node*>& outData, const T&) const;
    const Node* Find(const T&) const;
    Node* Find(const T&);
    const Node* GetNode(unsigned int) const;
    Node* GetNode(unsigned int);
    Node* Head() { return first; }
    const Node* Head() const { return first; }
    Node* Tail() { return last; }
    const Node* Tail() const { return last; }

    void AddHead(const T&);
    void AddTail(const T&);
    void AddNodesHead(const T*, unsigned int);
    void AddNodesTail(const T*, unsigned int);
    void InsertAfter(Node*, const T&);
    void InsertBefore(Node*, const T&);
    void InsertAt(const T&, unsigned int);

    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T&);
    bool RemoveAt(int);
    void Clear();

    const T& operator[](unsigned int) const;
    T& operator[](unsigned int);
    bool operator==(const LinkedList<T>&) const;
    LinkedList<T>& operator=(const LinkedList<T>&);

    LinkedList();
    LinkedList(const LinkedList<T>& ll) { Set(ll); };
    ~LinkedList() { Clear(); }

private:

    unsigned int count;
    LinkedList<T>::Node* first;
    LinkedList<T>::Node* last;

};

template <typename T>
LinkedList<T>::LinkedList() {

    this->count = 0;
    this->first = nullptr;
    this->last = nullptr;

}

template <typename T>
void LinkedList<T>::Set(const LinkedList<T>& list) {

    count = 0;
    first = nullptr;
    last = nullptr;

    Node* tail; Node* curtail;

    for (unsigned int x = 0; x < list.NodeCount(); x++) {

        tail = new Node (list[x]);

        if (x > 0) {

            tail->prev = curtail;
            curtail->next = tail;

        }

        else if (x == 0) {

            first = tail;

        }

        curtail = tail;

        count++;

    }

    last = tail;

}

template <typename T>
void LinkedList<T>::Clear() {

    while (count > 0)
        RemoveTail();

}

template <typename T>
void LinkedList<T>::removeNode(LinkedList<T>::Node* node) {

    Node* curr = first;

    for (unsigned int x = 0; x < count; x++) {

        if (curr == node)
            break;

        curr = curr->next;

    }

    if (curr != node)
        throw std::runtime_error("No such node");

    Node* a = curr->next;

    Node* b = curr->prev;

    delete curr;

    count--;

    a->prev = b;
    b->next = a;

}

template <typename T>
bool LinkedList<T>::RemoveHead() {

    if (count == 0)
        return false;

    Node* pos = first->next;

    delete first;

    first = pos;

    if(count > 1)
        first->prev = nullptr;

    else {

        first = nullptr;
        last = nullptr;

    }

    count--;

    return true;

}

template <typename T>
bool LinkedList<T>::RemoveTail() {

    if (count == 0)
        return false;

    Node* pos = last->prev;

    delete last;

    last = pos;

    if (count > 1)
        last->next = nullptr;

    else {

        first = nullptr;
        last = nullptr;

    }

    count--;

    return true;

}

template <typename T>
unsigned int LinkedList<T>::Remove(const T& data) {

    unsigned int c = 0;

    Node* curr = first;

    while (curr != nullptr) {

        if(curr->data == data) {

            Node* outlaw = curr;

            curr = curr->next;

            removeNode(outlaw);

            c++;

        }

        else curr = curr->next;

    }

    return c;

}

template <typename T>
bool LinkedList<T>::RemoveAt(int index) {

    if(index < 0 || index >= (int) count)
        return false;

    Node* curr = first;

    for (int x = 0; x < index; x++)
        curr = curr->next;

    removeNode(curr);

    return true;

}

template <typename T>
const T* LinkedList<T>::getData() {

    T* data = new T [count];

    Node* curr = first;

    for (unsigned int x = 0; x < count; x++) {

        data[x] = curr->data;
        curr = curr->next;

    }

    return data;

}

template <typename T>
void LinkedList<T>::PrintForward() {

    LinkedList<T>::Node* curr = first;

    do {

        std::cout << curr->data << "\n";
        curr = curr->next;

    } while (curr != nullptr);


}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {

    if (node != nullptr) {

        std::cout << node->data << "\n";
        PrintForwardRecursive(node->next);

    }

}

template <typename T>
void LinkedList<T>::PrintReverse() {

    LinkedList<T>::Node* curr = last;

    do {

        std::cout << curr->data << "\n";
        curr = curr->prev;

    } while (curr != nullptr);

}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const LinkedList<T>::Node* node) const {

    if (node != nullptr) {

        std::cout << node->data << "\n";
        PrintReverseRecursive(node->prev);

    }

}

template <typename T>
void LinkedList<T>::FindAll(std::vector<LinkedList<T>::Node*>& outData, const T& data) const {

    Node* curr = first;

    do {

        if (curr->data == data)
            outData.push_back(curr);

        curr = curr->next;

    } while (curr != nullptr);

}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {

    Node* curr = first;

    for (unsigned int x = 0; x < count; x++) {

        if (curr->data != data)
            curr = curr->next;

        else return curr;

    }

    return nullptr;

}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {

    Node* curr = first;

    for (unsigned int x = 0; x < count; x++) {

        if (curr->data != data)
            curr = curr->next;

        else return curr;

    }

    return nullptr;

}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {

    if (index < 0 || index >= count)
        throw std::invalid_argument("Invalid index");

    Node* curr = first;

    for (unsigned int x = 0; x < index; x++) {

        curr = curr->next;

    }

    return curr;

}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {

    if (index < 0 || index >= count)
        throw std::invalid_argument("Invalid index");

    Node* curr = first;

    for (unsigned int x = 0; x < index; x++) {

        curr = curr->next;

    }

    return curr;

}

template <typename T>
void LinkedList<T>::AddHead(const T& data) {

    auto newHead = new LinkedList<T>::Node(data);

    if (count == 0) {

        first = newHead;
        last = newHead;

    }

    else {

        newHead->next = first;

        first->prev = newHead;

        first = newHead;

    }

    count++;

}

template <typename T>
void LinkedList<T>::AddTail(const T& data) {

    auto tail = new Node(data);

    if (count == 0) {

        first = tail;
        last = tail;

    }

    else {

        tail->prev = last;

        last->next = tail;

        last = tail;

    }

    count++;

}

template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int dataSize) {

    for (unsigned int x = dataSize - 1; x > 0; x--) {

        AddHead(data[x]);

    }

    AddHead(data[0]);

}

template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int dataSize) {

    for (unsigned int x = 0; x < dataSize; x++) {

        AddTail(data[x]);

    }

}

template <typename T>
void LinkedList<T>::InsertAfter(LinkedList<T>::Node* node, const T& data) {

    if (node == last) {

        AddTail(data);
        return;

    }

    Node* curr = first;

    while (curr != node)
        curr = curr->next;

    if (curr == nullptr)
        throw std::invalid_argument("No such node");

    auto baby = new Node(data);

    baby->next = curr->next;
    baby->prev = curr;

    curr->next = baby;
    baby->next->prev = baby;

    count++;

}

template <typename T>
void LinkedList<T>::InsertBefore(LinkedList<T>::Node* node, const T& data) {

    if (node == first) {

        AddHead(data);
        return;

    }

    Node* curr = first;

    while (curr != node)
        curr = curr->next;

    if (curr == nullptr)
        throw std::invalid_argument("No such node");

    auto baby = new Node(data);

    baby->next = curr;
    baby->prev = curr->prev;

    curr->prev = baby;
    baby->prev->next = baby;

    count++;

}

template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {

    if (index < 0 || index > count)
        throw std::invalid_argument("Invalid index");

    if (index == 0) {

        AddHead(data);
        return;

    }

    if (index == count) {

        AddTail(data);
        return;

    }

    Node* curr = first;

    // Get node currently at index
    for (unsigned int y = 0; y < index; y++)
        curr = curr->next;

    auto baby = new Node(data);

    baby->prev = curr->prev;
    baby->next = curr;

    curr->prev->next = baby;
    curr->prev = baby;

    count++;

}

template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {

    if (index < 0 || index >= count)
        throw std::invalid_argument("Invalid index");

    Node* curr = first;

    for (unsigned int x = 0; x < index; x++) {

        curr = curr->next;

    }

    return curr->data;

}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {

    if (index < 0 || index >= count)
        throw std::invalid_argument("Invalid index");

    Node* curr = first;

    for (unsigned int x = 0; x < index; x++) {

        curr = curr->next;

    }

    return curr->data;

}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& list) const {

    for (unsigned int x = 0; x < count; x++) {

        if (this->GetNode(x)->data != list.GetNode(x)->data)
            return false;

    }

    return (count == list.NodeCount());

}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list) { Set(list); return *this; }

#endif