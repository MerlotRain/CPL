/****************************************************************************
**
** Copyright (C) 2023 MerlotRain
** Github:https://github.com/MerlotRain
**
** M2 is a cross platform C++basic library that encapsulates commonly 
** used C++ classes and functional modules, shields system functions from 
** the outside, and provides a unified interface.
**
** $M2_BEGIN_LICENSE:MIT$
** Permission is hereby granted, free of charge, to any person obtaining a 
** copy of this software and associated documentation files (the “Software”), 
** to deal in the Software without restriction, including without limitation 
** the rights to use, copy, modify, merge, publish, distribute, sublicense, 
** and/or sell copies of the Software, and to permit persons to whom the 
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included 
** in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS 
** OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
** DEALINGS IN THE SOFTWARE.
** 
** $M2_END_LICENSE$
**
****************************************************************************/

#ifndef M2_OBJECT_H_
#define M2_OBJECT_H_

#include <m2_delegate.h>
#include <preconfig.h>

namespace m2 {

class StringList;

class M2_API NonCopyable
{
public:
    NonCopyable();
    virtual ~NonCopyable();

private:
    NonCopyable(const NonCopyable &);
    NonCopyable &operator=(const NonCopyable &);
};

class M2_API RefObject : public NonCopyable
{
public:
    RefObject();
    virtual ~RefObject();
    void addRef();
    bool tryAddRef();
    void release();
    int refCount();
    virtual long long hashCode() const;

public:
    void *operator new(size_t size);
    void *operator new[](size_t size);
    void operator delete(void *data);
    void operator delete[](void *data);
    Delegate<void(RefObject *)> Destory;

protected:
    std::atomic<int> m_RefCount;
};

class M2_API WeakRefObject : public RefObject
{
public:
    WeakRefObject(RefObject *obj);
    virtual ~WeakRefObject() override;
    RefObject *lock();
    void OnDestroy(RefObject *obj);
    bool expired() const noexcept;
    void Unlink() noexcept;

private:
    RefObject *m_RefObject;
    mutable std::mutex _mutex;
};


template<typename T>
class SmarterPointer
{
    static_assert(!std::is_pointer<T>::value,
                  "SmarterPointer's template type must not be a pointer type");

public:
    SmarterPointer() noexcept { p = nullptr; }
    SmarterPointer(int nNull) noexcept { p = nullptr; }
    SmarterPointer(long int nNull) noexcept { p = nullptr; }

    template<typename O>
    SmarterPointer(O *point, bool bAddRef = true) noexcept
    {
        p = dynamic_cast<T *>(point);
        if (p != nullptr && bAddRef)
            p->addRef();
    }
    template<typename O>
    SmarterPointer(const SmarterPointer<O> &point) noexcept
    {
        p = dynamic_cast<T *>(point.p);
        if (p != nullptr)
            p->addRef();
    }
    SmarterPointer(const SmarterPointer<T> &point) noexcept
    {
        p = point.p;
        if (p != nullptr)
            p->addRef();
    }
    SmarterPointer(const RefObject *point, bool bAddRef = true) noexcept
    {
        p = dynamic_cast<T *>(point);
        if (p != nullptr && bAddRef)
            p->addRef();
    }
    SmarterPointer(T *point, bool bAddRef = true) noexcept
    {
        p = point;
        if (p != nullptr && bAddRef)
            p->addRef();
    }
    ~SmarterPointer() noexcept
    {
        if (p) p->release();
    }

    template<typename Q>
    SmarterPointer<Q> as()
    {
        if (!p) return 0;
        return dynamic_cast<Q *>(p);
    }

    template<typename Q>
    bool is()
    {
        if (!p) return false;
        return dynamic_cast<Q *>(p) != 0;
    }

