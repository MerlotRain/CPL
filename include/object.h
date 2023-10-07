/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file object.h
 * @brief
 * @details
 * @date 2023-06-18
 * @author
 *
 ******************************************************************************/

#pragma once

#include "delegate.h"
#include "preconfig.h"
#include <atomic>

namespace Lite {
namespace Utility {


/// @brief 不可拷贝对象，所有继承此类的对象将不可拷贝
class UTILITY_EXPORT GsNonCopyable
{
public:
    GsNonCopyable() = default;
    virtual ~GsNonCopyable() = default;

private:
    GsNonCopyable(const GsNonCopyable &) = delete;
    GsNonCopyable &operator=(const GsNonCopyable &) = delete;

    /// @brief 如果定义了不可移动宏，则屏蔽掉移动构造和移动赋值构造
#ifdef GS_DISABLE_MOVE
    GsNonCopyable(GsNonCopyable &&) = delete;
    GsNonCopyable &operator=(GsNonCopyable &&) = delete;
#endif
};


/// @brief 引用对象，通过继承该类获取对对象引用计数的支持
/// @details 默认裸指针的引用计数为0
/// @details 建议所有引用对象在构造时都是用智能指针模板装饰，从而实现对引用计数的自动管理
/// @details 引用对象基类接口的所有方法外部禁止调用和重写
class UTILITY_EXPORT GsRefObject : public GsNonCopyable
{
public:
    /// @brief 默认构造
    GsRefObject();

    /// @brief 默认析构
    virtual ~GsRefObject();

    /// @brief 添加引用计数
    void AddRef();

    /// @brief 尝试添加引用计数
    /// @return
    bool TryAddRef();

    /// @brief 减少引用计数
    void Release();

    /// @brief 获取引用计数值
    /// @return
    int RefCount();

    /// @brief 获取对象的Hash值
    /// @details 默认使用MD5算法
    /// @return
    virtual long long HashCode() const;

public:
    /// @brief
    /// @param size
    /// @return
    void *operator new(size_t size);
    /// @brief
    /// @param size
    /// @return
    void *operator new[](size_t size);
    /// @brief
    /// @param data
    void operator delete(void *data);
    /// @brief
    /// @param data
    void operator delete[](void *data);

    /// @brief 析构时调用，弱智能指针绑定委托实现自动析构
    GsDelegate<void(GsRefObject *)> Destory;

protected:
    std::atomic<int> m_RefCount;
};


/// @brief 弱引用对象
class UTILITY_EXPORT GsWeakReference : public GsRefObject
{
public:
    /// @brief 默认构造
    /// @param obj
    GsWeakReference(GsRefObject *obj);

    /// @brief 默认析构
    virtual ~GsWeakReference() override;

    /// @brief 获取强引用计数对象
    /// @return
    GsRefObject *Lock();

    /// @brief 函数委托，强引用对象析构时调用
    /// @param obj
    void OnDestroy(GsRefObject *obj);

    /// @brief 是否过期，引用的对象是否已经失效
    /// @return
    bool Expired() const noexcept;

    /// @brief 解绑强对象和弱对象的关系
    void Unlink() noexcept;

private:
    GsRefObject *m_RefObject;
    mutable std::mutex _mutex;
};


/// @brief 共享智能指针模板
/// @tparam T
template<typename T>
class GsSharedPointer
{
    static_assert(!std::is_pointer<T>::value,
                  "GsSharedPointer's template type must not be a pointer type");

public:
    /// @brief 默认构造
    GsSharedPointer() noexcept(false)
    {
        p = nullptr;
    }

    /// @brief 使用整型构造
    /// @param nNull
    GsSharedPointer(int nNull) noexcept(false)
    {
        p = nullptr;
    }

    /// @brief 使用长整型构造
    /// @param nNull
    GsSharedPointer(long int nNull) noexcept(false)
    {
        p = nullptr;
    }

    /// @brief 模板构造函数，实现引用计数加1
    /// @tparam O
    /// @param point
    /// @param bAddRef
    template<typename O>
    GsSharedPointer(O *point, bool bAddRef = true) noexcept(false)
    {
        p = dynamic_cast<T *>(point);
        if (p != nullptr && bAddRef)
        {
            p->AddRef();
        }
    }

    /// @brief 模板构造函数，实现引用计数加1
    /// @tparam O
    /// @param point
    template<typename O>
    GsSharedPointer(const GsSharedPointer<O> &point) noexcept(false)
    {
        p = dynamic_cast<T *>(point.p);
        if (p != nullptr)
        {
            p->AddRef();
        }
    }

