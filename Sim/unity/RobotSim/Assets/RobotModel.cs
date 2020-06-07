using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System;

public class RobotModel : MonoBehaviour
{
    public GameObject Frame1;
    public GameObject Frame2;
    public GameObject Frame3;

    public double[] Qs = new double[3];
    public float[] thetas = new float[3];

    public double[] Taus = new double[3];
    // Start is called before the first frame update
    void Start()
    {
        start();
    }

    // Update is called once per frame
    void Update()
    {
        get_Q(Qs);
        for (int i = 0; i < 3; i++){
            thetas[i] = (float)(Mathf.Rad2Deg*Qs[i]);
        }

        Frame1.transform.localEulerAngles = new Vector3(0.0f,-thetas[0],0.0f);
        Frame2.transform.localEulerAngles = new Vector3(0.0f,0.0f,thetas[1]);
        Frame3.transform.localEulerAngles = new Vector3(0.0f,0.0f,thetas[2]);

        set_Tau(Taus);
    }

    private void OnApplicationQuit() {
        stop();
    }

    [DllImport("robot_sim")]
    public static extern void start();
    
    [DllImport("robot_sim")]
    public static extern void stop();
    
    [DllImport("robot_sim")]
    public static extern void get_Q(double[] Qs); 

    [DllImport("robot_sim")]
    public static extern void set_Tau(double[] Tau);
}
