let str_to_ele = ReasonReact.stringToElement;

let ele_of_str = ReasonReact.stringToElement;

let ele_of_arr = ReasonReact.arrayToElement;

type debounceOptions = {
  .
  "leading": bool,
  "maxWait": int,
  "trailing": bool
};

[@bs.module]
external _debounce : ('fArgs => 'fOutput, int, debounceOptions) => [@bs] ('fArgs => 'fOutput) = "lodash.debounce";

let debounce = (~wait=0, ~options=Js.Obj.empty(), f) => _debounce(f, wait, options);

module Debounce = {
  [@bs.module]
  external _make : ('fArgs => 'fOutput, int, debounceOptions) => [@bs] ('fArgs => 'fOutput) = "lodash.debounce";
  let make = (~wait=0, ~options=Js.Obj.empty(), f) => _make(f, wait, options);
  let call = (input, f) => [@bs] f(input);
};
