using System;
using System.Runtime.InteropServices;

namespace NativeTextureLoader
{

public static class Lib
{
    const string pluginName = "NativeTextureLoader";

    [DllImport(pluginName)]
    public static extern IntPtr CreateLoader();

    [DllImport(pluginName)]
    public static extern void DestroyLoader(IntPtr loader);

    [DllImport(pluginName)]
    public static extern void Load(IntPtr loader, IntPtr data, int size);

    [DllImport(pluginName)]
    public static extern void SetTexture(IntPtr loader, IntPtr texture);

    [DllImport(pluginName)]
    public static extern void UpdateTexture(IntPtr loader);

    [DllImport(pluginName)]
    public static extern void UpdateTextureImmediate(IntPtr loader);

    [DllImport(pluginName)]
    public static extern int GetWidth(IntPtr loader);

    [DllImport(pluginName)]
    public static extern int GetHeight(IntPtr loader);

    [DllImport(pluginName)]
    public static extern IntPtr GetRenderEventFunc();
}

}