// ensure this library description is only included once
#ifndef PD_Controller_h
#define PD_Controller_h

// library interface description
class PD_Controller
{
  // user-accessible "public" interface
  public:
    PD_Controller(float P, float D, bool flip_dir_);
    
    float CalcTorque(float pos, float vel, float pos_d, float vel_d);

  // library-accessible "private" interface
  private:
    float kp;
    float kd;
    bool flip_dir;
};

#endif

