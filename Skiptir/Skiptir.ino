
//  Ingangar  #####################
const int GUPin = 2;
const int GDPin = 3;
const int NULLPin = 4;
const int WentInGear = 5;
const int WentBack = 6;
//  �tgangar  #####################
const int GUOut = 7;
const int GDOut = 8;

// Breytur  #####################

int whatGear = 0;
bool isChangingGear;

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
}

//####################   THE LOOP   ############################
void loop() {



  //Change Gear upp #####################
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
  
  //Change gear down #####################
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
  
  //Gear change sucessfull #####################
  if (isChangingGear && digitalRead(WentInGear) == HIGH) {
    shift_complete();
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
  isChangingGear = false;
  //Endursetja
  digitalWrite(GUOut,LOW);
  digitalWrite(GDOut,LOW);
  //Prenta
  Serial.println("### ERROR: Gear failed to shift! ###");
  return;
};

//Skipting tókst
void shift_complete()
{ 
  isChangingGear = false;  
  //Hækka um gýr númer
  if (GDOut == HIGH) { whatGear--; };
  if (GUOut == HIGH) { whatGear++; };
  //Endursetja
  digitalWrite(GDOut, LOW);
  digitalWrite(GUOut, LOW);
  //Prenta
  Serial.print("Current gear: ");
  Serial.print(whatGear);

  return;
};
//Skipta upp
void shift_up()
{
  digitalWrite(GUOut, HIGH);
  isChangingGear = true;
  //Prenta
  Serial.print("Skipti upp");
  
  //$$$$$$$$$$$$$$Vantar timer fall hér!$$$$$$$$$$$$$$$$$$  
  
};
//Skipta niður
void shift_down()
{
  digitalWrite(GDOut, HIGH);
  isChangingGear = true;
  //Prenta
  Serial.print("Skipti nidur");
  
  //$$$$$$$$$$$$$$Vantar timer fall hér!$$$$$$$$$$$$$$$$$$  
  
};


