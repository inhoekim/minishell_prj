#include <iostream>
#include <list>
using namespace std;

class Node {
public:
    int data;
    Node* next;
};

class CircularLinkedList {
public:
    Node* head;
    CircularLinkedList() {
        head = NULL;
    }
    void addNode(int data) {
        Node* newNode = new Node();
        newNode->data = data;

        if (head == NULL) {
            head = newNode;
            head->next = head;
        }
        else {
            Node* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
    }
    Node* delNode(Node* target)
    {
        Node* current = head;
        Node* prev = NULL;
        do {
            prev = current;
            current = current->next;
        } while(current != target);
        if (current == head && prev == head) {
            head = NULL;
            cout << current->data;
            delete current;
            return (NULL);
        }
        if (current == head) {
            Node* tmp = head;
            while (tmp->next != head) {
                tmp = tmp->next;
            }
            head = current->next;
            tmp->next = head;
            cout << current->data;
            delete current;
        }
        else {
            prev->next = current->next;
            cout << current->data;
            delete current;
        }
        return (prev);
    }
    int size()
    {
        int cnt;
        if (head == NULL) {
            cnt = 0;
            // cout << "Size is 0!" << endl;
        }
        else {
            Node* temp = head;
            cnt = 1;
            while (temp->next != head) {
                temp = temp->next;
                cnt++;
            }
        }
        return (cnt);
    }
    void display() {
        if (head == NULL) {
            cout << "List is empty!" << endl;
        }
        else {
            Node* temp = head;
            do {
                cout << temp->data << " ";
                temp = temp->next;
            } while (temp != head);
            cout << endl;
        }
    }
};

int main()
{
    CircularLinkedList cir_lt;

    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
        cir_lt.addNode(i);
    cout << '<';
    int cnt = 0;
    Node* cur = cir_lt.head;
    while(cir_lt.size()) {
        cnt++;
        if(cnt == k)
        {
            cur = cir_lt.delNode(cur);
            if (cir_lt.size() != 0)
                cout << ", ";
            else
            {
                cout << '>';
                break;
            }
            cnt = 0;
        }
        cur = cur->next;
    }
}
