#include <iostream>
#include <sstream>

using namespace std;

template<typename K, typename V>
class Table 
{
private:
    class Node
    {
    public:
        K key;
        V value;
        Node* next;
        Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };
    Node* head; 
public:
    Table() : head(nullptr) {} 

    void setValue(const K& key, const V& value) {
        Node* newNode = new Node(key, value);
        newNode->next = head;
        head = newNode;
    }

    V getValue(const K& key) const 
    {
        Node* current = head;
        while (current != nullptr) 
        {
            if (current->key == key) 
            {
                return current->value;
            }
            current = current->next;
        }
        ostringstream oss;
        oss << "Can't get value, key: " << key << " not found\n";
        throw out_of_range(oss.str());
    }

    void removeValue(const K& key) {
        Node* current = head;
        Node* prev = nullptr;
        while (current != nullptr) {
            if (current->key == key) {
                if (prev != nullptr) {
                    prev->next = current->next;
                }
                else {
                    head = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
        ostringstream oss;
        oss << "Can't remove node, key: " << key << " not found\n";
        throw out_of_range(oss.str());
    }

    void print(ostream& os = cout) const 
    {
        Node* current = head;
        while (current != nullptr) 
        {
            os << current->key << ": " << current->value << endl;
            current = current->next;
        }
    }

    ~Table() 
    {
        Node* current = head;
        while (current != nullptr) 
        {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main()
{

    Table<string, int> table;

    table.setValue("1", 3);
    table.setValue("2", 4);
    table.setValue("3", 5);
    table.print();
    try
    {
        table.removeValue("4");
    }
    catch (const out_of_range& e) {
        cerr << e.what() << endl;
    }
    try
    {
        cout << "Value with key 1: " << table.getValue("1") << endl;
        cout << table.getValue("5");
    }
    catch (const out_of_range& e) 
    {
        cerr << e.what() << endl;
    }
    return 0;
}