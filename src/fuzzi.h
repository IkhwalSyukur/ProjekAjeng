#pragma once
#include <fuzzy.h>
#include <Arduino.h>

Fuzzy *fuzzy = new Fuzzy();

typedef struct
{
  void begin();
  bool setinput(int index, float input);
  bool fuzify();
  int output();
} FuzzyHandler;

void FuzzyHandler::begin()
{
  FuzzyInput *Sensor1 = new FuzzyInput(1);
  FuzzyOutput *pintu = new FuzzyOutput(1);

  FuzzySet *kurang = new FuzzySet(0, 0, 9, 13);
  Sensor1->addFuzzySet(kurang);
  FuzzySet *sedang = new FuzzySet(13, 14, 15, 16);
  Sensor1->addFuzzySet(sedang);
  FuzzySet *normal = new FuzzySet(16, 17, 18, 19);
  Sensor1->addFuzzySet(normal);

  FuzzySet *buka = new FuzzySet(50, 75, 75, 100);
  pintu->addFuzzySet(buka);
  FuzzySet *bukasedang = new FuzzySet(0, 50, 50, 100);
  pintu->addFuzzySet(bukasedang);
  FuzzySet *tutup = new FuzzySet(0, 0, 25, 50);
  pintu->addFuzzySet(tutup);

  fuzzy->addFuzzyInput(Sensor1);
  fuzzy->addFuzzyOutput(pintu);

  // Rules
  // Rules 1
  FuzzyRuleAntecedent *ifSensorKurang = new FuzzyRuleAntecedent();
  ifSensorKurang->joinSingle(kurang);
  FuzzyRuleConsequent *thenPintuBuka1 = new FuzzyRuleConsequent();
  thenPintuBuka1->addOutput(buka);
  FuzzyRule *FuzzyRule1 = new FuzzyRule(1, ifSensorKurang, thenPintuBuka1);
  fuzzy->addFuzzyRule(FuzzyRule1);

  //Rules 2
  FuzzyRuleAntecedent *ifSensorSedang = new FuzzyRuleAntecedent();
  ifSensorSedang->joinSingle(sedang);
  FuzzyRuleConsequent *thenPintuSedang1 = new FuzzyRuleConsequent();
  thenPintuSedang1->addOutput(bukasedang);
  FuzzyRule *FuzzyRule2 = new FuzzyRule(2, ifSensorSedang, thenPintuSedang1);
  fuzzy->addFuzzyRule(FuzzyRule2);

  //Rules 3
  FuzzyRuleAntecedent *ifSensorNormal = new FuzzyRuleAntecedent();
  ifSensorNormal->joinSingle(normal);
  FuzzyRuleConsequent *thenPintuTutup1 = new FuzzyRuleConsequent();
  thenPintuTutup1->addOutput(tutup);
  FuzzyRule *FuzzyRule3 = new FuzzyRule(3, ifSensorNormal, thenPintuTutup1);
  fuzzy->addFuzzyRule(FuzzyRule3);
}

bool FuzzyHandler::setinput(int index, float input)
{
  return fuzzy->setInput(index, input);
}

bool FuzzyHandler::fuzify()
{
  return fuzzy->fuzzify();
}

int FuzzyHandler::output()
{
  return fuzzy->defuzzify(1);
}