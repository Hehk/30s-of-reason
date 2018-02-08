/* @title List :: Reduce */
/* @description hope this works */
/* @content */
let reduce = List.fold_left;

/* @example */
reduce((a,b) => a + b, 0, [1,2,3]); /* 6 */
