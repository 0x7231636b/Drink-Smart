#include <HTTPClient.h>
#include "DrinkDetectionConnector.hpp"

class RestDrinkDetectionConnector : public DrinkDetectionConnector {
public:
    RestDrinkDetectionConnector();

    void sendWeight(const long& weight);

private:
    HTTPClient client;
};
