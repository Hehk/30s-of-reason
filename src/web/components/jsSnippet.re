open Utils;

module JsSnippetQuery = [%graphql {|
query getJsSnippet($id: ID!) {
  snippet(id: $id) {
    jsOutput
  }
}
|}];

let component = ReasonReact.statelessComponent("JsSnippet");

let renderLoading = () => ele_of_str("loading");

let renderFailed = () => ele_of_str("failed");

let renderLoaded = text => <Code text language="js" />;

let make = (~query as q, ~id, _children) => {
  ...component,
  render: _self => {
    let query = JsSnippetQuery.make(~id, ());
    module Query = (val (q: (module Apollo.Query)));
    <Query query>
      ...(
           (response, parse) =>
             switch response {
             | Loading => renderLoading()
             | Failed(_error) => renderFailed()
             | Loaded(result) => renderLoaded(parse(result)##snippet##jsOutput)
             }
         )
    </Query>;
  }
};
