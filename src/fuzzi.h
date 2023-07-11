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

  FuzzySet *buka = new FuzzySet(1, 1, 1, 1);
  pintu->addFuzzySet(buka);
  FuzzySet *tutup = new FuzzySet(0, 0, 0, 0);
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

  FuzzyRuleAntecedent *ifSensorSedang = new FuzzyRuleAntecedent();
  ifSensorSedang->joinSingle(sedang);
  FuzzyRuleConsequent *thenPintuTutup1 = new FuzzyRuleConsequent();
  thenPintuTutup1->addOutput(tutup);
  FuzzyRule *FuzzyRule2 = new FuzzyRule(2, ifSensorSedang, thenPintuTutup1);
  fuzzy->addFuzzyRule(FuzzyRule2);

  FuzzyRuleAntecedent *ifSensorNormal = new FuzzyRuleAntecedent();
  ifSensorNormal->joinSingle(normal);
  FuzzyRuleConsequent *thenPintuTutup2 = new FuzzyRuleConsequent();
  thenPintuTutup2->addOutput(tutup);
  FuzzyRule *FuzzyRule3 = new FuzzyRule(3, ifSensorNormal, thenPintuTutup2);
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