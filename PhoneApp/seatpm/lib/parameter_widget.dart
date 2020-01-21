/*
  The SeatPM device has three user-controlled parameters:
  1) Minimum knee angle
  2) Maximum knee angle
  3) Speed of the device

  Each of these is controlled by this same widget format.
  On the left and right sides of the widget there shall be
  a "parameter down" and "parameter up" button, respectively.
  Inbetween those two buttons, the parameter's value shall be displayed.
*/

import 'package:flutter/material.dart';
import 'parameter.dart';

class ParameterWidget {
  String name;
  Parameter myParameter;
  Row parameterControls;

  ParameterWidget(String parameterName)
  {
    name = parameterName;
    parameterControls = _makeParameterControls(name);
  }

  Row _makeParameterControls(parameterName) {
  return Row (
    children: <Widget>[
      // *********** Parameter DOWN button on the left ***********
      Expanded( 
        child: RaisedButton(
          onPressed: () {}, // TODO
          onLongPress: () {}, // TODO
          child: Text(
             parameterName + 'Down'
            ),
          ),
        ),

      // *********** Parameter VALUE display ***********
      Expanded(
        child: ValueDisplay( )
          
        ),
      ),

      // *********** Parameter UP button on the right ***********
      Expanded(
        child: RaisedButton(
          onPressed: () {}, // TODO
          onLongPress: () {}, // TODO
          child: Text(
             parameterName + 'Up'
            ),
          ),
       ),

    ],
  );
  }
}

class ValueDisplay extends StatefulWidget {
  final String parName;
  final String parValue;

  const ValueDisplay(this.parName, this.parValue);

  @override
  _ValueDisplayState createState() => _ValueDisplayState();
}

class _ValueDisplayState extends State<ValueDisplay> {
  @override 
  Widget build(BuildContext context) {
    return Text(widget.parName + ' value: ' + widget.parValue);
  }
}