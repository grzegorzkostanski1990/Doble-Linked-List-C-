//Linked list implementation
//By Grzegorz Kostanski, ZUT student
#include <iostream>
#include <string>
#include <time.h>
#include <random>
using namespace std;

/*struct some_obj{
  int field1;
  char field2;

  some_obj(int a, char b){
  }
  bool opperator<(const some_obj&o)const{
  }
};*/

template <typename T>
class LinkedList {
    class Node {
    public:
        T data;
        Node* next;
        Node* prev;

        Node(T d) {
            T data = d;
            next = NULL;
            prev = NULL;
        }
    };
    Node* head;
    Node* tail;
    unsigned int listsize = 0;
public:
    LinkedList() {
        head = NULL;
        tail = NULL;
    }
    ~LinkedList() {
        Clearlist();
    }

    void Addontop(T a) {
        Node* temp = new Node(a);
        temp->data = a;
        listsize++;
        if (head == NULL) {
            head = temp;
            tail = temp;
        }
        else {
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
    }

    void Addonbottom(T a) {
        Node* temp = new Node(a);
        temp->data = a;
        listsize++;
        if (head == NULL) {
            head = temp;
            tail = temp;
        }
        else {
            temp->prev = tail;
            tail->next = temp;
            tail = temp;
        }
    }

    void insert_ordered(T a){
        if (head == NULL) {
            Node* temp = new Node(a);
            temp->data = a;
            listsize++;
            head = temp;
            tail = temp;
        }
        else if (a <= head->data) { Addontop(a); }
        else if (a > tail->data) { Addonbottom(a); }
        else {
            Node* temp = new Node(a);
            temp->data = a;
            listsize++;
            Node* temp2 = head;
            while (temp2->data < a) {
                temp2 = temp2->next;
            }
            temp->next = temp2;
            temp2->prev->next = temp;
            temp->prev = temp2->prev;
            temp2->prev = temp;
        }
    }

    void Deletefirst() {
        if (listsize == 0) { return; }
        else if (listsize == 1) {
            delete head;
            listsize--;
            head  = tail = NULL;
            cout << "deletion to empty"<<endl; return;
        }
        else if (listsize > 1) {
            Node* tmp = head;
            head->prev = NULL;
            head = head->next;
            delete tmp;
            listsize--;
            //cout << "deletion first node" << endl; return;
        }
    }

    void Deletelast() {
        if (listsize == 0) { return; }
        else if (listsize == 1) {
            delete tail;
            head = tail = NULL;
            listsize--;
            cout << "deletion to empty" << endl; return;
        }
        else if (listsize > 0) {
            Node* tmp = tail;
            tail = tail->prev;
            tail->next = NULL;
            delete tmp;
            listsize--;
            //cout << "deletion last node" << endl; return;
        }
    }

    Node* Returnindex(int i) {
        if ((i >= listsize) || (i < 0)) { return NULL; }
        Node* tmp = head;
        for (int j = 0; j < i; j++) {
            tmp = tmp->next;
        }
        return tmp;
    }

    void Swapindex(int i, T ndata) {
        Node* tmp = Returnindex(i);
        if (tmp != NULL) {
            tmp->data = ndata;
        }
    }

    Node* Searchelement(T searched) {
        
        Node* tmp = head;
        while (tmp != NULL) {
            if (tmp->data == searched) { return tmp; }
            tmp = tmp->next;
        }
        return NULL;
    }

    bool Deletetarget(T target) {
        Node* tmp = Searchelement(target);
        if (tmp != NULL) {
            if (tmp == head) { Deletefirst(); }
            else if (tmp == tail) { Deletelast(); }
            else {
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
                delete tmp;
                listsize--;
            }
            return true;
        }
        return false;
    }

    void Clearlist() {
        for (int i = listsize; i > 0; i--) {
            Deletefirst();
        }
    }

    void Printsize() { cout << endl << "Actual size of list: " << listsize << endl; }

    void Drawrepresentation() {
        Printsize();
        if ((head == NULL) || (listsize <= 0)) { cout << "List empty"<<endl;  return; }
        else if (listsize == 1) { cout <<"head -> "<< head->data <<" ->tail" << endl; return; }
        else{
            Node* tmp = head;
            cout << "head -> ";
            for (int i = listsize; i > 0; i--) {
                cout << tmp->data << " -> ";
                tmp = tmp->next;
            }
            cout << "tail"<<endl;
        }
    }
};

int randomint() {
    int r = rand()%100000;
    return r;
}


int main()
{
    LinkedList<int> l;
    const int MAX_ORDER = 4; // size of added data
    clock_t t1 = clock();

    for (int o = 1; o < MAX_ORDER; o++) {
        const int n = pow(10, o);
        for (int i = 0; i < n; i++) {
            int a = randomint();
            l.insert_ordered(a);
        }
    }
    clock_t t2 = clock();// clock stop
    double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
    cout <<  "time of adding:" << time << "sec"<< endl;
    l.Drawrepresentation();
    
    const int m = pow(10, 4); // number of search and delete operation
    t1 = clock();
    for (int i = 0; i < m; i++) {
            l.Deletetarget(randomint());
    }
    t2 = clock();
    time = (t2 - t1) / (double)CLOCKS_PER_SEC;
    cout << endl << "time of search and delete:" << time << "sec"<<endl;
    l.Clearlist();
    //l.insert_ordered(10);     l.insert_ordered(10);
    //l.insert_ordered(5);
    //l.insert_ordered(7);
    //l.insert_ordered(15);
    //l.Drawrepresentation();
    //l.Deletelast();
    //l.Deletefirst();
    //l.Clearlist();
    //l.Drawrepresentation();
    //cout<<l.Returnindex(2)->data<<endl;
    //l.Swapindex(0, 100);
    //cout<<l.Searchelement(7)->data<<endl;
    //l.Deletetarget(8);
    return 0;
}