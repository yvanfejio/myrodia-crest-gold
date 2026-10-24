using System;
using System.IO.Ports;
using UnityEngine;

// Myrodia - sender (Unity side)
//
// Opens the USB serial port to the Arduino and sends it one-character commands:
//   "1" to "4" = turn on that scent, "0" = turn everything off.
//
// Setup:
//   1. Make an empty GameObject called "Myrodia" and add this script to it.
//   2. Set Port Name to the Arduino's port (Arduino IDE > Tools > Port, e.g. COM3).
//   3. Edit > Project Settings > Player > Other Settings > Api Compatibility Level
//      must be ".NET Framework", because System.IO.Ports is not in .NET Standard.
//
// Written after the project (October 2026, with AI help) to show how the
// game-to-device link described in the report works.
public class ScentSender : MonoBehaviour
{
    public static ScentSender Instance { get; private set; }

    [Tooltip("The Arduino's port. Find it in the Arduino IDE under Tools > Port, e.g. COM3.")]
    public string portName = "COM3";

    [Tooltip("Must match Serial.begin() in the Arduino sketch.")]
    public int baudRate = 9600;

    SerialPort port;
    int currentScent = 0;  // 0 = no scent playing

    void Awake()
    {
        Instance = this;

        port = new SerialPort(portName, baudRate);
        port.WriteTimeout = 100;
        try
        {
            port.Open();
            Debug.Log("Myrodia: connected on " + portName);
        }
        catch (Exception e)
        {
            Debug.LogWarning("Myrodia: could not open " + portName + " (" + e.Message +
                             "). Is the Arduino plugged in and the Serial Monitor closed?");
        }
    }

    // Called by ScentZone when the player walks into an environment
    public void EnterZone(int scent)
    {
        currentScent = scent;
        Send(scent.ToString());
    }

    // Called by ScentZone when the player walks out of an environment
    public void ExitZone(int scent)
    {
        // If the player has already walked into the next zone, leave that scent on
        if (scent != currentScent) return;

        currentScent = 0;
        Send("0");
    }

    public void Send(string command)
    {
        if (port == null || !port.IsOpen) return;

        try
        {
            port.Write(command);
        }
        catch (Exception e)
        {
            Debug.LogWarning("Myrodia: send failed (" + e.Message + ")");
        }
    }

    // Emergency stop: turn every atomizer off when the game stops or closes
    void OnApplicationQuit()
    {
        Send("0");
        if (port != null && port.IsOpen) port.Close();
    }
}
