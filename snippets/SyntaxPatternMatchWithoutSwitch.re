/* @title Pattern match without switch */
/* @section Syntax */
/* @description Cannot believe i forgot this purty */
/* @type none */
/* @content */
let patternMatch =
  fun
  | 0 => "zero"
  | 1 => "one"
  | _ => "way too big";

let funnyAdd = x =>
  fun
  | 0 => 0
  | 1 => 1
  | n => x + n;

/* @example */
patternMatch(0); /* zero */

patternMatch(1); /* one */

patternMatch(1337); /* way too big */