    /// @brief 移动构造，实现引用计数加1
    /// @param point
    GsSharedPointer(const GsSharedPointer<T> &point) noexcept(false)
    {
        p = point.p;
        if (p != nullptr)
        {
            p->AddRef();
        }
    }

    /// @brief 使用引用对象构造，实现引用计数加1
    /// @param point
    /// @param bAddRef
    GsSharedPointer(const GsRefObject *point, bool bAddRef = true) noexcept(false)
    {
        p = dynamic_cast<T *>(point);
        if (p != nullptr && bAddRef)
        {
            p->AddRef();
        }
    }

    /// @brief 不能被隐式调用的构造函数，实现引用计数加1
    /// @param point
    /// @param bAddRef
    GsSharedPointer(T *point, bool bAddRef = true) noexcept(false)
    {
        p = point;
        if (p != nullptr && bAddRef)
        {
            p->AddRef();
        }
    }

    /// @brief 析构函数，实现引用计数减1
    ~GsSharedPointer() noexcept
    {
        if (p)
        {
            p->Release();
        }
    }

    /// @brief 如果指针不为空，则尝试转换为指定类型
    /// @tparam Q
    /// @return
    template<typename Q>
    GsSharedPointer<Q> As()
    {
        if (!p)
        {
            return 0;
        }
        return dynamic_cast<Q *>(p);
    }

    /// @brief 判断指针是否是指定类型
    /// @tparam Q
    /// @return
    template<typename Q>
    bool Is()
    {
        if (!p)
        {
            return false;
        }
        return dynamic_cast<Q *>(p) != 0;
    }

    /// @brief 类型转化模板
    operator T *() const noexcept(false)
    {
        return p;
    }

    /// @brief 类型转化
    operator GsRefObject *() const noexcept(false)
    {
        return p;
    }

    /// @brief 类型转化
    operator bool() const noexcept(false)
    {
        return 0 != p;
    }

    /// @brief 符号重载
    /// @return
    T &operator*() const
    {
        return *p;
    }

    /// @brief 符号重载
    /// @return
    T *operator->() const noexcept(false)
    {
        return p;
    }

    /// @brief 符号重载
    /// @return
    bool operator!() const noexcept(false)
    {
        return (p == 0);
    }

    /// @brief 符号重载
    /// @param point
    /// @return
    bool operator<(T *point) const noexcept(false)
    {
        return p < point;
    }

    /// @brief 引用计数加1
    void AddRef() noexcept(false)
    {
        if (p)
        {
            p->AddRef();
        }
    }

    /// @brief 引用计数减1
    void Release() noexcept(false)
    {
        T *temp = p;
        if (temp)
        {
            p = nullptr;
            temp->Release();
        }
    }

    /// @brief 比较2个指针的值
    /// @param pOther
    /// @return
    bool IsEqual(GsRefObject *pOther) noexcept(false)
    {
        if (p == nullptr && pOther == nullptr)
        {
            return true;
        }
        if (p == nullptr || pOther == nullptr)
        {
            return false;
        }
        auto *p1 = dynamic_cast<GsRefObject *>(p);
        return p1 == pOther;
    }

    /// @brief 绑定一个管理对象，引用计数不增加
    /// @param point
    void Attach(T *point) noexcept(false)
    {
        if (p)
        {
            p->Release();
        }
        p = point;
    }

    /// @brief 传递指针的值
    /// @return
    T *Detach() noexcept(false)
    {
        T *pt = p;
        p = nullptr;
        return pt;
    }

    /// @brief 对象克隆
    /// @param point
    /// @return
    bool CopyTo(T **point) noexcept(false)
    {
        if (point == nullptr)
        {
            return false;
        }
        *point = p;
        if (p)
        {
            p->AddRef();
        }
        return true;
    }

    /// @brief 符号重载，若指针非空，则引用计数加1，否则减1
    /// @param point
    /// @return
    T *operator=(T *point) noexcept(false)
    {
        if (p != nullptr)
        {
            if (this->p == point)
            {
                return *this;
            }
        }
        if (point)
        {
            point->AddRef();
        }
        Attach(point);
        return *this;
    }

    /// @brief 符号重载，若指针非空，则引用计数加1，否则减1
    /// @param point
    /// @return
    T *operator=(const GsSharedPointer<T> &point) noexcept(false)
    {
        if (this->p != point.p)
        {
            if (point)
            {
                point->AddRef();
            }
            Attach(point);
        }
        return *this;
    }
    T *Get()
    {
        return p;
    }

