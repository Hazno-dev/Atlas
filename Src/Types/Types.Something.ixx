// Hazno - 2026

export module Types:Something;

export struct SomethingStruct
{
    virtual ~SomethingStruct() = delete;
    int   Value;

    SomethingStruct() : Value(0) {}

    explicit SomethingStruct(const int value) : Value(value) {}

    virtual void DoSomething() = 0;
};

