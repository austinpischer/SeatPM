import 'parameter_model.dart';
import 'parameter_widget.dart';

class Parameter {
  // Properities
  String name;
  ParameterModel model;
  ParameterWidget widget;

  // Constructor
  Parameter(String parameterName) {
    name = parameterName;
    model = ParameterModel();
    widget = new ParameterWidget(name, model);
  }
}
