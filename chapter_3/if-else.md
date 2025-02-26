/***
* - The if-else statement is used to express decisions. Formally the syntax is
    ```
    {
      if (expression)
        statement~1
      else
        statement~2
    }
    ```
*   where the else part is optional.
* - The expression is evaluated; if it is true (that is, if expression has a
*   non-zero value), statement_1 is executed. If it is false (expression is
                                                              *   zero) and if
*   there is an else part, statement_2 is executed instead.
* - Since an if tests the numeric value of an expression, certain coding
*   shortcuts are possible. The most obvious is writing
*
*   if (expression) instead of if (expression != 0). Sometime this is natural
*   and clear; at other times it can be cryptic.
