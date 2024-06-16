#ifndef _INFLUENCER_H_
#define _INFLUENCER_H_

#include <iostream>
#include <vector>
#include "SNFollowers.h"
#include "Util.h"
struct BinInfluencer{
  char name[KMAXNAME];
  double commission;
  int numFollowers;
};

class Influencer{
  private:
    std::string name;
    double commission;
    std::vector<SNFollowers> followers;
  public:
    Influencer(std::string name);
    Influencer(const BinInfluencer &bI);
    void setCommission(double commission);
    void addFollowers(const SNFollowers &follower);
    void addFollowers(std::string snName, int nfollowers);
    void addEvent(int nsns, std::string sn[], double rat[]);
    double collectCommission();
    std::string getName() const;
    std::vector<SNFollowers> getFollowers() const;
    double getCommission() const;
    BinInfluencer toBinInfluencer()const;
    friend std::ostream & operator<<(std::ostream &os, const Influencer &inf);

};

#endif
