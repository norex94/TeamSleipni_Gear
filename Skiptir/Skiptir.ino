
//  Ingangar#####################
const int GUPin = 2;
const int GDPin = 3;
const int NULLPin = 4;
const int WentInGear = 5;
const int WentBack = 6;
//  �tgangar#####################
const int GUOut = 7;
const int GDOut = 8;

// Breytur#####################

int whatGear = 0;
bool isChangingGear;

//Föll#####################
void shift_fail();


//#################  SETUP  #####################
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

//#####################THE LOOP#####################
void loop() {



  //Change Gear upp #####################
  if (digitalRead(GUPin) == HIGH && !isChangingGear) {

    digitalWrite(GUOut, HIGH);
    isChangingGear = true;
    Serial.print("Skipti upp");

  }
  //Change gear down #####################
  if (digitalRead(GUPin) == HIGH && !isChangingGear) {

    digitalWrite(GDOut, HIGH);
    isChangingGear = true;
    Serial.print("Skipti ni�ur");

  }
  //Gear change sucessfull #####################
  if (isChangingGear && digitalRead(WentInGear) == HIGH) {

    if (GDOut == HIGH) { whatGear--; };
    if (GUOut == HIGH) { whatGear++; };

    digitalWrite(GDOut, LOW);
    digitalWrite(GUOut, LOW);
    isChangingGear = false;

  }


  Serial.print("Current gear: ");
  Serial.print(whatGear);
  Serial.println();
  Serial.print("GearUp: ");
  Serial.print(GUPin);
  Serial.println();



}
//######################################## FÖLL #################################################
//Skipting mistókst
void shift_fail()
{
  isChangingGear = false;
  digitalWrite(GUOut,LOW);
  digitalWrite(GDOut,LOW);
  Serial.println("### Gear failed to shift! ###");
  return;
};
