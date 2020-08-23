#ifndef FRAME_QUEUE_H_DFAFAD234FG345ADF
#define FRAME_QUEUE_H_DFAFAD234FG345ADF

#include "ftf.h"
#include "frame.h"
#include "packet_queue.h"

class FrameQueue
{
  public:
    FrameQueue(sp<PacketQueue> pq, int max_size, bool keep_last);
    ~FrameQueue();
    void Wait();
    void Signal();
    ///< Peek: to check
    ///< 查看“棧頂”的元素
    ///< 但棧頂的元素分兩種狀態
    ///< 一種是被讀過的，一種未讀
    ///< 未讀是指，PUSH進去後，沒有被read
    Frame* Peek();
    Frame* PeekNext();
    Frame* PeekLast();
    ///< 如果没有写入空间, 阻塞
    ///< 有写入空间后返回该空间的地址
    ///< 可能的問題： A, B線程申請寫入空間，A線程先得到
    ///< 但可能比 B 線程後寫入
    Frame* PeekWritable();
    ///< 如果队列是空的, 阻塞
    ///< 直到有 Packet 进入队列
    Frame* PeekReadable();
    ///< 改变写指针, 但不负责写入东西
    ///< 空队列时,某些线程正在等待新的包
    ///< 这时候发一个信号它就会收到
    ///< 即使队列不为空, 发个信号也无所谓
    void Push();
    ///< 如果當前的幀還沒被讀，那就不移動
    ///< 如果讀了，就將這一幀給釋放，移動到下一幀
    ///< 将 read 指针当前所指的帧释放掉
    ///< 然后移动一位
    void Next();
    ///< 返回还未展示(undisplayed)的帧的数目
    int GetNbRemaining();
    ///< 返回上一个 shown 位置
    int GetLastPos();


  private:
    Frame queue_[FRAME_QUEUE_SIZE];
    ///< rindex_ 所指的地方相当于 last
    int rindex_;
    ///< 標誌位
    ///< rindex_ 指向的节点是否被读过
    int rindex_shown_;
    ///< 写一个,
    int windex_;
    ///< 帧的数量
    int size_;
    ///< 最大容量
    int max_size_;
    bool keep_last_;
    SDL_mutex *mutex_;
    SDL_cond *cond_;
    sp<PacketQueue> packet_queue_;

    public:  // getters

};

#endif