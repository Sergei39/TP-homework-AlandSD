//
// Created by sergei on 12.12.2020.
//

#include "Huffman.h"
#include <vector>

using std::vector;

typedef unsigned char Byte;

class OutBitsStream {
public:
    OutBitsStream();

    void WriteBit(Byte bit);
    void WriteByte(Byte byte);

    const Byte* GetBuffer() const;
    int GetBitCount() const;

private:
    vector<Byte> buffer;
    int bitsCount;
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

int OutBitsStream::GetBitCount() const {
    return bitsCount;
}




class InBitsStream {
public:
    InBitsStream(const Byte* buffer, int bitsCount);

    Byte ReadBit();
    Byte ReadByte();

private:
    const Byte* buffer_;
    int bitsCount_;
    int bitsCurr_;
};

InBitsStream::InBitsStream(const Byte* buffer, int bitsCount)
        : buffer_(buffer)
        , bitsCount_(bitsCount)
        , bitsCurr_(0) {}

Byte InBitsStream::ReadBit() {
    if(bitsCurr_ > bitsCount_)
        return 0;

    Byte byte = buffer_[bitsCurr_ / 8];
    Byte bit = byte >> bitsCurr_ % 8;
    bit &= 1;

    ++bitsCurr_;

    return bit;
}

Byte InBitsStream::ReadByte() {
    if(bitsCurr_ + 8 > bitsCount_)
        return 0;

    int offset = bitsCurr_ % 8;
    Byte byteStart = buffer_[bitsCurr_ / 8 + 1] << (8 - offset);
    Byte byteEnd = buffer_[bitsCurr_ / 8] >> offset;

    bitsCurr_ += 8;

    return (byteStart | byteEnd);
}












//static void copyStream(IInputStream& input, IOutputStream& output)
//{
//    Byte value;
//    while (input.Read(value))
//    {
//        output.Write(value);
//    }
//}
//
//void Encode(IInputStream& original, IOutputStream& compressed)
//{
//    copyStream(original, compressed);
//}
//
//void Decode(IInputStream& compressed, IOutputStream& original)
//{
//    copyStream(compressed, original);
//}

