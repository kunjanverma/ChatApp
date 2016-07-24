#include <exception>
#include <string>

#ifndef UTIL_EXCEPTION
#define UTIL_EXCEPTION

namespace ServerUtils
{

class Exception:public std::exception
{
    std::string m_reason;

    public:
        Exception(std::string reason):std::exception(),
                                    m_reason(reason)
        {
        }

        const char* what() const noexcept
        {
            return m_reason.c_str();
        }
};

}
#endif
