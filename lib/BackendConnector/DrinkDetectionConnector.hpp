class DrinkDetectionConnector {
public:
    virtual ~DrinkDetectionConnector() = default;

    virtual void sendWeight(const long& weight) = 0;
};
