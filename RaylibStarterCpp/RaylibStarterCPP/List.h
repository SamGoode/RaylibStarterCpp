#pragma once

template <class T>
class List {
private:
    int capacity;
    int count;
    T* vars;

public:
    List() {
        capacity = 1;
        count = 0;
        vars = new T[capacity];
    }

    ~List() {
        delete[] vars;
    }

    T& operator[](int index) {
        if (index < 0 || index > count - 1) {
            throw "list out of bounds";
        }

        return vars[index];
    }

    int getCount() {
        return count;
    }

    void resize() {
        T* oldPtr = vars;

        capacity = capacity * 2;
        vars = new T[capacity];
        for (int i = 0; i < count - 1; i++) {
            vars[i] = oldPtr[i];
        }
        delete[] oldPtr;
    }

    void append(T newVar) {
        count++;
        if (count > capacity) {
            resize();
        }
        vars[count - 1] = newVar;
    }

    void remove(int index) {
        if (index < 0 || index > count - 1) {
            throw "list out of bounds";
        }

        count--;
        for (int i = index; i < count; i++) {
            vars[i] = vars[i + 1];
        }
        vars[count] = T();
    }

    void clear() {
        for (int i = 0; i < count; i++) {
            vars[i] = T();
        }
        count = 0;
    }
};