    T *p;
};


/// @brief 判断两个智能指针是否相同
/// @tparam T
/// @tparam Q
/// @param point1
/// @param point2
/// @return
template<typename T, typename Q>
inline bool operator==(const GsSharedPointer<T> &point1,
                       const GsSharedPointer<Q> &point2) noexcept(false)
{
    return (point1.p == point2.p);
}

/// @brief 判断两个智能指针是否不等
/// @tparam T
/// @tparam Q
/// @param point1
/// @param point2
/// @return
template<typename T, typename Q>
inline bool operator!=(const GsSharedPointer<T> &point1,
                       const GsSharedPointer<Q> &point2) noexcept(false)
{
    return point1.p != point2.p;
}

/// @brief 判断智能指针是否为空
/// @tparam T
/// @param point
/// @param
/// @return
template<typename T>
inline bool operator==(const GsSharedPointer<T> &point, std::nullptr_t) noexcept(false)
{
    return point.p == nullptr;
}

/// @brief 判断智能指针是否为空
/// @tparam T
/// @param
/// @param point
/// @return
template<typename T>
inline bool operator==(std::nullptr_t, const GsSharedPointer<T> &point) noexcept(false)
{
    return nullptr == point.p;
}

/// @brief 判断智能指针是否不为空
/// @tparam T
/// @param point
/// @param
/// @return
template<typename T>
inline bool operator!=(const GsSharedPointer<T> &point, std::nullptr_t) noexcept(false)
{
    return point.p != nullptr;
}

/// @brief 判断智能指针是否不为空
/// @tparam T
/// @param
/// @param point
/// @return
template<typename T>
inline bool operator!=(std::nullptr_t, const GsSharedPointer<T> &point) noexcept(false)
{
    return nullptr != point.p;
}


/// @brief 弱智能指针模板
/// @tparam T
template<typename T>
class GsWeakPointer
{
    static_assert(!std::is_pointer<T>::value,
                  "GsSharedPointer's template type must not be a pointer type");

public:
    GsWeakReference *m_WeakRef;

public:
    /// @brief 默认构造
    GsWeakPointer() : m_WeakRef(nullptr)
    {
    }

    /// @brief 使用对象构造
    /// @param obj
    GsWeakPointer(T *obj) : m_WeakRef(nullptr)
    {
        if (!obj)
        {
            return;
        }
        m_WeakRef = new GsWeakReference(obj);
        m_WeakRef->AddRef();
    }

    /// @brief 使用强智能指针构造
    /// @param obj
    GsWeakPointer(const GsSharedPointer<T> &obj) : m_WeakRef(nullptr)
    {
        if (!obj.p)
        {
            return;
        }
        m_WeakRef = new GsWeakReference(obj.p);
        m_WeakRef->AddRef();
    }

    /// @brief 拷贝构造
    /// @param weak
    GsWeakPointer(const GsWeakPointer<T> &weak) : m_WeakRef(nullptr)
    {
        Reset(weak);
    }

    /// @brief 析构
    ~GsWeakPointer()
    {
        if (m_WeakRef)
        {
            m_WeakRef->Release();
        }
    }

    /// @brief 引用的对象是否有效，没有过期则有效
    operator bool()
    {
        return !Expired();
    }

    /// @brief 是否过期，引用的对象是否已经失效
    /// @return
    bool Expired()
    {
        if (!m_WeakRef)
        {
            return true;
        }
        return m_WeakRef->Expired();
    }

    /// @brief 释放被管理对象的所有权
    void Reset()
    {
        if (m_WeakRef)
        {
            m_WeakRef->Release();
        }
        m_WeakRef = nullptr;
    }

    /// @brief 设置新的管理指针，释放原有的指针管理权
    /// @param weak
    void Reset(const GsWeakPointer<T> &weak)
    {
        if (weak.m_WeakRef)
        {
            weak.m_WeakRef->AddRef();
        }
        Reset();
        m_WeakRef = weak.m_WeakRef;
    }

    /// @brief 设置新的管理指针，释放原有的指针管理权
    /// @param obj
    void Reset(const GsSharedPointer<T> &obj)
    {
        Reset(obj.p);
    }

    /// @brief 释放被管理对象的所有权
    /// @param obj
    void Reset(T *obj)
    {
        Reset();
        if (!obj)
        {
            return;
        }
        m_WeakRef = new GsWeakReference(obj);
        m_WeakRef->AddRef();
    }

