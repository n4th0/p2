#ifndef _SNDATA_H_
#define _SNDATA_H_

#include <iostream>
#include <vector>

struct SocialNetworkData{
  std::string name;
  double averageRating;
  double averageMonetizing;
  
};

class SNData{
  private:
    static std::vector<SocialNetworkData> sns;
  public:
    static void newSocialNetwork(std::string name, double avgR, double avgM);
    static bool checkSN(std::string name);
    static double getAvgRating(std::string name);
    static double getAvgMonetizing(std::string name);

};
#endif
