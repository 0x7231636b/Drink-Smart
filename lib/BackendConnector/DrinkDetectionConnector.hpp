#include "RestClient.h"

class DrinkDetectionConnector {
public:
    DrinkDetectionConnector();

    void sendWeight(const long& weight);

private:
    RestClient client;
};
