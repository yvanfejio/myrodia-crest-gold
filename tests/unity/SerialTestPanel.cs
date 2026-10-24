using UnityEngine;

// Test 6 (Unity side): send commands to the Arduino with on-screen buttons,
// without walking the character around the map.
//
// Add this to the same GameObject as ScentSender, press Play, and click the
// buttons in the top-left corner of the Game view.
//
// Written after the project (October 2026, with AI help) to document this test.
public class SerialTestPanel : MonoBehaviour
{
    readonly string[] labels = { "0  All off", "1  Forest", "2  Bakery", "3  Beach", "4  Christmas" };

    void OnGUI()
    {
        GUILayout.BeginArea(new Rect(10, 10, 160, 220));
        GUILayout.Label("Myrodia serial test");

        for (int i = 0; i < labels.Length; i++)
        {
            if (GUILayout.Button(labels[i]) && ScentSender.Instance != null)
            {
                ScentSender.Instance.Send(i.ToString());
            }
        }

        GUILayout.EndArea();
    }
}
