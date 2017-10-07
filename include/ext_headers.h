#ifndef BASECONVERTER_EXT_HEADERS_H
#define BASECONVERTER_EXT_HEADERS_H


#if defined(_MSC_VER)
#define EXT_HEADERS_OPEN \
__pragma(warning(push))\
__pragma(warning(disable:4365))
#define EXT_HEADERS_CLOSE \
__pragma(warning(pop))
#elif defined(__GNUC__)
#define EXT_HEADERS_OPEN \
_Pragma("GCC diagnostic push")\
_Pragma("GCC diagnostic ignored \"-Wzero-as-null-pointer-constant\"")\
_Pragma("GCC diagnostic ignored \"-Wconversion\"")\
_Pragma("GCC diagnostic ignored \"-Wsuggest-override\"")
#define EXT_HEADERS_CLOSE \
_Pragma("GCC diagnostic pop")
#else
#define EXT_HEADERS_OPEN
#define EXT_HEADERS_CLOSE
#endif


#endif //BASECONVERTER_EXT_HEADERS_H
