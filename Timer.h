#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
    Timer();
    ~Timer();

    void start();
    void stop();
    void paused();
    void unpaused();

    int get_tick();

    bool const start_check() {return is_started;};
    bool const pause_check() {return is_paused;};

private:
    int start_tick;
    int paused_tick;

    bool is_started;
    bool is_paused;
};

#endif // TIMER_H
