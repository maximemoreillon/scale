void display_setup() {
  display.init();
  display.flipScreenVertically();
  display.clear();
  display.display();
}

void display_nothing(){
  display.clear();
  display.display();
}
void display_weight() {

  static float last_weight;

  if(weight != last_weight){
    last_weight = weight;
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(Roboto_48);
    display.drawString(DISPLAY_WIDTH / 2, 0, get_weight_string(weight));
    display.display();
  }
}

void display_blinking_weight() {

  const int blinking_delay = 250;
  
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(Roboto_48);
  
  for(int i=0; i<3; i++){
    display.clear();
    display.drawString(DISPLAY_WIDTH / 2, 0, get_weight_string(weight));
    display.display();
    delay(blinking_delay);
    display.clear();
    display.display();
    delay(blinking_delay);
  }
}

void display_uploading(){
  display.clear();
  display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, uploading_image);
  display.display();
}

void display_upload_success(){

  const int blinking_delay = 500;
  
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(Roboto_48);
  
  for(int i=0; i<10; i++){
    display.clear();
    display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, uploaded_image);
    display.display();
    delay(blinking_delay);
    display.clear();
    display.drawString(DISPLAY_WIDTH / 2, 0, get_weight_string(weight));
    display.display();
    delay(blinking_delay);
  }

  display.clear();
  display.display();
}

void display_upload_fail(){

  const int blinking_delay = 500;
  
  for(int i=0; i<10; i++){
    display.clear();
    display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, upload_fail);
    display.display();
    delay(blinking_delay);
    display.clear();
    display.display();
    delay(blinking_delay);
  }
}


void display_connecting(){

  long now = millis();
  static long last_change;
  const long change_period = 200;
  static int frame = 0;
  
  if(now-last_change > change_period){
    last_change = now;
    frame++;
    if(frame > 3){
      frame = 0;
    }
  }

  display.clear();
  if(frame == 0) display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, connecting_bar_1_2_3_off);
  else if(frame == 1) display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, connecting_bar_2_3_off);
  else if(frame == 2) display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, connecting_bar_3_off);
  else if(frame == 3) display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, connecting_full);
  display.display();
  
}


void display_connected(){
  display.clear();
  display.drawXbm(0,0, IMAGES_WIDTH, IMAGES_HEIGHT, wifi_ok);
  display.display();
  delay(2000);
  display.clear();
  display.display();
}


