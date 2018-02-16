open Jest;

Enzyme.configureEnzyme(Enzyme.react_16_adapter());

/* Todo: I need to figure out a way to mock more behaviour in the system */
describe("JsSnippet", () => {
  open Expect;
  test("renderLoading renders", () =>
    <div> (JsSnippet.renderLoading()) </div> |> Enzyme.shallow |> Enzyme.exists |> expect |> toBe(true)
  );
  test("renderFailed renders", () =>
    <div> (JsSnippet.renderFailed()) </div> |> Enzyme.shallow |> Enzyme.exists |> expect |> toBe(true)
  );
  test("renderLoaded renders", () =>
    JsSnippet.renderLoaded("test") |> Enzyme.shallow |> Enzyme.exists |> expect |> toBe(true)
  );
  test("renders with mock", () =>
    <JsSnippet query=(module ApolloMock.Client.Query) id="0" />
    |> Enzyme.shallow
    |> Enzyme.exists
    |> expect
    |> toBe(true)
  );
});
