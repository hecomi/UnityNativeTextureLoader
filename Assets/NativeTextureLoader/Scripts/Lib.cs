using UnityEngine;
using System;
using System.Runtime.InteropServices;

namespace NativeTextureLoader
{

public static class Lib
{
    [DllImport("NativeTextureLoader")]
    public static extern IntPtr CreateLoader();

    [DllImport("NativeTextureLoader")]
    public static extern void DestroyLoader(IntPtr loader);

    [DllImport("NativeTextureLoader")]
    public static extern void SetData(IntPtr loader, IntPtr data, int size);

    [DllImport("NativeTextureLoader")]
    public static extern void Load(IntPtr loader);

    [DllImport("NativeTextureLoader")]
    public static extern void SetTexture(IntPtr loader, IntPtr texture);

    [DllImport("NativeTextureLoader")]
    public static extern void UpdateTexture(IntPtr loader);

    [DllImport("NativeTextureLoader")]
    public static extern void UpdateTextureImmediate(IntPtr loader);

    [DllImport("NativeTextureLoader")]
    public static extern int GetWidth(IntPtr loader);

    [DllImport("NativeTextureLoader")]
    public static extern int GetHeight(IntPtr loader);

    [DllImport("NativeTextureLoader")]
    public static extern IntPtr GetRenderEventFunc();
}

}