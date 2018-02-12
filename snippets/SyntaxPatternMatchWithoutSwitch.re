/* @title Pattern match without switch */
/* @section Syntax */
/* @description Cannot believe i forgot this purty */
/* @content */
let patternMatch =
  fun
  | 0 => "zero"
  | 1 => "one"
  | _ => "way too big";

/* @example */
patternMatch(0);    /* zero */
patternMatch(1);    /* one */
patternMatch(1337); /* way too big */
