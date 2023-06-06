#include "common/callback.h"
#include "common/logger/logger.h"

int main()
{
    int n = 3;
    // EventEmitter<Events> event;
    // event.on(Events::Change, [&]() {
    //     LOG_INFO("CCC %d", n);
    // });
    // event.emit(Events::Change);

    // EventEmitter<> emitter;
    // Event<>& changeEvent = *emitter.event(Events::Change);
    // changeEvent.connect([&](){
    //     LOG_INFO("CCC SSSSSSSSSSSSs %d", n);
    // });
    // changeEvent.emit();
    Callback callback;
    callback.regCallbackFunc([&]()
                             { LOG_INFO("CCC SSSSSSSSSSSSs %d", n); });
    callback.regCallbackFunc([&]()
                             { LOG_INFO("CCC RRRRRRRRRRRr %d", n); });
    callback.emit();
    return 0;
}