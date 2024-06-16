#ifndef _SNDATA_H_
#define _SNDATA_H_

#include <iostream>
#include <string>
#include <vector>

#define SEPARATOR ':'

struct SocialNetworkData{
  std::string name;
  double averageRating;
  double averageMonetizing;
};

class SNData{
  private:
    static std::vector<struct SocialNetworkData> sns;
  public:
    static void readFromCSV(std::string filename);
    static void writeToCSV(std::string filename);
    static unsigned int getSocialNetworkNumber();
    static void newSocialNetwork(std::string name, double avgR, double avgM);
    static bool checkSN(std::string name); 
    static double getAvgRating(std::string name);
    static double getAvgMonetizing(std::string name);

};


#endif
