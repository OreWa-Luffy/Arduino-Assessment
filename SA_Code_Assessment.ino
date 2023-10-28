
// Setting up the arrays needed for the SA code.


char * Sa[47] {
  "+",    // A
  "@@+",  // B
  "@+>",  // C
  "+@",   // D
  "@",    // E
  "@+@",  // F
  "@++", // G
  "++", // H
  "@@", // I
  "+@@", // J
  "+>",   // K
  "@@>", // L
  "@+", // M
  ">+", // N
  "@>", // O
  ">@", // P
  "+@>",  // Q
  "@>+",  // R
  "@>@",  // S
  ">",    // T
  ">>",   // U
  "+++",  // V
  "++@",  // W
  "+>@",  // X
  "@>>",  // Y
  "++>",  // Z
  ">@@+", // 1
  ">@@>", // 2
  ">@+@", // 3
  ">@++", // 4
  ">@+>", // 5
  ">@>@", // 6
  ">@>+", // 7
  ">@>>", // 8
  ">+@@", // 9
  ">@@@", // 0
  ">@@",  // .
  ">@+",  // ,
  ">+@",  // '
  ">++",  // ?
  ">+>",  //!
  ">>@",  // +
  ">>+",  // -
  ">>>",  // *
  ">@>",  // /
  ">+++>" // =
  "++++++++" // error
};

char ascii[47] {
  'A',
  'B',
  'C',
  'D',
  'E',
  'F',
  'G',
  'H',
  'I',
  'J',
  'K',
  'L',
  'M',
  'N',
  'O',
  'P',
  'Q',
  'R',
  'S',
  'T',
  'U',
  'V',
  'W',
  'X',
  'Y',
  'Z',
  '1',
  '2',
  '3',
  '4',
  '5',
  '6',
  '7',
  '8',
  '9',
  '0',
  '.',
  ',',
  39, // this is due to not being able to do ' ' ' in C. 
  '?',
  '!',
  '+',
  '-',
  '*',
  '/',
  '=',
  '#'
};





//converting an individual character to SA, this will be used when converting an entire String

char * char2Sa(char c) {
  c = toupper(c);
  for (int i = 0; i < 46; i++) {
    if (c == ascii[i]) {
      return Sa[i];
    }
  }
}




//Converting the ascii array to morse using an inputted value assigned to S
String ascii2Sa(String s) {
  String Sa = "";
  for (int i = 0; i < s.length(); i++) {
    Sa += char2Sa(s[i]);
    if (i == s.length() - 1 || s[i + 1] == ' ' || s[i] == ' ') {
      Sa += ' ';
    }

    else {
      Sa += '/';
    }
  }
  return Sa;
}



//converting a indvidual SA char to the array char.

char Sa2char(String m) {

  for (int i = 0; i < 46; i++) {
    if (m.equals(Sa[i])) {
      return ascii[i];

    }
  }
  return ascii[46];
}

//converting a inputted SA Code to ASCII using the users inputted

String Sa2ascii(String m) {
  char c;
  String fullString;
  String tempString;
  for (int i = 0; i < m.length(); i++) {
    c = m[i];
    if (c == '+' || c == '@' || c == '>') {
      tempString += c;
    }
    else if (c == '/') {
      fullString += Sa2char(tempString);
      tempString = "";
    }
    else if (c == ' ') {
      fullString += Sa2char(tempString);
      fullString += ' ';
      tempString = "";
    }
  }
  fullString += Sa2char(tempString);
  return fullString;
}



String promptReadln() {     // takes in users inputted variables and asks for it. Repeats forever as it is called in the loop void.
  Serial.println("SA CODE INPUT");
  while (!Serial.available()) {};
  return Serial.readString();

}




#define MORSELED 10
#define MORSELED 11
#define potPin A0 //patinetiometer pin


void SaOutputLED(String message, int p) {
  int  atInterval = analogRead(potPin);
  int  greaterInterval = atInterval * 2; 
  int plusInterval = atInterval * 4;
  int wordInterval = atInterval * 6;

  if (atInterval <= 500) {
    atInterval = 500;
    greaterInterval = 1000;
    plusInterval = 2000;
    wordInterval = 3000;
  }
  int len = message.length();
  for (int i = 0; i < len; i++) {
    if ('>' == message[i]) {
      delay(greaterInterval);
      digitalWrite(p, HIGH);
      delay (greaterInterval);
      digitalWrite(p, LOW);
    }
     else if ('+' == message[i]) {
      delay(plusInterval);
      digitalWrite(p, HIGH);
      delay (plusInterval);
      digitalWrite(p, LOW);
    }
     else if ('@' == message[i]) {
      delay(atInterval);
      digitalWrite(p, HIGH);
      delay (atInterval);
      digitalWrite(p, LOW);
    }
    else if(' ' == message[i]){
      delay(wordInterval);
      digitalWrite(p, HIGH);
      delay(wordInterval);
      digitalWrite(p, LOW);
    }
  }
}










void setup() {
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  int p = 0;
//  String SaMessage = "e t morse code";
//  Serial.println(SaMessage);
//  String Sa = ascii2Sa(SaMessage);
//  Serial.println(Sa);
//  SaOutputLED(Sa, p);


  
}





void loop() { // Here is where all the values are inputted, the reason its in the void loop is to allow as many different inputs as possible to test the code.
  pinMode(10, OUTPUT);
  int p = 0;
  String s;
  String a;
  String m;
  s = promptReadln();
  a = s;
  a.trim();
  if (a[0] == '>' || a[0] == '@') {
    Serial.println("The SA code translates too: ");
    Serial.println(Sa2ascii(s));


   p = 10;
   String LED = Sa2ascii(s);
   SaOutputLED(LED, p);

  }
  else {
    Serial.println("The String translates too: ");
    Serial.println(ascii2Sa(s));
    p = 11;
    String LED = ascii2Sa(s);
    SaOutputLED(LED, p);
  }


}
