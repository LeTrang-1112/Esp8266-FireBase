import 'package:flutter/material.dart';
import 'package:firebase_database/firebase_database.dart';

class IoTControlScreen extends StatefulWidget {
  @override
  _IoTControlScreenState createState() => _IoTControlScreenState();
}

class _IoTControlScreenState extends State<IoTControlScreen> {
  bool isLedOn = false;
  bool isBuzzerOn = false;
  double ledBrightness = 50.0;

  final DatabaseReference database = FirebaseDatabase.instance.ref();

  @override
  void initState() {
    super.initState();
    database.child('LedOn').onValue.listen((event) {
      setState(() {
        isLedOn = event.snapshot.value == true;
      });
    });

    database.child('BuzOn').onValue.listen((event) {
      setState(() {
        isBuzzerOn = event.snapshot.value == true;
      });
    });

    database.child('LedBrightness').onValue.listen((event) {
      setState(() {
        ledBrightness = double.tryParse(event.snapshot.value.toString()) ?? 0.0;
      });
    });
  }

  void updateFirebase() {
    database.update({
      'LedOn': isLedOn,
      'LedBrightness': ledBrightness.round(),
      'BuzOn': isBuzzerOn,
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('IoT LED & Buzzer Control'),
        backgroundColor: Colors.deepPurple,
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: [
                Text(
                  'LED On/Off',
                  style: TextStyle(fontSize: 18),
                ),
                Switch(
                  value: isLedOn,
                  onChanged: (value) {
                    setState(() {
                      isLedOn = value;
                      updateFirebase();
                    });
                  },
                  activeColor: Colors.deepPurple,
                ),
              ],
            ),
            SizedBox(height: 16),
            Text(
              'LED Brightness',
              style: TextStyle(fontSize: 18),
            ),
            Slider(
              value: ledBrightness,
              min: 0,
              max: 255,
              divisions: 100,
              label: '${ledBrightness.round()}%',
              activeColor: Colors.deepPurple,
              onChanged: isLedOn
                  ? (value) {
                      setState(() {
                        ledBrightness = value;
                        updateFirebase(); // Cập nhật Firebase
                      });
                    }
                  : null,
            ),
            SizedBox(height: 16),
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: [
                Text(
                  'Buzzer On/Off',
                  style: TextStyle(fontSize: 18),
                ),
                Switch(
                  value: isBuzzerOn,
                  onChanged: (value) {
                    setState(() {
                      isBuzzerOn = value;
                      updateFirebase();
                    });
                  },
                  activeColor: Colors.deepPurple,
                ),
              ],
            ),
            SizedBox(height: 32),
            Container(
              padding: EdgeInsets.all(16),
              decoration: BoxDecoration(
                color: Colors.grey[200],
                borderRadius: BorderRadius.circular(8),
              ),
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Text(
                    'Control Data:',
                    style: TextStyle(fontSize: 16, fontWeight: FontWeight.bold),
                  ),
                  SizedBox(height: 8),
                  Text('LED On: ${isLedOn ? "Yes" : "No"}'),
                  Text('LED Brightness: ${ledBrightness.round()}%'),
                  Text('Buzzer On: ${isBuzzerOn ? "Yes" : "No"}'),
                ],
              ),
            ),
          ],
        ),
      ),
    );
  }
}
