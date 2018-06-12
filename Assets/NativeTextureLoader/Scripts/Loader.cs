using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;

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
		var url = "file://" + System.IO.Path.Combine(Application.streamingAssetsPath, path);

        using (var www = new WWW(url)) 
		{
			yield return www;
			if (string.IsNullOrEmpty(www.error))
			{
				yield return OnDataLoaded(www.bytes);
			}
			else
			{
				Debug.LogError(www.error);
			}
        }
	}

	IEnumerator OnDataLoaded(byte[] data)
	{
		GCHandle handle = GCHandle.Alloc(data, GCHandleType.Pinned);
		var pointer = handle.AddrOfPinnedObject();

		loader_ = Lib.CreateLoader();
		Lib.SetData(loader_, pointer, data.Length);

		handle.Free();

		Lib.Load(loader_); // 非同期にする

		var width = Lib.GetWidth(loader_);
		var height = Lib.GetHeight(loader_);

		Debug.Log(width);

		texture_ = new Texture2D(width, height, TextureFormat.RGBA32, false);
		Lib.SetTexture(loader_, texture_.GetNativeTexturePtr());
		Lib.UpdateTexture(loader_);

		var renderer = GetComponent<Renderer>();
		renderer.material.mainTexture = texture_;

		Lib.UpdateTextureImmediate(loader_);

		yield return new WaitForEndOfFrame();
		//GL.IssuePluginEvent(Lib.GetRenderEventFunc(), 0);
	}
}

}