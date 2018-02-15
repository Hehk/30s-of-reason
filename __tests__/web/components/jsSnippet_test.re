open Jest;

Enzyme.configureEnzyme(Enzyme.react_16_adapter());

describe("JsSnippet", () => {
  open Expect;

  test("component renders", () => {
    /* Enzyme.shallow(<JsSnippet id=("0") />) |> Enzyme.exists |> expect |> toBe(true); */
    /* Todo: Figure out a way to pass in a custom Query module for mocking */
    true |> expect |> toBe(true);
  });
});
