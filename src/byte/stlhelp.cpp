#include <stlhelp.h>


namespace Lite {
namespace Utility {

void *GsByteAllocator::Allocate(size_t size)
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

void GsByteAllocator::Deallocate(void *p, size_t n)
{
    std::free(p);
}

}// namespace Utility
}// namespace Lite
