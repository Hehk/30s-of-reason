/* @title (@@) Application Operator */
/* @section Operator */
/* @description Takes a function and applies the next parameter to it. */
/* @type let (@@): ('a => 'b, 'a) => 'b; */
/* @content */
let add = (a, b) => a + b;

let add5 = add @@ 5; /* (5, b) => 5 + b */

let a = add5 @@ 10; /* 15 */
/* @example */
