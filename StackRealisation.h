#include "StackImplementation.h"
#include "Vector.h"
#include "FWList.h"

class VectorStack : public IStackImplementation
{
    private:
        Vector _data;
    public:
        VectorStack() = default;
        VectorStack(const ValueType* rawArray, const size_t size);
        VectorStack(const VectorStack& other);
        VectorStack& operator=(const VectorStack& other);
        void push(const ValueType& value) override;
        void pop() override;
        const ValueType& top() const override;
        bool isEmpty() const override;
        size_t size() const override;
};

class FWListStack : public IStackImplementation
{
    private:
        ForwardList _data;
    public:
        FWListStack() = default;
        FWListStack(const ValueType* rawArray, const size_t size);
        FWListStack(const FWListStack& other);
        FWListStack& operator=(const FWListStack& other);
        void push(const ValueType& value) override;
        void pop() override;
        const ValueType& top() const override;
        bool isEmpty() const override;
        size_t size() const override;
};
