#include <iostream>

#include <vector>
#include <array>
#include <cassert>
#include <stack>

//#include "Huffman.h"

using std::vector;

typedef unsigned char Byte;


/// Запись по битам / байтам
class OutBitsStream {
public:
    OutBitsStream();

    void WriteBit(Byte bit);
    void WriteByte(Byte byte);

    const Byte* GetBuffer() const;
    unsigned long GetBitCount() const;

private:
    vector<Byte> buffer;
    unsigned long bitsCount;
};

OutBitsStream::OutBitsStream() : bitsCount(0) {
}

void OutBitsStream::WriteBit(Byte bit) {
    if(bitsCount + 1 > buffer.size() * 8)
        buffer.push_back(0);

    if(bit != 0) {
        int bitPos = bitsCount % 8;
        buffer[bitsCount / 8] |= 1 << bitPos;
    }

    ++bitsCount;
}

void OutBitsStream::WriteByte(Byte byte) {
    if(bitsCount % 8 == 0) {
        buffer.push_back(byte);
    } else {
        int offset = bitsCount % 8;
        buffer[bitsCount / 8] |= byte << offset;
        buffer.push_back(byte >> (8 - offset));
    }
    bitsCount += 8;
}

const Byte *OutBitsStream::GetBuffer() const {
    return buffer.data();
}

unsigned long OutBitsStream::GetBitCount() const {
    return bitsCount;
}


/// Чтение по битам / байтам
class InBitsStream {
public:
    InBitsStream(const Byte* buffer, unsigned long bitsCount);

    Byte ReadBit();
    Byte ReadByte();

    unsigned long GetBitCount() const;
    void Seek(unsigned long position);

private:
    const Byte* buffer_;
    unsigned long bitsCount_;
    unsigned long bitsCurr_;
};

InBitsStream::InBitsStream(const Byte* buffer, unsigned long bitsCount)
        : buffer_(buffer)
        , bitsCount_(bitsCount)
        , bitsCurr_(0) {}

Byte InBitsStream::ReadBit() {
    if(bitsCurr_ > bitsCount_)
        return 2; // если вышли за грани входного потока

    Byte byte = buffer_[bitsCurr_ / 8];
    Byte bit = byte >> bitsCurr_ % 8;
    bit &= 1;

    ++bitsCurr_;

    return bit;
}

Byte InBitsStream::ReadByte() {
    if(bitsCurr_ + 8 > bitsCount_)
        return 2;

    int offset = bitsCurr_ % 8;
    Byte byteStart = buffer_[bitsCurr_ / 8 + 1] << (8 - offset);
    Byte byteEnd = buffer_[bitsCurr_ / 8] >> offset;

    bitsCurr_ += 8;

    return (byteStart | byteEnd);
}

unsigned long InBitsStream::GetBitCount() const {
    return bitsCount_;
}

void InBitsStream::Seek(unsigned long position) {
    bitsCurr_ = position;
}


/// реализация кучи
template<class T, class Cmp>
class Heap {
public:
    Heap(Heap& h) = delete;
    explicit Heap(Cmp& l);
    ~Heap() = default;
    void Insert(const T& element);
    T ExtractMax();
    const T& PeekMax();

    int size() const;

    bool IsEmpty() { return array.IsEmpty(); }
private:
    Cmp less;
    std::vector<T> array;
    void add(T val);
    void buildHeap();
    void siftDown(int i);
    void siftUp(int i);
    T last();
    void delete_last();
};

template<class T, class Cmp>
Heap<T, Cmp>::Heap(Cmp& l)
    : less(l) {}

template<class T, class Cmp>
void Heap<T, Cmp>::add(T val) {
    array.push_back(val);
    siftUp(array.size() - 1);
}

template<class T, class Cmp>
T Heap<T, Cmp>::last() {
    return array[array.size() - 1];
}

template<class T, class Cmp>
void Heap<T, Cmp>::delete_last() {
    array.pop_back();
}

