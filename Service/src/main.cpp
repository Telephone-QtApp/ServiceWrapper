#include "common/eventemitter.h"
#include "common/logger/logger.h"

int main()
{
    int n = 3;
    EventEmitter<Events> event;
    event.on(Events::Change, [&]() {
        LOG_INFO("CCC %d", n);
    });
    event.emit(Events::Change);
    return 0;
}