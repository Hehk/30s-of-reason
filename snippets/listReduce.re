/* @title Reduce */
/* @section List */
/* @description hope this works */
/* @type let reduce: (('a, 'b) => 'a, 'a, list('b)) => 'b; */
/* @content */
let reduce = List.fold_left;

/* @example */
reduce((a, b) => a + b, 0, [1, 2, 3]); /* 6 */
