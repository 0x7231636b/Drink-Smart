#include <HTTPClient.h>

class DrinkDetectionConnector {
public:
    DrinkDetectionConnector();

    void sendWeight(const long& weight);

private:
    HTTPClient client;
};
