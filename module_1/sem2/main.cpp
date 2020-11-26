#include <iostream>
#include <vector>

struct Point {
    int X;
    int Y;

    Point() : X( 0 ), Y( 0 ) {}
    Point( int x, int y ) : X( x ), Y( y ) {}
};

// 1
bool operator < (const Point& l, const Point& r) {
    return l.X < r.X;
}

// 2
bool isLessByX(const Point& l, const Point& r) {
    return l.X < r.X;
}
bool isLessByY(const Point& l, const Point& r) {
    return l.Y < r.Y;
}

// 3
template<class T>
bool  isLessDefault(const T& l, const T& r){
    return l < r;
}

// 4 фунтор
class CmpByPoint {
public:
    CmpByPoint( const Point& _pt ) : pt( _pt ) {}

    bool operator()(const Point& l, const Point& r) { return std::abs(l.X - pt.X) < std::abs(r.X - pt.X); }

private:
    Point pt;
};

// 5
template<class T>
class CmpDefault {
public:
    bool operator()(const T& l, const T& r) { return l < r; }
};

template<class T, class Compare = CmpDefault<T>>
void MegaSort(T* arr, int l, int r, Compare cmp = CmpDefault<T> ()/*bool (*isLess)(const T&, const T&) = isLessDefault*/) {
    for( int i = l; i < r; ++i ) {
        for( int j = l; j < r; ++j ) {
            if( cmp( arr[j + 1], arr[j] ) ) {
                std::swap( arr[j+ 1], arr[j] );
            }
        }
    }
}

int main() {
    int intArr[5] = {1, 3, 3, 0, 5};
    MegaSort (intArr, 0, 4 );

    Point arr[5] = {{1, 2}, {3, 1}, {0, 2}, {3, 0}, {0, 5}};
    MegaSort (arr, 1, 4, CmpByPoint( arr[0] ) );

    MegaSort (arr, 0, 4, isLessByY );

    MegaSort (arr, 0, 4, []( const Point& l, const Point& r) { return l.Y < r.Y; });

    for(auto & i : arr) {
        std::cout << "(" << i.X << ", " << i.Y << "), ";
    }

    return 0;
}
