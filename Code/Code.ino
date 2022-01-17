int Cardnbr;
int nbrAgent = -1;
int authentication = 1;
char Agent = 0;
String inString = "";
int securityLevel[] = {1,1,2,2,3,3,4,5,0};
int publicKey[] = {601,619,631,641,647,653,661,673,691,701,733,739,751,797,809,811};
int privateKey[] ={1273,103,883,653,467,641,1321,589,1039,953,745,919,1159,713,233,1063};
int CardID[] ={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
int crypted;
int i = 0;

int Level (int authentication, int securityLevel) {
  if (securityLevel == 1) {
    authentication = MA1(authentication);
    authentication = MA3(authentication);
    return(authentication);
  }
  else if (securityLevel == 2){
    authentication = MA1(authentication);
    authentication = MA4(authentication);
    return(authentication);
  }
  else if (securityLevel == 3) {
    authentication = MA2(authentication);
    authentication = MA5(authentication, Agent);
    return(authentication);
  }
  else if (securityLevel == 4) {
    authentication = MA2(authentication);
    authentication = MA3(authentication);
    authentication = MA4(authentication);
    return(authentication);
    }
  else if (securityLevel == 5) {
    authentication = MA1(authentication);
    authentication = MA2(authentication);
    authentication = MA3(authentication);
    authentication = MA5(authentication, Agent);
    return(authentication);
  }
  else if (securityLevel == 0) {
    Serial.println("Erreur dans la lecture de la carte. Veuillez reessayer.");
    return -1;
  }
}

int Cardread (int i) {
  switch (i) {
  case 1:
    Cardnbr = 10;
    break;
  case 2:
    Cardnbr = 1;
    break;
  case 3:
    Cardnbr = 2;  
    break;
  case 4:
    Cardnbr = 3;  
    break;
  case 5:
    Cardnbr = 4;  
    break;
  case 6:
    Cardnbr = 5;  
    break;
  case 7:
    Cardnbr = 6;  
    break;
  case 8:
    Cardnbr = 7;  
    break;
  default:
    Cardnbr = 8;
    break;
  return Cardnbr;
}
}

String answer () {
  while (Serial.available() == 0)
  delay(50);
  if (Serial.available() >= 1)
  {
    return read_input();
  }
  else
  {
    Serial.println("Format de reponse invalide");
    error();
  }
}
void error () {
  while(1) {
  }
}
String read_input() {
  char charInput;
  String stringInput = "";
  while (Serial.available() == 0)
  {}
  delay(50);
  while (Serial.available() > 0)
  {
    charInput = Serial.read();
    stringInput = stringInput + charInput;
  }
  return (stringInput);
}
int MA1 (int authentication) {
  if (authentication == 0) {
    return authentication;
  }
  Serial.println("Veuillez repondre aux questions. Les reponses possibles sont : A ; B ; C ou D. Une seule reponse est possible à chaque fois.");
  Serial.println("En quelle annee a ete fonde CESI ?");
  Serial.println("A 1956; B 1957; C 1958; D 1959");
  inString = answer();
  if (inString == ("A") || inString == ("a")) {
    Serial.println("Quel Agent est responsable des innovations technologiques ?");
    Serial.println("A l'agent O; B l'agent P; C l'agent Q; D l'agent R");
    inString = answer();
    if (inString == ("D") || inString == ("d")) {
      Serial.println("Reponses corrects");
      return authentication;
    }
  }
  else {
    Serial.println("Reponse incorrect.");
    authentication = 0;
    return authentication;
  }
}

int MA2(int authentication) {
  if (authentication == 0) {
    return authentication;
  }
  Serial.println("Identifiez vous avec votre lettre d'agent.");
  int randKey = 12;
  delay(50);
  while (1) {
  while (Serial.available() > 0 && nbrAgent == -1) {
    Agent = Serial.read();
    Agent = Agent - 65;
    delay(150);
    if(Agent > 16 || Agent < 0 || Agent == 6) {
      Serial.println("Lettre d'agent incorrecte.");
      authentication = 0;
      return authentication;
    }
    else if(Agent >= 0 && Agent <= 16) {
    nbrAgent = Agent;
    if (nbrAgent > 6)
      nbrAgent--;
    crypted = encrypt(randKey, publicKey[nbrAgent]);
    Serial.print("Veuillez Decrypter ce message : ");
    delay(50);
    Serial.println(crypted); 
    }
  }
  if (nbrAgent >= 0) {
    while(Serial.available() > 0) {
      inString = Serial.readString();
    if(inString.toInt() == randKey) {
      Serial.println("Bienvenue Agent.");
      delay(200);
      return authentication;
    }
    else {
      Serial.println("Code incorrect. Erreur");
      authentication = 0;
      return authentication;
    }
    }
  }
}
}
int MA3 (int authentication) {
  if (authentication == 0) {
    return authentication;
  }
  Serial.println("Veuillez proceder au scanner retinien. ");
  Serial.println("Scanner valide");
  return authentication;
  }

int MA4 (int authentication) {
  if (authentication == 0) {
    return authentication;
  }
  Serial.println("Veuillez proceder au scanner digital. ");
  Serial.println("Scanner valide");
    return authentication;
  }

int MA5(int authentication, char Agent) {
  if (authentication == 0) {
    return authentication;
  }
  Agent = Agent + 65;
  Serial.println("Recuperation des donnees du MA2 ...");
  Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  Serial.println("Veuillez renseigner votre numero de carte.");
  inString = answer();
  Cardnbr = inString.toInt();
  if(Agent >= 72 && Agent <= 81) {
    if (Agent == (Cardnbr + 65) && (Agent) == (CardID[Cardnbr - 1] + 65 )) {
      return authentication;
  }
  }
  else if (Agent >= 65 && Agent < 72) {
    if (Agent == (Cardnbr + 64) && (Agent) == (CardID[Cardnbr -1] + 64 )) {
      return authentication;
  }
  }
  else {
    authentication = 0;
    return authentication;
  }
}

int encrypt(int randKey, int publicKey) {
  int c = 0;
  int randMAX = 2881;
  return (c = modexp(randKey, publicKey, randMAX));
}

long modexp(int randKey, int publicKey, int randMAX) { 
  long r;
  if (publicKey < 0) {
    Serial.println("Cas non traite");
    return(-1);
  }
  if (randKey == 0 || randMAX == 1) {
    r = 0;
  }
  else {
    r = 1;
    while (publicKey > 0) {
      r  = (r*(randKey%randMAX))%randMAX ; //traduction de l'algorythme du prosit
      publicKey = publicKey - 1;
    }
  }
  return (r); //return la valeur cryptee
}

void setup() {
  Serial.begin(9600);
  Serial.println("Veuillez renseigner votre modele de carte.");
  inString = answer();
  i = inString.toInt();
  Cardnbr = Cardread(i);
  Cardnbr = Cardnbr % 10;
  authentication = Level(authentication, securityLevel[Cardnbr]);
  if (authentication == 1) {
    Serial.println("Ouverture du coffre.");
    digitalWrite(13, HIGH);
  }
  else {
    Serial.println("Erreur d'authentification. Veuillez vous identifier de nouveau.");
  }
}

void loop() {
}
