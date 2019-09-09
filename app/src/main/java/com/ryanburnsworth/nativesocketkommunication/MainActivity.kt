package com.ryanburnsworth.nativesocketkommunication

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import kotlinx.android.synthetic.main.activity_main.*
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch

class MainActivity : AppCompatActivity() {

    external fun init(hostname: String, port: Int): Int
    external fun sendData(sock: Int, data: String): Int
    external fun recvData(sock: Int): String
    external fun disconnect(sock: Int)

    private var sock = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

    }

    override fun onResume() {
        super.onResume()
        GlobalScope.launch {
            var incomingData = ""

            sock = init("10.0.0.14", 9090)

            sendData(sock, "Hello Server!")

            while (incomingData == "") {
                incomingData = recvData(sock)
                Log.e("DATA", "Incoming: $incomingData")
            }

            disconnect(sock)
        }
    }

    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }
}