    operator T *() const noexcept { return p; }
    operator RefObject *() const noexcept { return p; }
    operator bool() const noexcept { return 0 != p; }
    T &operator*() const { return *p; }
    T *operator->() const noexcept { return p; }
    bool operator!() const noexcept { return (p == 0); }
    bool operator<(T *point) const noexcept { return p < point; }

    void addRef() noexcept
    {
        if (p) p->addRef();
    }
    void release() noexcept
    {
        T *temp = p;
        if (temp)
        {
            p = nullptr;
            temp->release();
        }
    }
    bool isEqual(RefObject *pOther) noexcept
    {
        if (p == nullptr && pOther == nullptr)
            return true;
        if (p == nullptr || pOther == nullptr)
            return false;

        auto *p1 = dynamic_cast<RefObject *>(p);
        return p1 == pOther;
    }

    void attach(T *point) noexcept
    {
        if (p) p->release();
        p = point;
    }
    T *detach() noexcept
    {
        T *pt = p;
        p = nullptr;
        return pt;
    }

    bool copyTo(T **point) noexcept
    {
        if (point == nullptr)
            return false;
        *point = p;
        if (p)
            p->addRef();
        return true;
    }
    T *operator=(T *point) noexcept
    {
        if (p != nullptr)
            if (this->p == point)
                return *this;

        if (point)
            point->addRef();
        attach(point);
        return *this;
    }
    T *operator=(const SmarterPointer<T> &point) noexcept
    {
        if (this->p != point.p)
            if (point)
                point->addRef();
        attach(point);

        return *this;
    }

    T *p;
};

template<typename T, typename Q>
inline bool operator==(const SmarterPointer<T> &point1,
                       const SmarterPointer<Q> &point2) noexcept
{
    return (point1.p == point2.p);
}

template<typename T, typename Q>
inline bool operator!=(const SmarterPointer<T> &point1,
                       const SmarterPointer<Q> &point2) noexcept
{
    return point1.p != point2.p;
}

template<typename T>
inline bool operator==(const SmarterPointer<T> &point, std::nullptr_t) noexcept
{
    return point.p == nullptr;
}

template<typename T>
inline bool operator==(std::nullptr_t, const SmarterPointer<T> &point) noexcept
{
    return nullptr == point.p;
}

template<typename T>
inline bool operator!=(const SmarterPointer<T> &point, std::nullptr_t) noexcept
{
    return point.p != nullptr;
}

template<typename T>
inline bool operator!=(std::nullptr_t, const SmarterPointer<T> &point) noexcept
{
    return nullptr != point.p;
}


template<typename T>
class WeakPointer
{
    static_assert(!std::is_pointer<T>::value,
                  "SmarterPointer's template type must not be a pointer type");

public:
    WeakRefObject *m_WeakRef;

public:
    WeakPointer() : m_WeakRef(nullptr) {}
    WeakPointer(T *obj) : m_WeakRef(nullptr)
    {
        if (!obj) return;
        m_WeakRef = new WeakRefObject(obj);
        m_WeakRef->addRef();
    }
    WeakPointer(const SmarterPointer<T> &obj) : m_WeakRef(nullptr)
    {
        if (!obj.p) return;
        m_WeakRef = new WeakRefObject(obj.p);
        m_WeakRef->addRef();
    }
    WeakPointer(const WeakPointer<T> &weak) : m_WeakRef(nullptr) { reset(weak); }
    ~WeakPointer()
    {
        if (m_WeakRef) m_WeakRef->release();
    }

    operator bool() { return !expired(); }

