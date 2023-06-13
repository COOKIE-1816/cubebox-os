#include "kernel/kdrivers.h"

typedef struct kdriver_t {
    int status;
    bool critical;

    String displayedName;
    String vendor;

    int load(int __targetAddress);
    int load_auto();
    void unload();
    
    void statusShow(const int __status);
} kdriver_t;