template<class T, class Cmp>
const T& Heap<T, Cmp>::PeekMax() {
    assert(!array.empty());
    return array[0];
}

template<class T, class Cmp>
void Heap<T, Cmp>::siftDown( int i )
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
// Ищем большего сына, если такой есть.
    int largest = i;
    if(left < array.size() && less(array[left], array[i]))
        largest = left;
    if(right < array.size() && less(array[right], array[largest]))
        largest = right;
// Если больший сын есть, то проталкиваем корень в него.
    if( largest != i ) {
        std::swap(array[i], array[largest]);
        siftDown(largest);
    }
}

template<class T, class Cmp>
void Heap<T, Cmp>::buildHeap()
{
    for(int i = array.size() / 2 - 1; i >= 0; i--) {
        siftDown( i );
    }
}

template<class T, class Cmp>
void Heap<T, Cmp>::siftUp( int index )
{
    while(index > 0) {
        int parent = (index - 1) / 2;
        if(less(array[parent], array[index]))
            return;
        std::swap(array[index], array[parent]);
        index = parent;
    }
}

template<class T, class Cmp>
void Heap<T, Cmp>::Insert( const T& element )
{
    add(element);
    siftUp(array.size() - 1);
}

template<class T, class Cmp>
T Heap<T, Cmp>::ExtractMax()
{
    assert(!array.empty());
// Запоминаем значение корня.
    T result = array[0];
// Переносим последний элемент в корень.
    array[0] = last();
    delete_last();
// Вызываем SiftDown для корня.
    if(array.size() != 0) {
        siftDown(0);
    }
    return result;
}

template<class T, class Cmp>
int Heap<T, Cmp>::size() const {
    return array.size();
}


struct Node {
    Node* Left;
    Node* Right;
    int P; // частота встречаемости, по этому элементу строится куча
    Byte B;

    Node(int p, Byte b) : Left(nullptr), Right(nullptr), P(p), B(b) {}
    explicit Node(Byte b) : Left(nullptr), Right(nullptr), P(0), B(b) {}
    Node(int p, Node* left, Node* right) : Left(left), Right(right), P(p), B(0) {}

    void InOrder(vector<Byte>& code, vector<Byte>* arr);

    template<typename F, typename G>
    void InOrder2(F VisitList, G VisitNode);
};

// TODO что то сделать с этим методом
void Node::InOrder(vector<Byte>& code, vector<Byte>* arr) {
    if (Left == nullptr) {
        arr[B] = code;
        code.pop_back();
        return;
    }
    code.push_back(0);
    Left->InOrder(code, arr);
    code.push_back(1);
    Right->InOrder(code, arr);
    code.pop_back();
}

template<typename F, typename G>
void Node::InOrder2(F VisitList, G VisitNode) {
    if (Left == nullptr && Right == nullptr) // лист
        VisitList(B);
    else {
        Left->InOrder2(VisitList, VisitNode);
        Right->InOrder2(VisitList, VisitNode);
        VisitNode();
    }
}


template<class T>
class CmpDef {
public:
    bool operator()(const T* l, const T* r) { return l->P < r->P; }
};


