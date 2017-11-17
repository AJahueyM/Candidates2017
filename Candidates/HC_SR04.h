class HC_SR04{
  
  private:
    long distance;
    int pinTrigger, pinEcho;
    
  public:
    long getDistance();
    HC_SR04(int pinTrigger, int pinEcho);
  
};
