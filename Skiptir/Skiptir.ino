
//  Ingangar  #####################
const int GUPin = 2;
const int GDPin = 3;
const int NULLPin = 4;
const int outputA = 5;
const int outputB = 6;

//  utgangar  #####################
const int GUOut = 7;
const int GDOut = 8;

// Breytur  #####################

int whatGear = 0; // Byrjar í Nautral
bool isChangingGear = false;
bool tooLongShift = false;
bool goHome = false;
int const goHomeMaxTime = 1000; //millisekúndur

const int maxShiftTime = 500; // millisekúndur

//Föll  #####################
void shift_fail();
void shift_complete();
void shift_up();
void shift_down();
void reset_Gears();
void go_Home();

//Rotary Counter ###############
 int counter = 0; 
 int aState;
 int aLastState;  
 
 const int counterHome = 0;
 const int counterSafePos = 50;
 const int counterGearUp = 100;
 const int counterGearDown = -100;


//####################    SETUP    ############################
void setup() {
  pinMode(GUPin, INPUT);
  pinMode(GDPin, INPUT);
  pinMode(NULLPin, INPUT);
  
  pinMode(GUOut, OUTPUT);
  pinMode(GDOut, OUTPUT);

  // initialize serial communications:
  Serial.begin(9600);
  Serial.print("################     TeamSleipnir_Shifter_V1     ###################");

  //Rotary encoder
  aLastState = digitalRead(outputA);   
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);
}

//####################   THE LOOP   ############################
void loop() {
  
  //Rotary encoder #####################
  aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
  if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
    if (digitalRead(outputB) != aState) { 
      counter ++;
    } else {
      counter --;
    }
    
    //Serial.print("Position: ");
    //Serial.println(counter);
  } 
  aLastState = aState;
  

  //Skipta upp? #####################
  if (digitalRead(GUPin) == HIGH && !isChangingGear) {
    //Er armurinn heima? innan við marka?
    // counterHome+conterSafePos > counter > counterHome-counterSafePos
    if(counter < (counterHome+counterSafePos) && counter > (counterHome-counterSafePos))
    {
      void shift_up();  
    }
    else
    {
      Serial.println("### ERROR: Gear not at home! ###");
      go_Home();
    }
  }
  
  //Skipta niður? #####################
  if (digitalRead(GDPin) == HIGH && !isChangingGear) {
    //Er armurinn heima? innan við marka?
    // counterHome+conterSafePos > counter > counterHome-counterSafePos
    if(counter < (counterHome+counterSafePos) && counter > (counterHome-counterSafePos))
    {
      void shift_down();  
    }
    else
    {
      // Some kind of error 
      Serial.println("### ERROR: Gear not at home! ###");
      go_Home();
    }
  }
  
  /*Gear change sucessfull #####################
    if (isChangingGear && digitalRead(WentInGear) == HIGH) {
    shift_complete();
  }*/
  //Erum við að skipta?
  if(isChangingGear == true){
    
    
    //Búinn að skipta?

    //JÁ!
    if(counter > (counterGearUp)){
      shift_complete();
    }
    else if(counter < counterGearDown){
      shift_complete();
    }
    
    //Nei!
    else{
      //Eitthvað sniðugt <-------------------------------------------Ræsa TIME fall hérna
      if(tooLongShift == true){
        shift_fail();
      }
    }
  }

  if(digitalRead(GUPin) == HIGH && digitalRead(GDPin) == HIGH){
    reset_Gears();
  }
  //Reynir að fara aftur í heima punkt
  if(goHome){go_Home();}
  

}
//##########################     FÖLL     ##############################
//Skipting mistókst
void shift_fail()
{
  //Endursetja
  isChangingGear = false;
  digitalWrite(GUOut,LOW);
  digitalWrite(GDOut,LOW);
  //Prenta
  Serial.println("### ERROR: Gear failed to shift! ###");
  //<-------------------------------------------resetja TIME fall hérna
};

//Skipting tókst
void shift_complete()
{ 
   
  //Hækka um gýr númer
  if (GDOut == HIGH) { whatGear--; };
  if (GUOut == HIGH) { whatGear++; };
  //Endursetja
  isChangingGear = false; 
  digitalWrite(GDOut, LOW);
  digitalWrite(GUOut, LOW);
  //Prenta
  Serial.print("INFO: Current gear: ");
  Serial.println(whatGear);
   //           <-------------------------------------------resetja TIME fall hérna
  return;
};

//Skipta upp
void shift_up()
{
  digitalWrite(GUOut, HIGH);
  isChangingGear = true;
  //Prenta
  Serial.println("INFO: Skipti upp");
  
    
};

//Skipta niður
void shift_down()
{
  digitalWrite(GDOut, HIGH);
  isChangingGear = true;
  //Prenta
  Serial.println("INFO: Skipti nidur");
 
  
};

//Endursetja allt
void reset_Gears(){
  isChangingGear = false;
  tooLongShift = false;
  
  //Ef stönginn er ekki heima
  if(counter < (counterHome+counterSafePos) && counter > (counterHome-counterSafePos)){
    Serial.println("### ERROR: Gear not home! ###");
    go_Home();
  }
  else{
    digitalWrite(GDOut, LOW);
    digitalWrite(GUOut, LOW);
  }
 
  whatGear = 0; // <-------------------------- Spurning með þetta
  Serial.println("INFO: SYSTEM RESTARTED");
};
//Reynir að fara sjálfur aftur í heimastöðu ef hann festist
void go_Home(){//<------------------------- Vantar hérna að ef hann er of lengi að reyna þá endursetur það sig goHome = false
  goHome = true;
  if(counter > (counterHome+counterSafePos)){
    Serial.println("INFO: Trying to move down...");
    digitalWrite(GUOut, LOW);
    digitalWrite(GDOut, HIGH);
  }
  else if(counter < (counterHome-counterSafePos)){
    Serial.println("INFO: Trying to move up...");
    digitalWrite(GDOut, LOW);
    digitalWrite(GUOut, HIGH);
  }
  if(counter < (counterHome+counterSafePos) && counter > (counterHome-counterSafePos)){
    digitalWrite(GDOut, LOW);
    digitalWrite(GUOut, LOW);
    Serial.println("INFO: GEAR IS HOME!");
    goHome = false;
  }
  
};

