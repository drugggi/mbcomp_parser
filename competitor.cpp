#include <iostream>
#include "competitor.h"
#include "route.h"
#include <string>
#include <vector>

Competitor::Competitor(std::string name) :
    mName(name)
{
}

Competitor::~Competitor() {

}


void Competitor::addRoute(Route newRoute) const {

    if (newRoute.getAttempts() == 0) {
        std::cout << std::to_string(newRoute.getRouteNumber() ) << " is " << mName << "'s project\n";
        return;
    }
    bool found = false;
    for (Route r: routesClimbed) {
        if ( newRoute.getRouteNumber() == r.getRouteNumber() ) {
            found = true;
            std::cout << mName << " has already Climbed route"  
                << std::to_string(newRoute.getRouteNumber() ) << "\n";
            break;
        }
    }
    if (found == false) {
       routesClimbed.push_back(newRoute);
    }

}
void Competitor::displayInfo() {
    // std::cout << mName << " Attempts: " <<  getAttempts() << " "  << mGrade << " " << mDate << '\n';
     std::cout <<  mName;
     for (int i = mName.length() ; i < 41 ; i++) {
         std::cout << " ";
     }
     std::cout << "\t";
     int attempts = 0;
     std::string routeInfo = "";
     for (int i = 1 ; i < 11 ; i++) {
         routeInfo = "\t";
         for (Route r: routesClimbed) {
             routeInfo += r.addRouteAttempts(i);
            // r.printRouteInfo(i);
             //attempts += r.getAttempts();
         }
         std::cout << routeInfo;
     }
     for (Route r: routesClimbed) {
         attempts += r.getAttempts();
     }
     std::cout << "\t\t" << std::to_string(routesClimbed.size() ) << "\t" << std::to_string(attempts) << "\n";
}
std::string Competitor::getResults() const {
    std::string resultLine = mName;
    for (int i = mName.length() ; i < 41 ; i++) {
        resultLine += " ";
    }
    
    for (int i = 1 ; i < 11 ; i++) {
        resultLine += "\t";
        for (Route r: routesClimbed) {
            resultLine += r.addRouteAttempts(i);
        }
    }
    int attempts = 0;
    for (Route r: routesClimbed) {
        attempts += r.getAttempts();
    }

    resultLine += "\t\t" + std::to_string(routesClimbed.size() ); 
    resultLine += "\t" + std::to_string(attempts);

    return resultLine;
}

int Competitor::getAttempts(std::string attempts) const {
    if (attempts == "Flashed" ) { return 1; }
    else if (attempts == "2nd try"){return 2; }
    else if (attempts == "3rd try") {return 3; }
    else if (attempts == "Project") {return 0; }
    else if (attempts == "more than 3 tries") {return 4; }
    else { return 10; }

    return 666;
}

std::string Competitor::getName() const {
    return mName;
}

void Competitor::editGradeOpinions(int stats[][10]) const {
    int gradeOpinion = 0;
    int routeNumber = 0;
    for (Route r: routesClimbed) {
        gradeOpinion = r.getGradeOpinion();
        routeNumber = r.getRouteNumber()-1;
        stats[gradeOpinion][routeNumber]++;
    }

}
void Competitor::editTotalRouteStats(int routeStats[][10]) const {

    int routeNumber = 0;
    int attempts = 0;
    for (Route r: routesClimbed) {
        routeNumber = r.getRouteNumber()-1;
        attempts = r.getAttempts();
        routeStats[0][routeNumber]++;
        routeStats[1][routeNumber]+= attempts;
    }
}
void Competitor::editAttemptStats(int attemptStats[][10]) const {

    int routeNumber = 0;
    int attempts = 0;
    for (Route r: routesClimbed) {
        routeNumber = r.getRouteNumber()-1;
        attempts = r.getAttempts()-1;
        attemptStats[attempts][routeNumber] += 1;

        // std::cout << "attempts: " << attempts << " rnro: " << routeNumber << " ";

    }
}
std::vector<std::string> Competitor::getAscentDates() {
    std::vector<std::string> ascentDates;
    for (Route r: routesClimbed) {
        ascentDates.push_back(r.getDate() );
    }

    return ascentDates;
}

bool Competitor::operator ==(const Competitor & obj) const {
    if (mName == obj.mName) {
        return true;
    }
    else {
        return false;
    }
}
