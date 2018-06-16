using UnityEngine;
using UnityEngine.Networking;
using System.Collections;
using System.Runtime.InteropServices;
using System.Threading.Tasks;

namespace NativeTextureLoader
{

public class Loader : MonoBehaviour
{
    [SerializeField]
    string path = "hecomi.png";

    System.IntPtr loader_;
    Texture2D texture_ ;

    void Start()
    {
        StartCoroutine(LoadImage());
    }

    void OnDestroy()
    {
        if (loader_ != System.IntPtr.Zero)
        {
            Lib.DestroyLoader(loader_);
        }
    }

    IEnumerator LoadImage()
    {
        var url = System.IO.Path.Combine(Application.streamingAssetsPath, path);
#if UNITY_EDITOR
        url = "file://" + url;
#endif

        var req = UnityWebRequest.Get(url);
        yield return req.SendWebRequest();

        if (req.isDone)
        {
            OnDataLoaded(req.downloadHandler.data);
        }
        else
        {
            Debug.LogError(req.error);
        }
    }

    async void OnDataLoaded(byte[] data)
    {
        var handle = GCHandle.Alloc(data, GCHandleType.Pinned);
        var pointer = handle.AddrOfPinnedObject();
        await Task.Run(() => 
        {
            loader_ = Lib.CreateLoader();
            Lib.Load(loader_, pointer, data.Length);
        });
        handle.Free();

        var width = Lib.GetWidth(loader_);
        var height = Lib.GetHeight(loader_);
        texture_ = new Texture2D(width, height, TextureFormat.RGBA32, false);
        Lib.SetTexture(loader_, texture_.GetNativeTexturePtr());
        Lib.UpdateTexture(loader_);

        var renderer = GetComponent<Renderer>();
        renderer.material.mainTexture = texture_;

        StartCoroutine(IssuePluginEvent());
    }

    IEnumerator IssuePluginEvent()
    {
        yield return new WaitForEndOfFrame();
        GL.IssuePluginEvent(Lib.GetRenderEventFunc(), 0);
    }
}

}