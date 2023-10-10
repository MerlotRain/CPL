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

class M2_API BackgroundTask : public RefObject
{
public:
    virtual ~BackgroundTask() {}

    virtual void ExecuteTask() = 0;

    virtual void Cancel();

    static SharedPointer<BackgroundTask> Create(std::function<void()> funcationTask);

protected:
    BackgroundTask();
    volatile bool m_bCancel;
};
M2_SMARTER_PTR(BackgroundTask)


enum DispatchOption
{
    eDummy,
    eRoundRobin,
};

class DispatchOp;
class M2_API PackagedTack : public RefObject
{
    std::queue<BackgroundTaskPtr> m_Tasks;
    std::unique_ptr<DispatchOp> m_Option;

public:
    PackagedTack(DispatchOption option = eDummy);

    ~PackagedTack();

    void AddTask(BackgroundTask *pTask);

    void Shutdown();
};
M2_SMARTER_PTR(PackagedTack)
