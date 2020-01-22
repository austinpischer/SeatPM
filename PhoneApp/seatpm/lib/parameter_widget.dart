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
import 'parameter_model.dart';

class ParameterWidget extends StatelessWidget {
  final String name;
  final ParameterModel model;

  ParameterWidget(this.name, this.model);

  @override
  Widget build(BuildContext context) {
    return Row(
      children: <Widget>[
        //=====================================================================
        // Down Button
        //=====================================================================
        Expanded(
          child: RaisedButton(
            onPressed: () {
              model.setValue(model.getValue() - 1);
            }, // TODO
            onLongPress: () {}, // TODO
            child: Text(name + ' Down'),
          ),
        ),

        //=====================================================================
        // Value Display
        //=====================================================================
        Expanded(
          child: ValueDisplay(name, model),
        ),

        //=====================================================================
        // Up Button
        //=====================================================================
        Expanded(
          child: RaisedButton(
            onPressed: () {
              model.setValue(model.getValue() + 1);
            }, // TODO
            onLongPress: () {}, // TODO
            child: Text(name + ' Up'),
          ),
        ),
      ],
    );
  }
}

class ValueDisplay extends StatefulWidget {
  final String name;
  final ParameterModel model;

  ValueDisplay(this.name, this.model);

  @override
  ValueDisplayState createState() => ValueDisplayState();
}

class ValueDisplayState extends State<ValueDisplay> {
  @override
  Widget build(BuildContext context) {
    return Text(widget.name + ' value: ' + widget.model.getValue().toString());
  }
}
