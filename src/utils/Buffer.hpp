#ifndef AETIOENGINE_BUFFER_HPP
#define AETIOENGINE_BUFFER_HPP

template <typename T>
class Buffer
{
private:
    int size;
    T *buffer;
public:
    Buffer(T *buffer, int size):buffer(buffer), size(size) {};
    ~Buffer() {};

    T* getBuffer() { return buffer; }
    int getSize() { return size; }
    int getMemorySize() { return size * sizeof(T); }
};


#endif //AETIOENGINE_BUFFER_HPP
