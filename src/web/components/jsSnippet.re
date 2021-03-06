open Utils;

module JsSnippetQuery = [%graphql
  {|
query getJsSnippet($id: ID!) {
  snippet(id: $id) {
    jsOutput
  }
}
|}
];

let component = ReasonReact.statelessComponent("JsSnippet");

let title = "JavaScript Output";

let renderLoading = () =>
  <LoadingAnimation>
    <Code title text="Loading the impure world" language="js" />
  </LoadingAnimation>;

let renderFailed = () => ele_of_str("failed");

let renderLoaded = text => <Code title text language="js" />;

let make = (~id, _children) => {
  ...component,
  render: _self => {
    let query = JsSnippetQuery.make(~id, ());
    <Query
      query
      render=(
        (response, parse) =>
          switch response {
          | Loading => renderLoading()
          | Failed(_error) => renderFailed()
          | Loaded(result) => renderLoaded(parse(result)##snippet##jsOutput)
          }
      )
    />;
  }
};
