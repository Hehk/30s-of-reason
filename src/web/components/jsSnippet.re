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

module Query = Apollo.Client.Query;

let component = ReasonReact.statelessComponent("JsSnippet");

let make = (~id, _children) => {
  ...component,
  render: _self => {
    let query = JsSnippetQuery.make(~id, ());
    <Query query>
      ...(
           (response, parse) =>
             switch response {
             | Loading => str_to_ele("loading")
             | Failed(_error) => str_to_ele("error")
             | Loaded(result) =>
               let snippet = parse(result)##snippet;
               <Code text=snippet##jsOutput language="js" />;
             }
         )
    </Query>;
  }
};
