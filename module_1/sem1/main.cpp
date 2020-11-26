#include <iostream>
#include <assert.h>
#include <strstream>
#include <sstream>

template <class T>
class Queue {
public:
    Queue();
    ~Queue();

    // Положить элемент в очередь
    void Enqueue(const T& value); // конст который говорит что элемент изменяться не будет
    // Извлечь элемент из очереди
    T Dequeue();
    // Проверка на пустоту
    bool IsEmpty() const; // конст потому что не модифицирует поля класса

private:
    struct Node {
        T Value;
        Node* Next;

        Node() : Next( nullptr ) {}
    };
    Node* head;
    Node* tail;
};

template <class T>
Queue<T>::Queue() :
    head(nullptr),
    tail(nullptr)
{
}

template <class T>
Queue<T>::~Queue()
{
    while(!IsEmpty()) {
        Node* tmpNode = head;
        head = head->Next;
        delete tmpNode;
    }
}

template <class T>
void Queue<T>::Enqueue(const T& value)
{
    Node* newNode = new Node;
    newNode->Value = value;
    if(IsEmpty()) {
        head = newNode;
    } else {
        tail->Next = newNode;
    }
    tail = newNode;
}

template <class T>
T Queue<T>::Dequeue()
{
    assert(!IsEmpty());

    Node* tmpNode = head;
    head = head->Next;
    if(head == nullptr) {
        tail = nullptr;
    }
    T tmpValue = tmpNode->Value;
    delete tmpNode;
    return tmpValue;
}

template <class T>
bool Queue<T>::IsEmpty() const {
    return head == nullptr;
}

void run(std::istream& input, std::ostream& out) {
    Queue<int> q;
    int n = 0;
    input >> n;
    bool result = true;
    for(int i = 0; i < n; i++){
        int command = 0;
        int value = 0;
        input >> command >> value;
        switch (command) {
            case 2:
                if(q.IsEmpty()) {
                    result = result && value == -1;
                } else {
                    result = result && q.Dequeue() == value;
                }
                break;
            case 3:
                q.Enqueue(value);
                break;
            default:
                assert(false);
        }
    }

    out << (result ? "Yes" : "No");
}

void testQueue()
{
    { // Случай А
        std::stringstream input;
        std::stringstream output;
        input << "3 3 44 3 50 2 44";
        run(input, output);
        assert(output.str() == "Yes");
    }
    { // Случай Б
        std::stringstream input;
        std::stringstream output;
        input << "2 3 44 2 66";
        run(input, output);
        assert(output.str() == "No");
    }
}

int main()
{
    //run(std::cin, std::cout);
    testQueue();
    return 0;
}
