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
    // TODO implement the operator

};

