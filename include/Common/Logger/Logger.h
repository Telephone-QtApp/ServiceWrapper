namespace logger
{
    #include <stdio.h>
    #include <stdarg.h>

    void log(const char* format, ...) 
    {
        va_list args;
        va_start(args, format);
        ::vprintf(format, args);
        va_end(args);
        printf("\n");
    }


} // namespace logger

#define LOG_ERR(F, ...)  logger::log("\033[1;31m[ERR]\033[0m: " F, __VA_ARGS__)
#define LOG_INFO(F, ...) logger::log("\033[1;33m[INFO]\033[0m: " F, __VA_ARGS__)
#define LOG(L)           logger::log(L)
