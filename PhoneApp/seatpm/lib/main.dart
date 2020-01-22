import 'package:flutter/material.dart';
import 'parameter.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  final Parameter minAngle = new Parameter('Minimum Angle');
  final Parameter maxAngle = new Parameter('Maximum Angle');
  final Parameter speed = new Parameter('Speed');

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
        title: 'SeatPM',
        theme: ThemeData(
          primarySwatch: Colors.blue,
        ),
        home: Scaffold(
          // ====================================================================
          // Title
          // ====================================================================
          appBar: AppBar(
            title: Text('SeatPM'),
          ),

          body: Column(
            children: <Widget>[
              // ==============================================================
              // Bluetooth info
              // ==============================================================

              // ==============================================================
              // Parameters
              // ==============================================================
              minAngle.widget,
              maxAngle.widget,
              speed.widget,

              // ==============================================================
              // On/Off Button
              // ==============================================================
            ],
          ),
        )
      );
  }
}
