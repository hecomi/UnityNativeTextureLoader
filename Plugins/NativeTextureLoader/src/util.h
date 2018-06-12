#include <functional>

namespace NativeImageLoader
{

class ScopeReleaser
{
public:
    using Func = std::function<void()>;
    ScopeReleaser(const Func &func) : m_func(func) {}
    ~ScopeReleaser() { if (m_func) m_func(); }

private:
    Func m_func;
};

}
