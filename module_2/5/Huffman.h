//
// Created by sergei on 12.12.2020.
//

#ifndef INC_5_HUFFMAN_H
#define INC_5_HUFFMAN_H


// Метод архивирует данные из потока original
void Encode(IInputStream& original, IOutputStream& compressed);
// Метод восстанавливает оригинальные данные
void Decode(IInputStream& compressed, IOutputStream& original);

#define interface struct

interface IInputStream {
    // Возвращает false, если поток закончился
    virtual bool Read(byte& value) = 0;
};

interface IOutputStream {
    virtual void Write(byte value) = 0;
};



#endif //INC_5_HUFFMAN_H
