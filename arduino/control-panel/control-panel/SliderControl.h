
class SliderControl {
private:

  int sliderPin;
  bool pressed = false;
  int reversingPin;
  bool forward = true;

public:
  SliderControl(int sliderPin, int reversingPin);

  void reverseDirection();
  void init();
  void update();
  void setDirection(bool fwd);
  int getSlider();
  bool getForward();
};
