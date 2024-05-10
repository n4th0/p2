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
   // SNData tests
   try {
      SNData::newSocialNetwork("JungleBook",0.1,0.1);
   
    } catch (const exception& e) {
       if (strcmp(e.what(), "JungleBook")==0) {
          cout << "test 1 OK"<<endl;
       }
    }
   try {

      SNData::newSocialNetwork("Prueba",-1,0.1);
   } catch (const exception& e) {
      if (strcmp(e.what(),to_string((double)-1).c_str())==0) {
         cout << "test 2 OK"<<endl;
      }
   }

   if (!SNData::checkSN("prueba")) {
      cout << "test 3 OK"<< endl;
   }

   if (SNData::checkSN("TokTik")) {
      cout << "test 4 OK"<< endl;
   }

   if (0.0==SNData::getAvgMonetizing("prueba")) {
      cout << "test 5 OK"<< endl;
   }

   if (0.0==SNData::getAvgRating("prueba")) {
      cout << "test 7 OK"<< endl;
   }

   if (0.8==SNData::getAvgRating("prueba")) {
      cout << "test 8 OK"<< endl;
   }

   // SNFollowers tests
   try {
      SNFollowers test1("no existe", -5);
   } catch (Exception e) {
      if (e == EXCEPTION_UNKNOWN_SN){
         cout << "test 9 OK"<<endl;
      }
   }

   try {

      SNFollowers test1("TokTik", -5);
   } catch (const exception& e) {
      if (strcmp(e.what(),to_string((int)-5).c_str())==0) {
         cout << "test 10 OK"<<endl;
      }
   }

   SNFollowers test2("TokTik", 50);
   test2.addFollowers(50);
   if (100==test2.getNumFollowers()) {
      cout << "test 11 OK "<< endl;
   }
   test2.addFollowers(-150);
   if (0==test2.getNumFollowers()) {
      cout << "test 12 OK "<< endl;
   }

   SNData::newSocialNetwork("pruebaAddEvent", 0.8, 0.5);
   SNFollowers test3("pruebaAddEvent", 1000);
   test3.addEvent(0.65);
   if (test3.getNumFollowers()==1812) {
      cout << "test 13 OK "<< endl;
   }
   if (test3.getMoney()==406) {
      cout << "test 14 OK "<< endl;
   }

   SNData::newSocialNetwork("pruebaAddEvent2", 0.8, 0.5);
   SNFollowers test4("pruebaAddEvent2", 1000);
   test3.addEvent(0.56);
   if (test4.getNumFollowers()==800) {
      cout << "test 15 OK "<< endl;
   }
   if (test4.getMoney()==0.0) {
      cout << "test 16 OK "<< endl;
   }
   try {
      test3.collectCommission(12);
    } catch (const exception& e) {
       if (strcmp(e.what(), "12.000000")==0) {
          cout << "test 17 OK"<<endl;
       }
    }

   if(203==test3.collectCommission(0.5)){
      cout << "test 18 OK "<< endl;
   }

   // influencers tests
   Influencer testInf1("test1");
   try {
      testInf1.setCommission(-1);
   } catch (Exception e) {
      if (e == EXCEPTION_WRONG_COMMISSION) {
         cout << "test 19 OK "<< endl;
      }
   }
   testInf1.setCommission(0.5);
   cout << "debe salir ERR_UNKNOWN_SN: "<<endl;
   testInf1.addFollowers("no existe", 10);

   try {
      testInf1.addFollowers("TokTik", -10);
   } catch (const exception& e) {
      if (strcmp(e.what(),to_string((int)-10).c_str())==0) {
         cout << "test 20 OK"<<endl;
      }
   }

   // TODO test addEvent



   








   
   /*
   Agency pufosAmos("Los pufos amos",1000.0);
   
   pufosAmos.addInfluencer("Pijus Magnificus",0.25);
   pufosAmos.addInfluencer("Brian",0.15);

   pufosAmos.addInfluencer("Brian",0.55);   // ERR_DUPLICATED
   pufosAmos.addInfluencer("Loretta",1.05); // ERR_WRONG_COMMISSION 

   pufosAmos.addInfluencer("Loretta",.75);

   cout << pufosAmos ;   

   pufosAmos.addFollowers("Pijus Magnificus", "YZ", 500);
   pufosAmos.addFollowers("Bdian","MSNotExist",400);    // ERR_NOT_FOUND
   pufosAmos.addFollowers("Brian","MSNotExist",400);    // ERR_UNKNOWN_SN
   pufosAmos.addFollowers("Loretta","TokTik",1200);
   pufosAmos.addFollowers("Loretta","Infagram",1300);
   pufosAmos.addFollowers("Loretta","YZ",700);
   pufosAmos.addFollowers("Loretta","TokTik",300);
   pufosAmos.addFollowers("Brian","JungleBook",65);

   cout << pufosAmos ;   
   

   // Event data
   cout << "---------- First event -----------" << endl;
   string snNames[] = { "TokTik", "JungleBook", "Infagram", "MSN", "YZ" };
   double evRat[]   = {  0.95,   0.05, 0.7, 0.003, 0.85 };
   vector<string> inm;
   inm.push_back("Loretta");
   inm.push_back("Pijus Ticus");  // ignore
   inm.push_back("Brian");
   inm.push_back("Pijus Magnificus");

   pufosAmos.newEvent(inm,5,snNames,evRat);
   cout << pufosAmos ;   


   double moneyEvent = pufosAmos.collectCommissions();
   cout << "Money generated by the event: " << moneyEvent << endl
        << pufosAmos ;
   
   */
   return 0;

}
