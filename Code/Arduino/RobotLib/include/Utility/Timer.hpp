class Timer
{
private:
    float period;
    float period_micros;
    unsigned long int last_time_micros;
    unsigned long int current_time_micros;
    unsigned long int start_time_micros;

public:
    Timer(float period_);
    ~Timer();

    void start();
    float wait();
};

// TODO ADD HERTZ, MILLISECONDS, SECONDS, etc option