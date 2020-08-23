#include "def.h"

int common = 0;
SDL_cond *cond_;
SDL_mutex *mutex_;

int thread_A(void *)
{
    while (1)
    {
        SDL_Delay(500);
        SDL_LockMutex(mutex_);
        ++common;
        printf("A: update common to %d\n", common);
        SDL_CondSignal(cond_);
        SDL_UnlockMutex(mutex_);
    }
    return 0;
}

int thread_B(void *)
{
    int old = common;
    while (1)
    {
        SDL_LockMutex(mutex_);
        while (old == common)
        {
            printf("B: waiting for update\n");
            SDL_CondWait(cond_, mutex_);
        }
        old = common;
        printf("B: get new common %d\n", common);
        SDL_UnlockMutex(mutex_);
    }
    return 0;
}

int main()
{
    cond_ = SDL_CreateCond();
    mutex_ = SDL_CreateMutex();

    SDL_Thread *a = SDL_CreateThread(thread_A, "a", (void *)NULL);
    SDL_Thread *b = SDL_CreateThread(thread_B, "b", (void *)NULL);

    SDL_WaitThread(a, NULL);
    SDL_WaitThread(b, NULL);

    SDL_DestroyCond(cond_);
    SDL_DestroyMutex(mutex_);
}