#ifndef Filter_h
#define Filter_h

class  FilterBuLp2
{
  public:
    FilterBuLp2();
  private:
    float v[3];
  public:
    float step(float x);
};

#endif