// Copyright 2023 <Carmine Cartman, Vojan Najov>

#ifndef INCLUDE_S21_UTILS_H_
#define INCLUDE_S21_UTILS_H_

namespace s21 {

// Auxiliary structs

template <typename Arg, typename Result>
struct UnaryFunction {
  using argument_type = Arg;
  using result_type = Result;
};

template <typename T>
struct Identity : public UnaryFunction<T, T> {
  T& operator()(T& x) const { return x; }
  const T& operator()(const T& x) const { return x; }
};

template <typename Pair>
struct Select1st : public UnaryFunction<Pair, typename Pair::first_type> {
  typename Pair::first_type& operator()(Pair& x) const { return x.first; }

  const typename Pair::first_type& operator()(const Pair& x) const {
    return x.first;
  }
};

template <typename Pair>
struct Select2nd : public UnaryFunction<Pair, typename Pair::second_type> {
  typename Pair::second_type& operator()(Pair& x) const { return x.second; }

  const typename Pair::second_type& operator()(const Pair& x) const {
    return x.second;
  }
};

template <typename Arg1, typename Arg2, typename Result>
struct BinaryFunction {
  using first_argument_type = Arg1;
  using second_argument_type = Arg2;
  using result_type = Result;
};

template <typename T>
struct Less : public BinaryFunction<T, T, bool> {
  bool operator()(const T& lhs, const T& rhs) const { return lhs < rhs; }
};

}  // namespace s21

#endif  // INCLUDE_S21_UTILS_H_
