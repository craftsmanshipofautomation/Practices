#ifndef D625F45F6_0134_1398_EA65_473CBDC145F8
#define D625F45F6_0134_1398_EA65_473CBDC145F8

#include "ftf.h"
#include "packet_queue.h"

class Demuxer
{
    public:
        Demuxer(const char* filename);
        ~Demuxer();
        void Start();

        AVCodecParameters* audio_codecpar() { return audio_codecpar_;}
        sp<PacketQueue>& audio_packet_queue() { return audio_pktq_;}
        SDL_cond * continue_read_thread() { return continue_read_thread_; }
    private:
        int read_thread();
        static int thread_function(void*);

        bool packet_queue_is_full();
        bool have_enough_visible_packets();
    private:
        AVFormatContext *ic_;
        AVCodecParameters *audio_codecpar_;
        int audio_stream_index_;
        sp<PacketQueue> audio_pktq_;

        SDL_cond* continue_read_thread_;
        SDL_Thread *read_tid_;

        bool eof_;
        bool abort_request_;
};







#endif /* 625F45F6_0134_1398_EA65_473CBDC145F8 */
