#include <iostream>
#include <stdexcept>
#include <string.h>
#include "Influencer.h"
#include "SNData.h"
#include "Agency.h"
#include "Util.h"
using namespace std;

int main()
{
   // correct social networks
   SNData::newSocialNetwork("TokTik",0.8,0.1);
   SNData::newSocialNetwork("Infagram",0.6,0.05);
   SNData::newSocialNetwork("YZ",0.5,0.2);
   SNData::newSocialNetwork("JungleBook",0.1,0.1);




   cout << "\n============================" << endl;
   cout << "ejemplo enunciado incrementa" << endl;
   cout << "============================" << endl;

   SNData::newSocialNetwork("enunciado sn", .8, .2);

   SNFollowers enunciado("enunciado sn", 1000);
   enunciado.addEvent(.65);

   if(enunciado.getNumFollowers()!=1812) 
      cout << "mal1";

   if(enunciado.getMoney()!=(812 * .2)) 
      cout << "mal2";

   // falta ejemplo enunciado decrementa!!


    try{    
       SNFollowers("pinpun", 100);

    }catch(const Exception &e){
      if(e==EXCEPTION_UNKNOWN_SN)
         cout << "bien1";
    }

    try{    
       SNFollowers("TokTik", -100);
    }catch(const invalid_argument &e){
      if(strcmp(e.what(), "-100")==0)
         cout << "bien2";
    }

   SNFollowers sinf("YZ", 100);

   if (sinf.getNumFollowers()!=100) {
      cout << "algo malo";
   
   }
   sinf.addFollowers(200);
   if (sinf.getNumFollowers()!=300) {
      cout << "mal4";
   }

   sinf.addFollowers(-500);
   if (sinf.getNumFollowers()!=0) {
      cout << "mal4";
   }

   sinf.addFollowers(1000);
   int old_followers = sinf.getNumFollowers();
   double old_money = sinf.getMoney();

   cout << "\n==========" << endl;
   cout << "addEvent(.5)" << endl;
   cout << "============" << endl;
   sinf.addEvent(.5);

   if (sinf.getNumFollowers()!=(int) ((0.5/0.5) * old_followers) + old_followers) {
      cout << "mal5";
   
   }

   cout << "\nnuevos: " << sinf.getNumFollowers() << endl;

   if (sinf.getMoney()!=(int) ((0.5 / 0.5) * old_followers) * 0.2 + old_money) {
      cout << "mal6";
   }
   double new_money = sinf.getMoney();
   cout << "dinero nuevo: " << new_money << endl;


   // este da exactamente .8
   int actuales_followers = sinf.getNumFollowers(); // me guardo los followers antes del evento
   int perdidos = (int) ((0.9 - 0.4/0.5) * actuales_followers); // los que pierdo

   cout << "\n==========" << endl;
   cout << "addEvent(.4)" << endl;
   cout << "============" << endl;
   sinf.addEvent(.4);
   cout << "los que tiene: " << actuales_followers << endl;
   cout << "los que perdera: " << perdidos << endl;
   cout << "nuevos (ha perdido): " << sinf.getNumFollowers() << endl;
   cout << "dinero no cambia: " << sinf.getMoney() << endl;
   if (sinf.getNumFollowers()!=(actuales_followers-perdidos)) {
      cout << "mal7";
   }
   if (sinf.getMoney() != new_money) {
      cout << "mal8";
   }



   // 1801, 200
    try{
         sinf.addEvent(-.1);
    }catch(const invalid_argument &i){
       if (strcmp(i.what(), "-0.100000")==0) {
          cout<< "bien3";
       }

    }

   // Ahora pierde mas 
   // ==================================
   actuales_followers = sinf.getNumFollowers();
   perdidos = (int) ((0.9 - 0.01/0.5) * actuales_followers); // los que pierdo

   cout << "\n==========" << endl;
   cout << "addEvent(.01)" << endl;
   cout << "============" << endl;
   sinf.addEvent(.01);
   cout << "los que tiene: " << actuales_followers << endl;
   cout << "los que perdera: " << perdidos << endl;
   cout << "nuevos (ha perdido): " << sinf.getNumFollowers() << endl;
   cout << "dinero no cambia: " << sinf.getMoney() << endl;
   if (sinf.getNumFollowers()!=(actuales_followers-perdidos)) {
      cout << "mal10";
   }
   if (sinf.getMoney() != new_money) {
      cout << "mal11";
   }



   // Ahora pierde mas aun
   // ==================================
   actuales_followers = sinf.getNumFollowers();
   perdidos = (int) ((0.9 - 0.1/0.5) * actuales_followers); // los que pierdo

   cout << "\n==========" << endl;
   cout << "addEvent(.1)" << endl;
   cout << "============" << endl;
   sinf.addEvent(.1);
   cout << "los que tiene: " << actuales_followers << endl;
   cout << "los que perdera: " << perdidos << endl;
   cout << "nuevos (ha perdido): " << sinf.getNumFollowers() << endl;
   cout << "dinero no cambia: " << sinf.getMoney() << endl;
   if (sinf.getNumFollowers()!=(actuales_followers-perdidos)) {
      cout << "mal12";
   }
   if (sinf.getMoney() != new_money) {
      cout << "mal13";
   }



   // constructor
   SNFollowers snf("TokTik", 900);

   // getters

   if (snf.getName()!="TokTik") {
      cout << "mal14";
   }

   if (snf.getNumFollowers()!=900) {
      cout << "mal15";
   }
   if (snf.getMoney()!=0.0) {
      cout << "mal16";
   }


   snf.addFollowers(100);
   if (snf.getNumFollowers()!=1000) {
      cout << "mal17";
   }


   snf.addEvent(0.65);
   if (snf.getNumFollowers()!=1812) {
      cout << "mal18";
   }

   cout << snf.getMoney()<< "tiene que ser: 81.2"<< endl;

   // operator<<
   cout << snf<<endl;  
   cout << "tiene que ser:[TokTik|1812|81.2]"<<endl;

   cout << "Collect commission => commission cero: " << endl;
   try{
      snf.collectCommission(0);
   }
   catch(invalid_argument &e){
      cout << "error en comision cero: " << e.what() << endl;
   }

   try{
      snf.collectCommission(1);
   }
   catch(invalid_argument &e){
      cout << "error en comision uno: " << e.what() << endl;
   }

   try{
         snf.collectCommission(0);
   }catch(const invalid_argument &i){
      if (strcmp(i.what(), "0.000000")==0) {
         cout <<"bien4";
      
      }
      cout <<"bien4" <<i.what()<<endl;

   }

   cout << "Collect commission => commission uno: " << endl;
   try{
         snf.collectCommission(1);
   }catch(const invalid_argument &i){
      if (strcmp(i.what(), "1.000000")==0) {
         cout << "bien5";
      }
      cout <<"bien5" <<i.what()<<endl;

   }



   cout <<snf.collectCommission(0.2) << "Tiene que ser: 16.24"<<endl;
   cout <<snf.getMoney()<< "tiene que ser 0.0"<<endl;

   cout <<endl<< snf<<endl;
    cout <<"[TokTik|1812|0]"<<endl;;


   
   // Agency pufosAmos("Los pufos amos",1000.0);
   // 
   // pufosAmos.addInfluencer("Pijus Magnificus",0.25);
   // pufosAmos.addInfluencer("Brian",0.15);

   // pufosAmos.addInfluencer("Brian",0.55);   // ERR_DUPLICATED
   // pufosAmos.addInfluencer("Loretta",1.05); // ERR_WRONG_COMMISSION 

   // pufosAmos.addInfluencer("Loretta",.75);

   // cout << pufosAmos ;   

   // pufosAmos.addFollowers("Pijus Magnificus", "YZ", 500);
   // pufosAmos.addFollowers("Bdian","MSNotExist",400);    // ERR_NOT_FOUND
   // pufosAmos.addFollowers("Brian","MSNotExist",400);    // ERR_UNKNOWN_SN
   // pufosAmos.addFollowers("Loretta","TokTik",1200);
   // pufosAmos.addFollowers("Loretta","Infagram",1300);
   // pufosAmos.addFollowers("Loretta","YZ",700);
   // pufosAmos.addFollowers("Loretta","TokTik",300);
   // pufosAmos.addFollowers("Brian","JungleBook",65);

   // cout << pufosAmos ;   
   // 

   // // Event data
   // cout << "---------- First event -----------" << endl;
   // string snNames[] = { "TokTik", "JungleBook", "Infagram", "MSN", "YZ" };
   // double evRat[]   = {  0.95,   0.05, 0.7, 0.003, 0.85 };
   // vector<string> inm;
   // inm.push_back("Loretta");
   // inm.push_back("Pijus Ticus");  // ignore
   // inm.push_back("Brian");
   // inm.push_back("Pijus Magnificus");

   // pufosAmos.newEvent(inm,5,snNames,evRat);
   // cout << pufosAmos ;   


   // double moneyEvent = pufosAmos.collectCommissions();
   // cout << "Money generated by the event: " << moneyEvent << endl
   //      << pufosAmos ;
   
   return 0;
}
