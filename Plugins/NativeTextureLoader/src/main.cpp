#include <queue>
#include "png_loader.h"

using namespace NativeImageLoader;
using UnityRenderEvent = void(*)(int);

std::queue<PngLoader*> g_updateQueue;


extern "C"
{

void * CreateLoader()
{
    return new PngLoader();
}

void DestroyLoader(PngLoader *pPngLoader)
{
    if (pPngLoader == nullptr) return;
    delete pPngLoader;
}

void SetData(PngLoader *pPngLoader, const void *pData, size_t dataSize)
{
    if (pPngLoader == nullptr || pData == nullptr) return;
    pPngLoader->SetData(pData, dataSize);
}

void Load(PngLoader *pPngLoader)
{
    if (pPngLoader == nullptr) return;
    pPngLoader->Load();
}

void SetTexture(PngLoader *pPngLoader, GLuint texture)
{
    if (pPngLoader == nullptr) return;
    pPngLoader->SetTexture(texture);
}

void UpdateTexture(PngLoader *pPngLoader)
{
    if (pPngLoader == nullptr) return;
    g_updateQueue.push(pPngLoader);
}
    
void UpdateTextureImmediate(PngLoader *pPngLoader)
{
    if (pPngLoader == nullptr) return;
    pPngLoader->UpdateTexture();
}

int GetWidth(PngLoader *pPngLoader)
{
    if (pPngLoader == nullptr) return 0;
    return pPngLoader->GetWidth();
}

int GetHeight(PngLoader *pPngLoader)
{
    if (pPngLoader == nullptr) return 0;
    return pPngLoader->GetHeight();
}

void OnRenderEvent(int eventId)
{
    while (!g_updateQueue.empty())
    {
        g_updateQueue.front()->UpdateTexture();
        g_updateQueue.pop();
    }
}

UnityRenderEvent GetRenderEventFunc()
{
    return OnRenderEvent;
}

}
