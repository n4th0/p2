#ifndef _INFLUENCER_H_
#define _INFLUENCER_H_

#include <iostream>
#include <vector>
#include "SNFollowers.h"

class Influencer{
  private:
    std::string name;
    double commission;
    std::vector<SNFollowers> followers;
  public:
    Influencer(std::string name);
    void setCommission(double commission);
    void addFollowers(std::string snName, int nfollowers);
    void addEvent(int nsns, std::string sn[], double rat[]);
    double collectCommission();
    std::string getName() const;
    std::vector<SNFollowers> getFollowers() const;
    double getCommission() const;
    friend std::ostream & operator<<(std::ostream &os, const Influencer &inf);

};

#endif
