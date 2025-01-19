/**
 * CPL - Common Portability Library
 *
 * Copyright (C) 2024 Merlot.Rain
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include "cpl_atomic.h"
#include "cpl_delegate.h"
#include <cpl_exports.h>

namespace CPL {

/// \brief Non-copyable utility class
/// This class is designed to be inherited by other classes to prevent
/// copying and assignment. It achieves this by deleting the copy constructor
/// and copy assignment operator.
class CPL_API GsNoneCopyable
{
public:
    /// \brief Default constructor
    /// Allows construction of the derived class instances.
    GsNoneCopyable() {}

private:
    /// \brief Deleted copy constructor
    /// Prevents copying of the derived class.
    GsNoneCopyable(const GsNoneCopyable &) = delete;

    /// \brief Deleted copy assignment operator
    /// Prevents assignment of the derived class.
    GsNoneCopyable &operator=(const GsNoneCopyable &) = delete;
};

/// \brief Base class for reference-counted objects
/// This class provides functionality for managing reference counts and ensures
/// automatic cleanup of objects when their reference count reaches zero.
/// It is designed to be inherited by other classes requiring reference-counting
/// functionality.
class CPL_API RefObject : private GsNoneCopyable
{
protected:
    /// \brief The reference count for the object
    /// Manages the number of references to the object.
    Atomic<int> m_RefCount;

    /// \brief Triggered when the reference count reaches zero
    /// Derived classes can override this method to perform custom cleanup or
    /// prevent automatic deletion by returning `false`.
    /// \return Returns `false` if the object should not be automatically deleted.
    virtual bool OnFinalRelease();

public:
    /// \brief Constructor
    /// Initializes the reference count to zero.
    RefObject();

    /// \brief Destructor
    /// Ensures proper cleanup of the object.
    virtual ~RefObject() {}

    /// \brief Increment the reference count
    /// Increases the reference count by one, indicating an additional reference
    /// to the object.
    /// \return Returns the updated reference count.
    virtual int AddRef() noexcept;

    /// \brief Decrement the reference count
    /// Decreases the reference count by one. When the count reaches zero,
    /// `OnFinalRelease` is triggered.
    /// \return Returns the updated reference count.
    virtual int Release() noexcept;

    /// \brief Retrieve the current reference count
    /// \return Returns the current value of the reference count.
    virtual int RefCount() noexcept;

    /// \brief Cast the object to a specific type
    /// Attempts to cast the current object to the specified type using
    /// `dynamic_cast`.
    /// \tparam T The target type to cast to.
    /// \return A pointer to the object cast to the target type, or `nullptr`
    /// if the cast fails.
    template<class T>
    T *CastTo()
    {
        return dynamic_cast<T *>(this);
    }

    /// \brief Check if the object is of a specific type
    /// Verifies whether the current object is of the specified type.
    /// \tparam T The type to check against.
    /// \return Returns `true` if the object is of the specified type, `false` otherwise.
    template<class T>
    bool Is()
    {
        return dynamic_cast<T *>(this) != nullptr;
    }

    /// \brief Event triggered when the object is destructed
    /// Allows external handlers to be notified when the object is destroyed.
    Delegate<void(RefObject *)> OnDestructor;
};


/// \brief Weak reference to a RefObject
/// This class allows for a weak reference to a RefObject, meaning it does not
/// increase the reference count of the target object. It can check if the object
/// has been destroyed and retrieve it if it is still valid.
class CPL_API WeakReference : public RefObject
{
    RefObject *m_RefObject;///< Pointer to the referenced object.

    /// \brief Triggered when the referenced object is destroyed.
    /// This method is called to handle cleanup when the referenced RefObject is
    /// destructed.
    /// \param obj Pointer to the object that is being destructed.
    void OnDestructor(RefObject *obj);

public:
    /// \brief Constructor to create a WeakReference.
    /// \param ref Pointer to the RefObject to be referenced weakly.
    WeakReference(RefObject *ref);

    /// \brief Destructor to clean up the WeakReference.
    ~WeakReference();

    /// \brief Locks and retrieves the referenced object.
    /// \return Pointer to the referenced RefObject if it is still valid, or `nullptr`
    ///         if the object has already been destroyed.
    RefObject *LockReferenceObject();

    /// \brief Checks if the referenced object has expired.
    /// \return `true` if the referenced object has been destroyed, otherwise `false`.
    bool Expired();
};


/// \brief Smart pointer template for automatic reference counting of RefObject
/// This template class manages reference counts for objects derived from
/// RefObject, ensuring proper resource management and preventing memory leaks.
template<class T>
class SmarterPtr
{
public:
    /// \brief Default constructor
    /// Initializes the smart pointer to `nullptr`.
    SmarterPtr() noexcept { p = NULL; }

    /// \brief Constructor with integer argument
    /// \param nNull Dummy parameter, initializes the pointer to `nullptr`.
    SmarterPtr(int nNull) noexcept { p = NULL; }

    /// \brief Constructor with long integer argument
    /// \param nNull Dummy parameter, initializes the pointer to `nullptr`.
    SmarterPtr(long int nNull) noexcept { p = NULL; }

    /// \brief Template constructor to initialize and optionally increment reference count
    /// \param lp Pointer to the object
    /// \param bAddRef If true, increments the reference count of the object.
    template<class O>
    SmarterPtr(O *lp, bool bAddRef = true) noexcept
    {
        p = dynamic_cast<T *>(lp);            // Type conversion
        if (p != NULL && bAddRef) p->AddRef();// Increment reference count
    }

    /// \brief Template copy constructor
    /// \param lp Another smart pointer whose object will be referenced.
    template<class O>
    SmarterPtr(const SmarterPtr<O> &lp) noexcept
    {
        p = dynamic_cast<T *>(lp.p);// Type conversion
        if (p != NULL) p->AddRef(); // Increment reference count
    }

    /// \brief Copy constructor
    /// \param lp Another smart pointer whose object will be referenced.
    SmarterPtr(const SmarterPtr<T> &lp) noexcept
    {
        p = lp.p;
        if (p != NULL) p->AddRef();// Increment reference count
    }

    /// \brief Constructor with RefObject pointer
    /// \param lp Pointer to the RefObject
    /// \param bAddRef If true, increments the reference count of the object.
    SmarterPtr(const RefObject *lp, bool bAddRef = true) noexcept
    {
        p = dynamic_cast<T *>(lp);            // Type conversion
        if (p != NULL && bAddRef) p->AddRef();// Increment reference count
    }

    /// \brief Explicit constructor with object pointer
    /// \param lp Pointer to the object
    /// \param bAddRef If true, increments the reference count of the object.
    explicit SmarterPtr(T *lp, bool bAddRef = true) noexcept
    {
        p = lp;
        if (p != NULL && bAddRef) p->AddRef();// Increment reference count
    }

public:
    /// \brief Destructor
    /// Decrements the reference count of the object.
    ~SmarterPtr() noexcept
    {
        if (p) p->Release();// Decrement reference count
    }

    /// \brief Convert to another smart pointer type
    /// \tparam Q Target type
    /// \return Smart pointer of type `Q`, or `nullptr` if conversion fails.
    template<class Q>
    SmarterPtr<Q> As()
    {
        if (!p) return 0;
        return dynamic_cast<Q *>(p);
    }

    /// \brief Check if the object is of a specific type
    /// \tparam Q Type to check against
    /// \return `true` if the object is of type `Q`, otherwise `false`.
    template<class Q>
    bool Is()
    {
        if (!p) return false;
        return dynamic_cast<Q *>(p) != 0;
    }

    /// \brief Implicit cast operator to raw pointer
    operator T *() const noexcept { return p; }

    /// \brief Cast to RefObject pointer
    operator RefObject *() const noexcept { return p; }

    /// \brief Explicit cast operator to boolean
    explicit operator bool() const noexcept { return 0 != p; }

    /// \brief Dereference operator
    T &operator*() const { return *p; }

    /// \brief Member access operator
    T *operator->() const noexcept { return p; }

    /// \brief Logical negation operator
    bool operator!() const noexcept { return (p == 0); }

    /// \brief Less-than operator
    bool operator<(T *pT) const noexcept { return p < pT; }

    /// \brief Increment reference count
    void AddRef() noexcept
    {
        if (p) p->AddRef();
    }

    /// \brief Decrement reference count and release the object
    void Release() noexcept
    {
        T *pTemp = p;
        if (pTemp)
        {
            p = NULL;
            pTemp->Release();
        }
    }

    /// \brief Compare two pointers for equality
    /// \param pOther Pointer to compare against
    /// \return `true` if the pointers are equal, otherwise `false`.
    bool IsEqualObject(RefObject *pOther) noexcept
    {
        if (p == NULL && pOther == NULL) return true;
        if (p == NULL || pOther == NULL) return false;
        RefObject *p1 = dynamic_cast<RefObject *>(p);
        return p1 == pOther;
    }

    /// \brief Attach a new object without incrementing the reference count
    /// \param p2 Pointer to the new object
    void Attach(T *p2) noexcept
    {
        if (p) p->Release();
        p = p2;
    }

    /// \brief Detach the managed object
    /// \return Pointer to the detached object
    T *Detach() noexcept
    {
        T *pt = p;
        p = NULL;
        return pt;
    }

    /// \brief Copy the pointer and increment reference count
    /// \param ppT Pointer to store the result
    /// \return `true` if successful, otherwise `false`.
    bool CopyTo(T **ppT) noexcept
    {
        if (ppT == NULL) return false;
        *ppT = p;
        if (p) p->AddRef();
        return true;
    }

    /// \brief Assignment operator for raw pointers
    /// \param lp Raw pointer to assign
    /// \return Pointer to the assigned object
    T *operator=(T *lp) noexcept
    {
        if (p != NULL)
            if (this->p == lp) return *this;
        if (lp) lp->AddRef();
        Attach(lp);
        return *this;
    }

    /// \brief Assignment operator for smart pointers
    /// \param lp Smart pointer to assign
    /// \return Pointer to the assigned object
    T *operator=(const SmarterPtr<T> &lp) noexcept
    {
        if (this->p != lp.p)
        {
            if (lp) lp->AddRef();
            Attach(lp);
        }
        return *this;
    }

    /// \brief Managed object pointer
    T *p;
};


template<class T, class Q>
bool operator==(const SmarterPtr<T> &lp1, const SmarterPtr<Q> &lp2) noexcept
{// test if SmarterPtr == SmarterPtr
    return (lp1.p == lp2.p);
}

template<class T, class Q>
bool operator!=(const SmarterPtr<T> &lp1, const SmarterPtr<Q> &lp2) noexcept
{// test if SmarterPtr != SmarterPtr
    return lp1.p != lp2.p;
}

template<class T>
bool operator==(const SmarterPtr<T> &lp, std::nullptr_t) noexcept
{// test if SmarterPtr == nullptr
    return lp.p == nullptr;
}

template<class T>
bool operator==(std::nullptr_t, const SmarterPtr<T> &lp) noexcept
{// test if nullptr == SmarterPtr
    return nullptr == lp.p;
}

template<class T>
bool operator!=(const SmarterPtr<T> &lp, std::nullptr_t) noexcept
{// test if SmarterPtr != nullptr
    return lp.p != nullptr;
}

template<class T>
bool operator!=(std::nullptr_t, const SmarterPtr<T> &lp) noexcept
{// test if nullptr != SmarterPtr
    return nullptr != lp.p;
}

/// \brief Template class for a weak pointer.
///        Provides non-owning references to objects managed by SmarterPtr,
///        allowing safe access without preventing object destruction.
template<class T>
class WeakSmarterPtr
{
    WeakReference *m_WeakRef;///< Internal weak reference to the object.

public:
    /// \brief Default constructor. Initializes with no reference.
    WeakSmarterPtr() : m_WeakRef(nullptr) {}

    /// \brief Constructor to initialize with a raw pointer.
    /// \param obj The raw pointer to manage as a weak reference.
    WeakSmarterPtr(T *obj) : m_WeakRef(nullptr)
    {
        if (!obj) return;
        m_WeakRef = new WeakReference(obj);
        m_WeakRef->AddRef();
    }

    /// \brief Constructor to initialize with a strong pointer (SmarterPtr).
    /// \param obj The strong pointer to convert to a weak reference.
    WeakSmarterPtr(const SmarterPtr<T> &obj) : m_WeakRef(nullptr)
    {
        if (!obj.p) return;
        m_WeakRef = new WeakReference(obj.p);
        m_WeakRef->AddRef();
    }

    /// \brief Copy constructor.
    /// \param weak Another WeakSmarterPtr to copy from.
    WeakSmarterPtr(const WeakSmarterPtr<T> &weak) : m_WeakRef(nullptr)
    {
        Reset(weak);
    }

    /// \brief Destructor. Releases the managed weak reference if it exists.
    ~WeakSmarterPtr()
    {
        if (m_WeakRef) m_WeakRef->Release();
    }

    /// \brief Checks whether the referenced object has expired.
    /// \return True if the referenced object is expired; otherwise false.
    bool Expired()
    {
        if (!m_WeakRef) return true;
        return m_WeakRef->Expired();
    }

    /// \brief STL-compatible alias for `Expired`.
    /// \return True if the referenced object is expired; otherwise false.
    bool expired() { return Expired(); }

    /// \brief Conversion operator to check if the reference is valid.
    /// \return True if the reference is valid; otherwise false.
    operator bool() { return !Expired(); }

    /// \brief Releases ownership of the managed object. STL-compatible.
    void reset() { Reset(); }

    /// \brief Releases ownership of the managed object.
    void Reset()
    {
        if (m_WeakRef) m_WeakRef->Release();
        m_WeakRef = nullptr;
    }

    /// \brief Resets to another WeakSmarterPtr, releasing the current reference.
    /// \param weak The WeakSmarterPtr to assign from.
    void Reset(const WeakSmarterPtr<T> &weak)
    {
        if (weak.m_WeakRef) weak.m_WeakRef->AddRef();
        Reset();
        m_WeakRef = weak.m_WeakRef;
    }

    /// \brief Resets to a strong SmarterPtr, releasing the current reference.
    /// \param obj The SmarterPtr to assign from.
    void Reset(const SmarterPtr<T> &obj) { Reset(obj.p); }

    /// \brief STL-compatible reset with a raw pointer.
    /// \param obj The raw pointer to assign from.
    void reset(T *obj) { Reset(obj); }

    /// \brief Resets to a raw pointer, releasing the current reference.
    /// \param obj The raw pointer to assign from.
    void Reset(T *obj)
    {
        Reset();
        if (!obj) return;
        m_WeakRef = new WeakReference(obj);
        m_WeakRef->AddRef();
    }

    /// \brief Assignment operator for another WeakSmarterPtr.
    /// \param right The WeakSmarterPtr to assign from.
    /// \return Reference to this WeakSmarterPtr.
    WeakSmarterPtr<T> &operator=(const WeakSmarterPtr<T> &right)
    {
        Reset(right);
        return *this;
    }

    /// \brief Assignment operator for a raw pointer.
    /// \param right The raw pointer to assign from.
    /// \return Reference to this WeakSmarterPtr.
    WeakSmarterPtr<T> &operator=(T *right)
    {
        Reset(right);
        return *this;
    }

    /// \brief Assignment operator for a strong SmarterPtr.
    /// \param right The SmarterPtr to assign from.
    /// \return Reference to this WeakSmarterPtr.
    WeakSmarterPtr<T> &operator=(const SmarterPtr<T> &right)
    {
        Reset(right);
        return *this;
    }

    /// \brief Converts the weak pointer to a strong SmarterPtr. STL-compatible.
    /// \return A strong SmarterPtr if the object is still valid; otherwise an empty SmarterPtr.
    SmarterPtr<T> lock() const { return Lock(); }

    /// \brief Converts the weak pointer to a strong SmarterPtr.
    /// \return A strong SmarterPtr if the object is still valid; otherwise an empty SmarterPtr.
    SmarterPtr<T> Lock() const
    {
        if (!m_WeakRef) return SmarterPtr<T>();

        RefObject *ref = m_WeakRef->LockReferenceObject();
        if (!ref) return SmarterPtr<T>();

        // Do not increment reference count because LockReferenceObject already does.
        return SmarterPtr<T>(ref, false);
    }
};

}// namespace CPL


/// \brief Macro to define smart pointer types based on object reference counting.
///        This macro generates two typedefs for the given class:
///        - A strong smart pointer type using `SmarterPtr`.
///        - A weak smart pointer type using `WeakSmarterPtr`.
///
/// \param P The class type for which smart pointer types will be defined.
#define CPL_SMARTER_PTR(P)             \
    typedef CPL::SmarterPtr<P> P##Ptr; \
    typedef CPL::WeakSmarterPtr<P> P##WPtr;