#ifndef _SNFOLLOWERS_H_
#define _SNFOLLOWERS_H_

#include <iostream>
#include "Util.h"
#include <vector>

struct BinSNFollowers{
  char name[KMAXNAME];
  int numFollowers;
  double money;
};


class SNFollowers{
  private:
    std::string name;
    int numFollowers;
    double money;
  public:
    SNFollowers(std::string name, int initialFollowers);
    SNFollowers(const BinSNFollowers &bSNF);
    void addFollowers(int nf);
    void addEvent(double rating);
    double collectCommission(double commission);
    std::string getName() const;
    int getNumFollowers() const;
    double getMoney() const;
    BinSNFollowers toBinSNFollowers() const;

    friend std::ostream& operator<<(std::ostream &os, const SNFollowers &snf);
};

#endif
