/* @title (^) Reference Content Operator */
/* @section Operator */
/* @description returns the content of a reference. */
/* @type let (^): ref('a) => 'a; */
/* @content */
let a = ref(5);

let b = a^;

/* @example */
Js.log(a^);
