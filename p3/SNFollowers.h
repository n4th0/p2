#ifndef _SNFOLLOWERS_H_
#define _SNFOLLOWERS_H_

#include <iostream>
#include <vector>

class SNFollowers{
  private:
    std::string name;
    int numFollowers;
    double money;
  public:
    SNFollowers(std::string name, int initialFollowers);
    void addFollowers(int nf);
    void addEvent(double rating);
    double collectCommission(double commission);
    std::string getName() const;
    int getNumFollowers() const;
    double getMoney() const;
    friend std::ostream& operator<<(std::ostream &os, const SNFollowers &snf);
};

#endif
