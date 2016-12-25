
//  Ingangar  #####################
const int GUPin = 2;
const int GDPin = 3;
const int NULLPin = 4;
const int WentInGear = 5;
const int WentBack = 6;

//  utgangar  #####################
const int GUOut = 7;
const int GDOut = 8;

// Breytur  #####################

int whatGear = 0; // Byrjar í Nautral
bool isChangingGear;
bool tooLongShift;
const int maxShiftTime = 500; // millisekúndur

//Föll  #####################
void shift_fail();
void shift_complete();
void shift_up();
void shift_down();



//####################    SETUP    ############################
void setup() {
  pinMode(GUPin, INPUT);
  pinMode(GDPin, INPUT);
  pinMode(NULLPin, INPUT);
  pinMode(WentInGear, INPUT);
  pinMode(WentBack, INPUT);

  pinMode(GUOut, OUTPUT);
  pinMode(GDOut, OUTPUT);

  // initialize serial communications:
  Serial.begin(9600);
  Serial.print("################     TeamSleipnir_Shifter_V1     ###################");
}

//####################   THE LOOP   ############################
void loop() {



  //Skipta upp? #####################
  if (digitalRead(GUPin) == HIGH && !isChangingGear) {
    //Er armurinn heima?
    if(digitalRead(WentBack)== HIGH)
    {
      void shift_up();  
    }
    else
    {
      // Some kind of error
      Serial.print("### ERROR: Gear not at home! ###");
    }
  }
  
  //Skipta niður? #####################
  if (digitalRead(GUPin) == HIGH && !isChangingGear) {
    //Er armurinn heima?
    if(digitalRead(WentBack)== HIGH)
    {
      void shift_down();  
    }
    else
    {
      // Some kind of error 
      Serial.print("### ERROR: Gear not at home! ###");
    }
  }
  
  /*Gear change sucessfull #####################
    if (isChangingGear && digitalRead(WentInGear) == HIGH) {
    shift_complete();
  }*/
  //Erum við að skipta?
  if(isChangingGear == true){
    // <-------------------------------------------Ræsa TIME fall hérna
    
    //Búinn að skipta?

    //JÁ!
    if(digitalRead(WentInGear)==HIGH){
      shift_complete();
    }
    //Nei!
    else{
      //Eitthvað sniðugt
      if(tooLongShift == true){
        shift_fail();
      }
    }
  }

/*
  Serial.print("Current gear: ");
  Serial.print(whatGear);
  Serial.println();
  Serial.print("GearUp: ");
  Serial.print(GUPin);
  Serial.println();

*/

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
  Serial.print(whatGear);
   //           <-------------------------------------------resetja TIME fall hérna
  return;
};

//Skipta upp
void shift_up()
{
  digitalWrite(GUOut, HIGH);
  isChangingGear = true;
  //Prenta
  Serial.print("INFO: Skipti upp");
  
  //$$$$$$$$$$$$$$Vantar timer fall hér!$$$$$$$$$$$$$$$$$$  
  
};

//Skipta niður
void shift_down()
{
  digitalWrite(GDOut, HIGH);
  isChangingGear = true;
  //Prenta
  Serial.print("INFO: Skipti nidur");
  
  //$$$$$$$$$$$$$$Vantar timer fall hér!$$$$$$$$$$$$$$$$$$  
  
};


