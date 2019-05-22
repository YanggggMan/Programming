effective modern c++

template deduction

1. T&  value  : deduction will  ignore   passed value's  reference
2. T&& value  
3. T  value   : always pass by value
4. T&  value  and   array、function pointer which will decay

auto deduction:will be differ  when passed  a  {var1} (with  braces)