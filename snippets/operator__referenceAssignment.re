/* @title (:=) Reference Assignment Operator */
/* @section Operator */
/* @description Changes the value stored in a reference. */
/* @type let (:=): (ref('a), 'a) => unit; */
/* @content */
let a = ref(5);

a := 4;

let b = a^ == 4; /* true */

/* @example */
Js.log(a^);
