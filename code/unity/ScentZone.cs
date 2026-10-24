using UnityEngine;

// Myrodia - scent zone
//
// Put this on an invisible trigger box that covers one environment:
//   1. GameObject > 3D Object > Cube, then move and scale it to cover the environment.
//   2. Untick its Mesh Renderer so it is invisible.
//   3. On its Box Collider, tick "Is Trigger".
//   4. Add this script and set Scent: 1 = Forest, 2 = Bakery, 3 = Beach, 4 = Christmas.
//
// The player character must have the tag "Player" (check the Tag box at the top of its Inspector).
//
// Written after the project (October 2026, with AI help) to show how the
// game-to-device link described in the report works.
public class ScentZone : MonoBehaviour
{
    [Range(1, 4)]
    public int scent = 1;

    public string playerTag = "Player";

    void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag(playerTag) && ScentSender.Instance != null)
        {
            ScentSender.Instance.EnterZone(scent);
        }
    }

    void OnTriggerExit(Collider other)
    {
        if (other.CompareTag(playerTag) && ScentSender.Instance != null)
        {
            ScentSender.Instance.ExitZone(scent);
        }
    }
}
