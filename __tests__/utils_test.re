open Jest;

open Utils;

/* Just simple test incase if I accidentally change these functions */
describe("ele_of_ functions", () => {
  open Expect;
  test("str", () =>
    ele_of_str("test") |> expect |> toEqual(ReasonReact.stringToElement("test"))
  );
  test("arr", () => {
    let arr = [|<div />|];
    ele_of_arr(arr) |> expect |> toEqual(ReasonReact.arrayToElement(arr));
  });
  test("list", () => {
    let l = [<div />, <span />, <header />];
    ele_of_list(l) |> expect |> toEqual(ReasonReact.arrayToElement(Array.of_list(l)));
  });
});

describe("Debounce call", () => {
  open Expect;
  let count = ref(0);
  beforeEachAsync(
    ~timeout=10,
    finish => {
      let f = () => {
        count := count^ + 1;
        finish();
      };
      let dF = Debounce.make(f);
      Debounce.call((), dF);
      Debounce.call((), dF);
      Debounce.call((), dF);
      Debounce.call((), dF);
      Debounce.call((), dF);
      ();
    }
  );
  test("First group of calls", () =>
    count^ |> expect |> toBe(1)
  );
  test("Second group of calls", () =>
    count^ |> expect |> toBe(2)
  );
  test("Third group of calls", () =>
    count^ |> expect |> toBe(3)
  );
});
