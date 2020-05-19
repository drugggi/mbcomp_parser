#ifndef COMPETITOR_H
#define COMPETITOR_H
#include <vector>
#include <string>
#include "route.h"

class Competitor {
    private:
        std::string mName;
        mutable std::vector<Route> routesClimbed;

    public:
        Competitor(std::string name); 
        ~Competitor();
        void displayInfo();
        bool operator ==(const Competitor & obj) const;
        int getAttempts(std::string attempts) const;
        std::string getName() const;
        void addRoute(Route newRoute) const ;
        std::string getResults() const;
        void editGradeOpinions(int stats[][10]) const;
        void editTotalRouteStats(int routeStats[][10]) const;
        void editAttemptStats(int attemptStats[][10]) const;
        std::vector< std::string> getAscentDates();

};

#endif
