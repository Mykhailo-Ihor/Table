#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

template<typename K, typename V>
class Table
{
public:
    class Node
    {
    public:
        K key;
        V value;
        Node* next;
        Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };
private:
    Node* head;
public:
    Table() : head(nullptr) {}
    Table& setValue(const K& key, const V& value)
    {
        Node* current = head;
        while (current != nullptr)
        {
            if (current->key == key)
            {
                current->value = value;
                return *this;
            }
            current = current->next;
        }
        Node* newNode = new Node(key, value);
        newNode->next = head;
        head = newNode;
        return *this;
    }
    V getValue(const K& key) const
    {
        if (head == nullptr)
        {
            ostringstream oss;
            oss << "Can't get value, table is empty\n";
            throw runtime_error(oss.str());
        }
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

    void removeValue(const K& key)
    {
        if (head == nullptr)
        {
            throw runtime_error("Table is empty\n");
        }
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
        if (head == nullptr)
        {
            os << "Table is empty\n";
        }
        Node* current = head;
        while (current != nullptr)
        {
            os << current->key << ": " << current->value << " | ";
            current = current->next;
        }
        os << endl;
    }

    Node* getHead()
    {
        return head;
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

template<typename V>
class HashTable
{
public:
    int itemCount; 
private:
    int TABLE_SIZE = 10;
    Table<int, V>* tableArray; 
    double loadFactorThreshold; 
    

    int hashFunction(int key) const {
        return key % TABLE_SIZE;
    }

    void checkLoadFactor() 
    {
        double loadFactor = (double)itemCount / (double)(TABLE_SIZE * TABLE_SIZE);
        if (loadFactor > loadFactorThreshold) {
            rebuild();
        }
    }

    void rehash()
    {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            typename Table<int, V>::Node* current = tableArray[i].getHead();
            while (current != nullptr) {
                int index = hashFunction(current->key);
                tableArray[index].setValue(current->key, current->value);
                current = current->next;
            }
        }
    }
    void rebuild()
    {
        int newCapacity = TABLE_SIZE * 2;
        Table<int, V>* tempArray = new Table<int, V>[newCapacity];
        for (int i = 0; i < TABLE_SIZE; ++i) {
            typename Table<int, V>::Node* current = tableArray[i].getHead();
            while (current != nullptr) {
                int newIndex = hashFunction(current->key) % newCapacity;
                tempArray[newIndex].setValue(current->key, current->value); 
                current = current->next;
            }
        }
        delete[] tableArray; 
        tableArray = tempArray; 
        TABLE_SIZE = newCapacity; 
        rehash();
    }
public:
   
    HashTable(double loadFactor = 0.75) : loadFactorThreshold(loadFactor), itemCount(0) 
    {
        tableArray = new Table<int, V>[TABLE_SIZE]; 
    }

    void add(int key, const V& value) 
    {
        int index = hashFunction(key);
        tableArray[index].setValue(key, value);
        ++itemCount;
        checkLoadFactor();
    }

    V getValue(int key) const 
    {
        int index = hashFunction(key);
        return tableArray[index].getValue(key);
    }

    void remove(int key) 
    {
        int index = hashFunction(key);
        tableArray[index].removeValue(key);
        itemCount--;
    }

    void print(ostream& os = cout) const {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            os << "Bucket " << i << ":" << endl;
            tableArray[i].print(os);
        }
    }

    ~HashTable() {
        delete[] tableArray;
    }
};

int main()
{
    HashTable<string> hashTable;
    for (int i = 0; i < 75; ++i)
    {
        ostringstream oss;
        oss << "Value " << i;
        hashTable.add(i, oss.str());
    }
    ofstream fout("HashTable.txt", ios::out);
    hashTable.print(fout);
    hashTable.print();
    fout.close();
    for (int i = 75; i < 100; ++i)
    {
        ostringstream oss;
        oss << "Value " << i;
        hashTable.add(i, oss.str());
    }
    fout.open("100 elements.txt", ios::out);
    hashTable.print(fout);
    fout.close();
    for (int i = 100; i < 301; ++i)
    {
        ostringstream oss;
        oss << "Value " << i;
        hashTable.add(i, oss.str());
    }
    fout.open("300 elements.txt", ios::out);
    hashTable.print(fout);
    fout.close();
    return 0;
}
