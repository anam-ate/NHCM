class Button
{
  private:
    bool _state;
    uint8_t _pin;
    int _counter;

  public:
    Button(uint8_t pin) : _pin(pin) {}

    void begin() {
      pinMode(_pin, INPUT_PULLUP);
      _state = digitalRead(_pin);
      _counter = 0;
    }

    bool isReleased() {
      bool v = digitalRead(_pin);
      if (v != _state) {
        _state = v;
        if (_state) {
          return true;
        }
      }
      return false;
    }

    bool isPushed() {
      bool v = digitalRead(_pin);
      if (v != _state)
      {
        _counter++;
      }
      else
      {
        _counter = 0;
      }
      if (_counter >= 50)
      {
        _counter = 0;
        if (v != _state)
        {
          _state = v;
          if (_state == false)
          {
            return true;
          }
        }
      }
      return false;
    }
};
