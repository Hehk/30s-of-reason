open Jest;

Enzyme.configureEnzyme(Enzyme.react_16_adapter());

describe("Header", () => {
  open Expect;
  test("component renders", () => {
    Enzyme.shallow(<Header />) |> Enzyme.exists |> expect |> toBe(true); 
  });
});
