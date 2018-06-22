using UnityEngine;
using UnityEngine.Profiling;
using System.Collections;

namespace NativeTextureLoader 
{

public class LoadTextureSync : MonoBehaviour
{
    [SerializeField]
    string path = "hecomi.png";

    IEnumerator Start()
    {
    	var material = GetComponent<Renderer>().material;

        var url = System.IO.Path.Combine(Application.streamingAssetsPath, path);
#if UNITY_EDITOR
        url = "file://" + url;
#endif

        using (var www = new WWW(url)) 
        {
            yield return www;
    		Profiler.BeginSample("Decode Texture (Sync)");
    		{
    			material.mainTexture = www.texture;
    		}
    		Profiler.EndSample();
        }
    }
}

}