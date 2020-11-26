/**На числовой прямой окрасили N отрезков.
 * Известны координаты левого и правого концов каждого отрезка [Li, Ri].
 * Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.
 *
 * N ≤ 10000. Li, Ri — целые числа в диапазоне [0, 109].**/

#include <iostream>
#include <cstring>

struct Point {
    int X;
    int Delta;

    Point() : X(0), Delta(0) {}
    Point( int x, int delta ) : X(x), Delta(delta) {}
};

class CmpByPoint {
public:
    explicit CmpByPoint(const Point& _pt) : pt( _pt ) {}

    bool operator()(const Point& l, const Point& r) { return l.X < r.X; }

private:
    Point pt;
};


template<class T>
class CmpDefault {
public:
    bool operator()(const T& l, const T& r) { return l < r; }
};


template<class T, class Compare = CmpDefault<T>>
void Merge(const T* firstArr, int firstLen,
           const T* secondArr, int secondLen,
           T* res, Compare less = CmpDefault<T> ()) {

    int i = 0, j = 0;
    while(i < firstLen && j < secondLen) {
        if(less(firstArr[i], secondArr[j])) {
            res[i + j] = firstArr[i];
            i++;
        } else {
            res[i + j] = secondArr[j];
            j++;
        }
    }
    while(i < firstLen) {
        res[i + j] = firstArr[i];
        i++;
    }
    while(j < secondLen) {
        res[i + j] = secondArr[j];
        j++;
    }
}

template<class T, class Compare = CmpDefault<T>>
void MergeSort(T* a, int aLen, Compare less = CmpDefault<T> ()) {
    if(aLen <= 1) {
        return;
    }
    int firstLen = aLen / 2;
    int secondLen = aLen - firstLen;
    MergeSort(a, firstLen, less);
    MergeSort(a + firstLen, secondLen, less);
    T* res = new T[aLen];
    Merge(a, firstLen, a + firstLen, secondLen, res, less);
    memcpy(a, res, sizeof(T) * aLen);
    delete[] res;
}

int getLen(Point* points, int len) {
    int depth = 0;
    int sum = 0;

    for(int i = 0; i < len - 1; i++) {
        depth += points[i].Delta;
        if(depth == 1) {
            sum += (points[i + 1].X - points[i].X);
        }
    }

    return sum;
}

int main() {
    int len = 0;
    std::cin >> len;

    len *= 2;
    Point* points = new Point[len];
    for(int i = 0; i < len; i += 2) {
        std::cin >> points[i].X >> points[i + 1].X;
        points[i].Delta = 1;
        points[i + 1].Delta = -1;
    }

    MergeSort(points, len, []( const Point& l, const Point& r) { return l.X < r.X; });

    std::cout << getLen(points, len);

    delete [] points;

    return 0;
}
