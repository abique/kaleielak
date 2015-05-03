#ifndef VALUE_HH
# define VALUE_HH

# include <algorithm>

# include <mimosa/non-copyable.hh>

class AbstractValue : public mimosa::NonCopyable
{
public:
  inline virtual ~AbstractValue() {}
  inline virtual double get() const = 0;
  inline virtual AbstractValue *clone() const = 0;
};

template <typename T>
class DirectValue : public AbstractValue
{
public:
  DirectValue(T v) : value_(v) {}

  inline virtual double get() const override { return value_; }
  inline AbstractValue *clone() const override { return new DirectValue(value_); }

  inline void set(T v) { value_ = v; }

private:
  T value_;
};

template <typename T>
class IndirectValue : public AbstractValue
{
public:
  IndirectValue(T *v) : value_(v) {}

  inline virtual double get() const override { return *value_; }
  inline AbstractValue *clone() const override { return new IndirectValue(value_); }

private:
  T *value_;
};

class Value
{
public:
  inline Value(const Value & v) : value_(v.value_ ? v.value_->clone() : nullptr) {}
  inline Value(double val = 0) : value_(new DirectValue<double>(val)) {}
  inline Value(double *val) : value_(new IndirectValue<double>(val)) {}
  inline Value(uint32_t *val) : value_(new IndirectValue<uint32_t>(val)) {}
  inline Value(AbstractValue *val) : value_(val) {}
  inline Value(Value && val) : value_(val.value_) { val.value_ = nullptr; }
  inline ~Value() { delete value_; }

  inline operator double() const { return value_->get(); }

  inline Value& operator=(Value && val) {
    delete value_;
    value_ = val.value_;
    val.value_ = nullptr;
    return *this;
  }

  inline Value& operator=(const Value & val) {
    delete value_;
    value_ = val.value_ ? val.value_->clone() : nullptr;
    return *this;
  }

private:
  AbstractValue *value_;
};

class AddValue : public AbstractValue
{
public:
  AddValue(Value v1, Value v2) : v1_(v1), v2_(v2) {}

  inline virtual double get() const override { return v1_ + v2_; }
  inline AbstractValue *clone() const override { return new AddValue(v1_, v2_); }

private:
  Value v1_;
  Value v2_;
};

class SubValue : public AbstractValue
{
public:
  SubValue(Value v1, Value v2) : v1_(v1), v2_(v2) {}

  inline virtual double get() const override { return v1_ - v2_; }
  inline AbstractValue *clone() const override { return new SubValue(v1_, v2_); }

private:
  Value v1_;
  Value v2_;
};

class MulValue : public AbstractValue
{
public:
  MulValue(Value v1, Value v2) : v1_(v1), v2_(v2) {}

  inline virtual double get() const override { return v1_ * v2_; }
  inline AbstractValue *clone() const override { return new MulValue(v1_, v2_); }

private:
  Value v1_;
  Value v2_;
};

class DivValue : public AbstractValue
{
public:
  DivValue(Value v1, Value v2) : v1_(v1), v2_(v2) {}

  inline virtual double get() const override { return v1_ / v2_; }
  inline AbstractValue *clone() const override { return new DivValue(v1_, v2_); }

private:
  Value v1_;
  Value v2_;
};

#endif /* !VALUE_HH */
