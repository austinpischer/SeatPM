class ParameterModel {
  //===========================================================================
  // Fields
  double _value;
  double _minValue;
  double _maxValue;

  //===========================================================================
  // Default Constructor
  Parameter() {
    _value = 0;
    _minValue = 0;
    _maxValue = 0;
  }

  //===========================================================================
  // Get and Set functions for each field, where Set performs error checking:
  // Set functions return false if passed value is invalid,
  // otherwise returns true.
  double getMinValue() {
    return _minValue;
  }

  bool setMinValue(double newMinimum) {
    // Min should not exceed max
    if (newMinimum > _maxValue) {
      return false;
    }
    // Questionable program behavior here
    // Check that current parameter value falls within new range
    if (_value < newMinimum) {
      return false;
    }
    // New minimum has passed all checks past this point
    _minValue = newMinimum;
    return true;
  }

  double getMaxValue() {
    return _maxValue;
  }

  bool setMaxValue(double newMaximum) {
    // Max should not be less than min
    if (newMaximum < _minValue) {
      return false;
    }
    // Questionable program behavior here
    // Check that current parameter value falls within new range
    if (_value > newMaximum) {
      return false;
    }
    // New minimum has passed all checks past this point
    _maxValue = newMaximum;
    return true;
  }

  double getValue() {
    return _value;
  }

  bool setValue(double newValue) {
    if (newValue < _minValue || newValue > _maxValue) {
      return false;
    }
    _value = newValue;
  }
}
