#ifndef _PIT_H_
#define _PIT_H_

// Programmable Interval Timer (PIT)
namespace PIT {
    void phase(int __frequency /*hz*/);
    void pit_init();
    void wait(int __ticks);
};

#endif