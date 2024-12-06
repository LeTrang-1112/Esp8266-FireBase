import 'package:esp8266/IoTControlScreen.dart';
import 'package:flutter/material.dart';
import 'package:firebase_core/firebase_core.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp(
    options: const FirebaseOptions(
      apiKey: "AIzaSyBVibgpC1wxhkHz9gJrM60Bkzosfw-Jry0",
      appId: "1:22168065282:android:37b537936d79ee48f11e1b",
      messagingSenderId: "22168065282",
      projectId: "ltnhung-4e40f",
      databaseURL:
          "https://ltnhung-4e40f-default-rtdb.asia-southeast1.firebasedatabase.app",
      storageBucket: "ltnhung.firebasestorage.app",
    ),
  );

  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'IoT Control',
      home: IoTControlScreen(),
    );
  }
}
