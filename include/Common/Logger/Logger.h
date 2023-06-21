namespace logger
{
    void log(const char* format, ...);
}

#define LOG_ERR(F, ...)  logger::log("\033[1;31m[ERR]\033[0m: " F, __VA_ARGS__)
#define LOG_INFO(F, ...) logger::log("\033[1;33m[INFO]\033[0m: " F, __VA_ARGS__)
#define LOG(L)           logger::log(L)