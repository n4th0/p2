#ifndef _AGENCY_H_
#define _AGENCY_H_

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "Influencer.h"
#include "Util.h"

struct BinAgency{
  char name[KMAXNAME];
  double money;
  int numInfluencers;
};


class Agency{
  private:
    std::string name;
    double money;
    std::vector<Influencer> influencers;
  public:
    Agency(std::string name, double initialMoney);
    Agency(std::string filename);
    Influencer * searchInfluencer(std::string infName);
    unsigned int getNumberInfluencers()const;
    BinAgency toBinAgency()const;
    void saveData(std::string filename);
    void addInfluencer(std::string infName, double commission);
    void addFollowers(std::string infName, std::string snName, int nfollowers);
    void newEvent(std::vector<std::string> infNames, int nsns, std::string snNames[], double evtRatings[]);
    void deleteInfluencer(std::string infName);
    double collectCommissions();
    std::string getName() const;
    double getMoney() const;
    friend std::ostream& operator<<(std::ostream &os, const Agency &ag);
};

#endif
