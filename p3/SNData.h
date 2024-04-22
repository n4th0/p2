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
    std::vector<SocialNetworkData> sns;
  public:
    void newSocialNetwork(std::string name, double avgR, double avgM);
    bool checkSN(std::string name);
    double getAvgRating(std::string name);
    double getAvgMonetizing(std::string name);

};
#endif
