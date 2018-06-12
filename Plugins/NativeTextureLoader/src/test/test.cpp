#include <cstdio>
#include "../png_loader.h"
#include "../util.h"

using namespace NativeImageLoader;


int main()
{
    constexpr const char *name = "hecomi.png";

    auto *fp = fopen(name, "rb");
    if (!fp)
    {
        fprintf(stderr, "Unable to open file %s", name);
        return -1;
    }

    ScopeReleaser releaser([&] { fclose(fp); });

    fseek(fp, 0, SEEK_END);
    const int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    auto buffer = std::make_unique<unsigned char[]>(size + 1);
    fread(buffer.get(), size, 1, fp);

    PngLoader loader(buffer.get(), size);

    return 0;
}