    bool expired()
    {
        if (!m_WeakRef) return true;
        return m_WeakRef->expired();
    }
    void reset()
    {
        if (m_WeakRef) m_WeakRef->release();
        m_WeakRef = nullptr;
    }
    void reset(const WeakPointer<T> &weak)
    {
        if (weak.m_WeakRef) weak.m_WeakRef->addRef();
        reset();
        m_WeakRef = weak.m_WeakRef;
    }
    void reset(const SmarterPointer<T> &obj) { reset(obj.p); }
    void reset(T *obj)
    {
        reset();
        if (!obj)
        {
            return;
        }
        m_WeakRef = new WeakRefObject(obj);
        m_WeakRef->addRef();
    }
    SmarterPointer<T> lock() const
    {
        if (!m_WeakRef) return SmarterPointer<T>();
        RefObject *ref = m_WeakRef->lock();
        if (!ref) return SmarterPointer<T>();
        return SmarterPointer<T>(ref, false);
    }
    WeakPointer<T> &operator=(const WeakPointer<T> &right)
    {
        reset(right);
        return *this;
    }
    WeakPointer<T> &operator=(T *right)
    {
        reset(right);
        return *this;
    }
    WeakPointer<T> &operator=(const SmarterPointer<T> &right)
    {
        reset(right);
        return *this;
    }
};


#define M2_SMARTER_PTR(Class)                     \
    typedef m2::SmarterPointer<Class> Class##Ptr; \
    typedef m2::WeakPointer<Class> Class##WPtr;

#define STD_SHARED_POINTER(Class)              \
    typedef std::shared_ptr<Class> Class##Ptr; \
    typedef std::weak_ptr<Class> Class##WPtr;


template<class T>
class SingletonRef
{
public:
    SingletonRef()
    {
    }
};


class M2_API ClassFactory
{
public:
    typedef RefObject *(*FactoryCreateFun)();
    static void registerFactoryCreate(FactoryCreateFun fun, const char *className,
                                      const char *category = nullptr);

    template<typename T>
    static T *createInstance(const char *classname)
    {
        RefObject *obj = createInstancePrivate(classname);
        if (!obj) return 0;

        T *o = dynamic_cast<T *>(obj);
        if (!o)
        {
            delete obj;
            return 0;
        }
        return o;
    }
    template<typename T>
    static SmarterPointer<T> createInstanceT(const char *classname)
    {
        RefObject *obj = createInstancePrivate(classname);
        if (!obj) return 0;
        T *o = dynamic_cast<T *>(obj);
        if (!o)
        {
            delete obj;
            return 0;
        }
        return SmarterPointer<T>(o);
    }
    StringList classNamesByCategory(const char *category);

private:
    static RefObject *createInstancePrivate(const char *className);
};


class M2_API Singleton
{
};

#ifdef _WIN32
#define GS_MODULE_EXPORT __declspec(dllexport)
#else
#define GS_MODULE_EXPORT __attribute__((visibility("default")))
#endif
#define DECLARE_CLASS_CREATE(ClassName) \
    extern "C" GS_MODULE_EXPORT m2::RefObject *createClass##ClassName();
#define DECLARE_CLASS_CREARE_IMPL(ClassName)                            \
    extern "C" GS_MODULE_EXPORT m2::RefObject *createClass##ClassName() \
    {                                                                   \
        return new ClassName();                                         \
    }

#define REGISTER_CLASS_CREATE(ClassName) \
    m2::ClassFactory::registerFactoryCreate(CreateClass##ClassName, #ClassName);
#define REGISTER_CLASS_CREATE_NAMESPACE(ClassName, NS) \
    m2::ClassFactory::registerFactoryCreate(NS::CreateClass##ClassName, #ClassName);

#define REGISTER_CLASS_CREATE_CATEGORY(ClassName, category) \
    m2::ClassFactory::registerFactoryCreate(CreateClass##ClassName, #ClassName, #category);
#define REGISTER_CLASS_CREATE_NAMESPACE_CATEGORY(ClassName, category, NS)           \
    m2::ClassFactory::registerFactoryCreate(NS::CreateClass##ClassName, #ClassName, \
                                            #category);

#define DECLARE_CLASS_NAME(class_name)  \
    virtual m2::String fullClassName()  \
    {                                   \
        return m2::String(#class_name); \
    }


}// namespace m2

#endif//M2_OBJECT_H_