    /// @brief 获取强指针的引用
    /// @return
    GsSharedPointer<T> Lock() const
    {
        if (!m_WeakRef)
        {
            return GsSharedPointer<T>();
        }

        GsRefObject *ref = m_WeakRef->Lock();
        if (!ref)
        {
            return GsSharedPointer<T>();
        }
        return GsSharedPointer<T>(ref, false);
    }

    GsWeakPointer<T> &operator=(const GsWeakPointer<T> &right)
    {
        Reset(right);
        return *this;
    }

    GsWeakPointer<T> &operator=(T *right)
    {
        Reset(right);
        return *this;
    }

    GsWeakPointer<T> &operator=(const GsSharedPointer<T> &right)
    {
        Reset(right);
        return *this;
    }
};


#define GS_SMARTER_PTR(Class)                                 \
    typedef Lite::Utility::GsSharedPointer<Class> Class##Ptr; \
    typedef Lite::Utility::GsWeakPointer<Class> Class##WPtr;

#define STD_SHARED_POINTER(Class)              \
    typedef std::shared_ptr<Class> Class##Ptr; \
    typedef std::weak_ptr<Class> Class##WPtr;


template<class T>
class GsSingletonRef
{
public:
    GsSingletonRef()
    {
    }
};


/// @brief 类工厂模型
class UTILITY_EXPORT GsClassFactory
{
public:
    typedef GsRefObject *(*FactoryCreateFun)();

    /// @brief 注册类工厂
    /// @param fun
    /// @param className
    /// @param category
    static void RegisterFactoryCreate(FactoryCreateFun fun, const char *className,
                                      const char *category = nullptr);

    /// @brief 根据名称创建类实例
    /// @tparam T
    /// @param classname
    /// @return
    template<typename T>
    static T *CreateInstance(const char *classname)
    {
        GsRefObject *obj = CreateInstancePrivate(classname);
        if (!obj)
        {
            return 0;
        }

        T *o = dynamic_cast<T *>(obj);
        if (!o)
        {
            delete obj;
            return 0;
        }
        return o;
    }

    /// @brief 根据名称创建类实例
    /// @tparam T
    /// @param classname
    /// @return
    template<typename T>
    static GsSharedPointer<T> CreateInstanceT(const char *classname)
    {
        GsRefObject *obj = CreateInstancePrivate(classname);
        if (!obj)
        {
            return 0;
        }

        T *o = dynamic_cast<T *>(obj);
        if (!o)
        {
            delete obj;
            return 0;
        }
        return GsSharedPointer<T>(o);
    }

    /// @brief 获取一族类名称
    /// @param category
    /// @return
    std::vector<std::string> GetClassNamesByCategory(const char *category);

private:
    static GsRefObject *CreateInstancePrivate(const char *className);
};


class UTILITY_EXPORT GsSingleton
{
};

#ifdef _WIN32
#define GS_MODULE_EXPORT __declspec(dllexport)
#else
#define GS_MODULE_EXPORT __attribute__((visibility("default")))
#endif
#define DECLARE_CLASS_CREATE(ClassName) \
    extern "C" GS_MODULE_EXPORT Lite::Utility::GsRefObject *createClass##ClassName();
#define DECLARE_CLASS_CREARE_IMPL(ClassName)                                         \
    extern "C" GS_MODULE_EXPORT Lite::Utility::GsRefObject *createClass##ClassName() \
    {                                                                                \
        return new ClassName();                                                      \
    }

#define REGISTER_CLASS_CREATE(ClassName) \
    Lite::Utility::GsClassFactory::registerFactoryCreate(CreateClass##ClassName, #ClassName);
#define REGISTER_CLASS_CREATE_NAMESPACE(ClassName, NS) \
    Lite::Utility::GsClassFactory::registerFactoryCreate(NS::CreateClass##ClassName, #ClassName);

#define REGISTER_CLASS_CREATE_CATEGORY(ClassName, category) \
    Lite::Utility::GsClassFactory::registerFactoryCreate(CreateClass##ClassName, #ClassName, #category);
#define REGISTER_CLASS_CREATE_NAMESPACE_CATEGORY(ClassName, category, NS)                        \
    Lite::Utility::GsClassFactory::registerFactoryCreate(NS::CreateClass##ClassName, #ClassName, \
                                                         #category);


#define DECLARE_CLASS_NAME(class_name)               \
    virtual Lite::Utility::GsString FullClassName()  \
    {                                                \
        return Lite::Utility::GsString(#class_name); \
    }


}// namespace Utility
}// namespace Lite
