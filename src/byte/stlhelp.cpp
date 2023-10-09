#include <stlhelp.h>


namespace m2 {

void *ByteAllocator::Allocate(size_t size)
{
    if (size == 0)
        size = 1;
    void *p;
    while ((p = std::malloc(size)) == nullptr)
    {
        std::new_handler nh = std::get_new_handler();
        if (nh)
            nh();
        else
            throw std::bad_alloc();
    }
    return p;
}

void ByteAllocator::Deallocate(void *p, size_t n)
{
    std::free(p);
}

}// namespace m2
