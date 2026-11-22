#ifndef __SQ_LIST_H__
#define __SQ_LIST_H__

#include <iostream>
#include <cstring>
using namespace std;

#define DEFAULT_SIZE 1000 // 缺省元素个数

template <class ElemType>
class SqList {
protected:
    int length;             // 顺序表的当前长度 
    int maxLength;          // 顺序表的最大容量
    ElemType* data;         // 元素存储空间的首地址 
public:
    // 1. 构造一个空表
    SqList(int size = DEFAULT_SIZE) {
        maxLength = size;
        length = 0;
        data = new ElemType[maxLength];
    }

    // 2. 根据数组v的内容构造顺序表
    SqList(ElemType v[], int n, int size = DEFAULT_SIZE) {
        maxLength = size;
        length = n;
        data = new ElemType[maxLength];
        for (int i = 0; i < n; i++) data[i] = v[i];
    }

    // 3. 析构函数
    virtual ~SqList() { if (data != NULL) delete[] data; }

    // 4. 取顺序表长度
    int GetLength() const { return length; }

    // 5. 判断顺序表是否为空
    bool IsEmpty() const { 
        return length == 0; 
    }

    // 6. 将顺序表清空
    void Clear() { length = 0; }

    // 7. 遍历顺序表 (回调函数)
    //这个函数就是单纯遍历一遍顺序表,对这个元素怎么操作看传入的Visit函数
    void Traverse(void (*Visit)(const ElemType&)) const {
        for (int i = 0; i < length; i++) {
            Visit(data[i]);
        }
    }

    // 8. 元素定位
    int LocateElem(const ElemType& e) const {
        for (int i = 0; i < length; i++) {
            if (data[i].id == e.id) return i + 1; 
        }
        return 0; // 没找到
    }

    // 9. 取顺序表中第i个元素的值
    int GetElem(int i, ElemType& e) const {
        if (i < 1 || i > length) return 0;
        e = data[i - 1];
        return 1;
    }

    // 10. 修改顺序表中第i个元素的值
    int SetElem(int i, const ElemType& e) {
        if (i < 1 || i > length) return 0;
        data[i - 1] = e;
        return 1;
    }

    // 11. 删除顺序表中第i个元素
    int DeleteElem(int i, ElemType& e) {
        if (i < 1 || i > length) return 0;
        e = data[i - 1];
        for (int j = i; j < length; j++) data[j - 1] = data[j];
        length--;
        return 1;
    }

    // 12. 在顺序表第i个位置插入元素
    int InsertElem(int i, const ElemType& e) {
        if (i < 1 || i > length + 1) return 0;
        if (length >= maxLength) return 0;
        for (int j = length; j >= i; j--) data[j] = data[j - 1];
        data[i - 1] = e;
        length++;
        return 1;
    }

    // 13. 在顺序表表尾插入元素
    int InsertElem(const ElemType& e) { return InsertElem(length + 1, e); }

    // 14. 复制构造函数
    SqList(const SqList<ElemType>& sa) {
        maxLength = sa.maxLength;
        length = sa.length;
        data = new ElemType[maxLength];
        for (int i = 0; i < length; i++) data[i] = sa.data[i];
    }

    // 15. 赋值运算符重载
    SqList<ElemType>& operator=(const SqList<ElemType>& sa) {
        if (this != &sa) {
            delete[] data;
            maxLength = sa.maxLength;
            length = sa.length;
            data = new ElemType[maxLength];
            for (int i = 0; i < length; i++) data[i] = sa.data[i];
        }
        return *this;
    }
};

#endif // !__SQ_LIST_H__
