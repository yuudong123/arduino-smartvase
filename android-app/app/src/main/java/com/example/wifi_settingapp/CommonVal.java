package com.example.wifi_settingapp;

import android.bluetooth.BluetoothDevice;
import android.widget.ArrayAdapter;

import java.util.ArrayList;
import java.util.Set;

public class CommonVal {
    public static Set<BluetoothDevice> pairedDevices;
    public static ArrayAdapter<String> btArrayAdapter;
    public static ArrayList<String> deviceAddressArray;
}
