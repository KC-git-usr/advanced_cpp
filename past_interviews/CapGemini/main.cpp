// H -- T -> X
// T<-X

#include <iostream>
#include <bits/stdc++.h>

struct Node {
    int val;
    Node* prev;
    Node* next;
    Node() {
        val = 0;
        prev = nullptr;
        next = nullptr;
    }
    Node(int _val) {
        val = _val;
        prev = nullptr;
        next = nullptr;
    }
};

class DoubleLL {
public:
    Node *tail;
    Node *head;

    DoubleLL() {
        tail = nullptr;
        head = nullptr;
    }
    DoubleLL(Node *input_node) {
        tail = input_node;
        head = input_node;
    }
    void addToTail(Node *input_node) {
        this->tail->next = input_node;
        input_node->prev = this->tail;
        this->tail = input_node;
    }
};

int main() {
    // create a Node
    Node *new_ptr1 = new Node();
    Node *new_ptr2 = new Node(6);
    DoubleLL *my_obj = new DoubleLL(new_ptr2);
    std::cout << "tail->val : " << my_obj->tail->val << std::endl;
    Node *new_ptr3 = new Node(12);
    my_obj->addToTail(new_ptr3);
    std::cout << "tail->val : " << my_obj->tail->val << std::endl;
    return 0;
}
