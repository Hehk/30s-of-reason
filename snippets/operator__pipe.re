/* @title (|>) Pipe Operator */
/* @section Operator */
/* @description Reverse-application operator. let (|>): ('a, 'a => 'b) => 'b */
/* @content */
let add = (a, b) => a + b;

let add5 = add(5);

let a = 10 |> add5; /* 15 */
/* @example */
