#include "Event/CallbackEvent.h"
#include "Logger/Logger.h"

void F() {
    LOG("CCC SSSSSSSSSSSSs");
}

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
    CallbackEvent<void()> callback;
    callback.regCallbackFunc(F);
    callback.emit();
    return 0;
}