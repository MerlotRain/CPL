#pragma once

#include <cstddef>
#include <limits>

template<typename T, size_t blockSize = 4096>
class MemoryPool
{
public:
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef const T *const_pointer;
    typedef const T &const_refernece;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    MemoryPool() noexcept = default;
    MemoryPool(const MemoryPool &pool) noexcept = default;
    MemoryPool(MemoryPool &&pool) noexcept
    {
        current_block = pool.current_block;
        pool.current_block = nullptr;
        current_slot = pool.current_slot;
        last_slot = pool.last_slot;
        free_slot = pool.freeSlots;
    }

    template<typename U>
    MemoryPool(const MemoryPool<U> &pool) noexcept = default;
    MemoryPool &operator=(const MemoryPool &&pool) = delete;
    MemoryPool &operator=(MemoryPool &&pool) noexcept
    {
        if (this != &pool)
        {
            std::swap(current_block, pool.current_block);
            current_slot = pool.current_slot;
            last_slot = pool.last_slot;
            free_slot = pool.freeSlots;
        }
        return *this;
    }

    ~MemoryPool() noexcept
    {
        slot_pointer curr = current_block;
        while (curr != nullptr)
        {
            slot_pointer prev = curr->next;
            operator delete(reinterpret_cast<void *>(curr));
            curr = prev;
        }
    }

    pointer address(reference ref) const noexcept
    {
        return &ref;
    }
    const_pointer address(const_refernece ref) const noexcept
    {
        return &ref;
    }

    pointer allocate(size_type size = 1, const_pointer hint = 0)
    {
        if (free_slot != nullptr)
        {
            pointer result = reinterpret_cast<pointer>(free_slot);
            free_slot = free_slot->next;
            return result;
        }
        else
        {
            if (current_slot >= last_slot)
            {
                allocateBlock();
            }
            return reinterpret_cast<pointer>(current_slot++);
        }
    }

    void deallocate(pointer p, size_type size = 1)
    {
        if (p != nullptr)
        {
            reinterpret_cast<slot_pointer>(p)->next = free_slot;
            free_slot = reinterpret_cast<slot_pointer>(p);
        }
    }

    size_type max_size() const noexcept
    {
        size_type maxBlocks = -1 / blockSize;
        return (blockSize - sizeof(data_pointer)) / sizeof(slot_type) * maxBlocks;
    }

    template<typename U, template... Args>
    void construct(U *p, Args &&...args)
    {
        new (p) U(std::forward<Args>(args)...);
    }
    template<typename U>
    void destory(U *p)
    {
        p->~U();
    }

    template<typename... Args>
    void new_element(Args &&...args)
    {
        pointer result = allocate();
        construct<value_type>(result, std::forward<Args>(args)...);
        return result;
    }
    void delete_element(pointer p)
    {
        if (p != nullptr)
        {
            p->~value_type();
            deallocate(p);
        }
    }

private:
    union Slot
    {
        value_type element;
        Slot *next;
    };

    typedef char *data_pointer;
    typedef Slot slot_type;
    typedef Slot *slot_pointer;

    slot_pointer current_block = nullptr;
    slot_pointer current_slot = nullptr;
    slot_pointer last_slot = nullptr;
    slot_pointer free_slot = nullptr;

    size_type pad_pointer(data_pointer p, size_type align) const
    {
        uintptr_t result = reinterpret_cast<uintptr_t>(p);
        return ((align - result) % align);
    }
    void allocate_block()
    {
        data_pointer newBlock = reinterpret_cast<data_pointer>(operator new(blockSize));
        reinterpret_cast<slot_pointer>(newBlock)->next = current_block;
        current_block = reinterpret_cast<slot_pointer>(newBlock);
        data_pointer body = newBlock + sizeof(slot_pointer);
        size_type bodyPadding = padPointer(body, alignof(slot_type));
        current_slot = reinterpret_cast<slot_pointer>(body + bodyPadding);
        last_slot = reinterpret_cast<slot_pointer>(newBlock + blockSize - sizeof(slot_type) + 1);
    }

    static_assert(blockSize >= 2 * sizeof(slot_type), "blockSize too small.")
};