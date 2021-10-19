#include <iostream>
#include <utility>
#include <string.h>

/**
 * Single cache node that holds key value pair.
 */
class Node {
public:
    std::string key, value;
    char dirty_type;
    int frequency;
    Node *prev;
    Node *next;

    Node(std::string key, std::string value) : key(key), value(value), dirty_type(0), prev(NULL), next(NULL), frequency(1) {
    }
};

/**
 * List data-structure to hold multiple cache node.
 */
class List {
private:
    Node *front, *rear;
public:

    /**
     * Default constructor for initializing the queue.
     */
    List() {
        front = NULL;
        rear = NULL;
    }

    /**
     * Checking if the queue is empty or not
     * @return true if empty
     */
    bool isEmpty() {
        return rear == NULL;
    }

    /**
     * Returns the last element
     * @return
     */
    Node *last() {
        return rear;
    }


    /**
     * Add key at the front of the queue.
     * @param key
     * @param value
     * @return  Node
     */
    Node *push_front(std::string key, std::string value) {
        Node *node = new Node(key, value);
        if (front == NULL && rear == NULL) {
            front = rear = node;
        } else {
            node->next = front;
            front->prev = node;
            front = node;
        }
        return node;
    }

    /**
     * Fetch the node from the queue and push it to the front of the doublylinked queue.
     * @param node
     */
    void pop_push_front(Node *node) {
        //fetching the node from the list
        if (node == front) {
            return;
        } else if (node == rear) {
            rear = rear->prev;
            rear->next = nullptr;
        } else {
            node->next->prev = node->prev;
            node->prev->next = node->next;
        }
        node->prev = nullptr;

        //pushing to the front.
        node->next = front;
        front->prev = node;
        front = node;
    }


    /**
     *  delete last element from the list
     */
    void remove_last() {
        Node *temp;
        if (isEmpty()) {
            return;
        }
        temp = rear;
        if (front == rear) {
            front = rear = NULL;
        } else {
            rear = rear->prev;
            rear->next = NULL;
        }
        delete temp;
    }

    /**
     * Delete the node from the given doubly linked list.
     * @param node
     */
    void remove(Node *node) {
        if (node == rear) {
            remove_last();
        } else if (node == front) {
            front = node->next;
            front->prev = node->prev;
        } else {
            node->next->prev = node->prev;
            node->prev->next = node->next;
        }
        delete node;

    }

    void shift(Node *node) {
        Node *temp;
        if (node == front) {
            return;
        } else if (node == rear) {
            temp = rear->prev;
            rear = rear->prev;
            rear->next = nullptr;
        } else {
            temp = node->prev;
            node->next->prev = node->prev;
            node->prev->next = node->next;
        }
        node->prev = nullptr;
        while (temp != nullptr) {
            if (node->frequency <= temp->frequency) {
                temp->next->prev = node;
                node->next = temp->next;
                node->prev = temp;
                temp->next = node;
                break;

            } else {
                if (temp == front) {
                    node->next = front;
                    front->prev = node;
                    front = node;
                    break;
                }
                temp = temp->prev;
            }
        }
    }


    Node *push_rear(std::string key, std::string value) {
        Node *node = new Node(key, value);
        if (front == NULL && rear == NULL) {
            front = rear = node;
        } else {
            rear->next = node;
            node->prev = rear;
            rear = node;
        }
        return node;
    }

};