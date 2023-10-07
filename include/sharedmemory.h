/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file sharedmemory.h
 * @brief
 * @details
 * @date 2023-07-22
 * @author
 *
 ******************************************************************************/


#pragma once


#include "filesystem.h"
#include "preconfig.h"

namespace Lite {
namespace Utility {

/// @brief 共享内存模型
class UTILITY_EXPORT GsSharedMemory
{
public:
    /// @brief 访问方式
    enum AccessMode
    {
        AM_READ = 0,
        AM_WRITE
    };

    GsSharedMemory();
    /// @brief 创建一块共享内存
    /// @param name 文件名称
    /// @param size 内存大小
    /// @param mode 访问方式
    /// @param addrHint 共享内存的起始地址
    /// @param server linux下，当共享内存被破坏是，调用shm_unlink取消链接
    GsSharedMemory(const char *name, std::size_t size, AccessMode mode, const void *addrHint = 0, bool server = true);

    /// @brief 创建一块共享内存
    /// @param file 文件对象
    /// @param mode 访问方式
    /// @param addrHint 共享内存的起始地址
    GsSharedMemory(const GsFile &file, AccessMode mode, const void *addrHint = 0);

    /// @brief 拷贝构造
    /// @param other
    GsSharedMemory(const GsSharedMemory &rhs);

    /// @brief 默认析构
    ~GsSharedMemory();

    /// @brief 赋值复制构造
    /// @param rhs
    /// @return
    GsSharedMemory &operator=(const GsSharedMemory &rhs);

    /// @brief 交换共享内存
    /// @param rhs
    void Swap(GsSharedMemory &rhs) noexcept;
    /// @brief 返回共享内存的起始地址
    /// @return
    char *Begin() const;

    /// @brief 返回共享内存的结束地址
    /// @return
    char *End() const;

    /// @brief 共享内存的大小
    /// @return
    unsigned long long Size() const;

private:
    void *m_Handle;
};

}// namespace Utility
}// namespace Lite
