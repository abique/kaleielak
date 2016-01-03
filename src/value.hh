#ifndef VALUE_HH
# define VALUE_HH

# include <algorithm>

# include <mimosa/non-copyable.hh>

class AbstractValue : public mimosa::NonCopyable
{
public:
  inline virtual ~AbstractValue() {}
  virtual double get() const = 0;
  virtual AbstractValue *clone() const = 0;
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
  inline Value(int val) : value_(new DirectValue<int>(val)) {}
  inline Value(uint32_t val) : value_(new DirectValue<uint32_t>(val)) {}
  inline Value(double val = 0) : value_(new DirectValue<double>(val)) {}
  inline Value(const double *val) : value_(new IndirectValue<const double>(val)) {}
  inline Value(const uint32_t *val) : value_(new IndirectValue<const uint32_t>(val)) {}
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

  inline virtual double get() const override { return (double)v1_ + (double)v2_; }
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

  inline virtual double get() const override { return (double)v1_ * (double)v2_; }
  inline AbstractValue *clone() const override { return new MulValue(v1_, v2_); }

private:
  Value v1_;
  Value v2_;
};

class DivValue : public AbstractValue
{
public:
  DivValue(Value v1, Value v2) : v1_(v1), v2_(v2) {}

  inline virtual double get() const override { return (double)v1_ / (double)v2_; }
  inline AbstractValue *clone() const override { return new DivValue(v1_, v2_); }

private:
  Value v1_;
  Value v2_;
};

class ModValue : public AbstractValue
{
public:
  ModValue(Value v1, Value v2) : v1_(v1), v2_(v2) {}

  inline virtual double get() const override { return (int64_t)v1_ % (int64_t)v2_; }
  inline AbstractValue *clone() const override { return new ModValue(v1_, v2_); }

private:
  Value v1_;
  Value v2_;
};

class SinValue : public AbstractValue
{
public:
  SinValue(Value v) : v_(v) {}

  inline virtual double get() const override { return std::sin(v_); }
  inline AbstractValue *clone() const override { return new SinValue(v_); }

private:
  Value v_;
};

class CosValue : public AbstractValue
{
public:
  CosValue(Value v) : v_(v) {}

  inline virtual double get() const override { return std::cos(v_); }
  inline AbstractValue *clone() const override { return new CosValue(v_); }

private:
  Value v_;
};

class PowValue : public AbstractValue
{
public:
  PowValue(Value x, Value y) : x_(x), y_(y) {}

  inline virtual double get() const override { return std::pow(x_, y_); }
  inline AbstractValue *clone() const override { return new PowValue(x_, y_); }

private:
  Value x_;
  Value y_;
};

class ValueBuilder
{
public:
  inline ValueBuilder() : val_(0) {}
  inline ValueBuilder(const Value & val) : val_(val) {}

  inline ValueBuilder operator- () const {
    return ValueBuilder(new SubValue(0, val_));
  }

  inline ValueBuilder operator+ (const Value & val) const {
    return ValueBuilder(new AddValue(val_, val));
  }

  inline ValueBuilder operator- (const Value & val) const {
    return ValueBuilder(new SubValue(val_, val));
  }

  inline ValueBuilder operator* (const Value & val) const {
    return ValueBuilder(new MulValue(val_, val));
  }

  inline ValueBuilder operator/ (const Value & val) const {
    return ValueBuilder(new DivValue(val_, val));
  }

  inline const Value & get() const { return val_; }

private:
  Value val_;
};

typedef ValueBuilder V;

#endif /* !VALUE_HH */
