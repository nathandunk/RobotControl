//Low pass butterworth filter order=2 alpha1=0.2 
class  FilterBuLp2
{
  public:
    FilterBuLp2()
    {
      v[0]=0.0;
      v[1]=0.0;
    }
  private:
    float v[3];
  public:
    float step(float x) //class II 
    {
      v[0] = v[1];
      v[1] = v[2];
      v[2] = (3.621681514928615665e-3 * x)
         + (-0.83718165125602272969 * v[0])
         + (1.82269492519630826877 * v[1]);
      return 
         (v[0] + v[2])
        +2 * v[1];
    }
};