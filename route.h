#ifndef ROUTE_H
#define ROUTE_H
#include <string>

class Route {
    private:
        int mRouteNumber;
        int mAttempts;
        std::string mDate;
        std::string mGrade;

    public:
        Route(int routeNumber, int attempts, std::string grade, std::string date);
        ~Route();
        int getRouteNumber() const;
        void printRouteInfo(int nro) const;
        int getAttempts() const;
        std::string addRouteAttempts(int nro) const;
        int getGradeOpinion() const;
        std::string getDate() const;

};

#endif