void encode(InBitsStream& input, OutBitsStream& output) {
    std::array<int, 256> bytes{0};
    for (int i = 0; i * 8 < input.GetBitCount(); i++)
        bytes[input.ReadByte()]++;

    CmpDef<Node> less;
    Heap<Node*, CmpDef<Node>> heap(less);
    for (int i = 0; i < 256; i++)
        if (bytes[i] != 0) {
            heap.Insert(new Node(bytes[i], i));
        }

    while (heap.size() > 1) {
        Node* min1 = heap.ExtractMax();
        Node* min2 = heap.ExtractMax();

        Node* n = new Node(min1->P + min2->P, min1, min2);
        heap.Insert(n);
    }

    std::array<vector<Byte>, 256> code{};
    Node* root = heap.PeekMax();

    vector<Byte> c;
    root->InOrder(c, code.data());

    Byte numberNode = 0;
    auto FuncN = [&numberNode](Byte B = 0) {++numberNode;};
    root->InOrder2(FuncN, FuncN);
    output.WriteByte(numberNode);

    auto FuncList = [&output](Byte B) {output.WriteBit(1); output.WriteByte(B);};
    auto FuncNode = [&output]() {output.WriteBit(0);};
    root->InOrder2(FuncList, FuncNode);

    // считаем сколько будет в конце не значищих битов
    unsigned long numberBit = 0;
    for (int i = 0; i < 256; i++) {
        numberBit += bytes[i] * code[i].size();
    }
    Byte nullBit = 8 - ((output.GetBitCount() + numberBit) % 8);
    output.WriteByte(nullBit);
    for (int i = 0; i < nullBit; i++)
        output.WriteBit(0);

    // запись закодированного потока
    input.Seek(0);
    for (int i = 0; i * 8 < input.GetBitCount(); i++) {
        auto cd = code[input.ReadByte()];
        for (unsigned char j : cd)
            output.WriteBit(j);
    }

}

void decode(InBitsStream& input, OutBitsStream& output) {

    // декодирование хедора
    std::stack<Node*> stack;
    Byte numberNode = input.ReadByte();
    for(int i = 0; i < numberNode; i++) {
        if (input.ReadBit() == 1) {
            stack.push(new Node(input.ReadByte()));
        } else {
            auto first = stack.top();
            stack.pop();
            auto second = stack.top();
            stack.pop();
            stack.push(new Node(0, second, first));
        }
    }

    Node* root = stack.top();

    Byte nullBit = input.ReadByte();
    for (int i = 0; i < nullBit; ++i)
        input.ReadBit();

    // декодирование потока потока
    Node* cur = root;
    Byte bit = input.ReadBit();
    while (bit != 2) {
        if (cur->Left == nullptr) {
            output.WriteByte(cur->B);
            cur = root;
        }
        if (bit == 0)
            cur = cur->Left;
        else
            cur = cur->Right;

        bit = input.ReadBit();
    }
}


// для тестов в контексте
//void Encode(IInputStream& original, IOutputStream& compressed) {
//    Byte value;
//    vector<Byte> text;
//    while (original.Read(value))
//    {
//        text.push_back(value);
//    }
//
//    InBitsStream input(text.data(), text.size());
//    OutBitsStream output;
//    encode(input, output);
//
//    const Byte* data = output.GetBuffer();
//
//    for (int i = 0; i < text.size(); i++)
//        compressed.Write(data[i]);
//}
//
//void Decode(IInputStream& compressed, IOutputStream& original) {
//    Byte value;
//    vector<Byte> text;
//    while (compressed.Read(value))
//    {
//        text.push_back(value);
//    }
//
//    InBitsStream input(text.data(), text.size());
//    OutBitsStream output;
//    decode(input, output);
//
//    const Byte* data = output.GetBuffer();
//
//    for (int i = 0; i < text.size(); i++)
//        original.Write(data[i]);
//}





// чтобы тестить в коде
int main() {
    OutBitsStream outCoder;
    outCoder.WriteByte('a');
    outCoder.WriteByte('b');
    outCoder.WriteByte('a');
    outCoder.WriteByte('c');
    outCoder.WriteByte('a');
    outCoder.WriteByte('f');
    outCoder.WriteByte('\n');

    InBitsStream inputCoder(outCoder.GetBuffer(), outCoder.GetBitCount());

    OutBitsStream coder;
    encode(inputCoder, coder);


    InBitsStream inputDecoder(coder.GetBuffer(), coder.GetBitCount());

//    for(int i = 0; i < inputDecoder.GetBitCount(); i++)
//        std::cout << (int)inputDecoder.ReadBit();
//    inputDecoder.Seek(0);

    OutBitsStream decoder;
    decode(inputDecoder, decoder);

    InBitsStream dec(decoder.GetBuffer(), decoder.GetBitCount());
    for(int i = 0; i * 8 < dec.GetBitCount(); i++)
        std::cout << dec.ReadByte() << std::endl;

    return 0;
}
