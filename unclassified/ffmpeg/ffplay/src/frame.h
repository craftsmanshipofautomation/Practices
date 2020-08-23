#ifndef FRAME_H_12313dsflllfjljfdlsjasofasdfjasljfl
#define FRAME_H_12313dsflllfjljfdlsjasofasdfjasljfl

#include "ftf.h"

class Frame {
public:
  Frame();
  ~Frame();
  int reset();

public:
  AVFrame *frame;
  //AVSubtitle sub;
  int serial;
  double pts;      /* presentation timestamp for the frame */
  double duration; /* estimated duration of the frame */
  int64_t pos;     /* byte position of the frame in the input file */
  int width;
  int height;
  int format;
  AVRational sample_rate;
  int uploaded;
  int flip_v;

};

#endif
