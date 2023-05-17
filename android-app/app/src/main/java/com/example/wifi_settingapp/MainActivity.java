package com.example.wifi_settingapp;

import static com.example.wifi_settingapp.CommonVal.btArrayAdapter;
import static com.example.wifi_settingapp.CommonVal.deviceAddressArray;
import static com.example.wifi_settingapp.CommonVal.pairedDevices;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.os.Bundle;
import android.Manifest;
import android.view.View;
import android.widget.ArrayAdapter;

import com.example.wifi_settingapp.databinding.ActivityMainBinding;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    ActivityMainBinding binding;
    BluetoothAdapter btAdapter;
    private final static int REQUEST_ENABLE_BT = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding=ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
    }

    @Override
    protected void onStart() {
        super.onStart();

        String[] permission_list = {
                Manifest.permission.ACCESS_FINE_LOCATION,
                Manifest.permission.ACCESS_COARSE_LOCATION
        };
        ActivityCompat.requestPermissions(MainActivity.this, permission_list,  1);

        btAdapter = BluetoothAdapter.getDefaultAdapter();
        if (!btAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        }

        btArrayAdapter = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1);
        deviceAddressArray = new ArrayList<>();
        binding.listview.setAdapter(btArrayAdapter);
    }

    public void onClickButtonPaired(View view) {
        btArrayAdapter.clear();
        if (deviceAddressArray!=null&&!deviceAddressArray.isEmpty()){
            deviceAddressArray.clear();
        }
        if (pairedDevices.size()>0){

        }
    }
}