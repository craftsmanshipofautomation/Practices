#include "frame_queue.h"

FrameQueue::FrameQueue(sp<PacketQueue> pq, int max_size, bool keep_last)
:packet_queue_(std::move(pq))
, max_size_(FFMIN(max_size, FRAME_QUEUE_SIZE))
, keep_last_(keep_last)
, cond_(SDL_CreateCond())
, mutex_(SDL_CreateMutex())
{
}

void FrameQueue::Wait()
{
    SDL_LockMutex(mutex_);
    SDL_CondWaitTimeout(cond_, mutex_, 100);
    SDL_UnlockMutex(mutex_);
}

FrameQueue::~FrameQueue()
{
    for (int i = 0; i < max_size_; ++i)
    {
        queue_[i].reset();
    }
    SDL_DestroyCond(cond_);
    SDL_DestroyMutex(mutex_);
}

void FrameQueue::Signal()
{
    SDL_LockMutex(mutex_);
    SDL_CondSignal(cond_);
    SDL_UnlockMutex(mutex_);
}

Frame *FrameQueue::Peek()
{
    ///< 如果当前的节点没被读过, 那就返回当前节点, 否则下一个
    return &queue_[(rindex_ + rindex_shown_)
                    % // 环状
                    max_size_];
}

Frame *FrameQueue::PeekNext()
{
    return &queue_[(rindex_ + rindex_shown_ + 1) %
                       max_size_];
}

Frame *FrameQueue::PeekLast()
{
    return &queue_[rindex_];
}

Frame *FrameQueue::PeekWritable()
{
    #if 0
    lzlog(cond_, p);
    lzlog(mutex_, p);
    
    SDL_LockMutex(mutex_);
    
    SDL_CondWaitTimeout(cond_, mutex_, 100);
    
    SDL_UnlockMutex(mutex_);
    
    #endif

    SDL_LockMutex(mutex_);
    while (size_ >= max_size_ && !packet_queue_->abort_request())
    {
        LOGF("SDL_CondWait");
        LOGF("size_: %d, max_size_: %d, !packet_queue_->abort_request():%d",
            size_, max_size_, !packet_queue_->abort_request()
        );
        SDL_CondWait(cond_, mutex_);
    }
    SDL_UnlockMutex(mutex_);

    if (packet_queue_->abort_request())
        return NULL;

    return &queue_[windex_];
}

Frame *FrameQueue::PeekReadable()
{
    lzlog(cond_, p);
    lzlog(mutex_, p);
    SDL_LockMutex(mutex_);
    //while (size_ - rindex_shown_ <= 0 && !packet_queue_->abort_request())
        SDL_CondWait(cond_, mutex_);
    SDL_UnlockMutex(mutex_);
    

    if (packet_queue_->abort_request())
        return NULL;

    LOGF("PeekReadable exit");

    return &queue_[
        (rindex_ + rindex_shown_)
        %
        max_size_
        ];
}

void FrameQueue::Push()
{
    if (++windex_ == max_size_)
        windex_ = 0;
    SDL_LockMutex(mutex_);
    size_++;
    SDL_CondSignal(cond_);
    SDL_UnlockMutex(mutex_);
    LOGF("Push exit");
}

void FrameQueue::Next()
{
    if (keep_last_ && !rindex_shown_)
    {
        rindex_shown_ = true;
        return;
    }
    ///< wipe the fuck out
    queue_[rindex_].reset();
    ///< 如果读取指针到达尽头, 返回起点
    if (++rindex_ == max_size_)
    {
        rindex_ = 0;
    }
    SDL_LockMutex(mutex_);
    size_--;
    SDL_CondSignal(cond_);
    SDL_UnlockMutex(mutex_);
}

int FrameQueue::GetNbRemaining()
{
    return size_ - rindex_shown_;
}

int FrameQueue::GetLastPos()
{
    Frame *fp = &queue_[rindex_];
    ///< todo
    if (rindex_shown_ && fp->serial == packet_queue_->serial())
        return fp->pos;
    else
        return -1;
}

